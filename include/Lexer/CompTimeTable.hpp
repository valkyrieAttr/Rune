#ifndef COMPTIMETABLE_HPP
    #define COMPTIMETABLE_HPP


    #include <array>
    #include "Token.hpp"

    namespace
        [[
            /* namespaceSignature */
        ]] Vll
    {
        namespace
            [[
                using __gnu__:
                    __visibility__("internal") ,
                    __const__ ,
            ]] Detail
        {

            static constexpr
                std::array<Token::KeywordEntry, 31> Keywords =
            {
                {
                    [0] =
                        {
                            .Sv_Word_ = "from", .Type = Token::TokenType::From
                        }
                    ,

                    [1] =
                        {
                            .Sv_Word_ = "export", .Type = Token::TokenType::Export
                        }
                    ,

                    [2] =
                        {
                            .Sv_Word_ = "type", .Type = Token::TokenType::Type
                        }
                    ,

                    [3] =
                        {
                            .Sv_Word_ = "func", .Type = Token::TokenType::Func
                        }
                    ,

                    [4] =
                        {
                            .Sv_Word_ = "if", .Type = Token::TokenType::If
                        }
                    ,

                    [5] =
                        {
                            .Sv_Word_ = "else", .Type = Token::TokenType::Else
                        }
                    ,

                    [6] =
                        {
                            .Sv_Word_ = "while", .Type = Token::TokenType::While
                        }
                    ,

                    [7] =
                        {
                            .Sv_Word_ = "let", .Type = Token::TokenType::Let
                        }
                    ,

                    [8] =
                        {
                            .Sv_Word_ = "return", .Type = Token::TokenType::Return
                        }
                    ,

                    [9] =
                        {
                            .Sv_Word_ = "break", .Type = Token::TokenType::Break
                        }
                    ,

                    [10] =
                        {
                            .Sv_Word_ = "continue", .Type = Token::TokenType::Continue
                        }
                    ,

                    [11] =
                        {
                            .Sv_Word_ = "true", .Type = Token::TokenType::True
                        }
                    ,

                    [12] =
                        {
                            .Sv_Word_ = "false", .Type = Token::TokenType::False
                        }
                    ,

                    [13] =
                        {
                            .Sv_Word_ = "in", .Type = Token::TokenType::In
                        }
                    ,

                    [14] =
                        {
                            .Sv_Word_ = "main", .Type = Token::TokenType::Main
                        }
                    ,

                    [15] =
                        {
                            .Sv_Word_ = "match", .Type = Token::TokenType::Match
                        }
                    ,

                    [16] =
                        {
                            .Sv_Word_ = "module", .Type = Token::TokenType::Module
                        }
                    ,

                    [17] =
                        {
                            .Sv_Word_ = "class", .Type = Token::TokenType::Class
                        }
                    ,

                    [18] =
                        {
                            .Sv_Word_ = "this", .Type = Token::TokenType::This
                        }
                    ,

                    [19] =
                        {
                            .Sv_Word_ = "interface", .Type = Token::TokenType::Interface
                        }
                    ,

                    [20] =
                        {
                            .Sv_Word_ = "extend", .Type = Token::TokenType::Extend
                        }
                    ,

                    [21] =
                        {
                            .Sv_Word_ = "enum", .Type = Token::TokenType::Enum
                        }
                    ,

                    [22] =
                        {
                            .Sv_Word_ = "pub", .Type = Token::TokenType::Pub
                        }
                    ,

                    [23] =
                        {
                            .Sv_Word_ = "defer", .Type = Token::TokenType::Defer
                        }
                    ,

                    [24] =
                        {
                            .Sv_Word_ = "async", .Type = Token::TokenType::Async
                        }
                    ,

                    [25] =
                        {
                            .Sv_Word_ = "await", .Type = Token::TokenType::Await
                        }
                    ,

                    [26] =
                        {
                            .Sv_Word_ = "try", .Type = Token::TokenType::Try
                        }
                    ,

                    [27] =
                        {
                            .Sv_Word_ = "catch", .Type = Token::TokenType::Catch
                        }
                    ,

                    [28] =
                        {
                            .Sv_Word_ = "const", .Type = Token::TokenType::Const
                        }
                    ,

                    [29] =
                        {
                            .Sv_Word_ = "mut", .Type = Token::TokenType::Mut
                        }
                    ,

                    [30] = 
                        {
                            .Sv_Word_ = "var", .Type = Token::TokenType::Var
                        }
                    ,
                }
            };

            static constexpr
                std::array<Token::OperatorEntry, 25> SingleCharOperators =
            {
                {
                    [0] =
                        {
                            .Operator_ = "&", .Type = Token::TokenType::Ampersand
                        }
                    ,

                    [1] =
                        {
                            .Operator_ = "|", .Type = Token::TokenType::Pipe
                        }
                    ,

                    [2] =
                        {
                            .Operator_ = ".", .Type = Token::TokenType::Dot
                        }
                    ,

                    [3] =
                        {
                            .Operator_ = "+", .Type = Token::TokenType::Plus
                        }
                    ,

                    [4] =
                        {
                            .Operator_ = "-", .Type = Token::TokenType::Minus
                        }
                    ,

                    [5] =
                        {
                            .Operator_ = "*", .Type = Token::TokenType::Mul
                        }
                    ,

                    [6] =
                        {
                            .Operator_ = "/", .Type = Token::TokenType::Div
                        }
                    ,

                    [7] =
                        {
                            .Operator_ = "=", .Type = Token::TokenType::Assign
                        }
                    ,

                    [8] =
                        {
                            .Operator_ = "<", .Type = Token::TokenType::LessThan
                        }
                    ,

                    [9] =
                        {
                            .Operator_ = ">", .Type = Token::TokenType::GreaterThan
                        }
                    ,

                    [10] =
                        {
                            .Operator_ = "!", .Type = Token::TokenType::Bang
                        }
                    ,

                    [11] =
                        {
                            .Operator_ = ":", .Type = Token::TokenType::Colon
                        }
                    ,

                    [12] =
                        {
                            .Operator_ = "%", .Type = Token::TokenType::Mod
                        }
                    ,

                    [13] =
                        {
                            .Operator_ = "?", .Type = Token::TokenType::Question
                        }
                    ,

                    [14] =
                        {
                            .Operator_ = "~", .Type = Token::TokenType::Tilde
                        }
                    ,

                    [15] =
                        {
                            .Operator_ = "^", .Type = Token::TokenType::Caret
                        }
                    ,

                    [16] =
                        {
                            .Operator_ = "@", .Type = Token::TokenType::Annotation
                        }
                    ,

                    [17] =
                        {
                            .Operator_ = ";", .Type = Token::TokenType::SemiColon
                        }
                    ,

                    [18] =
                        {
                            .Operator_ = "(", .Type = Token::TokenType::LeftParen
                        }
                    ,

                    [19] =
                        {
                            .Operator_ = ")", .Type = Token::TokenType::RightParen
                        }
                    ,

                    [20] =
                        {
                            .Operator_ = "{", .Type = Token::TokenType::LeftBrace
                        }
                    ,

                    [21] =
                        {
                            .Operator_ = "}", .Type = Token::TokenType::RightBrace
                        }
                    ,

                    [22] =
                        {
                            .Operator_ = "[", .Type = Token::TokenType::LeftBracket
                        }
                    ,

                    [23] =
                        {
                            .Operator_ = "]", .Type = Token::TokenType::RightBracket
                        }
                    ,

                    [24] =
                        {
                            .Operator_ = ",", .Type = Token::TokenType::Comma
                        }
                    ,
                }
            };

            static constexpr
                std::array<Token::OperatorEntry, 18> TwoCharOperators =
            {
                {
                    [0] =
                        {
                            .Operator_ = "&&", .Type = Token::TokenType::And
                        }
                    ,

                    [1] =
                        {
                            .Operator_ = "||", .Type = Token::TokenType::Or
                        }
                    ,

                    [2] =
                        {
                            .Operator_ = "+=", .Type = Token::TokenType::PlusEqual
                        }
                    ,

                    [3] =
                        {
                            .Operator_ = "++", .Type = Token::TokenType::PlusPlus
                        }
                    ,

                    [4] =
                        {
                            .Operator_ = "->", .Type = Token::TokenType::Arrow
                        }
                    ,

                    [5] =
                        {
                            .Operator_ = "--", .Type = Token::TokenType::MinusMinus
                        }
                    ,

                    [6] =
                        {
                            .Operator_ = "-=", .Type = Token::TokenType::MinusEqual
                        }
                    ,

                    [7] =
                        {
                            .Operator_ = "*=", .Type = Token::TokenType::MulEqual
                        }
                    ,

                    [8] =
                        {
                            .Operator_ = "/=", .Type = Token::TokenType::DivEqual
                        }
                    ,

                    [9] =
                        {
                            .Operator_ = "^=", .Type = Token::TokenType::CaretEqual
                        }
                    ,

                    [10] =
                        {
                            .Operator_ = "<=", .Type = Token::TokenType::LessOrEqual
                        }
                    ,

                    [11] =
                        {
                            .Operator_ = ">=", .Type = Token::TokenType::GreaterOrEqual
                        }
                    ,

                    [12] =
                        {
                            .Operator_ = "==", .Type = Token::TokenType::Equal
                        }
                    ,

                    [13] =
                        {
                            .Operator_ = "=>", .Type = Token::TokenType::MapArrow
                        }
                    ,

                    [14] =
                        {
                            .Operator_ = "!=", .Type = Token::TokenType::NotEqual
                        }
                    ,

                    [15] =
                        {
                            .Operator_ = "::", .Type = Token::TokenType::DoubleColon
                        }
                    ,

                    [16] =
                        {
                            .Operator_ = "%=", .Type = Token::TokenType::ModEqual
                        }
                    ,

                    [17] =
                        {
                            .Operator_ = "..", .Type = Token::TokenType::Range
                        }
                    ,
                }
            };

            static constexpr std::uint32_t TableSize {64};

            static constexpr auto Hash
                ( std::string_view Sv_S )
                noexcept ( true )
            -> std::uint32_t
            {

                std::uint32_t h = 2166136261u;

                for
                    (
                        char C : Sv_S
                    )
                {

                    h ^= static_cast<std::uint8_t>(C);
                    h *= 16777619u;

                }

                return  h;

            }

            static constexpr auto Op
                ( char a, char b = '\0' )
                noexcept ( true )
            -> std::uint16_t
            {

                return
                    (
                        static_cast<std::uint16_t>
                        (
                            static_cast<std::uint8_t>(a) |
                            (
                                static_cast<std::uint8_t>(b) << 8
                            )
                        )
                    )

                ;

            }

            static constexpr auto BuildCharTable
                ( void [[ /* v_ */ ]] )
                noexcept ( true )
            -> std::array<std::uint8_t, 256>
            {

                std::array<std::uint8_t, 256> Table {};

                for
                    (
                        std::uint32_t i {0}; i < 256; i++
                    )
                {

                    switch
                        (
                            i
                        )
                    {

                        case
                            'A' ... 'Z':

                        case
                            'a' ... 'z':
                        {

                            Table.at(i) |= 0x1;
                            break;

                        }

                        case
                            '0' ... '9':
                        {

                            Table.at(i) |= 0x2;
                            break;

                        }

                        case
                            (
                                '_'
                            ):
                        {

                            Table.at(i) |= 0x1;
                            break;

                        }

                        case
                            (
                                ' '
                            ):

                        case
                            (
                                '\t'
                            ):

                        case
                            (
                                '\n'
                            ):

                        case
                            (
                                '\r'
                            ):
                        {

                            Table.at(i) |= 0x4;
                            break;

                        }

                    }

                }

                return Table;

            }

            static constexpr auto BuildOperatorTable
                ( void [[ /* v_ */ ]] )
                noexcept ( true )
            -> std::array<Token::LookUpOperatorEntry, 65536>
            {

                std::array<Token::LookUpOperatorEntry, 65536> Table {};

                std::uint16_t Key;

                for
                    (
                        const auto& o : SingleCharOperators
                    )
                {

                    Key =
                        Op
                        (
                            o.Operator_.at(0),
                            '\0'
                        )
                    ;

                    Table.at(Key) =
                        {
                            .Type = o.Type,
                            .AdvanceCount = 1
                        }
                    ;

                }

                for
                    (
                        const auto& o : TwoCharOperators
                    )
                {

                    Key =
                        Op
                        (
                            o.Operator_.at(0),
                            o.Operator_.at(1)
                        )
                    ;

                    Table.at(Key) =
                        {
                            .Type = o.Type,
                            .AdvanceCount = 2
                        }
                    ;

                }

                return Table;

            }

            static constexpr auto BuildTable
                ( void [[ /* v_ */ ]] )
                noexcept ( true )
            -> std::array<Token::HashEntry, TableSize>
            {

                std::array<Token::HashEntry, TableSize> Table {};

                for
                    (
                        auto& KW : Keywords
                    )
                {

                    std::uint32_t Idx =
                        Hash
                        (
                            KW.Sv_Word_
                        ) & (TableSize - 1)
                    ;

                    while
                        (
                            Table.at(Idx).BoolOccupied
                        )
                    {

                        Idx =
                            (
                                Idx + 1
                            ) & (TableSize - 1)
                        ;

                    }

                    Table.at(Idx) =
                        {
                            .Sv_Word_ = KW.Sv_Word_,
                            .Type = KW.Type,
                            .BoolOccupied = true
                        }
                    ;

                }

                return Table;

            }

        }

        class
            [[
                /* classSignature */
            ]] CompTimeTable
        {
            public:

                static auto constexpr KeywordTable = Detail::BuildTable();
                static auto constexpr OperatorTable = Detail::BuildOperatorTable();
                static auto constexpr CharTable = Detail::BuildCharTable();

                static constexpr auto Hash
                    ( std::string_view Sv_s )
                    noexcept ( true )
                -> std::uint32_t
                {

                    return Detail::Hash(Sv_s);

                }

                static constexpr auto Op
                    ( char a, char b = '\0' )
                    noexcept ( true )
                -> std::uint16_t
                {

                    return Detail::Op(a, b);

                }
        };

    }

#endif

