#ifndef PARSER_HPP
    #define PARSER_HPP

    #include <vector>
    #include <expected>

    #include <Lexer/Token.hpp>
    #include <Parser/Fields.hpp>
    #include <Parser/Hierarchy.hpp>
    #include <Diagnostic/Diagnostic.hpp>

    namespace
        Vll::Parser
    {

        class
            [[
                /* nullAttr */
            ]] SyntaxAnalysis
        {

            private:
                DiagnosticEngine& Diag_;
                HierarchyRules Rules_;

            public:
                std::vector<TokenData> Toks_;
                std::uint64_t Cursor_ {0};

                explicit SyntaxAnalysis
                    ( 
                        DiagnosticEngine& Diag, 
                        std::vector<TokenData> Tokens 
                    )
                    noexcept ( true )
                ;

                auto IsAtEnd
                    ( std::uint16_t Indx = 0 )
                    const noexcept ( true )
                -> bool;

                auto Advance
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> TokenData;

                auto Peek
                    ( std::uint16_t Indx = 0 )
                    noexcept ( true )
                -> TokenData;

                auto Previous
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> TokenData;

                auto Consume
                    ( 
                        const Token::TokenType& Toks, 
                        Diagnostic::Severity Level_, 
                        std::string_view Msg 
                    )
                    noexcept ( true )
                -> bool;

                auto ConsumeIdentifier
                    ( 
                        const Token::TokenType& Toks, 
                        Diagnostic::Severity Level_, 
                        std::string_view Msg 
                    )
                    noexcept ( true )
                -> std::expected<TokenData, Fields::ParseError>;

                auto ReportError
                    ( 
                        const TokenData& Tok, 
                        Diagnostic::Severity Level_, 
                        const std::string_view Msg 
                    )
                    const noexcept ( true )
                -> void;

        };

    }

#endif
