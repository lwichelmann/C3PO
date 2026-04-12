//
// Created by Leon on 12.04.2026.
//

#ifndef C3PO_BINARYEXPRESSION_HPP
#define C3PO_BINARYEXPRESSION_HPP
#include <memory>

#include "Expression.hpp"
#include "token/Token.hpp"

class BinaryExpression : public Expression {
private:
    std::unique_ptr<Expression> m_left_expression;
    TokenType m_op;
    std::unique_ptr<Expression> m_right_expression;

public:
    explicit BinaryExpression(TokenType  op,std::unique_ptr<Expression> left_expression,
        std::unique_ptr<Expression> right_expression);
    [[nodiscard]] std::string toString() const override;
    RuntimeValue accept(Visitor &visitor) override;
    TokenType getOperator() const;
    const std::unique_ptr<Expression>& getLeft() const;
    const std::unique_ptr<Expression>& getRight() const;

};

#endif //C3PO_BINARYEXPRESSION_HPP
