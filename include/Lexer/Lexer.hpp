#ifndef LEXER_HPP
    #define LEXER_HPP

    #include <vector>

    #include "SourceManager.hpp"
    #include "Token.hpp"

    namespace
        [[
            /* namespaceSignature */
        ]] Vll
    {

        class
            [[
                /* classSignature */
            ]] Lexer
        {

            private:
                [[maybe_unused]] std::byte _pad[4]{};
                std::uint32_t FileCursor_{0};
                std::string_view Sv_SourceView_;
                std::string_view Sv_FileName_;

                const SourceDepths::SourceManager& SrcManager_;

                constexpr auto IsAtEnd
                    ( std::uint32_t Pos = 0 )
                    noexcept ( true )
                -> bool;

                constexpr auto Advance
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> void;

                constexpr auto Peek
                    ( std::uint32_t Pos = 0, char Ch = '\0' )
                    noexcept ( true )
                -> bool;

                constexpr auto PeekChar
                    ( std::uint32_t Pos )
                    noexcept ( true )
                -> char;

                constexpr auto ScanLineComment
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> void;

                constexpr auto ScanBlockComment
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> void;

                constexpr auto KeyWordOrIdentifier
                    ( const std::string_view Toks_ )
                    noexcept ( true )
                -> Token::TokenType;


            public:
                explicit Lexer
                    (
                        std::string_view sourceView,
                        std::string_view FileName,
                        SourceDepths::SourceManager& SourceM
                    )
                    noexcept ( true )
                ;

                auto Lex
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::vector<TokenData>;

        };


    }

#endif
