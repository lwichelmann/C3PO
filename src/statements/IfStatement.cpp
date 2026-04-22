//
// Created by leonw on 22.04.2026.
//

#include "IfStatement.hpp"

#include "Expression.hpp"

IfStatement::IfStatement(std::unique_ptr<Statement> thenBranch, std::unique_ptr<Statement> elseBranch,
                         std::unique_ptr<Expression> condition) :
    m_condition(std::move(condition)),
    m_thenBranch(std::move(thenBranch)),
    m_elseBranch(std::move(elseBranch))
{
}

void IfStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

Expression& IfStatement::getCondition() const {
    return *m_condition;
}

Statement& IfStatement::getThenBranch() const {
    return *m_thenBranch;
}

bool IfStatement::hasElseBranch() const {
    return m_elseBranch != nullptr;
}

Statement& IfStatement::getElseBranch() const {
    if (!m_elseBranch) {
        throw std::runtime_error("Interner Fehler: Else-Block existiert nicht!");
    }
    return *m_elseBranch;
}


std::string IfStatement::toString() const
{
    return "if statement";
}
