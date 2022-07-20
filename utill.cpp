#include "utill.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

size_t count(const std::string& string, const char& charector){
    size_t count{0};

    for (size_t i{0}; i < string.length(); i++){
        if (string[i] == charector){
            count++;
        };
    };
    return count;
};

std::string to_lower(const std::string& string){
    std::string temp{string};
    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp;
};
std::string to_higher(const std::string& string){
    std::string temp{string};
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    return temp;
};

std::string trim(const std::string& string, char charector)
{
    size_t first = string.find_first_not_of(charector);
    size_t last = string.find_last_not_of(charector) + 1;
    if (first == string.npos || last == string.npos){
        return "";
    }
    return string.substr(first, last - first);
};

std::string justify(const std::string& string, size_t cell_width, justification just, char charector)
{
    std::stringstream ss{""};
    int space = cell_width - string.size();
    if (space <= 0){
        return string.substr(0, cell_width);
    };
    switch (just){
        case LEFT:
            ss << string << std::string(space, charector);
            break;
        case RIGHT:
            ss << std::string(space, charector) << string;
            break;
        case CENTER_LEFT:
            ss << std::string(std::floor(((double) space) / 2.0), ' ');
            ss << string;
            ss << std::string(std::ceil(((double) space) / 2.0), ' ');
            break;
        case CENTER_RIGHT:
            ss << std::string(std::ceil(((double) space) / 2.0), ' ');
            ss << string;
            ss << std::string(std::floor(((double) space) / 2.0), ' ');
            break;
    };

    return ss.str();
};

template <>
size_t get_input<size_t>(std::istream& stream, const char& delim){
    std::string input{""}; std::stringstream ss{""}; size_t temp;
    while (true){
        std::getline(stream, input, delim);
        input = trim(input);
        if (is_number(input)){
            ss << input; ss >> temp;
            return temp;
        };
        ss.clear(); ss.str("");
    };
};

template<>
int get_input<int>(std::istream& stream, const char& delim) {
    std::string input{""}; std::stringstream ss{""}; int temp;
    while (true){
        std::getline(stream, input, delim);
        input = trim(input);
        if (is_number(input)){
            ss << input; ss >> temp;
            return temp;
        };
        ss.clear(); ss.str("");
    };
};