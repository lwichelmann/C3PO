//
// Created by leonw on 05.10.2025.
//

#ifndef C3PO_VARIABLEDECLARATIONSTATEMENT_HPP
#define C3PO_VARIABLEDECLARATIONSTATEMENT_HPP
#include <optional>
#include <string>
#include <memory>
#include <variant>
#include "Statement.hpp"
#include "../token/Token.hpp"

class VariableDeclarationStatement : public Statement
{
    std::string m_variableName;
    std::optional<Token> m_initialValue;

public:
    VariableDeclarationStatement(const std::string& name, const Token& value);

    void accept(Visitor& visitor) override;
    const std::string& getVariableName() const;
    const std::optional<Token>& getInitialValue() const;

    std::string toString() const override;
};

#endif //C3PO_VARIABLEDECLARATIONSTATEMENT_HPP
