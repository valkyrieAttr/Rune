cmake_minimum_required ( VERSION 4.2.1 )

set(CMAKE_COLOR_DIAGNOSTICS ON)

project( lib_ullix_
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION ""
)

add_executable ( a.out )

target_compile_options( a.out PRIVATE
  -Wall
  -Werror
  -Weverything
  -Wno-c99-designator
  -Wno-gnu-case-range
  -Wno-c++98-compat
  -Wno-switch-enum
  -Wno-switch-default
  -Wno-c++23-extensions
  -Wno-c++98-compat-pedantic
  -Wno-reserved-module-identifier
  -fno-exceptions
  -ferror-limit=999999
  -fdiagnostics-color
  -std=c++26
)


target_sources( a.out PUBLIC
    src/Main.cpp
    src/Lexer/Lexer.cpp
    # src/Parser.cpp
    src/FileHandler.cpp
    src/SourceManager.cpp

#    src/Transpiler.cpp 
)
target_include_directories(a.out PRIVATE
    include/
)
target_compile_features (a.out PRIVATE
    cxx_std_26
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-O3 -flto -march=native)
    add_link_options(-flto)
endif()

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

target_link_options(a.out PRIVATE -lstdc++exp)
target_link_libraries(a.out PRIVATE -lstdc++exp)
