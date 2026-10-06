//
// Created by leonw on 17.01.2026.
//

export module ast:for_loop_statement;
import std;
import :visitor;
import :statement;
import :block_statement;

export class ForLoopStatement : public Statement {
    std::unique_ptr<BlockStatement> m_body;

public:
    explicit ForLoopStatement(std::unique_ptr<BlockStatement> body);

    void accept(Visitor &visitor) override;

    [[nodiscard]] virtual std::string toString() const override;

    std::unique_ptr<BlockStatement> &getBody();
};
