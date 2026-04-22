//
// Created by leonw on 22.04.2026.
//

#ifndef C3PO_IFSTATEMENT_HPP
#define C3PO_IFSTATEMENT_HPP
#include <memory>

#include "Expression.hpp"
#include "Statement.hpp"

class IfStatement : public Statement
{
    std::unique_ptr<Expression> m_condition;
    std::unique_ptr<Statement> m_thenBranch;
    std::unique_ptr<Statement> m_elseBranch;

public:
    explicit IfStatement(std::unique_ptr<Statement> thenBranch, std::unique_ptr<Statement> elseBranch,
                std::unique_ptr<Expression> condition);
    [[nodiscard]] std::string toString() const override;
    void accept(Visitor &visitor) override;

    [[nodiscard]] Expression& getCondition() const;
    [[nodiscard]] Statement& getThenBranch() const;

    // Da der Else-Block optional ist, brauchen wir diese Prüfung
    [[nodiscard]] bool hasElseBranch() const;
    [[nodiscard]] Statement& getElseBranch() const;;
};

#endif //C3PO_IFSTATEMENT_HPP
