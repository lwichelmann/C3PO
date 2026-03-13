cmake_minimum_required(VERSION 3.26)
project(C3PO)

set(CMAKE_CXX_STANDARD 26)

add_executable(C3PO
        src/main.cpp
        src/Lexer.cpp
        src/Token.cpp
        src/Parser.cpp
        src/statements/VariableDeclarationStatement.cpp
        src/statements/Statement.cpp
        src/visitor/Visitor.cpp
        src/statements/BlockStatement.cpp
        src/fileutil/FileUtil.cpp
)


target_include_directories(C3PO PUBLIC include/expressions)

target_include_directories(C3PO PUBLIC include/statements)

target_include_directories(C3PO PUBLIC include/visitor)
target_include_directories(C3PO PUBLIC include)

if(MINGW)
    target_link_options(C3PO PRIVATE -static)
endif()