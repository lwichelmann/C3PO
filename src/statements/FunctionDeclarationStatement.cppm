//
// Created by leonw on 15.03.2026.
//

export module ast:function_declaration_statement;
import std;
import :visitor;
import :statement;
import :block_statement;

export class FunctionDeclarationStatement: public Statement
{
public:
    explicit FunctionDeclarationStatement(const std::string& functionName, const std::shared_ptr<BlockStatement>& block_statement);
    void accept(Visitor& visitor) override;

    ~FunctionDeclarationStatement() override = default;
    std::string toString() const override;
    std::string getFunctionName() const;
    std::shared_ptr<BlockStatement> getBlockStatement() const;

private:
    std::string m_functionName;
    std::shared_ptr<BlockStatement> m_blockStatement;

};
