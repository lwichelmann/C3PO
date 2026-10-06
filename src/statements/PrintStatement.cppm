//
// Created by Leon on 20.04.2026.
//

export module ast:print_statement;
import std;
import :visitor;
import :statement;
import :expression;

export class PrintStatement : public Statement {
private:
    std::unique_ptr<Expression> m_expression;

public:
    explicit PrintStatement(std::unique_ptr<Expression> expression);

    [[nodiscard]] Expression* getExpression() const;
    [[nodiscard]] std::string toString() const override;
    void accept(Visitor &visitor) override;
};
