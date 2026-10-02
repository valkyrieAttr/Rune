#include <string_view>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>

#include <FileHandler.hpp>


namespace
    [[
        __gnu__::__visibility__("internal") ,
    ]] FileHandler
{

    FileWriter::FileWriter
        ( const char* FilePath )
        noexcept ( true )
    {

        this->FileDesc = ::open
            (
                FilePath,
                O_WRONLY | O_CREAT | O_TRUNC,
                0644
            )
        ;

    }

    FileWriter::~FileWriter
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    {

        if
            (
                this->FileDesc != -1
            )
        {

            ::close ( this->FileDesc );

        }

    }

    bool FileWriter::IsOpen
        ( void [[ /* v_ */ ]] )
        const noexcept ( true )
    {

        return this->FileDesc != -1;

    }

    bool FileWriter::Write
        ( std::string_view data )
        noexcept ( true )
    {

        if
            (
                !IsOpen()
            )
        {

            return false;

        }

        const ssize_t BytesWritten
            {
                ::write
                (
                    this->FileDesc,
                    data.data(),
                    data.size()
                )
            }
        ;

        return
            (
                BytesWritten == static_cast<ssize_t>( data.size() )
            )
        ;

    }

    constexpr auto FileOpener::load
        ( const char* FilePath_ )
        noexcept ( true )
    -> bool
    {

        this->release();


        auto const FileDesc = ::open
            (
                FilePath_,
                O_RDONLY
            )
        ;

        if
            (
                FileDesc == -1
            )
        {

            return false;

        }


        struct stat St {};

        if
            (
                ::fstat(FileDesc, &St) == -1 ||
                St.st_size == 0
            )
        {

            ::close(FileDesc);
            return (false);

        }

        auto const FileSize = static_cast<std::size_t>
            (
                St.st_size
            )
        ;

        this->sourceView =
            {
                reinterpret_cast<char const*>
                (
                    ::mmap
                    (
                        nullptr,
                        FileSize,
                        PROT_READ,
                        MAP_PRIVATE,
                        FileDesc,
                        0ZU
                    )
                ) , FileSize
            }
        ;

        ::close ( FileDesc );

        if
            (
                this->sourceView.data() == MAP_FAILED
            )
        {

            this->sourceView = {};
            return false;

        }

        ::madvise
            (
                const_cast<void* const>
                (
                    static_cast<void const* const>
                    (
                        this->sourceView.data()
                    )
                ), FileSize , MADV_SEQUENTIAL
            )
        ;

        return true;

    }

    constexpr auto FileOpener::release
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    -> void
    {

        if
            (
                !this->empty() &&
                this->data() != MAP_FAILED
            )
        {

            ::munmap
                (
                    const_cast<void*>
                    (
                        static_cast<void const* const>
                        (
                            this->data()
                        )
                    ),
                    this->size()
                )
            ;

            this->sourceView = {};

        }

    }


    auto FileOpener::operator =
        ( FileOpener&& other )
        noexcept ( true )
    -> FileOpener&
    {

        if
            (
                this != &other
            )
        {

            this->release();
            sourceView = std::move(other.sourceView);
            other.sourceView = {};

        }

        return *this;

    }

    FileOpener::FileOpener
        ( const char* FilePath_ )
        noexcept ( true )
    {

        if
            (
                this->load(FilePath_)
            )
        {

            return;

        }

        else
            [[ /* nullAttr*/  ]]
        {

            this->release();

        }

    }

    FileOpener::~FileOpener
        ( void [[ /* v_ */ ]] )
        noexcept( true )
    {

        this->release();

    }

}
