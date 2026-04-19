#ifndef C3PO_CONCRETEINTERPRETER_HPP
#define C3PO_CONCRETEINTERPRETER_HPP

#include "visitor/Visitor.hpp"
#include <map>
#include <string>

class ConcreteInterpreter : public Visitor {
private:
    std::map<std::string, RuntimeValue> variables;

public:
    void visit(ProgramStatement &stmt) override;
    void visit(VariableDeclarationStatement &stmt) override;
    void visit(ForLoopStatement &stmt) override;
    void visit(BlockStatement &block) override;
    void visit(FunctionDeclarationStatement &stmt) override;
    void visit(PrintStatement &stmt) override;
    
    RuntimeValue visit(LiteralExpression &stmt) override;
    RuntimeValue visit(BinaryExpression &stmt) override;
    RuntimeValue visit(VariableExpression &expr) override;

    void printVariables() const;
};

#endif //C3PO_CONCRETEINTERPRETER_HPP