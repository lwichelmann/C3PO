//
// Created by leonw on 17.01.2026.
//

export module ast:literal_expression;
import std;
import token;
import :visitor;
import :expression;

export class LiteralExpression : public Expression
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
