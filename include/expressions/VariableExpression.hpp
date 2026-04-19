//
// Created by Leon on 20.04.2026.
//

#ifndef C3PO_VARIABLEEXPRESSION_HPP
#define C3PO_VARIABLEEXPRESSION_HPP

#include "Expression.hpp"
#include <string>

#include "Expression.hpp"
#include <string>

class VariableExpression : public Expression {
private:
    std::string m_name;

public:
    explicit VariableExpression(std::string name);

    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] std::string toString() const override;
    RuntimeValue accept(Visitor& visitor) override;
};

#endif //C3PO_VARIABLEEXPRESSION_HPP
