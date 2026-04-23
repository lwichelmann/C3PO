//
// Created by leonw on 15.03.2026.
//

#include "token/Token.hpp"

#include <algorithm>
#include <string>

Token::Token(TokenType type, std::string value, size_t lineNumber, size_t columnNumber, size_t length) : m_type(type),
    m_value(std::move(value)),
    m_lineNumber(lineNumber), m_columnNumber(columnNumber), m_length(length)
{
}

Token::Token(TokenType type, int value, size_t lineNumber, size_t columnNumber, size_t length) : m_type(type),
    m_value(value),
    m_lineNumber(lineNumber), m_columnNumber(columnNumber), m_length(length)
{
}

Token::Token(TokenType type, size_t lineNumber, size_t columnNumber, size_t length) : m_type(type), m_value(""),
    m_lineNumber(lineNumber),
    m_columnNumber(columnNumber),
    m_length(length)

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

size_t Token::getLineNumber() const
{
    return m_lineNumber;
}

size_t Token::getColumnNumber() const
{
    return m_columnNumber;
}

size_t Token::getLength() const
{
    return m_length;
}

std::string Token::typeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::NUMBER: return "NUMBER";
    case TokenType::STRING: return "STRING";
    case TokenType::TRUE_LITERAL: return "TRUE";
    case TokenType::FALSE_LITERAL: return "FALSE";
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
