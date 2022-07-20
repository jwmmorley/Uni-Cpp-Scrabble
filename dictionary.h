#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "serializable.h"

#include <iostream>
#include <set>
#include <string>

class dictionary: public serializable
{
    public:
    dictionary();
    ~dictionary();

    std::ostream& serialize(std::ostream& stream) const;
    std::istream& deserialize(std::istream& stream);

    /**
     * Clears the internal cache of words. The cache is used to reduce the number of times the main dictionary is searched.
     */
    void clear_cache();

    /**
     * First checks the cache for the word then, if not found, the main dictionary. Returns wether the word is present.
     * 
     * @param string Word to search for
     * @return Whether the word is present
     */
    bool contains(const std::string& string);

    private:
    std::set<std::string> dic;
    std::set<std::string> cache;
};

#endif