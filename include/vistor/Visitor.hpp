//
// Created by leonw on 27.01.2026.
//

#ifndef C3PO_VISTOR_HPP
#define C3PO_VISTOR_HPP
#include "expressions/ExpressionStatement.hpp"
#include "statements/ForLoopStatement.hpp"
#include "statements/VariableDeclarationStatement.hpp"
#include "statements/BlockStatement.hpp"


class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(VariableDeclarationStatement& stmt) = 0;
    virtual void visit(ForLoopStatement& stmt) = 0;
    virtual void visit(BlockStatement& stmt) = 0;
    virtual void visit(ExpressionStatement& stmt) = 0;
};

#endif //C3PO_VISTOR_HPP
