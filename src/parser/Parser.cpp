//
// Created by leonw on 05.10.2025.
//

#include "../../include/parser/Parser.hpp"

#include <iostream>

#include "BinaryExpression.hpp"
#include "FunctionDeclarationStatement.hpp"
#include "LiteralExpression.hpp"
#include "../../include/statements/VariableDeclarationStatement.hpp"
#include "statements/ForLoopStatement.hpp"
#include "statements/ProgramStatement.hpp"
#include "../../include/statements/PrintStatement.hpp"
#include "VariableExpression.hpp"

std::unique_ptr<BlockStatement> Parser::parseBlockStatement() {
    std::vector<std::unique_ptr<Statement> > statements;

    consume(TokenType::LEFT_BRACE);

    while (currentToken().getType() != TokenType::RIGHT_BRACE &&
           currentToken().getType() != TokenType::END_OF_FILE) {
        if (currentToken().getType() == TokenType::VAR) {
            statements.push_back(parseVariableStatement());
        } else if (currentToken().getType() == TokenType::PRINT) {
            statements.push_back(parsePrintStatement());
        } else {
            throw std::runtime_error("Unexpected token in block");
        }
    }
    consume(TokenType::RIGHT_BRACE);

    return std::make_unique<BlockStatement>(std::move(statements));
}

std::unique_ptr<Expression> Parser::parseExpression() {
    auto left = parseTerm();

    while (true) {
        auto type = currentToken().getType();

        if (type != TokenType::PLUS && type != TokenType::MINUS)
            break;

        consume(type);
        auto right = parseTerm();

        left = std::make_unique<BinaryExpression>(
            type,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

std::unique_ptr<Expression> Parser::parseTerm() {
    auto left = parsePrimary();

    while (true) {
        auto type = currentToken().getType();

        if (type != TokenType::MULTIPLY && type != TokenType::DIVIDE)
            break;

        consume(type);
        auto right = parsePrimary();

        left = std::make_unique<BinaryExpression>(
            type,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

std::unique_ptr<Expression> Parser::parsePrimary() {
    auto token = currentToken();

    if (token.getType() == TokenType::NUMBER) {
        consume(TokenType::NUMBER);
        return std::make_unique<LiteralExpression>(std::get<int>(token.getValue()));
    }

    if (token.getType() == TokenType::STRING) {
        consume(TokenType::STRING);
        return std::make_unique<LiteralExpression>(std::get<std::string>(token.getValue()));
    }

    if (token.getType() == TokenType::TRUE_LITERAL)
    {
        consume(TokenType::TRUE_LITERAL);
        return std::make_unique<LiteralExpression>(true);
    }

    if (token.getType() == TokenType::FALSE_LITERAL)
    {
        consume(TokenType::FALSE_LITERAL);
        return std::make_unique<LiteralExpression>(false);
    }

    if (token.getType() == TokenType::IDENTIFIER) {
        consume(TokenType::IDENTIFIER);
        return std::make_unique<VariableExpression>(std::get<std::string>(token.getValue()));
    }

    if (token.getType() == TokenType::LEFT_PAREN) {
        consume(TokenType::LEFT_PAREN);
        auto expr = parseExpression();
        consume(TokenType::RIGHT_PAREN);
        return expr;
    }

    throw std::runtime_error("Unexpected token in parsePrimary");
}

std::unique_ptr<ProgramStatement> Parser::parse() {
    std::unique_ptr<BlockStatement> blockStatement = nullptr;

    std::vector<std::unique_ptr<Statement> > statements;

    while (currentToken().getType() != TokenType::END_OF_FILE) {
        if (currentToken().getType() == TokenType::LEFT_BRACE) {
            statements.push_back(parseBlockStatement());
        }

        if (currentToken().getType() == TokenType::FOR_LOOP) {
            consume(TokenType::FOR_LOOP);

            blockStatement = parseBlockStatement();
        }

        // TODO hier weitere möglichen Statements parsen

        else if (currentToken().getType() == TokenType::VAR) {
            statements.push_back(parseVariableStatement());
        }else if (currentToken().getType() == TokenType::PRINT) {
            statements.push_back(parsePrintStatement());
        } else if (currentToken().getType() == TokenType::FUNCTION) {
            statements.push_back(parseFunctionDeclarationStatement());
        }
    }

    if (!blockStatement) {
        // throw std::runtime_error("No for loop body found");
    }

    return std::make_unique<ProgramStatement>(std::move(statements));
}

Token Parser::peek() {
    if (m_current + 1 >= m_tokens.size()) {
        throw std::runtime_error("Unexpected end of file can not peek anymore");
    }
    return m_tokens.at(m_current + 1);
}

Token Parser::consume(TokenType type) {
    Token token = currentToken();

    if (type != TokenType::END_OF_FILE && token.getType() != type) {
        throw std::runtime_error(
            "Expected token type " + Token::typeToString(type) + " but got " + Token::typeToString(token.getType()));
    }
    m_current++;
    return token;
}

Token Parser::currentToken() {
    return m_tokens.at(m_current);
}

std::unique_ptr<Statement> Parser::parseVariableStatement() {
    consume(TokenType::VAR);
    Token tokenIdentifier = consume(TokenType::IDENTIFIER);
    consume(TokenType::EQUALS);

    auto initializer = parseExpression();

    consume(TokenType::SEMICOLON);

    std::string identifierString = std::get<std::string>(tokenIdentifier.getValue());
    return std::make_unique<VariableDeclarationStatement>(identifierString, std::move(initializer));
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
    consume(TokenType::PRINT);
    consume(TokenType::LEFT_PAREN);

    auto expression = parseExpression();

    consume(TokenType::RIGHT_PAREN);
    consume(TokenType::SEMICOLON);

    return std::make_unique<PrintStatement>(std::move(expression));
}

std::unique_ptr<FunctionDeclarationStatement> Parser::parseFunctionDeclarationStatement() {
    std::unique_ptr<BlockStatement> blockStatement = nullptr;


    consume(TokenType::FUNCTION);
    Token functionNameToken = consume(TokenType::IDENTIFIER);
    consume(TokenType::LEFT_PAREN);
    consume(TokenType::RIGHT_PAREN);
    std::unique_ptr<BlockStatement> statement = nullptr;

    std::string functionName = std::get<std::string>(functionNameToken.getValue());
    while (currentToken().getType() != TokenType::END_OF_FILE && currentToken().getType() != TokenType::RIGHT_BRACE) {
        blockStatement = parseBlockStatement();
    }

    if (!blockStatement) {
    }

    return std::make_unique<FunctionDeclarationStatement>(std::move(functionName), std::move(blockStatement));
}
