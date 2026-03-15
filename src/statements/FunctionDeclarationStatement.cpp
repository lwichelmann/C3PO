//
// Created by leonw on 15.03.2026.
//

#include "../include/statements/FunctionDeclarationStatement.hpp"
#include "../include/visitor/Visitor.hpp"

FunctionDeclarationStatement::FunctionDeclarationStatement(const std::string& identifier, const std::shared_ptr<BlockStatement>& block_statement) :
m_identifier(identifier), m_blockStatement(block_statement)
{

}

std::string FunctionDeclarationStatement::toString() const
{
    return "FunctionDeclarationStatement";
}

void FunctionDeclarationStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}