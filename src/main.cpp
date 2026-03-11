#include <iostream>
#include "../include/Token.hpp"
#include "../include/Lexer.hpp"
#include "../include/FileUtil.hpp"
#include "../include/Parser.hpp"
#include "../include/visitor/ConcreteInterpreter.hpp"

int main()
{
    auto content = FileUtil::read_file("../src/source.txt");
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
