#include "boost.h"
#include "letter.h"
#include "piece.h"
#include "piece_factory.h"
#include "symbol.h"

#include <memory>
#include <sstream>
#include <string>

std::shared_ptr<piece> piece_factory::create_piece(const std::string& string)
{
    std::stringstream sstream{string}; 
    char ctype; sstream >> ctype; piece::type type = piece::get_type(ctype);
    sstream.str(string);
    std::shared_ptr<piece> p;
    switch(type){
        case piece::type::LETTER:
            p = std::shared_ptr<letter>{new letter()};
            break; 
        case piece::type::BOOST:
            p = std::shared_ptr<boost>{new boost()};
            break; 
        default:
            p = std::shared_ptr<symbol>{new symbol()};
            break;
    };
    p -> deserialize(sstream);
    return p;
};

std::shared_ptr<letter> piece_factory::create_letter(const std::string& string)
{
    std::stringstream sstream{string}; 
    std::shared_ptr<letter> p{new letter()};
    p -> deserialize(sstream);
    return p;
};