#include "dictionary.h"
#include "utill.h"

#include <iostream>
#include <iterator>
#include <set>
#include <string>

dictionary::dictionary(): dic(std::set<std::string>{}), cache(std::set<std::string>{}) {};
dictionary::~dictionary() {};

std::ostream& dictionary::serialize(std::ostream& stream) const
{
    std::copy(dic.begin(), dic.end(), std::ostream_iterator<std::string>(stream, "\n"));
    return stream;
};
std::istream& dictionary::deserialize(std::istream& stream)
{
    dic = std::set<std::string>(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
    return stream;
};

void dictionary::clear_cache(){
    cache.clear();
};

bool dictionary::contains(const std::string& string){
    if (cache.find(to_lower(string)) != cache.end()){
        return true;
    };
    if (dic.find(to_lower(string)) != dic.end()){
        cache.insert(to_lower(string));
        return true;
    };
    return false;
};

