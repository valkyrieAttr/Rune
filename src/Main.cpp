#include "Parser/Parser.hpp"
#include <span>
#include <ranges>

#include <Lexer/Lexer.hpp>
#include <FileHandler.hpp>
#include <SourceManager.hpp>

auto main
(
    int argc,
    char *argv[]
) -> std::int32_t {

    std::span<char const *const> _arguments
    {
        std::views::counted
        (
          argv, argc
        )
    };

    if
    (
      _arguments.size() < 2
    ) exit(1);


    FileHandler::FileOpener file{_arguments.at(1)};


    Vll::SourceDepths::SourceManager SourceLoc
    {
      file.view()
    };

    Vll::Lexer LexTok{
      file.view(),
      _arguments.at(1),
      SourceLoc
    };


    auto Tokens = LexTok.Lex();

    // for
    // (
    //   auto i : Tokens
    // ) {

    //   std::println("{:<5} | {:<5}", i.Lexer_Size_t_Offset, i.Sv_Val_);

    // }

}
