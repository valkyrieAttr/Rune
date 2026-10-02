#ifndef FILEHANDLER_HPP
    #define FILEHANDLER_HPP

    #include <string_view>

    namespace
        [[
            /* namespaceSignature */
        ]] FileHandler
    {
        class
            [[
                /* classSignature */
            ]] FileWriter
        {

            private:
                int FileDesc{-1};

            public:
                explicit FileWriter
                    ( const char* FizlePath )
                    noexcept ( true )
                ;

                ~FileWriter
                    ( void [[ /* dtorSignature */ ]] )
                    noexcept ( true )
                ;

                auto IsOpen [[ __nodiscard__ ]]
                    ( void [[ /* v_ */ ]] )
                    const noexcept ( true )
                -> bool;

                auto Write
                    ( std::string_view data )
                    noexcept ( true )
                -> bool;

        };

        class
            [[
                /* classSignature */
            ]] FileOpener
        {

            private:
                std::string_view sourceView {};

                auto constexpr load [[ __nodiscard__ ]]
                    ( const char* FilePath_ )
                    noexcept ( true )
                -> bool;

                auto constexpr release
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> void;

            public:

                auto operator =
                    ( FileOpener const& )
                    noexcept ( true )
                -> FileOpener& = delete;

                auto operator =
                    ( FileOpener&& other )
                    noexcept ( true )
                -> FileOpener&;

                FileOpener
                    ( const char* FilePath_ )
                    noexcept ( true )
                ;

                explicit FileOpener
                    ( FileOpener const& )
                    noexcept ( true )
                = delete;

                FileOpener
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                = default;

                ~FileOpener
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                ;

                explicit FileOpener
                    ( FileOpener&& other )
                    noexcept ( true ): sourceView(std::move(other.sourceView))
                { other.sourceView = {}; }

                auto constexpr data [[ __nodiscard__ ]]
                    ( void [[ /* v_ */ ]] )
                    const noexcept ( true )
                -> char const*
                {

                    return this->sourceView.data();

                }

                auto constexpr size [[ __nodiscard__ ]]
                    ( void [[ /* v_ */ ]] )
                    const noexcept ( true )
                -> std::size_t
                {

                    return this->sourceView.size();

                }

                auto constexpr empty [[ __nodiscard__ ]]
                    ( void [[ /* v_ */ ]] )
                    const noexcept ( true )
                -> bool
                {

                    return this->sourceView.empty();

                }

                auto constexpr view [[ __nodiscard__ ]]
                    ( void [[ /* v_ */ ]] )
                    const noexcept ( true )
                -> std::string_view
                {

                    return this->sourceView;

                }
        };
    }
#endif
