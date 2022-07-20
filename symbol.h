#ifndef SYMBOL_H
#define SYMBOL_H

#include "piece.h"

#include <iostream>

class symbol: public piece
{
    public:
    symbol(const char& charector = '-');
    ~symbol();

    /**
     * Returns the charector the symbol represents
     * 
     * @return charector the symbol represents
     */
    char get_charector() const;

    piece::type get_type() const;

    std::ostream& draw(std::ostream& stream) const;

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    private:
    char charector;
};

#endif