#ifndef BOARD_H
#define BOARD_H

#include "letter.h"
#include "piece.h"
#include "render.h"
#include "serializable.h"

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


class board: public render, public serializable
{
    public:
    board(const size_t& width, const size_t& height, const size_t& cell_width = 3);
    board(const size_t& size);
    board(const board& b);
    board(board&& b);
    board();
    ~board();

    /**
     * Width of board
     * 
     * @return Width of board
     */
    size_t get_width() const;
    /**
     * Height of board
     * 
     * @return Height of board
     */
    size_t get_height() const;

    /**
     * Letter at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Letter at position
     */
    std::shared_ptr<letter>& letter_at(const size_t& x, const size_t& y);
    /**
     * Letter at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Letter at position
     */
    const std::shared_ptr<letter>& letter_at(const size_t& x, const size_t& y) const;

    /**
     * Tile at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Tile at position
     */
    std::shared_ptr<piece>& tile_at(const size_t& x, const size_t& y);
    /**
     * Tile at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Tile at position
     */
    const std::shared_ptr<piece>& tile_at(const size_t& x, const size_t& y) const;

    /**
     * Horizontal word at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Horizontal word at position
     */
    std::string get_horizontal_word(const size_t& x, const size_t& y) const;
    /**
     * Verticle word at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Veticle word at position
     */
    std::string get_verticle_word(const size_t& x, const size_t& y) const;

    /**
     * Horizontal word postions at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Horizontal word postions at position
     */
    std::deque<std::pair<size_t, size_t>> get_horizontal_word_positions(const size_t& x, const size_t& y) const;
    /**
     * Verticle word postions at given position
     * 
     * @param x X positions
     * @param y Y positions
     * @return Verticle word postions at position
     */
    std::deque<std::pair<size_t, size_t>> get_verticle_word_positions(const size_t& x, const size_t& y) const;

    board& operator=(const board& b);

    std::ostream& draw(std::ostream& stream) const;

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    private:
    std::vector<std::shared_ptr<letter>> letters;
    std::vector<std::shared_ptr<piece>> tiles;
    size_t width;
    size_t height;
    size_t cell_width;
};

#endif