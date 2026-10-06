//
// Created by leonw on 23.01.2026.
//

export module ast:program_statement;
import std;
import :visitor;
import :statement;

export class ProgramStatement : public Statement
{
    std::vector<std::unique_ptr<Statement>> m_statements;

public:
    explicit ProgramStatement(std::vector<std::unique_ptr<Statement>> statements) : m_statements(std::move(statements))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }

    std::string toString() const override
    {
        std::string result;
        for (const auto& statement : m_statements)
        {
            result += statement->toString() + "\n";
        }
        return result;
    }

    const std::vector<std::unique_ptr<Statement>>& getStatements() const
    {
        return m_statements;
    }
};
