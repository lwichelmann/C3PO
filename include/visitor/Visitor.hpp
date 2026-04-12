//
// Created by leonw on 27.01.2026.
//

#ifndef C3PO_VISITOR_HPP
#define C3PO_VISITOR_HPP
#include <variant>
#include <string>

using RuntimeValue = std::variant<int,std::string>;

class LiteralExpression;
class FunctionDeclarationStatement;
class VariableDeclarationStatement;
class ForLoopStatement;
class BlockStatement;
class ProgramStatement;

class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(VariableDeclarationStatement& stmt) = 0;
    virtual void visit(ForLoopStatement& stmt) = 0;
    virtual void visit(BlockStatement& stmt) = 0;
    virtual RuntimeValue visit(LiteralExpression& expr) = 0;
    virtual void visit(ProgramStatement& stmt) = 0;
    virtual void visit(FunctionDeclarationStatement& stmt) = 0;
};

#endif //C3PO_VISITOR_HPP
