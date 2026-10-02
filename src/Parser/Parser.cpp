#include <expected>

#include <Lexer/Token.hpp>
#include <Parser/Parser.hpp>
#include <Parser/Fields.hpp>
#include <SourceManager.hpp>
#include <Diagnostic/Diagnostic.hpp>

namespace
    Vll::Parser
{

    SyntaxAnalysis::SyntaxAnalysis
        ( 
            DiagnosticEngine& Diag, 
            std::vector<TokenData> Tokens 
        )
        noexcept ( true ):
            Diag_(Diag),
            Rules_(*this),
            Toks_(std::move(Tokens))
    {}

    auto SyntaxAnalysis::IsAtEnd
        ( std::uint16_t Indx )
        const noexcept ( true )
    -> bool
    {

        return 
            (
                this->Cursor_ + Indx >= this->Toks_.size() ||
                this->Toks_.at(this->Cursor_ + Indx).Type == Token::TokenType::EndOfFile
            );

    }

    auto SyntaxAnalysis::Peek
        ( std::uint16_t Indx )
        noexcept ( true )
    -> TokenData
    {

        if
            (
                this->IsAtEnd()
            )
        {

            static constexpr TokenData EofToken
                {
                    .Sv_Val_ = "",
                    .Lexer_Size_t_Offset = 0,
                    .Type = Token::TokenType::EndOfFile,
                }
            ;

            return EofToken;

        }

        return this->Toks_.at(this->Cursor_ + Indx);

    }

    auto SyntaxAnalysis::Previous
        ( void [[ /* v_ */ ]] )
        noexcept ( true )
    -> TokenData
    {

        if
            (
                this->IsAtEnd(0) ||
                this->Cursor_ == 0
            )
        {

            static constexpr TokenData EofToken
                {
                    .Sv_Val_ = "",
                    .Lexer_Size_t_Offset = 0,
                    .Type = Token::TokenType::EndOfFile,
                }
            ;

            return EofToken;

        }

        return this->Toks_.at(this->Cursor_ - 1);

    }

    auto SyntaxAnalysis::Advance
        ( void [[ /* v_ */]] )
        noexcept ( true )
    -> TokenData
    {

        if
            (
                this->IsAtEnd()
            )
        {

            static constexpr TokenData EofToken 
                {
                    .Sv_Val_ = ""
                    , .Lexer_Size_t_Offset = 0
                    , .Type = Token::TokenType::EndOfFile
                }
            ;

            return EofToken;

        }

        return this->Toks_.at(this->Cursor_++);

    }

    auto SyntaxAnalysis::ReportError
        ( 
            const TokenData& Tok, 
            Diagnostic::Severity Level_, 
            const std::string_view Msg 
        )
        const noexcept ( true )
    -> void
    {

        this->Diag_.ReportError(Tok, Level_, Msg);

    }

    auto SyntaxAnalysis::ConsumeIdentifier
        ( 
            const Token::TokenType& Toks, 
            Diagnostic::Severity Level_, 
            std::string_view Msg
        )
        noexcept ( true )
    -> std::expected<TokenData, Fields::ParseError>
    {

        if
            (
                this->Peek().Type == Toks
            )
        {

            return this->Advance();

        }

        this->ReportError(this->Peek(), Level_, Msg);

        return
            {
                std::unexpected
                (
                    Fields::ParseError::UnexpectedToken
                )
            }
        ;

    }

    auto SyntaxAnalysis::Consume
        ( 
            const Token::TokenType& Toks, 
            Diagnostic::Severity Level_, 
            std::string_view Msg 
        )
        noexcept ( true )
    -> bool
    {

        if
            (
                this->Peek().Type == Toks
            )
        {

            this->Advance();
            return true;

        }

        this->ReportError(this->Peek(), Level_, Msg);
        return false;

    }

}
