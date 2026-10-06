//
// Created by leonw on 05.10.2025.
//

export module ast:variable_declaration_statement;
import std;
import :visitor;
import :statement;
import :expression;

export class VariableDeclarationStatement : public Statement
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
