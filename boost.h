#ifndef BOOST_H
#define BOOST_H

#include "piece.h"

#include <iostream>

class boost: public piece
{
    public:
    enum type{
        LETTER,
        WORD
    };

    /**
     * Returns char representing boost::type
     * 
     * @param boost_type Type to convert
     * @return char representing type
     */
    static char get_charector(const boost::type& boost_type);
    /**
     * Returns boost::type representing char
     * 
     * @param charector char to convert
     * @return boost::type representing char
     */
    static boost::type get_type(const char& charector);

    boost(const boost::type& boost_type = boost::type::LETTER, const double& value = 1);
    ~boost();

    /**
     * Returns boost::type
     * 
     * @return boost::type
     */
    boost::type get_boost_type() const;
    /**
     * Returns magnitude of boost
     * 
     * @return magnitude
     */
    double get_value() const;
    piece::type get_type() const;

    std::ostream& draw(std::ostream& stream) const;

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    private:
    double value;
    boost::type boost_type;
};

#endif