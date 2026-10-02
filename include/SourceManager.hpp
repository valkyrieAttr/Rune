#ifndef SOURCEMANAGER_HPP
    #define SOURCEMANAGER_HPP

    #include <vector>
    #include <cstdint>
    #include <string_view>

    namespace
        Vll::SourceDepths
    {

        class
            [[
                /* classSignature */
            ]] SourceLocation
        {

            public:
                std::uint32_t Lexer_Size_t_Line;
                std::uint32_t Lexer_Size_t_Column;

        };

        class
            [[
                /* classSignature */
            ]] SourceManager
        {

            private:
                std::string_view Sv_SourceView_;
                std::vector<std::uint32_t> LineOffset_;

            public:
                explicit SourceManager
                    ( std::string_view SourceView )
                    noexcept ( true )
                ;

                auto ReturnLocation
                    ( const std::uint32_t Offset )
                    const noexcept ( true )
                -> SourceLocation;

                auto LineText
                    ( std::uint32_t LineIdx )
                    const noexcept ( true )
                -> std::string_view;

        };

    }

#endif
