//
// Created by Leon on 20.04.2026.
//

#include "statements/PrintStatement.hpp"

PrintStatement::PrintStatement(std::unique_ptr<Expression> expression)
    : m_expression(std::move(expression)) {
}

Expression *PrintStatement::getExpression() const {
    return m_expression.get();
}

std::string PrintStatement::toString() const {
    return "PrintStatement";
}

void PrintStatement::accept(Visitor &visitor) {
    visitor.visit(*this);
}
