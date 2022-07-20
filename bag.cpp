#include "bag.h"
#include "letter.h"
#include "player.h"
#include "utill.h"

#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <stdio.h> 
#include <stdlib.h> 
#include <sstream>
#include <string>
#include <time.h>  
#include <vector>

bag::bag(): contains(std::vector<std::unique_ptr<letter>>{}) {std::srand(time(NULL));};
bag::~bag() {};

std::ostream& bag::serialize(std::ostream& stream) const
{
    stream << contains.size() << std::endl;
    for (size_t i{0}; i < contains.size(); i++){
        contains[i] -> serialize(stream) << std::endl;
    }
    stream.clear();
    return stream;
};
std::istream& bag::deserialize(std::istream& stream)
{
    contains = std::vector<std::unique_ptr<letter>>{};

    std::string line{""}; std::stringstream line_stream{""}; size_t size; 
    std::getline(stream, line); line_stream = std::stringstream{line};
     
    line_stream >> size;
    if (size < 1){
        stream.clear();
        return stream;
    }

    contains.reserve(size);

    std::string value{""};
    for (size_t i{0}; i < size; i++){
        try{
            std::unique_ptr<letter> p{new letter()};
            p -> deserialize(stream);
            contains.push_back(std::move(p));
        } catch (std::runtime_error) {
            std::cerr << "Value: " << value << std::endl;
            stream.clear();
            continue;
        };
    };

    stream.clear();
    return stream;
};

bool bag::random_letter(std::shared_ptr<letter>& letter_to_fill)
{
    if (contains.size() == 0){
        return false;
    }
    size_t random_index = rand() % contains.size();
    letter_to_fill = std::move(contains.at(random_index));
    contains.erase(contains.begin() + random_index);
    return true;
};

void bag::fill_hand(std::shared_ptr<player>& p)
{
    while (p -> has_room_in_hand()) {
        std::shared_ptr<letter> random_letter;
        if ((*this).random_letter(random_letter)){
            p -> add_letter(random_letter);
        } else{
            break;
        };
    };
};