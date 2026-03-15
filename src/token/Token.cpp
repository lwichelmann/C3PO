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


    case TokenType::VAR: return "VAR";
    case TokenType::PRINT: return "PRINT";

    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::EQUALS: return "EQUALS";

    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::LEFT_PAREN: return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
    case TokenType::LEFT_BRACE: return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";

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


/*

class Token
{
public:
using Value = std::variant<int, std::string>;

private:
TokenType m_type;
Value m_value;

public:
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
}


TokenType getType() const { return m_type; }
const Value& getValue() const { return m_value; }

bool isLiteral() const
{
return m_type == TokenType::NUMBER ||
m_type == TokenType::STRING ||
m_type == TokenType::IDENTIFIER;
}

bool isOperator() const
{
return m_type == TokenType::PLUS ||
m_type == TokenType::MINUS ||
m_type == TokenType::EQUALS;
}

static std::string typeToString(TokenType type);

friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

#endif //C3PO_TOKEN_HPPenum class TokenType
{
IDENTIFIER,
NUMBER,
STRING,

VAR,
PRINT,
FOR_LOOP,

PLUS,
MINUS,
EQUALS,

SEMICOLON,
LEFT_PAREN,
RIGHT_PAREN,
LEFT_BRACE,
RIGHT_BRACE,
FUNCTION,
UNKNOWN,
END_OF_FILE,
};

class Token
{
public:
using Value = std::variant<int, std::string>;

private:
TokenType m_type;
Value m_value;

public:
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
}


TokenType getType() const { return m_type; }
const Value& getValue() const { return m_value; }

bool isLiteral() const
{
return m_type == TokenType::NUMBER ||
m_type == TokenType::STRING ||
m_type == TokenType::IDENTIFIER;
}

bool isOperator() const
{
return m_type == TokenType::PLUS ||
m_type == TokenType::MINUS ||
m_type == TokenType::EQUALS;
}

static std::string typeToString(TokenType type);

friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

#endif //C3PO_TOKEN_HPP
*/
