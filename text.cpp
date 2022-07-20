#include "text.h"

#include <iostream>
#include <string>

text::text(const std::string& string): string(string) {};
text::~text() {};

std::ostream&text::draw(std::ostream& stream) const
{
    stream << string;
    return stream;
}