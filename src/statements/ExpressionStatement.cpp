//
// Created by leonw on 04.06.2026.
//

module ast;
import std;

ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expression) : m_expression(std::move(expression))
{

}

Expression* ExpressionStatement::getExpression() const
{
    return m_expression.get();
}

std::string ExpressionStatement::toString() const
{
    return m_expression->toString();
}

void ExpressionStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}
