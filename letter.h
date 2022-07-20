#ifndef LETTER_H
#define LETTER_H

#include "piece.h"

#include <iostream>

class letter: public piece
{
    public:
    letter(const char& charector = ' ', const double& value = 0);
    ~letter();

    /**
     * Sets the letter
     * 
     * @param charector Letter to set
     */
    void set_charector(const char& charector);
    /**
     * Returns letter as char
     * 
     * @return charector letter class represents
     */
    char get_charector() const;
    /**
     * Sets the value
     * 
     * @param v value to set
     */
    void set_value(const double& v);
    /**
     * Returns value
     * 
     * @return value
     */
    double get_value() const;

    piece::type get_type() const;

    std::ostream& draw(std::ostream& stream) const;

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    private:
    char charector;
    double value;
};

#endif