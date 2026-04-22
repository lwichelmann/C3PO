//
// Created by leonw on 19.01.2026.
//

#ifndef C3PO_BLOCKSTATEMENT_HPP
#define C3PO_BLOCKSTATEMENT_HPP
#include <memory>
#include <vector>

#include "Statement.hpp"
#include "Visitor.hpp"

class BlockStatement: public Statement
{
    std::vector<std::unique_ptr<Statement>> statements;

public:
    explicit BlockStatement(std::vector<std::unique_ptr<Statement>> statements);
    void accept(Visitor& visitor) override;
    std::string toString() const override;
    const std::vector<std::unique_ptr<Statement>>& getStatements() const;
};

#endif //C3PO_BLOCKSTATEMENT_HPP