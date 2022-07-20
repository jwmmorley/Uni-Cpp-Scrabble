#ifndef BAG_H
#define BAG_H

#include "letter.h"
#include "player.h"
#include "serializable.h"

#include <iostream>
#include <memory>
#include <vector>

class bag: public serializable
{
    public:
    bag();
    ~bag();

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    /**
    * Fills the pointer with a random letter from the bag.
    *
    * @param letter_to_fill pointer whos object should be set to a letter in the bag.
    * @return wether the letter was succesfully set.
    */
    bool random_letter(std::shared_ptr<letter>& letter_to_fill);
    /**
    * Fills the players hand from the pointer wit random letters from the bag.
    *
    * @param p pointer to player object whos hand should be filled.
    */
    void fill_hand(std::shared_ptr<player>& p);

    private:
    std::vector<std::unique_ptr<letter>> contains;
};

#endif