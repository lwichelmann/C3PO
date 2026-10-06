//
// Created by Leon on 12.04.2026.
//

export module ast:binary_expression;
import std;
import token;
import :visitor;
import :expression;

export class BinaryExpression : public Expression {
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
