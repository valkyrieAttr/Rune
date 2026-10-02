#ifndef HIERARCHY_HPP
    #define HIERARCHY_HPP

    #include <utility>
    #include <expected>

    #include "Ast.hpp"
    #include "Lexer/Token.hpp"
    #include "Fields.hpp"

    namespace
        Vll::Parser
    {

        class SyntaxAnalysis;

        class
            [[
                /* classSignature */
            ]] HierarchyRules
        {

            private:

                class
                    [[
                        /* classSignature */
                    ]] ParseRule
                {

                    private:
                        using NudFunc = std::expected<
                            AbstractGrammar::AbstractNodes,
                            Fields::ParseError
                        > ( HierarchyRules::* )
                            (
                                void [[ /* v_ */ ]]
                            )
                        ;

                        using LedFunc = std::expected<
                            AbstractGrammar::AbstractNodes,
                            Fields::ParseError
                        > ( HierarchyRules::* )
                            (
                                AbstractGrammar::AbstractNodes Left
                            )
                        ;

                    public:
                        long : ( 8 * 4 );

                        Fields::Precedence Precedence;
                        NudFunc Nud;
                        LedFunc Led;

                };

            private:
                SyntaxAnalysis& EngineCtx_;

                constexpr auto ParseNumeric
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseString
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseIdentifier
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseParenthesis
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                // constexpr auto ParseClassField
                //     ( void [[ /* v_ */]] )
                //     noexcept ( true )
                // -> std::expected<
                //         AbstractGrammar::AbstractNodes,
                //         Fields::ParseError
                //     >
                // ;

                constexpr auto ParseStatementField
                    ( void [[ /* v_*/ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseBrace
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseArray
                    ( void [[ /* v_ */ ]] )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParsePostFix
                    ( AbstractGrammar::AbstractNodes Left )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseBinary
                    ( AbstractGrammar::AbstractNodes Left )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseMemberAccess
                    ( AbstractGrammar::AbstractNodes Left )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseVariableDeclaration
                    ( void [[ /* v_ */ ]] ) 
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseAssignment
                    ( AbstractGrammar::AbstractNodes Left )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseIndex
                    ( AbstractGrammar::AbstractNodes Left )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                constexpr auto ParseRange
                    ( AbstractGrammar::AbstractNodes Left )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

                static const
                    std::array<
                        std::pair<Token::TokenType, HierarchyRules::ParseRule>,
                        std::to_underlying(Token::TokenType::EndOfFile)
                    > Rules
                ;

            public:
                explicit HierarchyRules
                    ( SyntaxAnalysis& Ctx )
                    noexcept ( true )
                ;

                constexpr auto ParseExpression
                    ( const Fields::Precedence MinPrecedence )
                    noexcept ( true )
                -> std::expected<
                        AbstractGrammar::AbstractNodes,
                        Fields::ParseError
                    >
                ;

        };

    }
#endif
