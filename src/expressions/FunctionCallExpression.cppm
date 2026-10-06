//
// Created by leonw on 07.05.2026.
//

export module ast:function_call_expression;
import std;
import :visitor;
import :expression;

export class FunctionCallExpression: public Expression
{
    std::string m_functionName;

public:
    explicit FunctionCallExpression(std::string functionName);

    [[nodiscard]] std::string toString() const override;
    RuntimeValue accept(Visitor& visitor) override;
    [[nodiscard]] const std::string& getFunctionName() const;
};
