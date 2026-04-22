//
// Created by Leon on 04.04.2026.
//

#include "../include/expressions/LiteralExpression.hpp"

#include <memory>

LiteralExpression::LiteralExpression(int value) : m_value(value), m_tokenType(TokenType::NUMBER)
{
}

LiteralExpression::LiteralExpression(std::string value) : m_value(value), m_tokenType(TokenType::STRING)
{
}

LiteralExpression::LiteralExpression(bool value) : m_value(value), m_tokenType(value ? TokenType::TRUE_LITERAL : TokenType::FALSE_LITERAL)
{
}


std::string LiteralExpression::toString() const
{
    return std::visit([](auto&& arg) -> std::string
    {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>)
        {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            return "\"" + arg + "\"";
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return arg ? "true" : "false";
        }
        return "unknown";
    }, m_value);
}

TokenType LiteralExpression::getTokenType() const
{
    return m_tokenType;
}

const RuntimeValue& LiteralExpression::getValue() const
{
    return m_value;
}

RuntimeValue LiteralExpression::accept(Visitor& visitor)
{
    return visitor.visit(*this);
}
