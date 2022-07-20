#ifndef SCRABBLE_H
#define SCRABBLE_H

#include "bag.h"
#include "board.h"
#include "dictionary.h"
#include "player.h"
#include "render.h"
#include "serializable.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class scrabble: public render, public serializable
{
    public:
    scrabble();
    scrabble(std::shared_ptr<board> t, std::shared_ptr<bag> b,
        std::vector<std::shared_ptr<player>> players, std::string dictionary_name = "ukenglish");
    ~scrabble();

    /**
    * Returns a pointer to the active player
    * 
    * @return pointer to active player
    */
    std::shared_ptr<player>& get_active_player();
    /**
    * Returns a pointer to the active player
    * 
    * @return pointer to active player
    */
    const std::shared_ptr<player>& get_active_player() const;
    /**
    * Switches the active plaer to the next player
    */
    void next_player();

    /**
    * Called on game start. Initialises game and starts game loop.
    *  Once game loop is complete also calulates and displays the winner
    */
    void start();

    /**
    * Takes a stream and extracts user input from it.
    *  Attemps to run a command using it. If no command is recognised the help command is called.
    * 
    * @param stream stream to read command from
    * @return stream command has been read from
    */
    std::istream& on_command(std::istream& stream);
    /**
    * Saves the program and ends the game loop. This leads to scoring and termination of the program
    */
    void exit();
    /**
    * Saves the program to the provided filename or to a date time stamp if not provided
    * 
    * @param file_name name of file to save to/over
    */
    void save(std::string file_name = "") const;
    /**
    * Sets the message value to a help message for the next scrabble::draw call
    */
    void help();
    /**
    * Checks whether the board is valid, scores then passes the turn to the next player
    * 
    * @return whether the board was valid
    */
    bool turn();
    /**
    * Passes the turn to the next player. If passed 6 times and it's not the first turn the game ends.
    */
    void pass();
    /**
    * Resets all tiles played this turn
    */
    void reset();
    /**
    * Sets the tile at the given postion to the correct letter. Returns whether successful or not
    * 
    * @param x X position to be set
    * @param y Y position to be set
    * @param c Charicto to be set
    * 
    * @return Whether the position was succesfully set
    */
    bool set(size_t x, size_t y, char c);
    

    std::ostream& draw(std::ostream& stream) const;

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    private:
    bool running{false}, first_play{true};
    size_t num_passes{0};
    std::string message{};
    std::shared_ptr<board> temp_table;
    std::vector<std::pair<size_t, size_t>> edited_positions;
    std::shared_ptr<dictionary> dic;

    std::string language;
    std::shared_ptr<board> table;
    std::shared_ptr<bag> b;
    std::vector<std::shared_ptr<player>> players; size_t active_player{0};
};

#endif
