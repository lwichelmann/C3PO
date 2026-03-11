//
// Created by leonw on 08.03.2026.
//
#include "statements/BlockStatement.hpp"


void BlockStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

std::string BlockStatement::toString() const
{
    std::string result;
    result += "{";
    for (auto& statement : statements)
    {
        result += statement->toString();
    }
    result += "}";
    return result;
}

const std::vector<std::unique_ptr<Statement>>& BlockStatement::getStatements() const
{
    return statements;
}
