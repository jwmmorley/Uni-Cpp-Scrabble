#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * Returns wether the provided string is a number
 * 
 * @param s string to check
 * @return Whether its a number
 */
bool is_number(const std::string& s);

/**
 * Returns the number of a specific chaar in a string
 * 
 * @param s string to check
 * @param charector char to count
 * @return the number of times present
 */
size_t count(const std::string& string, const char& charector);

/**
 * Returns a new string of all lower case
 * 
 * @param string string to copy and return into lower case
 * @return lower case version of string
 */
std::string to_lower(const std::string& string);
/**
 * Returns a new string of all upper case
 * 
 * @param string string to copy and return into upper case
 * @return upper case version of string
 */
std::string to_higher(const std::string& string);
/**
 * Returns a new string with the triling and ending charector removed
 * 
 * @param string string to copy and return trimmed
 * @param charector charector to remove
 * @return trimmed version of the string
 */
std::string trim(const std::string& string, char charector = ' ');

enum justification{LEFT, RIGHT, CENTER_LEFT, CENTER_RIGHT};
/**
 * Returns a new string with the correct jusstification. justification::CENTER_ indicates
 *  that the text is first moved to the middle then to either left or the right if there
 *  is no whole centre.
 * 
 * @param string string to copy and return justified
 * @param cell_width width of cell to jusstify
 * @param just justification to use
 * @param charector char to use for padding
 * @return justified version of the string
 */
std::string justify(const std::string& string, size_t cell_width = 3, justification just = CENTER_RIGHT, char charector = ' ');

/**
 * Removes a pair of values from a vector.
 * 
 * @tparam T one of the types of the pair
 * @tparam U the other type of the pair
 * @param vector vector for the values to be removed from
 * @param value value to be removed
 */
template<class T, class U>
void remove_pair(std::vector<std::pair<T, U>>& vector, const std::pair<T, U>& value)
{
    for (size_t i{0}; i < vector.size(); i++){
        if (vector[i].first == value.first && vector[i].second == value.second){
            vector.erase(vector.begin() + i);
        };
    };
};

/**
 * Checks wether a pair is contained within a vector.
 * 
 * @tparam T one of the types of the pair
 * @tparam U the other type of the pair
 * @param vector vector for the value to be checked against
 * @param value value to be checked
 * @return whether the value was found in vector
 */
template<typename T, typename U>
bool contains_pair(const std::vector<std::pair<T, U>>& vector, const std::pair<T, U>& value)
{
    for (size_t i{0}; i < vector.size(); i++){
        if (vector[i].first == value.first && vector[i].second == value.second){
            return true;
        };
    }
    return false;
};

/**
 * Gets input from the provided input stream. Pre-selected options are provided
 *  and the user is prompted for input untill one of the options is selected.
 * 
 * @tparam T type of return option
 * @param options map of string values representing the return options
 * @param stream stream to be searched
 * @param delim deliminator of stream to indicate the end of an entry
 * @return copy of the option corresponding to the correct string in the map
 */
template<typename T>
T get_input_choice(const std::map<std::string, T>& options, std::istream& stream = std::cin, const char& delim = '\n'){
    if (options.size() == 0){
        throw std::runtime_error("Empty option list.");
    }
    std::string input{""};
    while (true){
        std::getline(stream, input, delim);
        auto temp = options.find(input);
        if (temp != options.end()){
            return temp -> second;
        };
    };
};

/**
 * Gets input from the provided input stream. The inputed value is cast to the provided type.
 *  If it fails it asks for input again.
 * 
 * @tparam T type of return
 * @param stream stream to be searched
 * @param delim deliminator of stream to indicate the end of an entry
 * @return copy of the option corresponding to the correct string in the map
 */
template<typename T>
T get_input(std::istream& stream = std::cin, const char& delim = '\n'){
    std::string input{""}; std::stringstream ss{""}; T temp;
    while (true){
        std::getline(stream, input, delim);
        input = trim(input);
        ss << input << ' '; ss >> temp;
        if (ss.good()){
            return temp;
        };
        ss.clear(); ss.str("");
    };
};

template <>
size_t get_input<size_t>(std::istream& stream, const char& delim);

template <>
int get_input<int>(std::istream& stream, const char& delim);

#endif