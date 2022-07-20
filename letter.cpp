#include "letter.h"
#include "piece.h"

#include <iostream>

letter::letter(const char& charector, const double& value): charector(charector), value(value) {};
letter::~letter() {};

void letter::set_charector(const char& c)
{
    charector = c;
};
char letter::get_charector() const
{
    return charector;
};
void letter::set_value(const double& v)
{
    value = v;
};
double letter::get_value() const
{
    return value;
};
piece::type letter::get_type() const
{
    return piece::type::LETTER;
};

std::ostream& letter::draw(std::ostream& stream) const
{
    stream << get_charector();
    return stream;
};

std::ostream& letter::serialize(std::ostream& stream) const
{
    stream << piece::get_charector(get_type()) << get_charector() << get_value();
    return stream;
};
std::istream& letter::deserialize(std::istream& stream)
{
    value = -1; charector = '-';
    char t;
    stream >> t >> charector >> value;
    if (t != 'l' || value == -1){
        throw std::runtime_error("Failed to deserialize letter");
    };
    return stream;
};