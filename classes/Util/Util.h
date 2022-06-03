#ifndef UTIL_H
#define UTIL_H

#include "../PersonList/PersonList.h"
#include <iostream>
#include <vector>

class Util {
    public:
        static bool checkName(const std::string& str);
        static bool checkBirth(const std::string& str);
        static bool checkNumber(const std::string& str);
        static void execute(int type, PersonList& list);
        static std::vector<int> birthNumsFrom(const std::string& str);
        static int dateDiff(std::vector<int>& d1, std::vector<int>& d2);
};

#endif