//
// Created by leonw on 17.01.2026.
//

#ifndef C3PO_LITERALEXPRESSION_HPP
#define C3PO_LITERALEXPRESSION_HPP

#include <string>

#include "Expression.hpp"
#include "variant"
#include "token/Token.hpp"
#include "visitor/Visitor.hpp"

class LiteralExpression : public Expression
{
private:
    std::variant<int, std::string, bool> m_value{};
    TokenType m_tokenType;

public:
    explicit LiteralExpression(int value);
    explicit LiteralExpression(std::string value);
    explicit LiteralExpression(bool value);
    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] const RuntimeValue& getValue() const;
    [[nodiscard]] TokenType getTokenType() const;

    RuntimeValue accept(Visitor& visitor) override;
};

#endif //C3PO_LITERALEXPRESSION_HPP
