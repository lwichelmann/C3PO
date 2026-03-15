//
// Created by leonw on 11.03.2026.
//

#ifndef C3PO_CONCRETEINTERPRETER_HPP
#define C3PO_CONCRETEINTERPRETER_HPP
#include "visitor/Visitor.hpp"
#include "statements/BlockStatement.hpp"
#include "statements/ForLoopStatement.hpp"
#include "statements/VariableDeclarationStatement.hpp"
#include "statements/ProgramStatement.hpp"
#include <map>
#include <variant>
#include <string>
#include <iostream>
class ConcreteInterpreter : public Visitor
{
    std::map<std::string, std::variant<int, std::string>> variables;
public:
    void visit(ProgramStatement& stmt) override {
        for (const auto& statement : stmt.getStatements()) {
            statement->accept(*this);
        }
    }
    void visit(VariableDeclarationStatement& stmt) override
    {
        if (stmt.getInitialValue().has_value()) {
            variables.emplace(stmt.getVariableName(), stmt.getInitialValue().value().getValue());
        }
    }
    void visit(ForLoopStatement& stmt) override {
        std::cout << "Executing for loop..." << std::endl;
        stmt.getBody()->accept(*this);
    }
    void visit(BlockStatement& block) override {
        for (const auto& statement : block.getStatements()) {
            statement->accept(*this);
        }
    }
    void visit(ExpressionStatement& stmt) override { }
    void visit(FunctionDeclarationStatement& stmt) override
    {

    }
    void printVariables() const {
        std::cout << "\n=== Variables ===" << std::endl;
        for (const auto& [name, value] : variables) {
            std::cout << name << " = ";
            std::visit([](const auto& val) { std::cout << val; }, value);
            std::cout << std::endl;
        }
    }
};

#endif //C3PO_CONCRETEINTERPRETER_HPP
