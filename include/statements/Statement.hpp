//
// Created by leonw on 10.01.2026.
//

#ifndef C3PO_STATEMENT_HPP
#define C3PO_STATEMENT_HPP
#include <string>

#include "Visitor.hpp"




class Statement
{
public:
    virtual ~Statement() = default;
    [[nodiscard]] virtual std::string toString() const = 0;
    virtual void accept(Visitor& visitor) = 0;
};


#endif //C3PO_STATEMENT_HPP