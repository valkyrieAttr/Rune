#include <format>
#include <utility>

#include <Parser/Ast.hpp>
#include <Parser/Fields.hpp>
#include <Parser/Parser.hpp>
#include <Diagnostic/Diagnostic.hpp>

using namespace Vll;
using namespace ::Parser;
using namespace ::AbstractGrammar;

HierarchyRules::HierarchyRules
    ( SyntaxAnalysis& Ctx )
    noexcept ( true ): EngineCtx_(Ctx) {}

constexpr auto HierarchyRules::ParseNumeric
    ( void [[ /* v_ */ ]] )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    TokenData Tok = this->EngineCtx_.Previous();

    switch
        (
            Tok.Type
        )
    {

        case
            (
                Token::TokenType::IntLiterals
            ):
        {

            std::size_t ParsedValue {0};

            std::from_chars
                (
                    Tok.Sv_Val_.data(),
                    std::to_address
                        (
                            Tok.Sv_Val_.end()
                        )
                    ,
                    ParsedValue
                )
            ;

            return
                {
                    AbstractGrammar::AbstractNodes
                    {
                        .Node_ =
                        {
                            AbstractGrammar::NumericASTNode
                            {
                                .Kind = Fields::NumericKind::Integer,
                                .IntValue = ParsedValue
                            }
                        }
                    }
                }
            ;

        }

        case
            (
                Token::TokenType::FloatLiterals
            ):
        {
            double ParsedValue = 0.0;
            std::from_chars
                (
                    Tok.Sv_Val_.data(),
                    std::to_address
                        (
                            Tok.Sv_Val_.end()
                        )
                    ,
                    ParsedValue
                )
            ;

            return
                {
                    AbstractGrammar::AbstractNodes
                    {
                        .Node_ =
                        {
                            AbstractGrammar::NumericASTNode
                            {
                                .Kind = Fields::NumericKind::Float,
                                .FloatValue = ParsedValue
                            }
                        }
                    }
                }
            ;

        }

        default:
        {
            return
                {    std::unexpected
                    (
                        Fields::ParseError::UnexpectedToken
                    )
                }
            ;
        }

    }


}

static constexpr auto DecodeString
    ( std::string_view text )
-> std::string
{

    std::string Out;

    if
        (
            text.length() < 2
        ) [[ unlikely ]]
    {

        return { Out };

    }

    Out.reserve
        (
            text.length()
        )
    ;

    for
        (
            std::size_t i {1}; i < text.size(); i++
        )
    {

        if
            (
                text.at(i) == '\\' &&
                (i + 1) < (text.size() - 1)
            ) [[ likely ]]
        {

            ++i; // Consume the backlash and look at the next character.

            switch
                (
                    text.at(i)
                )
            {

                case
                    (
                        'n'
                    ):
                {

                    Out += '\n';
                    break;

                }

                case
                    (
                        't'
                    ):
                {

                    Out += '\t';
                    break;

                }

                case
                    (
                        'r'
                    ):
                {

                    Out += '\r';
                    break;

                }

                case
                    (
                        '0'
                    ):
                {

                    Out += '\0';
                    break;

                }

                case
                    (
                        '\\'
                    ):
                {

                    Out += '\\';
                    break;

                }

                case
                    (
                        '\''
                    ):
                {

                    Out += '\'';
                    break;

                }

                case
                    (
                        '"'
                    ):
                {

                    Out += '"';
                    break;

                }

                case
                    (
                        '*'
                    ):
                {

                    Out += '*';
                    break;

                }

                default:
                {

                    Out += '\\';
                    Out += text.at(i);
                    break;

                }

            }

        }

        else
            [[
                /* nullAttr */
            ]]
        {

            Out += text.at(i);

        }

    }

    return { Out };

}

constexpr auto HierarchyRules::ParseString
    ( void [[ /* v_*/ ]] )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    const std::string_view RawText = this->EngineCtx_.Previous().Sv_Val_;

    std::string ParsedString;
    bool IsRaw {false};

    if
        (
            RawText.starts_with('\'')
        ) [[ unlikely ]]
    {

        IsRaw = true;

        // It is a raw string. Slice off the surrounding single quotes.
        if
            (
                RawText.size() >= 2
            ) [[ unlikely ]]
        {
            ParsedString =
                std::string
                (
                    RawText.substr
                    (
                        1,
                        RawText.size() - 2
                    )
                )
            ;
        }

    }

    else if
        (
            RawText.starts_with('"')
        ) [[ likely ]]
    {

        IsRaw = false;
        ParsedString =
            DecodeString
            (
                RawText
            )
        ;

    }

    else
        [[
            unlikely
        ]]
    {
        return
            {
                std::unexpected
                (
                    Fields::ParseError::UnexpectedToken
                )
            }
        ;
    }

    return
        AbstractGrammar::AbstractNodes
        {
            .Node_ =
            {
                AbstractGrammar::StringASTNode
                {
                    .Kind = IsRaw ? Fields::StringKind::RawString
                                  : Fields::StringKind::String,
                    .String = std::move(ParsedString)
                }
            }
        }
    ;

}

constexpr auto HierarchyRules::ParseIdentifier
    ( void [[ /* v_ */]] )
    noexcept ( true )
    -> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    return
        {
            AbstractGrammar::AbstractNodes
            {
                .Node_ =
                {
                    AbstractGrammar::IdentifierASTNode
                    {
                        .NameIdentifier = this->EngineCtx_.Previous().Sv_Val_
                    }
                }
            }
        }
    ;

}

constexpr auto HierarchyRules::ParsePostFix
    ( ::AbstractGrammar::AbstractNodes Left )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    return
        {
            AbstractGrammar::AbstractNodes
            {
                .Node_ =
                {
                    AbstractGrammar::PostfixASTNode
                    {
                        .Operand = 
                            std::indirect<AbstractGrammar::AbstractNodes>
                            (
                                std::move(Left)
                            )
                        ,
                        .Op = this->EngineCtx_.Previous().Type,
                        .IsPostFix = true
                    }
                }
            }
        }
    ;

}

constexpr auto HierarchyRules::ParseVariableDeclaration
    ( void [[ /* v_ */ ]] )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    this->EngineCtx_.Advance(); // Consumes 'let' or 'var'

    std::vector<std::indirect<AbstractNodes>> RightInitializers;
    std::vector<IdentifierASTNode> Identifiers;

    if 
        (
            this->EngineCtx_.Peek().Type == Token::TokenType::LeftParen
        ) [[ __unlikely__ ]]
    {

        this->EngineCtx_.Advance();

        while 
            (
                this->EngineCtx_.Peek().Type != Token::TokenType::RightParen &&
                !this->EngineCtx_.IsAtEnd()
            )
        {

            if 
                (
                    this->EngineCtx_.Peek().Type != Token::TokenType::Identifier
                ) [[ __unlikely__ ]]
            {

                this->EngineCtx_
                    .ReportError
                    (
                        this->EngineCtx_.Peek()
                        , Diagnostic::Severity::ERROR
                        , "Expected valid variable name, unable to be parsed by the compiler."
                    )
                ;

                while 
                    (
                        this->EngineCtx_.Peek().Type != Token::TokenType::Comma &&
                        this->EngineCtx_.Peek().Type != Token::TokenType::RightParen &&
                        !this->EngineCtx_.IsAtEnd()
                    )
                {

                    this->EngineCtx_.Advance(); 

                }

            } 

            else 
                [[ __likely__ ]]
            {

                auto IdentResult = this->EngineCtx_ 
                    .ConsumeIdentifier
                    (
                        Token::TokenType::Identifier 
                        , Diagnostic::Severity::ERROR 
                        , "Expected valid identifier, unable to be parsed by the compiler."
                    )
                ;

                if 
                    (
                        !IdentResult
                    )
                {

                    return { std::unexpected(IdentResult.error()) };

                }

                Identifiers.emplace_back
                    (
                        IdentifierASTNode
                        {
                            .NameIdentifier = IdentResult->Sv_Val_
                        }
                    )
                ;

            }

            if 
                (
                    this->EngineCtx_.Peek().Type == Token::TokenType::Comma
                ) [[ __likely__ ]]
            {

                this->EngineCtx_.Advance();

            } 

            else 
                [[ /* nullAttr */ ]]
            {

                break;

            }

        }

    }

    TypeSpecifier Type;


    if 
        (
            this->EngineCtx_.Peek(0).Type == Token::TokenType::Colon &&
            this->EngineCtx_.Peek(1).Type == Token::TokenType::Equal
        ) [[ __unlikely__ ]]
    {

        this->EngineCtx_.Advance();
        this->EngineCtx_.Advance();

        Type = 
        {
            .TypeArguments = {},
            .TypeKind = Parser::Fields::TypeKind::Deduce,
            .IsArray = {},
            .ArraySize = {}
        };

    } 

    else if 
        (
            this->EngineCtx_.Peek(0).Type == Token::TokenType::Colon &&
            this->EngineCtx_.Peek(1).Type != Token::TokenType::Equal
        )
    {

        this->EngineCtx_.Advance();

        while 
            (
                this->EngineCtx_.Peek(0).Type != Token::TokenType::Equal &&
                !this->EngineCtx_.IsAtEnd()
            )
        {

            /* DATA */
            this->EngineCtx_.Advance();

        }

    }


    while 
        (
            this->EngineCtx_.Peek(0).Type != Token::TokenType::SemiColon &&
            !this->EngineCtx_.IsAtEnd()
        )
    {

        auto ExprInitializers = 
            ParseExpression
            (
                Fields::Precedence::None
            )
        ;

        if 
            (
                !ExprInitializers
            )
        {

            this->EngineCtx_.ReportError
                (
                    this->EngineCtx_.Peek(0)
                    , Diagnostic::Severity::ERROR
                    , "Expected valid expression in initializers list"
                )
            ;

            return { std::unexpected(ExprInitializers.error()) };

        }

    }


}
constexpr auto HierarchyRules::ParseMemberAccess
    ( ::AbstractGrammar::AbstractNodes Left )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    const TokenData Op = this->EngineCtx_.Previous();

    if
        (
            this->EngineCtx_.Peek().Type != Token::TokenType::Identifier
        ) [[ unlikely ]]
    {

        this->EngineCtx_.ReportError
            (
                this->EngineCtx_.Peek()
                , Diagnostic::Severity::ERROR
                , std::format
                (
                    "Invalid member access: After operator '{}', expected an "
                        "identifier (field or method name) but got '{}'.",
                    Op.Sv_Val_,
                    this->EngineCtx_.Peek().Sv_Val_
                )
            )
        ;

        return
            {
                std::unexpected
                (
                    Fields::ParseError::MalformedMemberAccess
                )
            }
        ;

    }

    const TokenData Member = this->EngineCtx_.Advance();

    return
        {
            AbstractGrammar::AbstractNodes
            {
                .Node_ =
                {
                    AbstractGrammar::MemberAccessASTNode
                    {
                        .LeftSide = 
                            std::indirect<AbstractGrammar::AbstractNodes>
                            (
                                std::move(Left)
                            )
                        ,
                        .Op = Op,
                        .Member = Member
                    }
                }
            }
        }
    ;

}

constexpr auto HierarchyRules::ParseParenthesis
    ( void [[ /* v_ */ ]] )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    auto Result
        {
            ParseExpression
            (
                Fields::Precedence::None
            )
            .transform_error
            (
                [ ] ( Fields::ParseError e )
                    noexcept ( true )
                -> decltype ( Fields::ParseError { } )
                {

                    return e;

                }
            )
        }
    ;

    if
        (
            !this->EngineCtx_.Consume
            (
                Token::TokenType::RightParen
                , Diagnostic::Severity::ERROR
                , "Unclosed paranthesis in expression. Expected closing ')'"
            )
        ) [[ unlikely ]]
    {

        return
            {
                std::unexpected
                (
                    Fields::ParseError::MissingClosingParen
                )
            }
        ;

    }

    return
        {
            std::move
            (
                Result.value()
            )
        }
    ;

}

DeferredBraceASTNode::DeferredBraceASTNode
    (
        Fields::BraceKind kind_,
        std::vector<std::indirect<AbstractNodes>> elem_
    )
    noexcept ( true ):
        Kind(std::move(kind_)),
        Elements_(std::move(elem_))
{

    this->Elements_.reserve(1024);

}

constexpr auto HierarchyRules::ParseStatementField
    ( void [[ /* v_ */ ]] )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    std::vector<std::indirect<AbstractGrammar::AbstractNodes>> StatementFields;
    bool ErrorTrack { false };

    while
        (
            !this->EngineCtx_.IsAtEnd() &&
            this->EngineCtx_.Peek().Type != Token::TokenType::RightBrace
        ) [[ likely ]]
    {

        auto Statements_ =
            ParseExpression
            (
                Fields::Precedence::None
            )
        ;

        if
            (
                !Statements_
            ) [[ unlikely ]]
        {

            ErrorTrack = true;

            this->EngineCtx_
                .ReportError
                (
                    this->EngineCtx_.Peek()
                    , Diagnostic::Severity::ERROR 
                    , "Statement Parsing failed. Syncing to next statement..."
                )
            ;

            while
                (
                    !this->EngineCtx_.IsAtEnd() &&
                    this->EngineCtx_
                        .Peek()
                        .Type != Token::TokenType::RightBrace
                ) [[ likely ]]
            {

                this->EngineCtx_.Advance();

            }

            break;

        }

        StatementFields
            .emplace_back
            (
                std::indirect<AbstractGrammar::AbstractNodes>
                (
                    std::move(Statements_.value())
                )
            )
        ;

    }

    if
        (
            !this->EngineCtx_.Consume
            (
                Token::TokenType::RightBrace
                , Diagnostic::Severity::ERROR
                , "unterminated block: missing '}' brace to close the scope."
            )
        ) [[ unlikely ]]
    {

        return
            {
                std::unexpected
                (
                    Fields::ParseError::MissingClosingBrace
                )
            }
        ;

    }

    if
        (
            ErrorTrack
        ) [[ unlikely ]]
    {

        return
            {
                std::unexpected
                (
                    Fields::ParseError::InvalidStatement
                )
            }
        ;

    }

    return
        {
            AbstractGrammar::AbstractNodes
            {
                .Node_ =
                {
                    AbstractGrammar::DeferredBraceASTNode
                    (
                        Fields::BraceKind::StatementField,
                        std::move(StatementFields)
                    )
                }
            }
        }
    ;

}

// constexpr auto HierarchyRules::ParseClassField
//     ( void [[ /* v_*/]] )
//     noexcept ( true )
// -> std::expected<
//         AbstractGrammar::DeferredBraceASTNode,
//         Fields::ParseError
//     >
// {

//     this->EngineCtx_.Advance();

//     while
//         (
//             !this->EngineCtx_.IsAtEnd() &&
//             this->EngineCtx_.Peek().Type != Token::TokenType::RightBrace
//         )
//     {



//     }

// }

ArrayASTNode::ArrayASTNode
    ( std::vector<std::indirect<AbstractNodes>> elem_ )
    noexcept ( true ):
        Elements(std::move(elem_))
{

  Elements.reserve(1024);

}

constexpr auto HierarchyRules::ParseArray
    ( void [[ /* v_ */ ]] )
    noexcept ( true )
-> std::expected<
        AbstractGrammar::AbstractNodes,
        Fields::ParseError
    >
{

    const TokenData OpenBracket = this->EngineCtx_.Previous();
    std::vector<std::indirect<AbstractGrammar::AbstractNodes>> Elements_;

    bool ErrorTrack { false };

    while
        (
            !this->EngineCtx_.IsAtEnd() &&
            this->EngineCtx_.Peek().Type != Token::TokenType::RightBracket
        ) [[ likely ]]
    {

        auto ElementResolute =
            ParseExpression
            (
                Fields::Precedence::None
            )
        ;

        if
            (
                !ElementResolute
            ) [[ unlikely ]]
        {

            ErrorTrack = true;

            this->EngineCtx_.ReportError
                (
                    this->EngineCtx_.Peek()
                    , Diagnostic::Severity::ERROR
                    , "Array element parsing failed. Syncing out of bracket group."
                )
            ;

            while
                (
                    this->EngineCtx_.Peek().Type != Token::TokenType::Comma &&
                    this->EngineCtx_.Peek().Type != Token::TokenType::RightBracket &&
                    !this->EngineCtx_.IsAtEnd(0)
                )
            {

                this->EngineCtx_.Advance();

            }

            if
                (
                    this->EngineCtx_.Peek().Type == Token::TokenType::Comma
                )
            {

                this->EngineCtx_.Advance();
                continue;

            }

            break;

        }

        Elements_.emplace_back
            (
                std::indirect<
                        AbstractGrammar::AbstractNodes
                    >
                (
                    std::move(ElementResolute.value())
                )
            )
        ;

        if
            (
                this->EngineCtx_.Peek().Type != Token::TokenType::RightBracket
            )
        {

            this->EngineCtx_.ReportError
                (
                    this->EngineCtx_.Peek()
                    , Diagnostic::Severity::ERROR
                    , "Expected ']' to close this array literal"
                )
            ;

            this->EngineCtx_.ReportError
                (
                    OpenBracket
                    , Diagnostic::Severity::ERROR
                    , "To match this opening square bracket"
                )
            ;

            return
                {
                    std::unexpected
                    (
                        Fields::ParseError::MalformedArray
                    )
                }
            ;

        }
    }

    this->EngineCtx_.Advance();

    if
        (
            ErrorTrack
        )
    {

        return
            {
                std::unexpected
                (
                    Fields::ParseError::MalformedArray
                )
            }
        ;

    }

    return
        {
            AbstractGrammar::AbstractNodes
            {
                .Node_ =
                {
                    AbstractGrammar::ArrayASTNode
                    (
                        std::move(Elements_)
                    )
                }
            }
        }
    ;

}

const
    std::array<
        std::pair<Token::TokenType, HierarchyRules::ParseRule>,
        std::to_underlying(Token::TokenType::EndOfFile)
    > HierarchyRules::Rules =
{
    {

        [0] =
            {
                Token::TokenType::IntLiterals,
                {
                    .Precedence = Fields::Precedence::None,
                    .Nud = &HierarchyRules::ParseNumeric,
                    .Led = nullptr
                }
            }
        ,

        [1] =
            {
                Token::TokenType::FloatLiterals,
                {
                    .Precedence = Fields::Precedence::None,
                    .Nud = &HierarchyRules::ParseNumeric,
                    .Led = nullptr
                }
            }
        ,

        [2] =
            {
                Token::TokenType::StringLiterals,
                {
                    .Precedence = Fields::Precedence::None,
                    .Nud = &HierarchyRules::ParseString,
                    .Led = nullptr
                }
            }
        ,

        [3] =
            {
                Token::TokenType::Identifier,
                {
                    .Precedence = Fields::Precedence::None,
                    .Nud = &HierarchyRules::ParseIdentifier,
                    .Led = nullptr
                }
            }
        ,

        [4] =
            {
                Token::TokenType::Bang,
                {
                    .Precedence = Fields::Precedence::None,
                    .Nud = nullptr,
                    .Led = nullptr
                }
            }
        ,

        [5] =
            {
                Token::TokenType::Ampersand,
                {
                    .Precedence = Fields::Precedence::BitWiseAnd,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [6] =
            {
                Token::TokenType::PlusPlus,
                {
                    .Precedence = Fields::Precedence::Postfix,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParsePostFix
                }
            }
        ,

        [7] =
            {
                Token::TokenType::MinusMinus,
                {
                    .Precedence = Fields::Precedence::Postfix,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParsePostFix
                }
            }
        ,

        [8] =
            {
                Token::TokenType::Assign,
                {
                    .Precedence = Fields::Precedence::Assignment,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseAssignment
                }
            }
        ,

        [9] =
            {
                Token::TokenType::PlusEqual,
                {
                    .Precedence = Fields::Precedence::Assignment,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseAssignment
                }
            }
        ,

        [10] =
            {
                Token::TokenType::MinusEqual,
                {
                    .Precedence = Fields::Precedence::Assignment,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseAssignment
                }
            }
        ,

        [11] =
            {
                Token::TokenType::MulEqual,
                {
                    .Precedence = Fields::Precedence::Assignment,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseAssignment
                }
            }
        ,

        [12] =
            {
                Token::TokenType::DivEqual,
                {
                    .Precedence = Fields::Precedence::Assignment,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseAssignment
                }
            }
        ,

        [13] =
            {
                Token::TokenType::ModEqual,
                {
                    .Precedence = Fields::Precedence::Assignment,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseAssignment
                }
            }
        ,

        [14] =
            {
                Token::TokenType::Or,
                {
                    .Precedence = Fields::Precedence::LogicalOr,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [15] =
            {
                Token::TokenType::And,
                {
                    .Precedence = Fields::Precedence::LogicalAnd,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [16] =
            {
                Token::TokenType::Equal,
                {
                    .Precedence = Fields::Precedence::Equality,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [17] =
            {
                Token::TokenType::NotEqual,
                {
                    .Precedence = Fields::Precedence::Equality,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [18] =
            {
                Token::TokenType::LessThan,
                {
                    .Precedence = Fields::Precedence::Comparison,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [19] =
            {
                Token::TokenType::GreaterThan,
                {
                    .Precedence = Fields::Precedence::Comparison,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [20] =
            {
                Token::TokenType::LessOrEqual,
                {
                    .Precedence = Fields::Precedence::Comparison,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [21] =
            {
                Token::TokenType::GreaterOrEqual,
                {
                    .Precedence = Fields::Precedence::Comparison,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [22] =
            {
                Token::TokenType::Plus,
                {
                    .Precedence = Fields::Precedence::Term,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [23] =
            {
                Token::TokenType::Mul,
                {
                    .Precedence = Fields::Precedence::Factor,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [24] =
            {
                Token::TokenType::Div,
                {
                    .Precedence = Fields::Precedence::Factor,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [25] =
            {
                Token::TokenType::Mod,
                {
                    .Precedence = Fields::Precedence::Factor,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseBinary
                }
            }
        ,

        [26] =
            {
                Token::TokenType::Dot,
                {
                    .Precedence = Fields::Precedence::MemAccess,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseMemberAccess
                }
            }
        ,

        [27] =
            {
                Token::TokenType::DoubleColon,
                {
                    .Precedence = Fields::Precedence::MemAccess,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseMemberAccess
                }
            }
        ,

        [28] =
            {
                Token::TokenType::LeftParen,
                {
                    .Precedence = Fields::Precedence::CallIndx,
                    .Nud = &HierarchyRules::ParseParenthesis,
                    .Led = &HierarchyRules::ParseIndex
                }
            }
        ,

        [29] =
            {
                Token::TokenType::LeftBracket,
                {
                    .Precedence = Fields::Precedence::CallIndx,
                    .Nud = &HierarchyRules::ParseArray,
                    .Led = &HierarchyRules::ParseIndex
                }
            }
        ,

        [30] =
            {
                Token::TokenType::Range,
                {
                    .Precedence = Fields::Precedence::Comparison,
                    .Nud = nullptr,
                    .Led = &HierarchyRules::ParseRange
                }
            }
        ,
    }
};

