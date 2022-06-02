#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>

class Util {
    public:
        static bool checkName(const std::string& str, const std::string& errOutput);
        static bool checkBirth(const std::string& str);
        static std::vector<int> birthNumsFrom(const std::string& str);
};

#endif