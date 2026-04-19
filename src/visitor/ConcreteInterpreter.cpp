//
// Created by Leon on 20.04.2026.
//

#include <iostream>
#include <stdexcept>
#include "../../include/visitor/ConcreteInterpreter.hpp"
#include "../../include/statements/ProgramStatement.hpp"
#include "../../include/statements/VariableDeclarationStatement.hpp"
#include "../../include/statements/ForLoopStatement.hpp"
#include "../../include/statements/BlockStatement.hpp"
#include "../../include/statements/FunctionDeclarationStatement.hpp"
#include "../../include/statements/PrintStatement.hpp"
#include "../../include/expressions/LiteralExpression.hpp"
#include "../../include/expressions/BinaryExpression.hpp"
#include "../../include/expressions/VariableExpression.hpp"

void ConcreteInterpreter::visit(ProgramStatement &stmt) {
    for (const auto &statement: stmt.getStatements()) {
        statement->accept(*this);
    }
}

void ConcreteInterpreter::visit(VariableDeclarationStatement &stmt) {
    auto &expression = stmt.getExpression();
    if (expression) {
        RuntimeValue value = expression->accept(*this);
        variables.emplace(stmt.getVariableName(), value);
    } else {
        std::cout << "Error: expression is null" << std::endl;
    }
}

void ConcreteInterpreter::visit(ForLoopStatement &stmt) {
    std::cout << "Executing for loop..." << std::endl;
    stmt.getBody()->accept(*this);
}

void ConcreteInterpreter::visit(BlockStatement &block) {
    for (const auto &statement: block.getStatements()) {
        statement->accept(*this);
    }
}

RuntimeValue ConcreteInterpreter::visit(LiteralExpression &stmt) {
    return stmt.getValue();
}

RuntimeValue ConcreteInterpreter::visit(BinaryExpression &stmt) {
    auto op = stmt.getOperator();
    auto left = stmt.getLeft()->accept(*this);
    auto right = stmt.getRight()->accept(*this);

    return std::visit([op]<typename L, typename R>(L &&l, R &&r) -> RuntimeValue {
        using TYPE_LEFT = std::decay_t<L>;
        using TYPE_RIGHT = std::decay_t<R>;

        if constexpr (std::is_same_v<TYPE_LEFT, int> && std::is_same_v<TYPE_RIGHT, int>) {
            switch (op) {
                case TokenType::PLUS: return l + r;
                case TokenType::MINUS: return l - r;
                case TokenType::MULTIPLY: return l * r;
                case TokenType::DIVIDE:
                    if (r == 0) throw std::runtime_error("Laufzeitfehler: Division durch Null!");
                    return l / r;
                default:
                    throw std::runtime_error("Laufzeitfehler: Unbekannter Operator für Zahlen.");
            }
        } else if constexpr (std::is_same_v<TYPE_LEFT, std::string> && std::is_same_v<TYPE_RIGHT, std::string>) {
            switch (op) {
                case TokenType::PLUS: return l + r;
                default:
                    throw std::runtime_error("Laufzeitfehler: Strings können nur addiert werden.");
            }
        } else {
            throw std::runtime_error("Laufzeitfehler: Typen stimmen nicht überein (z.B. Zahl + String).");
        }
    }, left, right);
}

void ConcreteInterpreter::visit(FunctionDeclarationStatement &stmt) {

}

void ConcreteInterpreter::visit(PrintStatement &stmt) {
    if (stmt.getExpression()) {
        RuntimeValue value = stmt.getExpression()->accept(*this);
        std::visit([](const auto &val) { std::cout << val << std::endl; }, value);
    }
}

RuntimeValue ConcreteInterpreter::visit(VariableExpression &expr) {
    if (variables.contains(expr.getName())) {
        return variables.at(expr.getName());
    }
    throw std::runtime_error("Laufzeitfehler: Undefinierte Variable '" + expr.getName() + "'.");
}

void ConcreteInterpreter::printVariables() const {
    std::cout << "\n=== Variables ===" << std::endl;
    for (const auto &[name, value]: variables) {
        std::cout << name << " = ";
        std::visit([](const auto &val) { std::cout << val; }, value);
        std::cout << std::endl;
    }
}
