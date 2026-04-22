//
// Created by leonw on 05.10.2025.
//

#ifndef C3PO_VARIABLEDECLARATIONSTATEMENT_HPP
#define C3PO_VARIABLEDECLARATIONSTATEMENT_HPP
#include <optional>
#include <string>
#include <memory>
#include <variant>

#include "Expression.hpp"
#include "Statement.hpp"
#include "../token/Token.hpp"

class VariableDeclarationStatement : public Statement
{
    std::string m_variableName;
    std::unique_ptr<Expression> m_initializer;

public:
    explicit VariableDeclarationStatement(const std::string& name, std::unique_ptr<Expression> m_initializer);

    void accept(Visitor& visitor) override;
    const std::string& getVariableName() const;
    const std::unique_ptr<Expression>& getExpression() const;
    std::string toString() const override;
};

#endif //C3PO_VARIABLEDECLARATIONSTATEMENT_HPP
