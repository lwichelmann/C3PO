//
// Created by leonw on 19.01.2026.
//

export module ast:block_statement;
import std;
import :visitor;
import :statement;

export class BlockStatement: public Statement
{
    std::vector<std::unique_ptr<Statement>> statements;

public:
    explicit BlockStatement(std::vector<std::unique_ptr<Statement>> statements);
    void accept(Visitor& visitor) override;
    std::string toString() const override;
    const std::vector<std::unique_ptr<Statement>>& getStatements() const;
};
