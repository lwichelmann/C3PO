//
// Created by Leon on 20.04.2026.
//

export module ast:variable_expression;
import std;
import :visitor;
import :expression;

export class VariableExpression : public Expression {
private:
    std::string m_name;

public:
    explicit VariableExpression(std::string name);

    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] std::string toString() const override;
    RuntimeValue accept(Visitor& visitor) override;
};
