#ifndef RENDER_H
#define RENDER_H

#include <iostream>

class render
{
    public:
    /**
     * Writes to the provided stream in a user friendly manner intent for render.
     * 
     * @param stream Stream to write too
     * @return Stream writen too
     */
    virtual std::ostream& draw(std::ostream& stream) const = 0;
};

#endif