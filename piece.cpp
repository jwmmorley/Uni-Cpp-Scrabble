#include "piece.h"

piece::type piece::get_type(const char& charector)
{
    switch(charector){
        case 'l':
            return piece::type::LETTER;
        case 'b':
            return piece::type::BOOST;
        default:
            return piece::type::SYMBOL;
    };
};
char piece::get_charector(const piece::type& type)
{
    switch(type){
        case piece::type::LETTER:
            return 'l';
        case piece::type::BOOST:
            return 'b';
        default:
            return 's';
    };
};