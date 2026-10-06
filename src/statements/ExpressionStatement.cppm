//
// Created by leonw on 04.06.2026.
//

export module ast:expression_statement;
import std;
import :visitor;
import :statement;
import :expression;

export class ExpressionStatement : public Statement {
private:
    std::unique_ptr<Expression> m_expression;
public:
    explicit ExpressionStatement(std::unique_ptr<Expression> expression);
    [[nodiscard]] Expression* getExpression() const;
    void accept(Visitor& visitor) override;
    [[nodiscard]] std::string toString() const override;
};
