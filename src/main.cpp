#include "net/AsioSmokeTest.hpp"
#include <chrono>
#include <iostream>

import std;
import fileutil;
import lexer;
import parser;
import ast;
import interpreter;


int main(int argc, char* argv[])
{
   runAsioSmokeTest();

    std::string filePath = "../src/source.txt";
    bool printAst = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--printAst")
        {
            printAst = true;
        }
        else if (std::filesystem::exists(arg))
        {
            filePath = arg;
        }
        else
        {
            std::cerr << "Warnung: Unbekanntes Argument oder Datei nicht gefunden: " << arg << std::endl;
        }
    }

    auto content = FileUtil::read_file(filePath);
    Lexer lexer(content);
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto program = parser.parse();

    if (printAst)
    {
        std::cout << "\n=== Abstract Syntax Tree ===" << std::endl;
        for (const auto& statement : program->getStatements())
        {
            std::cout << statement->toString() << std::endl;
        }
        std::cout << "============================\n" << std::endl;
    }
    std::filesystem::path absoluteFilePath = std::filesystem::absolute(filePath);
    std::string basePath = absoluteFilePath.parent_path().string();

    ConcreteInterpreter interpreter {basePath};
    program->accept(interpreter);

    interpreter.printVariables();

    return 0;
}
