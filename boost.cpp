#include "boost.h"
#include "piece.h"

#include <iostream>


boost::type boost::get_type(const char& charector)
{
    switch(charector){
        case 'w':
            return boost::type::WORD;
        default:
            return boost::type::LETTER;
    };
};
char boost::get_charector(const boost::type& type)
{
    switch(type){
        case boost::type::WORD:
            return 'w';
        default:
            return 'l';
    };
};


boost::boost(const boost::type& boost_type, const double& value): boost_type(boost_type), value(value) {};
boost::~boost() {};

boost::type boost::get_boost_type() const
{
    return boost_type;
};
double boost::get_value() const
{
    return value;
};
piece::type boost::get_type() const
{
    return piece::type::BOOST;
};

std::ostream& boost::draw(std::ostream& stream) const
{
    stream << get_value() << get_charector(get_boost_type());
    return stream;
};

std::ostream& boost::serialize(std::ostream& stream) const
{
    stream << piece::get_charector(get_type()) << get_charector(get_boost_type()) << get_value();
    return stream;
};
std::istream& boost::deserialize(std::istream& stream)
{
    char t; char bt; double v;
    stream >> t;
    stream >> bt;
    stream >> v;
    boost_type = boost::get_type(bt);
    value = v;
    return stream;
};