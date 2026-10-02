#ifndef FIELDS_HPP
    #define FIELDS_HPP

    #include <cstdint>

    namespace
        [[
            /* namespaceSignature */
        ]] Vll
    {

        namespace
            Parser::Fields
        {


            enum class
                [[
                    /* enumSignature */
                ]] Precedence: std::uint32_t
            {

                None,
                Assignment,
                LogicalOr,
                LogicalAnd,
                BitWiseOr,
                BitWiseAnd,
                Equality,
                Comparison,
                BitShift,
                Term,
                Factor,
                Postfix,
                CallIndx,
                MemAccess

            };

            enum class
                [[
                    /* enumSignature */
                ]] ParseError
            {

                UnexpectedToken,
                MissingSemiColon,
                MissingOpeningParen,
                MissingOpeningBrace,
                MissingOpeningBracket,
                MissingClosingParen,
                MissingClosingBrace,
                MissingClosingBracket,
                MissingMapArrow,
                MissingColon,
                MissingComma,
                MalformedParameters,
                MalformedRangeLiterals,
                MalformedMemberAccess,
                MalformedLoopCondition,
                MalformedArray,
                ExpectedBraceOrColon,
                InvalidImportPath,
                InvalidExpression,
                InvalidDeclarationTarget,
                InvalidCallTarget,
                InvalidType,
                InvalidLoop,
                InvalidStatement,
                InvalidAssignmentTarget,
                InvalidMemberAccessOperand,
                ExpectedIdentifier,
                UnexpectedEndOfFile,
                InternalError

            };

            enum class
                [[
                    /* enumSignature */
                ]] NumericKind: std::uint64_t
            {

                Integer,
                Float

            };

            enum class
                [[
                    /* enumSignature */
                ]] StringKind: std::uint64_t
            {

                String,
                RawString

            };

            enum class 
                [[
                    /* enumSignature */
                ]] TypeKind: std::uint32_t 
            {

                Reference,
                MutableReference,
                Pointer,
                MutablePointer,
                CompileTimeConst,
                ConstPointer,
                ReferenceConst,
                Deduce,
                None

            };

            enum class
                [[
                    /* enumSignature */
                ]] BraceKind: std::uint64_t
            {

                ClassField,
                StatementField

            };

        }

    }

#endif
