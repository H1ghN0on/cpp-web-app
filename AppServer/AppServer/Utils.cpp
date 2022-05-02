#define _CRT_SECURE_NO_WARNINGS

#include "Utils.hpp"


namespace Server {

    inline std::string& Utils::Rtrim(std::string& s, const char* t)
    {
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }

    inline std::string& Utils::Ltrim(std::string& s, const char* t)
    {
        s.erase(0, s.find_first_not_of(t));
        return s;
    }

    inline std::string& Utils::Trim(std::string& s, const char* t)
    {
        return Ltrim(Rtrim(s, t), t);
    }

    std::vector<std::string> Utils::Split(std::string word, const char* symbol) {
        std::vector<std::string> words;
        char* cWord = (char*)Trim(word).c_str();

        char* pch = strtok(cWord, symbol);
        while (pch != nullptr) {
            words.push_back(pch);
            pch = strtok(NULL, symbol);
        }


        return words;
    }
}