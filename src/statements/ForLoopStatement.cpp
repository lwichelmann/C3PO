//
// Created by leonw on 11.03.2026.
//

module ast;
import std;

ForLoopStatement::ForLoopStatement(std::unique_ptr<BlockStatement> body) : m_body(std::move(body))
{
}

std::string ForLoopStatement::toString() const
{
    return m_body->toString();
}

void ForLoopStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

std::unique_ptr<BlockStatement>& ForLoopStatement::getBody()
{
    return m_body;
}
