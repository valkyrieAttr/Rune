#include <print>
#include <format>
#include <algorithm>

#include <SourceManager.hpp>
#include <Parser/Hierarchy.hpp>
#include <Diagnostic/Diagnostic.hpp>



namespace 
    [[
        /* namespace Signature */
    ]] Vll 
{

    constexpr DiagnosticEngine::DiagnosticEngine
        ( 
            std::string_view Filename_,
            const SourceDepths::SourceManager& SrcDepths
        )
        noexcept ( true ): 
            Sv_FileName_(Filename_),
            SrcManager_(SrcDepths)
    {}

    auto DiagnosticEngine::ReportError 
        ( 
            const TokenData& Tok,
            Diagnostic::Severity Level_,
            std::string_view Msg_
        )
        noexcept ( true )
    -> void 
    {

        auto SourceDesc = this->SrcManager_
            .ReturnLocation
            (
                Tok.Lexer_Size_t_Offset
            )
        ;

        this->diagnostics_
            .emplace_back
            ( 
                std::format
                    (
                        "\033[1m{}:{}:{}:\033[0m \033[1;31m error:\033[0m {}\033[0m"
                        , this->Sv_FileName_
                        , SourceDesc.Lexer_Size_t_Line
                        , SourceDesc.Lexer_Size_t_Column
                        , Msg_
                    )
                , Level_
            )
        ;

        std::string_view Sv_SourceLine_ = this->SrcManager_.LineText
            (
                SourceDesc.Lexer_Size_t_Line - 1
            )
        ;

        this->diagnostics_
            .emplace_back 
            (
                std::format
                    (
                        "{:<5} | {}"
                        , SourceDesc.Lexer_Size_t_Line
                        , Sv_SourceLine_
                    )
                , Level_
            )
        ;

        const std::size_t PaddingLength_ = (SourceDesc.Lexer_Size_t_Column > 0)
                                        ? (SourceDesc.Lexer_Size_t_Column - 1)
                                        : 0u;

        std::string Underline = "^";

        if
            (
                Tok.Sv_Val_.length() > 1
            )
        {

            Underline
                .append
                (
                    Tok.Sv_Val_.length() - 1,
                    '~'
                )
            ;

        }

        this->diagnostics_
            .emplace_back
            (
                std::format
                    (
                        "      | {}\033[1;31m{}\033[0m"
                        , std::string(PaddingLength_, ' ')
                        , Underline
                    )
                , Level_
            )
        ;

    }

    auto constexpr DiagnosticEngine::HasErrors_
        ( void [[ /* v_ */ ]] )
        const noexcept ( true )
    -> bool 
    {

        return std::ranges::any_of
            (
                this->diagnostics_,
                [ ] ( const Diagnostic& diags_ )
                    noexcept ( true )
                -> decltype ( bool { } )
                {
                    
                    return diags_.Level_ == Diagnostic::Severity::ERROR;

                }
            )
        ;

    }

    auto constexpr DiagnosticEngine::RenderDiagnostics_
        ( void [[ /* v_ */ ]] )
    -> void 
    {

        for 
            (
                const auto& D : this->diagnostics_
            )
        {

            std::println(stderr, "{}", D.Message_);

        }


    }
    
}
