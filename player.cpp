#include "letter.h"
#include "piece_factory.h"
#include "player.h"
#include "utill.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

player::player(const std::string& n, const size_t& max_hand_size, const double& initial_score): 
    score(initial_score), max_hand_size(max_hand_size)
{
    name = trim(n);
    if (count(name, ' ') > 0){
        throw std::runtime_error("Name cannot include spaces");
    }
    hand = std::vector<std::shared_ptr<letter>>{};
    hand.reserve(max_hand_size);
    num_players++;
};
player::player(): player("Player_" + std::to_string(num_players + 1)) {};
player::~player() {num_players--;};

std::string player::get_name() const
{
    return name;
};

size_t player::get_max_hand_size() const {return max_hand_size;};
size_t player::get_hand_size() const {return hand.size();};
double player::get_score() const {return score;};
void player::set_score(const double& s) {score = s;};

bool player::has_letter(const char& c) const
{
    for (size_t i{0}; i < get_hand_size(); i++){
        if (std::tolower(hand[i] -> get_charector()) == std::tolower(c)){
            return true;
        };
    };
    return false;
};

size_t player::get_letter_position(const char& c) const
{
    if (!has_letter(c)){
        return -1;
    };
    for (size_t i{0}; i < get_hand_size(); i++){
        if (std::tolower(hand[i] -> get_charector()) == std::tolower(c)){
            return i;
        };
    };
    return -1;
};
bool player::has_room_in_hand() const{
    return get_max_hand_size() > get_hand_size() ? true : false;
};

bool player::add_letter(const std::shared_ptr<letter>& letter)
{
    if (has_room_in_hand()){
        hand.push_back(letter);
        return true;
    };
    return false;
};
bool player::remove_letter(const size_t& index)
{
    if (index < get_hand_size()){
        hand.erase(hand.begin() + index);
    return true;
    };
    return false;
};

std::shared_ptr<letter>& player::at(const size_t& index) {return hand.at(index);};

std::ostream& player::draw(std::ostream& stream) const
{
    stream << "=== " << name << " =========" << std::endl;
    stream << ' ';
    for (size_t i{0}; i < hand.size(); i++){
        hand[i] -> draw(stream) << ' ';
    };
    stream << std::endl;
    stream << "=== Score: " << score << " =========" << std::endl;
    return stream;
};

std::ostream& player::serialize(std::ostream& stream) const
{
    stream << name << ' ' << score << ' ' << hand.size() << ' ' << max_hand_size << std::endl;
    for (size_t i{0}; i < hand.size(); i++){
        hand[i] -> serialize(stream) << ',';
    };
    stream.clear();
    return stream;
};
std::istream& player::deserialize(std::istream& stream)
{
    name = ""; score = 0; max_hand_size = 0;
    hand = std::vector<std::shared_ptr<letter>>{};
    
    size_t hand_size{0}; std::string line; std::stringstream line_stream{};
    std::getline(stream, line); line_stream.str(line);
    line_stream >> name >> score >> hand_size >> max_hand_size;

    hand.reserve(max_hand_size);

    std::string value{""};
    std::getline(stream, line); line_stream = std::stringstream{line};
    for (size_t i{0}; i < hand_size; i++){
        std::getline(line_stream, value, ',');
        if (value != ""){
            hand.push_back(piece_factory::create_letter(value));
        };
    };
    stream.clear();
    return stream;
};

size_t player::get_num_players() {return num_players;};

size_t player::num_players{0};