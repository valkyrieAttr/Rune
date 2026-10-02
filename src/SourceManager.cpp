#include <algorithm>

#include <SourceManager.hpp>

namespace
    [[
        /* namespaceSignature */
    ]] Vll
{

    SourceDepths::SourceManager::SourceManager
        ( std::string_view SourceView )
        noexcept ( true ): Sv_SourceView_(SourceView)
    {

        this->LineOffset_.reserve(512);

        LineOffset_.emplace_back(0);

        for
            (
                std::uint32_t i {0};
                i < Sv_SourceView_.size();
                ++i
            )
        {

            if
                (
                    Sv_SourceView_.at(i) == '\n'
                )
            {

                LineOffset_.emplace_back(i);

            }

        }

    }


    auto SourceDepths::SourceManager::ReturnLocation
        ( const std::uint32_t Offset )
        const noexcept ( true )
    -> SourceLocation
    {

        auto It = std::ranges::upper_bound
            (
                LineOffset_,
                Offset
            )
        ;

        std::uint32_t LineIdx = 
            static_cast<std::uint32_t>
            (
                std::ranges::distance
                (
                    LineOffset_.begin(), It
                )
            ) - 1
        ;

        std::uint32_t LineStart = 
            ( LineIdx == 0 ) ? 0u : LineOffset_.at(LineIdx) + 1u;


        return
            {
                SourceLocation
                {
                    .Lexer_Size_t_Line = LineIdx + 1,
                    .Lexer_Size_t_Column = (Offset - LineStart) + 1
                }
            }
        ;

    }

    auto SourceDepths::SourceManager::LineText
        ( const std::uint32_t LineIdx )
        const noexcept ( true )
    -> std::string_view 
    {

        std::uint32_t LineStart = 
            ( LineIdx == 0 ) ? 0u : LineOffset_.at(LineIdx) + 1u;

        std::uint32_t LineEnd = 
            ( LineIdx + 1 < LineOffset_.size() ) ? LineOffset_.at(LineIdx + 1)
                                                 : static_cast<std::uint32_t>(Sv_SourceView_.size());
        
        return Sv_SourceView_
            .subview
            (
                LineStart, 
                LineEnd - LineStart
            )
        ;

    }

}
