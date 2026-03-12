#include <filesystem>
#include <iostream>
#include "../include/Token.hpp"
#include "../include/Lexer.hpp"
#include "../include/FileUtil.hpp"
#include "../include/Parser.hpp"
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
    auto programm = parser.parse();

    for (const auto& statement : programm->getStatements())
    {
        std::cout << statement->toString() << std::endl;
    }

    ConcreteInterpreter interpreter;
    programm->accept(interpreter);

    interpreter.printVariables();

    return 0;
}
