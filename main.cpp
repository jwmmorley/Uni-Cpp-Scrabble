#include "bag.h"
#include "board.h"
#include "clear.h"
#include "dictionary.h"
#include "player.h"
#include "scrabble.h"
#include "text.h"
#include "utill.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


int main(){

    std::map<std::string, int> options_save{
        {"l", 0.0}, {"n", 1.0},
        {"L", 0.0}, {"N", 1.0}
    };

    std::unique_ptr<scrabble> scr{new scrabble()}; std::ifstream file;

    std::cout << "Load or new game? [l/n]" << std::endl;
    switch(get_input_choice(options_save)) {
        case 0: {
            std::string file_name{""}; 
            std::cout << "Save name: " << std::endl;
            while (true){
                file_name = get_input<std::string>();
                file.open("data/save/" + file_name + ".txt");
                if (!(!file)){
                    break;
                }
                std::cout << file_name << ".txt not found in directory data/save/" << std::endl;
            };
            std::cout << "Loading ..." << std::endl;
            scr -> deserialize(file);
            std::cout << "Loaded" << std::endl;
            file.close();
            break;
        }
        default: {
            std::cout << "How many players? " << std::endl;
            size_t num_players; num_players = get_input<size_t>();

            std::cout << "Generating game..." << std::endl;

            file.open("data/language/ukenglish/bag.txt");
            std::shared_ptr<bag> b{new bag()};
             b -> deserialize(file);
            file.close();

            file.open("data/board/default.txt");
            std::shared_ptr<board> table{new board()}; table -> deserialize(file); 
            file.close();

            std::vector<std::shared_ptr<player>> players{}; std::string name{""};
            for (size_t i{0}; i < num_players; i++){
                std::shared_ptr<player> p{new player{"Player-" + std::to_string(i + 1)}};
                b -> fill_hand(p);
                players.push_back(std::move(p));
            };

            scr = std::unique_ptr<scrabble>{new scrabble(
                std::move(table), std::move(b),
                std::move(players), "ukenglish"
            )};
            break;
        }
    };

    std::cout << "Starting game ..." << std::endl; 
    scr -> start();
    std::cout << "Game ended" << std::endl; 

    return 0;
};