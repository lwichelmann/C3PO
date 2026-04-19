//
// Created by Leon on 20.04.2026.
//

#ifndef C3PO_PRINTSTATEMENT_HPP
#define C3PO_PRINTSTATEMENT_HPP

#include "Statement.hpp"
#include "../expressions/Expression.hpp"
#include <memory>

class PrintStatement : public Statement {
private:
    std::unique_ptr<Expression> m_expression;

public:
    explicit PrintStatement(std::unique_ptr<Expression> expression);

    [[nodiscard]] Expression* getExpression() const;
    [[nodiscard]] std::string toString() const override;
    void accept(Visitor &visitor) override;
};

#endif //C3PO_PRINTSTATEMENT_HPP
