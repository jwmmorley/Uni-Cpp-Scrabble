#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include "piece.h"

#include <iostream>
#include <memory>

class piece_factory
{
    public:
    /**
     * Returns pointer to new piece object as constructed from the provided string.
     * 
     * @param string arguments to be used in piece construction
     * @return pointer to new piece
     */
    static std::shared_ptr<piece> create_piece(const std::string& string);
    /**
     * Returns pointer to new letter object as constructed from the provided string.
     * 
     * @param string arguments to be used in letter construction
     * @return pointer to new letter
     */
    static std::shared_ptr<letter> create_letter(const std::string& string);

    private:
    piece_factory();
};

#endif