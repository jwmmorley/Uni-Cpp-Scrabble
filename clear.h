#ifndef CLEAR_H
#define CLEAR_H

#include "render.h"

#include <iostream>

class clear: public render
{
    public:
    std::ostream& draw(std::ostream& stream) const;
};


#endif