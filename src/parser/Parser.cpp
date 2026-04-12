//
// Created by leonw on 05.10.2025.
//

#include "../../include/parser/Parser.hpp"

#include <iostream>

#include "FunctionDeclarationStatement.hpp"
#include "LiteralExpression.hpp"
#include "../../include/statements/VariableDeclarationStatement.hpp"
#include "statements/ForLoopStatement.hpp"
#include "statements/ProgramStatement.hpp"

std::unique_ptr<BlockStatement> Parser::parseBlockStatement()
{
    std::vector<std::unique_ptr<Statement>> statements;

    consume(TokenType::LEFT_BRACE);

    while (currentToken().getType() != TokenType::RIGHT_BRACE &&
        currentToken().getType() != TokenType::END_OF_FILE)
    {
        // TODO hier alle möglichen Statements abfragen
        if (currentToken().getType() == TokenType::VAR)
        {
            statements.push_back(parseVariableStatement());
        }
        else
        {
            throw std::runtime_error("Unexpected token in block");
        }
    }
    consume(TokenType::RIGHT_BRACE);

    return std::make_unique<BlockStatement>(std::move(statements));
}

std::unique_ptr<Expression> Parser::parseExpression() {
    return parsePrimary();
}

std::unique_ptr<Expression> Parser::parsePrimary() {
    auto current = currentToken();
    auto tokenType = current.getType();

    auto value = current.getValue();

    if (tokenType == TokenType::NUMBER) {
        consume(TokenType::NUMBER);
        return std::make_unique<LiteralExpression>(std::get<int>(value));
    }else if (tokenType == TokenType::STRING) {
        consume(TokenType::STRING);
        return std::make_unique<LiteralExpression>(std::get<std::string>(value));
    }
}

std::unique_ptr<ProgramStatement> Parser::parse()
{
    std::unique_ptr<BlockStatement> blockStatement = nullptr;

    std::vector<std::unique_ptr<Statement>> statements;
    std::cout << "started parsing ProgramStatement" << std::endl;

    while (currentToken().getType() != TokenType::END_OF_FILE)
    {
        if (currentToken().getType() == TokenType::FOR_LOOP)
        {
            consume(TokenType::FOR_LOOP);

            blockStatement = parseBlockStatement();
        }

        // TODO hier weitere möglichen Statements parsen

        else if (currentToken().getType() == TokenType::VAR)
        {
            statements.push_back(parseVariableStatement());
        }else if (currentToken().getType() == TokenType::FUNCTION)
        {
            statements.push_back(parseFunctionDeclarationStatement());
        }
    }

    if (!blockStatement)
    {
        // throw std::runtime_error("No for loop body found");
    }

    std::cout << "finished parsing..." << std::endl;
    return std::make_unique<ProgramStatement>(std::move(statements));
}

Token Parser::peek()
{
    if (m_current + 1 >= m_tokens.size())
    {
        throw std::runtime_error("Unexpected end of file can not peek anymore");
    }
    return m_tokens.at(m_current + 1);
}

Token Parser::consume(TokenType type)
{
    Token token = currentToken();

    if (type != TokenType::END_OF_FILE && token.getType() != type)
    {
        throw std::runtime_error(
            "Expected token type " + Token::typeToString(type) + " but got " + Token::typeToString(token.getType()));
    }
    m_current++;
    return token;
}

Token Parser::currentToken()
{
    return m_tokens.at(m_current);
}

std::unique_ptr<Statement> Parser::parseVariableStatement()
{
    consume(TokenType::VAR);
    Token tokenIdentifier = consume(TokenType::IDENTIFIER);
    consume(TokenType::EQUALS);
/*
    Token valueToken = currentToken();

    std::unique_ptr<Expression> initializer = nullptr;

    if (valueToken.getType() == TokenType::NUMBER)
    {
        int val = std::get<int>(valueToken.getValue());
        consume(TokenType::NUMBER);
        initializer = std::make_unique<LiteralExpression>(val);
    }
    else if (valueToken.getType() == TokenType::STRING)
    {
        std::string val = std::get<std::string>(valueToken.getValue());
        consume(TokenType::STRING);
        initializer = std::make_unique<LiteralExpression>(val);
    }
    else
    {
        throw std::runtime_error("Erwarte NUMBER oder STRING für LiteralExpression");
    }*/

    auto initializer = parseExpression();

    consume(TokenType::SEMICOLON);

    std::string identifierString = std::get<std::string>(tokenIdentifier.getValue());
    return std::make_unique<VariableDeclarationStatement>(identifierString, std::move(initializer));
}

std::unique_ptr<FunctionDeclarationStatement> Parser::parseFunctionDeclarationStatement()
{
    std::unique_ptr<BlockStatement> blockStatement = nullptr;


    consume(TokenType::FUNCTION);
    Token functionNameToken = consume(TokenType::IDENTIFIER);
    consume(TokenType::LEFT_PAREN);
    consume(TokenType::RIGHT_PAREN);
    std::unique_ptr<BlockStatement> statement = nullptr;

    std::string functionName = std::get<std::string>(functionNameToken.getValue());
    while (currentToken().getType() != TokenType::END_OF_FILE && currentToken().getType() != TokenType::RIGHT_BRACE)
    {
        blockStatement = parseBlockStatement();
    }

    if (!blockStatement)
    {

    }

    return std::make_unique<FunctionDeclarationStatement>(std::move(functionName),std::move(blockStatement));
}
