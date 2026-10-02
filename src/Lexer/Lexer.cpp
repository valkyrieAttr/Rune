#include <print>

#include <Lexer/Lexer.hpp>
#include <Lexer/Token.hpp>
#include <Lexer/CompTimeTable.hpp>

namespace
    [[
        /* namespaceSignature */
    ]] Vll
{

    Lexer::Lexer
        (
            std::string_view sourceView,
            std::string_view FileName,
            SourceDepths::SourceManager& SourceM
        )
        noexcept ( true ):
            Sv_SourceView_(sourceView),
            Sv_FileName_(FileName),
            SrcManager_(std::move(SourceM))
    {  }


    constexpr auto Lexer::IsAtEnd
        ( std::uint32_t Pos )
        noexcept ( true )
    -> bool
    {

        return
            (
                (this->FileCursor_ + Pos) >= this->Sv_SourceView_.size()
            )
        ;

    }

    constexpr auto Lexer::Advance
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    -> void
    {

        if
            (
                IsAtEnd()
            )
        {

            return;

        }

        this->FileCursor_++;

    }

    constexpr auto Lexer::Peek
        ( std::uint32_t Pos, char Ch )
        noexcept ( true )
    -> bool
    {

        return
            (
                !IsAtEnd(Pos) &&
                Sv_SourceView_.at(this->FileCursor_ + Pos) == Ch
            )
        ;

    }

    constexpr auto Lexer::PeekChar
        ( std::uint32_t Pos  )
        noexcept ( true )
    -> char
    {

        return
            (
                !IsAtEnd(Pos) ? this->Sv_SourceView_.at(this->FileCursor_ + Pos)
                            : '\0'
            )
        ;

    }


    constexpr auto Lexer::ScanLineComment
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    -> void
    {

        Advance();

        while
            (
                !IsAtEnd() &&
                PeekChar(0) != '\n'
            )
        {

            Advance();

        }

    }

    constexpr auto Lexer::ScanBlockComment
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    -> void
    {

        Advance();
        Advance();

        std::uint32_t Depth {1};

        while
            (
                !IsAtEnd() && Depth > 0
            )
        {

            std::uint16_t CommonPair =
                CompTimeTable::Op
                (
                    PeekChar(0),
                    PeekChar(1)
                )
            ;

            switch
                (
                    CommonPair
                )
            {

                case
                    (
                        CompTimeTable::Op('/', '*')
                    ):
                {

                    Advance();
                    Advance();
                    ++Depth;

                    continue;

                }

                case
                    (
                        CompTimeTable::Op('*', '/')
                    ):
                {

                    Advance();
                    Advance();

                    --Depth;

                    continue;

                }

            }

            Advance();

        }

        if
            (
                Depth > 0
            )
        {


            std::println
                (
                    stderr
                    , "\033[1m{}:{}:{}:\033[0m \033[1;31m error:\033[0m Unterminated block comment \033[0m"
                    , this->Sv_FileName_
                    , this->SrcManager_.ReturnLocation
                        (
                            this->FileCursor_
                        ).Lexer_Size_t_Line
                    ,
                    this->SrcManager_.ReturnLocation
                        (
                            this->FileCursor_
                        ).Lexer_Size_t_Column
                )
            ;

            std::exit(1);

        }

    }

    constexpr auto Lexer::KeyWordOrIdentifier
        ( const std::string_view Toks_ )
        noexcept ( true )
    -> Token::TokenType
    {

        std::uint32_t Idx = CompTimeTable::Hash(Toks_) & (Detail::TableSize - 1);

        while
            (
                CompTimeTable::KeywordTable.at(Idx).BoolOccupied
            )
        {

            if
                (
                    CompTimeTable::KeywordTable.at(Idx).Sv_Word_ == Toks_
                )
            {

                return CompTimeTable::KeywordTable.at(Idx).Type;

            }

            Idx = (Idx + 1) & (Detail::TableSize - 1);

        }

        return Token::TokenType::Identifier;

    }

    auto Lexer::Lex
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    -> std::vector<TokenData>
    {

        std::vector<TokenData> Tokens;
        Tokens.reserve(this->Sv_SourceView_.size() / 4);

        const std::string_view k_Cbuffer = this->Sv_SourceView_;

        while
            (
                !IsAtEnd()
            )
        {

            char CurrentChar = PeekChar(0);

            if
                (
                    CompTimeTable::CharTable.at
                    (
                        static_cast<std::uint8_t>(CurrentChar)
                    ) & 0x4
                )
            {

                Advance();
                continue;

            }

            std::uint16_t Pair =
                CompTimeTable::Op
                (
                    CurrentChar,
                    PeekChar(1)
                )
            ;

            std::uint32_t TokenStartOffset = this->FileCursor_;
            Token::TokenType Type = Token::TokenType::Unknown;

            switch
                (
                    CurrentChar
                )
            {

                case
                    (
                        '"'
                    ):
                case
                    (
                        '\''
                    ):
                {

                    auto QuoteChar = CurrentChar;
                    Advance();

                    bool IsClosed {false};

                    while
                        (
                            !IsAtEnd() &&
                            PeekChar(0) != QuoteChar
                        )
                    {

                        if
                            (
                                QuoteChar != '`' &&
                                Peek(0, '\\') &&
                                !IsAtEnd(1)
                            )
                        {

                            Advance();
                            Advance();

                            continue;

                        }

                        Advance();

                    }

                    if
                        (
                            !IsAtEnd() &&
                            Peek(0, QuoteChar)
                        )
                    {

                        IsClosed = true;
                        Advance();

                    }

                    if
                        (
                            !IsClosed
                        )
                    {

                        std::println
                            (
                                stderr
                                , "\033[1m{}:{}:{}:\033[0m \033[1;31m error:\033[0m Unclosed string literal found. \033[0m"
                                , this->Sv_FileName_
                                , this->SrcManager_.ReturnLocation
                                    (
                                        this->FileCursor_
                                    ).Lexer_Size_t_Line
                                ,
                                this->SrcManager_.ReturnLocation
                                    (
                                        this->FileCursor_
                                    ).Lexer_Size_t_Column

                            )
                        ;

                        std::exit(1);

                    }

                    switch
                        (
                            QuoteChar
                        )
                    {

                        case
                            (
                                '"'
                            ):
                        {

                            Type = Token::TokenType::StringLiterals;
                            break;

                        }

                        case
                            (
                                '\''
                            ):
                        {

                            Type = Token::TokenType::RawStringLiterals;
                            break;

                        }

                    }

                    break;

                }

                default:
                {

                    switch
                        (
                            Pair
                        )
                    {

                        case
                            (
                                CompTimeTable::Op('.', '.')
                            ):
                        {

                            Type = Token::TokenType::Range;
                            Advance();
                            Advance();


                            break;

                        }

                        case
                            (
                                CompTimeTable::Op('/', '/')
                            ):
                        {

                            ScanLineComment();
                            break;

                        }

                        case
                            (
                                CompTimeTable::Op('/', '*')
                            ):
                        {

                            ScanBlockComment();
                            break;

                        }

                        default:
                        {

                            const auto& Entry =
                                CompTimeTable::OperatorTable.at
                                (
                                    Pair
                                )
                            ;

                            if
                                (
                                    Entry.AdvanceCount > 0
                                )
                            {

                                Type = Entry.Type;

                                for
                                    (
                                        std::uint8_t i {};
                                        i < Entry.AdvanceCount;
                                        i++
                                    )
                                {

                                    Advance();

                                }

                                break;

                            }

                            std::uint16_t SingleKey =
                                CompTimeTable::Op
                                (
                                    CurrentChar,
                                    '\0'
                                )
                            ;

                            const auto& SingleCharEntry =
                                CompTimeTable::OperatorTable.at
                                (
                                    SingleKey
                                )
                            ;

                            if
                                (
                                    SingleCharEntry.AdvanceCount > 0
                                )
                            {

                                Type = SingleCharEntry.Type;
                                Advance();
                                break;

                            }

                            else if
                                (
                                    CompTimeTable::CharTable.at
                                    (
                                        static_cast<unsigned char>(CurrentChar)
                                    ) & 0x2
                                )
                            {

                                bool IsFloat {false};

                                while
                                    (
                                        !IsAtEnd()
                                    )
                                {

                                    char Current = PeekChar(0);

                                    if
                                        (
                                            CompTimeTable::CharTable.at
                                            (
                                                static_cast<unsigned char>
                                                (
                                                    Current
                                                )
                                            ) & 0x2
                                        )
                                    {

                                        Advance();

                                    }

                                    else if
                                        (
                                            Current == '.' && !IsFloat
                                        )
                                    {

                                        if
                                            (
                                                !IsAtEnd(1) &&
                                                Peek(1, '.')
                                            )
                                        {

                                            break;

                                        }

                                        IsFloat = true;
                                        Advance();

                                    }

                                    else
                                        [[ /* nullAttr */ ]]
                                    {

                                        break;

                                    }

                                }

                                Type = IsFloat ? Token::TokenType::FloatLiterals
                                               : Token::TokenType::IntLiterals;

                            }

                            else if
                                (
                                    CompTimeTable::CharTable.at
                                    (
                                        static_cast<unsigned char>(CurrentChar)
                                    ) & 0x1
                                )
                            {

                                while
                                    (
                                        !IsAtEnd()
                                    )
                                {

                                    char C = PeekChar(0);

                                    if
                                        (
                                            CompTimeTable::CharTable.at
                                                (
                                                    static_cast<unsigned char>(C)
                                                ) & 0x3
                                        )
                                    {

                                        Advance();

                                    }

                                    else
                                        [[ /* nullAttr */ ]]
                                    {

                                        break;

                                    }

                                }

                                std::string_view WordText
                                    (
                                        k_Cbuffer.subview
                                        (
                                            TokenStartOffset,
                                            this->FileCursor_ - TokenStartOffset
                                        )
                                    )
                                ;

                                Type = KeyWordOrIdentifier(WordText);

                            }

                            else
                                [[ /* nullAttr */]]
                            {

                                Advance();

                            }

                            break;

                        }

                    }

                }

            }

            if
                (
                    Type != Token::TokenType::Unknown
                )
            {

                std::string_view TokenText
                    (
                        k_Cbuffer.subview
                        (
                            TokenStartOffset,
                            this->FileCursor_ - TokenStartOffset
                        )
                    )
                ;

                Tokens.emplace_back
                    (
                        TokenData
                        {
                            .Sv_Val_ = TokenText,
                            .Lexer_Size_t_Offset = this->FileCursor_,
                            .Type = Type
                        }
                    )
                ;

            }

        }

        Tokens.emplace_back
            (
                TokenData
                {
                    .Sv_Val_ = "",
                    .Lexer_Size_t_Offset = this->FileCursor_,
                    .Type = Token::TokenType::EndOfFile,
                }
            )
        ;


        return { Tokens };

    }

}
