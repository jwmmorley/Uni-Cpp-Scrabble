#ifndef TEXT_H
#define TEXT_H

#include "render.h"

#include <iostream>
#include <string>

class text: public render
{
    public:
    text(const std::string& string = "");
    ~text();

    std::ostream& draw(std::ostream& stream) const;

    private:
    std::string string;
};

#endif