//
// Created by Leon on 12.04.2026.
//

#include "BinaryExpression.hpp"

#include <utility>

BinaryExpression::BinaryExpression(TokenType op, std::unique_ptr<Expression> left_expression,
                                   std::unique_ptr<Expression> right_expression) : m_op(op),
    m_left_expression(std::move(left_expression)),
    m_right_expression(std::move(right_expression)) {
}

std::string BinaryExpression::toString() const {

}

RuntimeValue BinaryExpression::accept(Visitor &visitor) {
    return visitor.visit(*this);
}

TokenType BinaryExpression::getOperator() const {
    return m_op;
}

const std::unique_ptr<Expression> & BinaryExpression::getLeft() const {
    return m_left_expression;
}

const std::unique_ptr<Expression> & BinaryExpression::getRight() const {
    return m_right_expression;
}
