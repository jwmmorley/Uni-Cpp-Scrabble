#include "board.h"
#include "letter.h"
#include "piece.h"
#include "piece_factory.h"
#include "symbol.h"
#include "utill.h"

#include <deque>
#include <iostream>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

board::board(const size_t& width, const size_t& height, const size_t& cell_width): width(width), height(height), cell_width(cell_width)
{
    letters.reserve(width * height);
    tiles.reserve(width * height);
    for (size_t i{0}; i < width * height; i++){
        letters.push_back(std::shared_ptr<letter>());
    };
    for (size_t i{0}; i < width * height; i++){
        tiles.push_back(std::shared_ptr<piece>(new symbol()));
    };
};
board::board(const size_t& size): board(size, size) {};
board::board(): board(15) {};
board::board(const board& b) 
{
    std::stringstream ss{};
    b.serialize(ss);
    this -> deserialize(ss);
};
board::board(board&& b): letters(std::move(b.letters)), tiles(std::move(b.tiles))
{
    width = b.width;
    height = b.height;
    cell_width = b.cell_width;

    b.width = b.height = b.cell_width = 0;
};
board::~board() {};

std::shared_ptr<letter>& board::letter_at(const size_t& x, const size_t& y) {return letters.at(x + width * y);};
const std::shared_ptr<letter>& board::letter_at(const size_t& x, const size_t& y) const {return letters.at(x + width * y);};

std::shared_ptr<piece>& board::tile_at(const size_t& x, const size_t& y) {return tiles.at(x + width * y);};
const std::shared_ptr<piece>& board::tile_at(const size_t& x, const size_t& y) const {return tiles.at(x + width * y);};

size_t board::get_width() const {return width;};
size_t board::get_height() const {return height;};

std::string board::get_horizontal_word(const size_t& x, const size_t& y) const
{
    std::deque<std::pair<size_t, size_t>> positions{get_horizontal_word_positions(x, y)};
    std::stringstream ss{""};
    for (auto pos : positions){
        ss << letter_at(pos.first, pos.second) -> get_charector();
    }
    return ss.str();
};
std::string board::get_verticle_word(const size_t& x, const size_t& y) const
{
    std::deque<std::pair<size_t, size_t>> positions{get_verticle_word_positions(x, y)};
    std::stringstream ss{""};
    for (auto pos : positions){
        ss << letter_at(pos.first, pos.second) -> get_charector();
    }
    return ss.str();
};

std::deque<std::pair<size_t, size_t>> board::get_horizontal_word_positions(const size_t& x, const size_t& y) const
{
    std::deque<std::pair<size_t, size_t>> temp{};
    if (x > width || y > height || !letter_at(x, y)){return temp;};
    for (size_t i{x + 1}; i < width; i++){
        if (letter_at(i, y)){
            temp.push_back(std::pair<size_t, size_t>(i, y));
        } else{
            break;
        };
    };

    for (auto i{x}; i >= 0; i--){
        if (letter_at(i, y)){
            temp.push_front(std::pair<size_t, size_t>(i, y));
        } else{
            break;
        };
        if (i == 0){
            break;
        }
    };
    return temp;
};
std::deque<std::pair<size_t, size_t>> board::get_verticle_word_positions(const size_t& x, const size_t& y) const
{
    std::deque<std::pair<size_t, size_t>> temp{};
    if (x > width || y > height || !letter_at(x, y)){return temp;};
    for (size_t i{y + 1}; i < height; i++){
        if (letter_at(x, i)){
            temp.push_back(std::pair<size_t, size_t>(x, i));
        } else{
            break;
        };
    };
    for (auto i{y}; i >= 0; i--){
        if (letter_at(x, i)){
            temp.push_front(std::pair<size_t, size_t>(x, i));
        } else{
            break;
        };
        if (i == 0){
            break;
        }
    };
    return temp;
};

board& board::operator=(const board& b)
{
    std::stringstream ss{""};
    b.serialize(ss);
    deserialize(ss);
    return *this;
};

std::ostream& board::draw(std::ostream& stream) const
{
    stream << std::string(cell_width, ' ');
    for (size_t i{0}; i < width; i++){
        stream << justify(std::to_string(i), cell_width);
    };
    stream << std::endl;
    std::stringstream cell{""};
        for (size_t y{0}; y < height; y++){
            stream << justify(std::to_string(y), cell_width);
            for (size_t x{0}; x < width; x++){
                letter_at(x, y) ?
                    letter_at(x, y) -> draw(cell) :
                    tile_at(x, y) -> draw(cell);
                stream << justify(cell.str(), cell_width);
                cell.str("");
            };
        stream << std::endl;
    };
    return stream;
};

std::ostream& board::serialize(std::ostream& stream) const
{
    stream << width << ' ' << height << ' ' << cell_width << ' ' << std::endl;
    for (size_t y{0}; y < height; y++){
            for (size_t x{0}; x < width; x++){
                if (!letter_at(x, y)){
                    stream << " ";
                } else{
                    letter_at(x, y) -> serialize(stream);
                };
                stream << ',';
            };
        stream << std::endl;
    };
    for (size_t y{0}; y < height; y++){
            for (size_t x{0}; x < width; x++){
                if (!tile_at(x, y)){
                    stream << " ";
                } else{
                    tile_at(x, y) -> serialize(stream);
                };
                stream << ',';
            };
        stream << std::endl;
    };
    return stream;
};
std::istream& board::deserialize(std::istream& stream){
    letters = std::vector<std::shared_ptr<letter>>{};
    tiles = std::vector<std::shared_ptr<piece>>{};
    width = 0, height = 0, cell_width = 0;

    std::string line{""}; std::stringstream line_stream{""};

    std::getline(stream, line); line_stream = std::stringstream{line};
    line_stream >> width >> height >> cell_width;
    line_stream.clear();
    
    letters.reserve(width * height);
    tiles.reserve(width * height);

    std::string value{""};
    for (size_t y{0}; y < height; y++){
        std::getline(stream, line); line_stream = std::stringstream{line};
        for (size_t x{0}; x < width; x++){
            std::getline(line_stream, value, ',');
            value == " " ?
                letters.push_back(std::shared_ptr<letter>{}) :
                letters.push_back(piece_factory::create_letter(value));
        };
    };
    line_stream.clear();
    for (size_t y{0}; y < height; y++){
        std::getline(stream, line); line_stream = std::stringstream{line};
        for (size_t x{0}; x < width; x++){
            std::getline(line_stream, value, ',');
            value == " " ?
                tiles.push_back(std::shared_ptr<piece>{}) :
                tiles.push_back(piece_factory::create_piece(value));
        };
    };
    line_stream.clear();
    stream.clear();
    return stream;
};