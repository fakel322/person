#include "Util.h"
#include <iostream>
#include <regex>
#include <vector>

bool Util::checkName(const std::string& str, const std::string& errOutput)
{
    std::regex r(R"([A-z\x80-\xFF-]{3,})");
    std::regex fail(R"(^((?![\\\^\_\-\`]).)*$)");

    std::cout << str << std::endl;

    if(!std::regex_match(str, r) || !std::regex_match(str, fail))
    {
        std::cout << errOutput << std::endl;
        return false;
    }
    return true;
}

bool Util::checkBirth(const std::string& str) {
    const std::regex r = std::regex(R"(^((\d{1,2})[\.\/](\d{1,2})[\.\/](\d{4}))$)");

    if (!std::regex_match(str, r)) return false;

    std::smatch match;
    if (std::regex_search(str, match, r))
    {
        const int y = std::stoi(match[4].str());
        const int m = std::stoi(match[3].str());
        const int d = std::stoi(match[2].str());

        if (y > 2022) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;

        if (m == 2)
        {
            if (( (y % 4 == 0) && (y % 100 != 0) ) || (y % 400 == 0)) return (d <= 29);
            else return (d <= 28);
        }
        if (m == 4 || m == 6 || m == 9 || m == 11) return (d <= 30);

        return true;
    }
    return false;
}

std::vector<int> Util::birthNumsFrom(const std::string &str) {
    std::smatch match;

    const std::regex r = std::regex(R"(^((\d{1,2})[\.\/](\d{1,2})[\.\/](\d{4}))$)");
    if(std::regex_search(str, match, r))
    {
        std::vector<int> arr {
            std::stoi(match[2].str()),
            std::stoi(match[3].str()),
            std::stoi(match[4].str())
        };
        return arr;
    }
    return std::vector<int> {};
}