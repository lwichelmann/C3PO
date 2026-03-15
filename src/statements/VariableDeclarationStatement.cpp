//
// Created by leonw on 05.10.2025.
//

#include "../../include/statements/VariableDeclarationStatement.hpp"

VariableDeclarationStatement::VariableDeclarationStatement(const std::string& name,const Token& value) :
    m_variableName(name),
    m_initialValue(value)
{
}

void VariableDeclarationStatement::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

const std::string& VariableDeclarationStatement::getVariableName() const
{
    return m_variableName;
}

const std::optional<Token>& VariableDeclarationStatement::getInitialValue() const
{
    return m_initialValue;
}

std::string VariableDeclarationStatement::toString() const
{
    std::string valueStr = "null";

    if (m_initialValue.has_value())
    {
        const Token& token = m_initialValue.value();

        std::visit([&valueStr](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, int>)
            {
                valueStr = std::to_string(val);
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                valueStr = "\"" + val + "\"";
            }
        }, token.getValue());
    }
    return "VariableDeclarationStatement(" + m_variableName + " = " + valueStr + ")";
}
