#include <filesystem>
#include <iostream>
#include "../include/fileutil/FileUtil.hpp"
#include "../include/token/Token.hpp"
#include "../include/lexer/Lexer.hpp"
#include "../include/parser/Parser.hpp"
#include "../include/visitor/ConcreteInterpreter.hpp"

int main(int argc, char* argv[])
{
    std::string filePath = "../src/source.txt";
    if (argc > 1 && std::filesystem::exists(argv[1]))
    {
        filePath = argv[1];
    }

    auto content = FileUtil::read_file(filePath);
    Lexer lexer(content);
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto program = parser.parse();

    for (const auto& statement : program->getStatements())
    {
        std::cout << statement->toString() << std::endl;
    }

    ConcreteInterpreter interpreter;
    program->accept(interpreter);

    interpreter.printVariables();

    return 0;
}
