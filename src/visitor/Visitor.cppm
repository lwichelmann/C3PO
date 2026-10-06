//
// Created by leonw on 27.01.2026.
//

export module ast:visitor;
import std;

export class FunctionCallExpression;
export using RuntimeValue = std::variant<int, std::string, bool>;

export class LiteralExpression;
export class FunctionDeclarationStatement;
export class VariableDeclarationStatement;
export class ForLoopStatement;
export class BlockStatement;
export class ProgramStatement;
export class BinaryExpression;
export class VariableExpression;
export class PrintStatement;
export class IfStatement;
export class ExpressionStatement;
export class ImportStatement;

export class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit(VariableDeclarationStatement &stmt) = 0;

    virtual void visit(ForLoopStatement &stmt) = 0;

    virtual void visit(BlockStatement &stmt) = 0;

    virtual void visit(ProgramStatement &stmt) = 0;

    virtual void visit(FunctionDeclarationStatement &stmt) = 0;
    virtual RuntimeValue visit(FunctionCallExpression &expr) = 0;

    virtual RuntimeValue visit(LiteralExpression &expr) = 0;

    virtual RuntimeValue visit(BinaryExpression &stmt) = 0;

    virtual void visit(PrintStatement &stmt) = 0;

    virtual RuntimeValue visit(VariableExpression &expr) = 0;
    virtual void visit(IfStatement &stmt) = 0;
    virtual void visit(ExpressionStatement &stmt) = 0;
    virtual void visit(ImportStatement &stmt) = 0;
};
