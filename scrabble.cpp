#include "bag.h"
#include "board.h"
#include "boost.h"
#include "clear.h"
#include "dictionary.h"
#include "letter.h"
#include "piece.h"
#include "player.h"
#include "scrabble.h"
#include "utill.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

scrabble::scrabble() = default;
scrabble::scrabble(std::shared_ptr<board> t, std::shared_ptr<bag> bb,
    std::vector<std::shared_ptr<player>> players, std::string language):
    table(std::move(t)), b(std::move(bb)),
    players(std::move(players)), language(language) {};
scrabble::~scrabble() {};

std::shared_ptr<player>& scrabble::get_active_player(){return players[active_player];};
const std::shared_ptr<player>& scrabble::get_active_player() const {return players[active_player];};

void scrabble::next_player() {
    active_player++;
    if (active_player == players.size()){
        active_player = 0;
    }
};

std::istream& scrabble::on_command(std::istream& stream)
{
    message = "";
    std::string command{""}; stream >> command; command = to_lower(command);
    if (command == "save" || command == "s"){
        std::string file_name{""}; std::getline(stream, file_name);
        save(file_name);
    } else if (command == "turn" || command == "t") {
        turn();
    } else if (command == "help" || command == "h") {
        help();
    } else if (command == "exit" || command == "e") {
        exit();
    } else if (command == "reset" || command == "r") {
        reset();
    } else if (command == "pass" || command == "p") {
        pass();
    } else if (is_number(command)) {
        size_t x, y; char c;
        std::stringstream ss{command}; ss >> x;
        stream >> y >> c; 
        set(x, y, c);
    } else{
        help();
    };
    return stream;
};
void scrabble::exit()
{
    save();
    running = false;
}
void scrabble::save(std::string file_name) const
{
    file_name = trim(file_name);
    if (file_name == ""){
        time_t ttime = std::time(0);
        std::tm *gmt_time = std::gmtime(&ttime);
        file_name =
            std::to_string(1900 + gmt_time -> tm_year) + "-" + 
            std::to_string(1 + gmt_time -> tm_mon) + "-" + 
            std::to_string(gmt_time -> tm_mday) + "_" + 
            std::to_string(1 + gmt_time -> tm_hour) + "-" + 
            std::to_string(gmt_time -> tm_min) + "-" + 
            std::to_string(gmt_time -> tm_sec);
    }
    std::ofstream file{};
    file.open("data/save/" + file_name + ".txt");
    std::cout << "Saving to file: data/save/" + file_name + ".txt ..." << std::endl;
    serialize(file);
    std::cout << "Saved" << std::endl;
    file.close();
};
void scrabble::help()
{
    message = 
        "Tiles:\n"
        "   2l - Double letter; 2w - Double word; 3l - Triple letter; 3w - Triple word\n"
        "Commands:\n"
        "   h / help - Brings up this list\n"
        "   s / save <filename> - Saves game to filename if provided, else saves to a date and time stamp\n"
        "   t / turn - Checks wether the current board is valid then scores and passes the turn to the next player\n"
        "   e / exit - Saves the game to a time stamp, announces the winner for the current game state and exits\n"
        "   r / reset - resets all tiles placed on the board this round\n"
        "   p / pass - Passes the turn to the other player. If passed 6 times and it's not the first go the game ends\n"
        "   <int> <int> <char> - Attempts to places the char at the stated place on the board"
    ;
}
void scrabble::pass()
{
    if (first_play == false){
        num_passes++;
    };
    reset();
    if (num_passes >= 6){
        exit();
        return;
    };
    next_player();
};
bool scrabble::turn()
{
    std::set<std::string> words{}; std::string word{""};
    for (auto pos : edited_positions){
        word = temp_table -> get_horizontal_word(pos.first,  pos.second);
        words.insert(word);
        word = temp_table -> get_verticle_word(pos.first,  pos.second);
        words.insert(word);
    };
    if (words.size() == 0){
            message = "You must play something";
            return false;
    };
    if (words.size() == 1){
        message = "Word needs to be more than one letter";
        return false;
    }
    std::set<std::string> temp_words{};
    for (auto word : words){
        if (word.size() > 1){
            temp_words.insert(word);
        };
    };
    words = temp_words;
    for (auto word : words){
        if (!(dic -> contains(word))){
            message = word + " is not a valid word";
            return false;
        };
    };
    if (!first_play){
        if(words.size() == 1 && (*words.begin()).size() == edited_positions.size()){
            message = "Words must be connected";
            return false;
        };
    } else {
        bool centre{false};
        for (auto position : edited_positions){
            if ((position.first == std::floor(table -> get_width() / 2) || position.first == std::ceil(table -> get_width() / 2))
                &&
                (position.second == std::floor(table -> get_height() / 2) || position.second == std::ceil(table -> get_height() / 2))){
                    centre = true;
                    break;
            };
        };
        if (!centre){
            message = "First word must include the centre (" +
                        std::to_string((int) table -> get_width() / 2) + 
                        ", " + 
                        std::to_string((int) table -> get_height() / 2) + ")";
            return false;
        }
        first_play = false;
    };
    // Scoring
    std::vector<std::pair<size_t, size_t>> word_boost_positions{};
    std::vector<std::pair<size_t, size_t>> letter_boost_positions{};
    for (auto position : edited_positions){
        if (temp_table -> tile_at(position.first, position.second) -> get_type() == piece::BOOST){
            auto boo = std::static_pointer_cast<boost>(temp_table -> tile_at(position.first, position.second));
            if (boo -> get_boost_type() == boost::LETTER){
                temp_table -> letter_at(position.first, position.second) -> set_value(
                    temp_table -> letter_at(position.first, position.second) -> get_value()
                    * boo -> get_value()
                );
                letter_boost_positions.push_back(position);
            } else{
                word_boost_positions.push_back(position);
            };
        };
    };

    std::set<std::deque<std::pair<size_t, size_t>>> word_positionss{}; std::deque<std::pair<size_t, size_t>> word_positions{};
    for (auto pos : edited_positions){
        word_positions = temp_table -> get_horizontal_word_positions(pos.first,  pos.second);
        if (word_positions.size() > 1){
            word_positionss.insert(word_positions);
        };
        word_positions = temp_table -> get_verticle_word_positions(pos.first,  pos.second);
        if (word_positions.size() > 1){
            word_positionss.insert(word_positions);
        };
    };

    double total_score{0};
    for (auto word_positions : word_positionss){
        double word_score{0};
        double multiplier{1};
        for (auto position : word_positions){
            if (contains_pair(word_boost_positions, position)){
                auto boo = std::static_pointer_cast<boost>(temp_table -> tile_at(position.first, position.second));
                multiplier *= boo -> get_value();
            };
            word_score += temp_table -> letter_at(position.first, position.second) -> get_value();
        };
        total_score += word_score * multiplier;
    };
    get_active_player() -> set_score(get_active_player() -> get_score() + total_score);

    for (auto position : letter_boost_positions){
        auto boo = std::static_pointer_cast<boost>(temp_table -> tile_at(position.first, position.second));
        temp_table -> letter_at(position.first, position.second) -> set_value(
            temp_table -> letter_at(position.first, position.second) -> get_value()
            / boo -> get_value()
        );
    };

    num_passes = 0;
    table = std::move(temp_table);
    temp_table = std::shared_ptr<board>{new board(*table)};
    b -> fill_hand(get_active_player());
    edited_positions.clear();
    next_player();
    return true;
};
void scrabble::reset()
{
    for (auto position : edited_positions){
        get_active_player() -> add_letter(std::move(temp_table -> letter_at(position.first, position.second)));
    };
    edited_positions.clear();
};
bool scrabble::set(size_t x, size_t y, char c)
{
    std::pair<size_t, size_t> position{x, y};
    size_t letter_index = get_active_player() -> get_letter_position(c);

    if (c == '-'){
        if (!contains_pair(edited_positions, position)){
            message = "You cannot switch a letter from a different turn";
            return false;
        };
        if (!get_active_player() -> has_room_in_hand()){
            message = "You do not have enough room in your hand";
            return false;
        };
        get_active_player() -> add_letter(std::move(temp_table -> letter_at(x, y)));
        remove_pair(edited_positions, position);
        return true;
    };
    if (letter_index == -1){
        message = "You do not have letter: " + std::to_string(c) + " in your hand";
        return false;
    };
    if (table -> letter_at(x, y)){
        message = "You cannot alter letters from previus rounds";
        return false;
    };
    if (contains_pair(edited_positions, position)){
        temp_table -> letter_at(x, y).swap(get_active_player() -> at(letter_index));
        return true;
    };
    if (edited_positions.size() > 0){
        if (!(edited_positions[0].first == x || edited_positions[0].second == y)){
             message = "Your new word must be in a straight line.";
             return false;
        };
    };
    if (edited_positions.size() > 1){
        if (!(edited_positions[1].first == x || edited_positions[1].second == y)){
             message = "Your new word must be in a straight line.";
             return false;
        };
    };
    temp_table -> letter_at(x, y) = std::move(get_active_player() -> at(letter_index));
    get_active_player() -> remove_letter(letter_index);
    edited_positions.push_back(position);
    return true;
};

void scrabble::start()
{
    running = true;
    message = "";
    num_passes = 0;
    edited_positions = std::vector<std::pair<size_t, size_t>>{};
    temp_table = std::shared_ptr<board>{new board(*table)};

    std::ifstream file;
    file.open("data/language/" + language + "/dictionary.txt");
    if (!file){
        throw std::runtime_error(language + " dictionary not found");
    }
    dic = std::unique_ptr<dictionary>(new dictionary); dic -> deserialize(file);
    file.close();

    help();

    while (running){
        this -> draw(std::cout);
        this -> on_command(std::cin);
    };

    std::sort(players.begin(), players.end(), 
    [](const auto & a, const auto & b) -> bool{ 
        return a -> get_score() > b -> get_score(); 
    });

    double max_score{-1};
    std::vector<std::shared_ptr<player>> winners;
    for (auto player : players){
        if (player -> get_score() > max_score){
            winners.clear();
            winners.push_back(player);
            max_score = player -> get_score();
        } else if(player -> get_score() == max_score){
            winners.push_back(player);
        };
    };
    std::cout << "Winner(s) with score " + std::to_string(max_score) + ": ";
    for (auto winner : winners){
        std::cout << winner -> get_name() + " ";
    }
    std::cout << std::endl;
    for (auto player : players){
        std::cout << player -> get_name() << ": " << player -> get_score() << std::endl;
    };
};

std::ostream& scrabble::draw(std::ostream& stream) const
{
    clear().draw(stream);
    stream << "=== Scrabble =========" << std::endl;
    temp_table -> draw(stream);
    players[active_player] -> draw(stream);
    stream << message << std::endl;
    return stream;
};

std::ostream& scrabble::serialize(std::ostream& stream) const
{
    stream << active_player << ' ' << players.size() << ' ' << first_play << ' ' << language << std::endl;
    for (auto player : players){
        player -> serialize(stream) << std::endl;
    };
    b -> serialize(stream);
    table -> serialize(stream);
    return stream;
};
std::istream& scrabble::deserialize(std::istream& stream)
{
    table = std::shared_ptr<board>{new board()};
    b = std::shared_ptr<bag>{new bag()};
    players = std::vector<std::shared_ptr<player>>{};
    active_player = 0; size_t num_players; first_play = true; language = "";

    std::string line; std::stringstream line_stream{};
    std::getline(stream, line); line_stream = std::stringstream{line};
    line_stream >> active_player >> num_players >> first_play >> language;
    for (size_t i{0}; i < num_players; i++) {
        std::shared_ptr<player> p{new player()};
        p -> deserialize(stream);
        players.push_back(p);
    };

    b -> deserialize(stream);
    stream.ignore(1);

    table -> deserialize(stream);

    return stream;
};