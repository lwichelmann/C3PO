//
// Created by leonw on 10.01.2026.
//

export module ast:statement;
import std;
import :visitor;

export class Statement {
public:
    virtual ~Statement() = default;

    [[nodiscard]] virtual std::string toString() const = 0;

    virtual void accept(Visitor &visitor) = 0;
};
