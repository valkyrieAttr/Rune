#ifndef TOKEN_HPP
    #define TOKEN_HPP

    #include <cstdint>
    #include <string_view>

    namespace
        [[
        /* classSignature */
        ]] Vll
    {

        namespace
            [[
                /* classSignature */
            ]] Token
        {

            enum class
                [[
                    /* enumSignature */
                ]] TokenType: std::uint8_t
            {

                /*
                    Keywords
                */

                From,                      // FromKeyword
                Export,                    // ExportKeyword
                Type,                      // TypeKeyword
                Func,                      // FuncKeyword
                If,                        // IfKeyword
                Else,                      // ElseKeyword
                For,                       // ForKeyword
                While,                     // WhileKeyword
                Let,                       // LetKeyword
                Var,                       // VarKeyword
                Return,                    // ReturnKeyword
                Break,                     // BreakKeyword
                Continue,                  // ContinueKeyword
                True,                      // TrueKeyword
                False,                     // FalseKeyword
                In,                        // InKeyword
                Main,                      // MainKeyword
                Match,                     // MatchKeyword
                Module,                    // ModuleKeyword
                Class,                     // ClassKeyword
                This,                      // ThisKeyword
                Interface,                 // InterfaceKeyword
                Extend,                    // ImplKeyword
                Enum,                      // EnumKeyword
                Pub,                       // PublicKeyword
                Defer,                     // DeferKeyword
                Async,                     // AsyncKeyword
                Await,                     // AwaitKeyword
                Try,                       // TryKeyword
                Catch,                     // CatchKeyword


                /*
                    Assignment Operators
                */

                Assign,                    // Assign
                PlusEqual,                 // PlusEqual
                MinusEqual,                // MinusEqual
                MulEqual,                  // MulEqual
                DivEqual,                  // DivEqual
                ModEqual,                  // ModEqual
                CaretEqual,                // CaretEqual

                /*
                    Operators
                */

                Arrow,                     // ArrowPointer
                MapArrow,                  // MapArrowPointer
                Range,                     // RangeOperand
                PlusPlus,                  // PlusPlusOperator
                MinusMinus,                // MinusMinusOperator


                /*
                    BitWise Operators
                */

                Ampersand,                 // AmpersandOperator
                Pipe,                      // PipeOperator

                /*
                    Comparison Operators
                */

                LessOrEqual,               // c-LessOrEqual-Operator
                GreaterOrEqual,            // c-GreaterOrEqual-Operator
                Equal,                     // c-Equal-Operator
                NotEqual,                  // c-NotEqual-Operator
                GreaterThan,               // c-GreaterThan-Operator
                LessThan,                  // c-LessThan-Operator
                And,                       // c-And-Operator
                Or,                        // c-Or-Operator
                Bang,                      // c-Bang-Operator

                /*
                    Mathmatical Operators
                */

                Plus,                      // PlusOperator
                Minus,                     // MinusOperator
                Mul,                       // MulOperator
                Div,                       // DivOperator
                Mod,                       // ModOperator
                Caret,                     // CaretOperator

                /*
                    Neutral Operators
                */

                Question,                  // n-Question-Operator
                Colon,                     // n-Colon-Operator
                Tilde,                     // n-Tilde-Operator
                Annotation,                // n-Annotation-Operator

                /*
                    Separator/Terminator
                */

                Comma,                     // Comma-Separator
                DoubleColon,               // DoubleColon-Separator
                Dot,                       // Dot-Separator
                SemiColon,                 // SemiColon-Terminator

                /*
                    Brackets
                */

                LeftParen,                 // LeftParen
                RightParen,                // RightParen

                LeftBrace,                 // LeftBrace
                RightBrace,                // RightBrace

                LeftBracket,               // LeftBracket
                RightBracket,              // RightBracket

                /*
                    Literals
                */

                FloatLiterals,             // FloatLiterals
                IntLiterals,               // IntLiterals
                StringLiterals,            // StringLiterals
                RawStringLiterals,         // RawStringLiterals

                /*
                    Primitive Default Types
                */

                Const,                      // ConstType
                Mut,                        // MutType

                /*
                    Default
                */

                Identifier,                 // IdentifierMarker
                Unknown,                    // UnknownMarker
                EndOfFile                   // EndOfFileMarker

            };

            struct
                [[
                    /* structSignature */
                ]] KeywordEntry
            {

                std::string_view Sv_Word_;
                std::byte _pad[7]{};
                TokenType Type;

            };

            static_assert
                (
                    sizeof(KeywordEntry) == 24,
                    "KeywordEntry must be 24 bytes for optimal cache packing"
                )
            ;

            struct
                [[
                    /* structSignature */
                ]] OperatorEntry
            {

                std::string_view Operator_;
                std::byte _pad[7]{};
                TokenType Type;

            };

            static_assert
                (
                    sizeof(OperatorEntry) == 24,
                    "OperatorEntry must be 24 bytes"
                )
            ;

            struct
                [[
                    /* structSignature */
                ]] LookUpOperatorEntry
            {

                Token::TokenType Type
                    {
                        Token::TokenType::Unknown
                    }
                ;

                std::uint8_t AdvanceCount {0};

            };

            static_assert
                (
                    sizeof(LookUpOperatorEntry) == 2
                )
            ;


            struct
                [[
                    /* structSignature */
                ]] HashEntry
            {

                std::string_view Sv_Word_;
                TokenType Type;
                std::byte _pad[6]{};
                bool BoolOccupied {false};

            };

            static_assert
                (
                    sizeof(HashEntry) == 24,
                    "HashEntry must be exactly 24 bytes."
                )
            ;

        }

        class
            [[
                /* classSignature */
            ]] TokenData
        {

            public:
                std::string_view Sv_Val_;
                std::uint32_t Lexer_Size_t_Offset;
                std::byte _pad[3]{};
                Token::TokenType Type;

        };

    }

#endif
