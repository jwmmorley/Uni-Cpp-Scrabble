#include "symbol.h"
#include "piece.h"

#include <iostream>

symbol::symbol(const char& charector): charector(charector) {};
symbol::~symbol() {};

char symbol::get_charector() const {return charector;};
piece::type symbol::get_type() const {return piece::type::SYMBOL;};

std::ostream& symbol::draw(std::ostream& stream) const
{
    stream << get_charector();
    return stream;
};

std::ostream& symbol::serialize(std::ostream& stream) const
{
    stream << piece::get_charector(get_type()) << get_charector();
    return stream;
};
std::istream& symbol::deserialize(std::istream& stream)
{
    char t; char c;
    stream >> t >> c;
    charector = c;
    return stream;
};