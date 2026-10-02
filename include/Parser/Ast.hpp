#ifndef AST_HPP
    #define AST_HPP

    #include <vector>
    #include <variant>
    #include <string>
    #include <string_view>
    #include <bits/indirect.h>

    #include "Fields.hpp"
    #include "Lexer/Token.hpp"

    namespace
        Vll::AbstractGrammar
    {

        // Forward declaration of AbstractNodes (ASTNode)
        class
            [[
                /* classSignature */
            ]] AbstractNodes
        ;

        class 
            [[
                /* classSignature */
            ]] TypeSpecifier
        {

            public:
                std::vector<std::indirect<AbstractNodes>> TypeArguments; // <int, string>
                Parser::Fields::TypeKind TypeKind { Parser::Fields::TypeKind::None }; // & or * or &mut or *mut

                std::byte _pad[3]{};

                bool IsArray {false};
                std::size_t ArraySize;

        };

        class
            [[
                /* classSignature */
            ]] NumericASTNode
        {

            public:
                Parser::Fields::NumericKind Kind;

                std::size_t IntValue{0};
                double FloatValue{0.0};

        };

        class
            [[
                /* classSignature */
            ]] StringASTNode
        {

            public:
                Parser::Fields::StringKind Kind;

                std::byte _pad[8]{};
                std::string String;

        };

        class
            [[
                /* classSignature */
            ]] IdentifierASTNode
        {

            public:
                std::string_view NameIdentifier;

        };

        class 
            [[
                /* classSignature */
            ]] VariableDeclarationASTNode 
        {

            public:
                std::vector<IdentifierASTNode> identifier;
                TypeSpecifier Type;
                std::vector<std::indirect<AbstractNodes>> Initializers;

        };

        /* 
            Oh, I remembre now!

            let x: i32 = { something here; }
            let x: class Sig = { a: 1, b: 2 }
        
        */
        class
            [[
                /* classSignature */
            ]] DeferredBraceASTNode
        {

            private:
                Parser::Fields::BraceKind Kind;
                std::vector<std::indirect<AbstractNodes>> Elements_;

            public:
                explicit DeferredBraceASTNode
                    (
                        Parser::Fields::BraceKind kind_,
                        std::vector<std::indirect<AbstractNodes>> elem_
                    )
                    noexcept ( true )
                ;

        };

        // operand++ or operand-op or x++
        // '++' here is Op
        // 'x' here is Operand
        class
            [[
                /* classSignature */
            ]] PostfixASTNode
        {

            public:
                std::indirect<AbstractNodes> Operand;
                Token::TokenType Op;
                std::byte _pad[6]{};
                bool IsPostFix {false};

        };

        // x + y
        class
            [[
                /* classSignature */
            ]] BinaryASTNode
        {

            public:
                std::indirect<AbstractNodes> Left;
                std::indirect<AbstractNodes> Right;
                std::byte _pad[3]{};
                Token::TokenType Op;

        };

        class
            [[
                /* classSignature */
            ]] MemberAccessASTNode
        {

            public:
                std::indirect<AbstractNodes> LeftSide;      // The Object or Namespace ::
                TokenData Op;                               // Captures '.' or '::' token
                TokenData Member;                           // The field or method name identifier

        };

        class
            [[
                /* classSignature */
            ]] ArrayASTNode
        {

            private:
                std::vector<std::indirect<AbstractNodes>> Elements;

            public:
                explicit ArrayASTNode
                    ( std::vector<std::indirect<AbstractNodes>> elem_ )
                    noexcept ( true )
                ;

        };

        class
            [[
                /* classSignature */
            ]] AbstractNodes
        {

            private:
                using ASTNode = std::variant<
                    NumericASTNode,
                    StringASTNode,
                    IdentifierASTNode,
                    PostfixASTNode,
                    MemberAccessASTNode,
                    ArrayASTNode,
                    DeferredBraceASTNode,
                    VariableDeclarationASTNode
                >;

            public:
                ASTNode Node_;

                template <typename T>
                constexpr auto&& Get
                    ( this T&& self )
                {

                    return std::forward<T>(self).Node_;

                }

        };

    }

#endif
