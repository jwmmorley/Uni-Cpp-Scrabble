#ifndef PIECE_H
#define PIECE_H

#include "piece.h"
#include "render.h"
#include "serializable.h"

class piece: public render, public serializable
{
    public:
    enum type{
        LETTER, BOOST, SYMBOL
    };

    /**
     * Returns piece::type representing char
     * 
     * @param charector char to convert
     * @return piece::type representing char
     */
    static piece::type get_type(const char& charector);
    /**
     * Returns char representing piece::type
     * 
     * @param type Type to convert
     * @return char representing type
     */
    static char get_charector(const piece::type& type);

    /**
     * Returns piece type for other classes to use to distinguish pieces.
     * 
     * @return enum of piece type
     */
    virtual piece::type get_type() const = 0;
};

#endif