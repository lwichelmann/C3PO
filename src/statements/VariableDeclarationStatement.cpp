//
// Created by leonw on 05.10.2025.
//

#include "../../include/statements/VariableDeclarationStatement.hpp"

VariableDeclarationStatement::VariableDeclarationStatement(const std::string& name, std::unique_ptr<Expression> m_initializer) :
    m_variableName(name),
    m_initializer(std::move(m_initializer))
{
}

void VariableDeclarationStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

const std::string& VariableDeclarationStatement::getVariableName() const
{
    return m_variableName;
}

const std::unique_ptr<Expression>& VariableDeclarationStatement::getExpression() const {
    return m_initializer;
}


std::string VariableDeclarationStatement::toString() const
{
    std::string value = m_initializer ? m_initializer->toString() : "uninitialized";
    return "VariableDeclarationStatement(" + m_variableName + " = " + value + ")";
}


