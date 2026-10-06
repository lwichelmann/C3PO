//
// Created by leonw on 17.01.2026.
//

export module ast:expression;
import std;
import :visitor;

export class Expression
{
    public:
    virtual ~Expression() = default;
    virtual std::string toString() const = 0;
    virtual RuntimeValue accept(Visitor &visitor) = 0;

};
