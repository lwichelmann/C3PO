//
// Created by leonw on 17.01.2026.
//

#ifndef C3PO_EXPRESSION_HPP
#define C3PO_EXPRESSION_HPP
#include <string>
#include "visitor/Visitor.hpp"
class Visitor;

class Expression
{
    public:
    virtual ~Expression() = default;
    virtual std::string toString() const = 0;
    virtual RuntimeValue accept(Visitor& visitor) = 0;

};

#endif //C3PO_EXPRESSION_HPP