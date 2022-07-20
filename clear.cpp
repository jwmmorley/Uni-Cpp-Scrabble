#include "clear.h"

#include <iostream>

std::ostream& clear::draw(std::ostream& stream) const
{
    for (size_t i{0}; i < 64; i++){
        stream << std::endl;
    };
    return stream;
};