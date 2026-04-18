//
// Created by leonw on 15.03.2026.
//

#include "token/Token.hpp"

#include <algorithm>
#include <string>
/*public:
Token(TokenType type, std::string value)
: m_type(type), m_value(std::move(value))
{
}

Token(TokenType type, int value)
: m_type(type), m_value(value)
{
}

explicit Token(TokenType type)
: m_type(type), m_value("")
{
}*/


Token::Token(TokenType type, std::string value) : m_type(type), m_value(std::move(value))
{
}

Token::Token(TokenType type, int value) : m_type(type), m_value(value)
{
}

Token::Token(TokenType type) : m_type(type), m_value("")
{
}

TokenType Token::getType() const
{
    return m_type;
}

const Token::Value& Token::getValue() const
{
    return m_value;
}

bool Token::isLiteral() const
{
    return m_type == TokenType::NUMBER ||
        m_type == TokenType::STRING ||
        m_type == TokenType::IDENTIFIER;
}

bool Token::isOperator() const
{
    return m_type == TokenType::PLUS ||
        m_type == TokenType::MINUS ||
        m_type == TokenType::EQUALS;
}

std::string Token::typeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::NUMBER: return "NUMBER";
    case TokenType::STRING: return "STRING";

    case TokenType::VAR: return "VAR";
    case TokenType::PRINT: return "PRINT";

    case TokenType::PLUS: return "+";
    case TokenType::MINUS: return "-";
    case TokenType::MULTIPLY: return "*";
    case TokenType::DIVIDE: return "/";
    case TokenType::EQUALS: return "=";

    case TokenType::SEMICOLON: return ";";
    case TokenType::LEFT_PAREN: return "(";
    case TokenType::RIGHT_PAREN: return ")";
    case TokenType::LEFT_BRACE: return "{";
    case TokenType::RIGHT_BRACE: return "}";

    case TokenType::UNKNOWN: return "UNKNOWN";
    case TokenType::END_OF_FILE: return "EOF";

    default: return "UNDEFINED";
    }
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << Token::typeToString(token.m_type) << "('";
    std::visit([&os](const auto& val)
    {
        os << val;
    }, token.m_value);
    os << "')";
    return os;
}
