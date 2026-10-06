//
// Created by Leon on 20.04.2026.
//

module ast;
import std;

VariableExpression::VariableExpression(std::string name)
    : m_name(std::move(name)) {
}

const std::string& VariableExpression::getName() const {
    return m_name;
}

std::string VariableExpression::toString() const {
    return "VariableExpression(" + m_name + ")";
}

RuntimeValue VariableExpression::accept(Visitor& visitor) {
    return visitor.visit(*this);
}
