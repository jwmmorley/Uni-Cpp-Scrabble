#ifndef MY_PLAYER_H
#define MY_PLAYER_H

#include "letter.h"
#include "render.h"
#include "serializable.h"

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class player: public render, public serializable
{
    public:
    player(const std::string& n, const size_t& max_hand_size = 7, const double& initial_score = 0);
    player();
    ~player();

    /**
     * Returns the player objects name
     * 
     * @return name
     */
    std::string get_name() const;
    
    /**
     * Returns the player objects score
     * 
     * @return score
     */
    double get_score() const;
    /**
     * Sets the player objects score
     * 
     * @param score score to set score too
     */
    void set_score(const double& score);

    /**
     * Checks wether the player objects hand contains a given letter
     * 
     * @param c charector to search for
     * @return wether the charector was found
     */
    bool has_letter(const char& c) const;
    /**
     * Gets the position in the player objects hand where the given char is, -1 if not found.
     * 
     * @param c charector to search for
     * @return where the charector was found
     */
    size_t get_letter_position(const char& c) const;

    /**
     * Returns the player objects hand size
     * 
     * @return hand size
     */
    size_t get_hand_size() const;
    /**
     * Returns the player objects maximum hand size
     * 
     * @return maximum hand size
     */
    size_t get_max_hand_size() const;
    /**
     * Returns whether the player objects has room for new letters in their hand
     * 
     * @return whether there is room
     */
    bool has_room_in_hand() const;

    /**
     * Attempts to add a letter to the player objects hand.
     * 
     * @param letter letter to add to hand
     * @return wether the letter was successfully added
     */
    bool add_letter(const std::shared_ptr<letter>& letter);
    /**
     * Attempts to remove a letter to the player objects hand.
     * 
     * @param letter letter index to remove from hand
     * @return wether the letter index was successfully removed
     */
    bool remove_letter(const size_t& index);

    /**
     * Letter at given index
     * 
     * @param index index in hand
     * @return letter at index
     */
    std::shared_ptr<letter>& at(const size_t& index);

    std::ostream& draw(std::ostream& stream) const;

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    /**
     * Returns the number of players in the game
     * 
     * @return the number of players
     */
    static size_t get_num_players();

    private:    
    std::string name;
    double score;
    std::vector<std::shared_ptr<letter>> hand{};
    size_t max_hand_size;

    static size_t num_players;
};

#endif