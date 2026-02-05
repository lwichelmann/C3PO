//
// Created by leonw on 27.01.2026.
//

// include/Interpreter.hpp
#ifndef C3PO_VISTOR_HPP
#define C3PO_VISTOR_HPP

#include <map>
#include <variant>
#include <string>
#include <iostream>

#include "vistor/Visitor.hpp"

#include "statements/ForLoopStatement.hpp"
#include "statements/VariableDeclarationStatement.hpp"
#include "vistor/Visitor.hpp"
#include "statements/BlockStatement.hpp"

class ConcreteInterpreter : public Visitor
{
    std::map<std::string, std::variant<int, std::string>> variables;

public:
    void visit(VariableDeclarationStatement& stmt) override {

    }

    void visit(ForLoopStatement& stmt) override {
        std::cout << "Executing for loop..." << std::endl;
        stmt.getBody()->accept(*this);
    }

    void visit(BlockStatement& stmt) override {
        for (const auto& statement : stmt.getStatements()) {
            statement->accept(*this); // Jedes Statement besuchen
        }
    }

    void visit(ExpressionStatement& stmt) override {
        // Noch nicht implementiert
    }

    // Für Debugging
    void printVariables() const {
        std::cout << "\n=== Variables ===" << std::endl;
        for (const auto& [name, value] : variables) {
            std::cout << name << " = ";
            std::visit([](const auto& val) { std::cout << val; }, value);
            std::cout << std::endl;
        }
    }
};

#endif


