#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>

class serializable
{
    public:
    /**
     * Writes to the provided stream in a manner intent for the object to be rebuilt from.
     * 
     * @param stream Stream to write too
     * @return Stream writen too
     */
    virtual std::ostream& serialize(std::ostream& stream) const = 0;
    /**
     * Reads from the provided stream and builds the object from it.
     * 
     * @param stream Stream to read from
     * @return Stream read from
     */
    virtual std::istream& deserialize(std::istream& stream) = 0;
};

#endif