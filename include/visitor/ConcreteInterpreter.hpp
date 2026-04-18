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

#include "BinaryExpression.hpp"
#include "LiteralExpression.hpp"

class ConcreteInterpreter : public Visitor {
    std::map<std::string, RuntimeValue> variables;

public:
    void visit(ProgramStatement &stmt) override {
        for (const auto &statement: stmt.getStatements()) {
            statement->accept(*this);
        }
    }

    void visit(VariableDeclarationStatement &stmt) override {
        auto &expression = stmt.getExpression();

        if (expression) {
            RuntimeValue value = expression->accept(*this);
            variables.emplace(stmt.getVariableName(), value);
        } else {
            std::cout << "Error: expression is null" << std::endl;
        }
    }

    void visit(ForLoopStatement &stmt) override {
        std::cout << "Executing for loop..." << std::endl;
        stmt.getBody()->accept(*this);
    }

    void visit(BlockStatement &block) override {
        for (const auto &statement: block.getStatements()) {
            statement->accept(*this);
        }
    }

    RuntimeValue visit(LiteralExpression &stmt) override {
        return stmt.getValue();
    }

    RuntimeValue visit(BinaryExpression &stmt) override {
        auto op = stmt.getOperator();
        auto left = stmt.getLeft()->accept(*this);
        auto right = stmt.getRight()->accept(*this);

        return std::visit([op]<typename L, typename R>(L &&l, R &&r) -> RuntimeValue {
            using TYPE_LEFT_EXPRESSION = std::decay_t<L>;
            using TYPE_RIGHT_EXPRESSION = std::decay_t<R>;

            if constexpr (std::is_same_v<TYPE_LEFT_EXPRESSION, int> && std::is_same_v<TYPE_RIGHT_EXPRESSION, int>) {
                switch (op) {
                    case TokenType::PLUS: return l + r;
                    case TokenType::MINUS: return l - r;
                    case TokenType::MULTIPLY: return l * r;
                    case TokenType::DIVIDE:
                        if (r == 0) {
                            throw std::runtime_error("Laufzeitfehler: Division durch Null!");
                        }
                        return l / r;
                    default:
                        throw std::runtime_error("Laufzeitfehler: Unbekannter Operator für Zahlen.");
                }
            } else if constexpr (std::is_same_v<TYPE_LEFT_EXPRESSION, std::string> && std::is_same_v<
                                     TYPE_RIGHT_EXPRESSION, std::string>) {
                switch (op) {
                    case TokenType::PLUS:
                        return l + r;
                    default:
                        throw std::runtime_error(
                            "Laufzeitfehler: Strings koennen nur addiert (+), nicht subtrahiert oder multipliziert werden.");
                }
            } else {
                throw std::runtime_error("Laufzeitfehler: Typen stimmen nicht ueberein (z.B. Zahl + String).");
            }
        }, left, right);
    }

    void visit(FunctionDeclarationStatement &stmt) override {
    }

    void printVariables() const {
        std::cout << "\n=== Variables ===" << std::endl;
        for (const auto &[name, value]: variables) {
            std::cout << name << " = ";
            std::visit([](const auto &val) { std::cout << val; }, value);
            std::cout << std::endl;
        }
    }
};

#endif //C3PO_CONCRETEINTERPRETER_HPP
