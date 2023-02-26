cmake_minimum_required(VERSION 3.8)
project(TreesitterLib)

set(CMAKE_CXX_STANDARD 14)

add_library(TreesitterCPP STATIC ./ThirdParty/tree-sitter-cpp/src/parser.c ./ThirdParty/tree-sitter-cpp/src/scanner.cc)
target_link_directories(TreesitterCPP PRIVATE ./ThirdParty/tree-sitter-cpp/src)

add_library(Treesitter ./ThirdParty/tree-sitter/lib/src/lib.c)
target_link_directories(Treesitter PRIVATE
    ./ThirdParty/tree-sitter/lib/src
    ./ThirdParty/tree-sitter/lib/include
)

file(GLOB LibSource
Source/*.cpp 
)

add_executable(${PROJECT_NAME} main.cpp ${LibSource})
target_link_libraries(${PROJECT_NAME} Treesitter TreesitterCPP)