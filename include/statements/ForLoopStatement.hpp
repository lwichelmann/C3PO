//
// Created by leonw on 17.01.2026.
//

#ifndef C3PO_FORLOOPSTATEMENT_HPP
#define C3PO_FORLOOPSTATEMENT_HPP
#include <memory>
#include <vector>
#include <string>

#include "BlockStatement.hpp"
#include "Statement.hpp"

class ForLoopStatement : public Statement {
    std::unique_ptr<BlockStatement> m_body;

public:
    explicit ForLoopStatement(std::unique_ptr<BlockStatement> body);

    void accept(Visitor &visitor) override;

    [[nodiscard]] virtual std::string toString() const override;

    std::unique_ptr<BlockStatement> &getBody();
};

#endif //C3PO_FORLOOPSTATEMENT_HPP
