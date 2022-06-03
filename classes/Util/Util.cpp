#include "Util.h"
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <ctime>

void operator>> (std::ifstream* fin, PersonList &List){
    while((*fin) && (fin->peek()!=EOF)){
        Person a(fin);
        List.add(a);
    }
}

std::ostream& operator<< (std::ostream &out, PersonList& list){
    PersonNode *current = list.getHead();
    while(current != nullptr){
        out << current->data.getFullName() << ", " << current->data.getBirthDate() << ", " << current->data.getNumber() << std::endl;
        current = current->next;
    }
    return out;
}

bool Util::checkName(const std::string& str)
{
    std::regex r(R"([A-z\x80-\xFF-\s]{3,})");
    std::regex fail(R"(^((?![\\\^\_\-\`]).)*$)");

    if(!std::regex_match(str, r) || !std::regex_match(str, fail)) return false;
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

bool Util::checkNumber(const std::string& str) {
    const std::regex r = std::regex(R"(^(((\+\d{1,3})|8)\d{10})$)");

    if(!std::regex_match(str, r)) return false;
    return true;
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

void Util::execute(int type, PersonList& list) {
    switch (type) {
        case -1:
        default:
            std::cout << "Unknown command, type '-help' to see command list.";
            break;
        case 0:
            std::cout <<
                 "clear - Clear the list.\n" <<
                 "load <file path> - Load list from the file.\n" <<
                 "write - Display the list\n" <<
                 "save <file path> - Save list to the file.\n" <<
                 "add - Add an object to the list.\n" <<
                 "sort <type> - Sort the list.\n" <<
                 "find - Find all elements by terms.\n" <<
                 "delete - Delete all elements by terms.\n" <<
                 "birthday - Get person with nearest birthday.\n" <<
                 "exit - Exit the program.\n";
            break;
        case 1:
            list.~PersonList();
            std::cout << "List cleared.\n";
            break;
        case 2: {
            std::string fpath;
            std::cout << "Enter file path:\n";
            std::cin >> fpath;

            std::ifstream fin(fpath);
            if (fin.is_open()) {
                list.remove("*", "*", "*");
                &fin >> list;
            } else {
                std::cout << "Incorrect file path. Please try again.\n";
            }
            break;
        }
        case 3: {
            std::string fpath;
            std::cout << "Enter file path:\n";
            std::cin >> fpath;

            std::ofstream fout(fpath);
            if (fout.is_open()) {
                list.save(&fout);
                std::cout << "The list has been successfully saved to " << fpath << std::endl;
            } else {
                std::cout << "Incorrect file path. Please try again.\n";
            }
            break;
        }
        case 4: {
            Person a;
            a.read();
            list.add(a);
            break;
        }
        case 5: {
            PersonNode *shead;
            shead = list.sort(list.getHead());
            list.setHead(shead);
            list.resetEnd();
            std::cout << "The list was successfully sorted.\n";
            break;
        }
        case 6: {
            std::string fullName, phoneNumber, birthDate;
            bool found = false;

            std::cout << "Enter fullname of person: >\n";
            std::cin >> fullName;
            std::cout << "Enter phone number: >\n";
            std::cin >> phoneNumber;
            std::cout << "Enter birth date: >\n";
            std::cin >> birthDate;

            for(int i = 0; i < list.size(); i++)
            {
                if(list[i].data.check(fullName, birthDate, phoneNumber))
                {
                    list[i].data.write();
                    found = true;
                }
            }
            if(!found) {
                std::cout << "Not found.\n";
            }
            break;
        }

        case 7: {
            std::string fullName, phoneNumber, birthDate;

            std::cout << "Enter fullname of person: >\n";
            std::cin >> fullName;
            std::cout << "Enter phone number: >\n";
            std::cin >> phoneNumber;
            std::cout << "Enter birth date: >\n";
            std::cin >> birthDate;

            int size = list.size();
            list.remove(fullName, birthDate, phoneNumber);
            if(list.size() == size) {
                std::cout << "Nothing deleted.\n";
            } else {
                std::cout << "Deleted " << size - list.size() << " elements.\n";
            }
            break;
        }

        case 8: {
            exit(0);
        }

        case 9: {
            Person needed;
            int mind = 400;
            for (int i = 0; i < list.size(); i++)
            {
                if(mind > list[i].data.daysBeforeBirthday())
                {
                    needed = list[i].data;
                    mind = list[i].data.daysBeforeBirthday();
                }
            }
            needed.write();
            std::cout << "Days before b-day: " << mind << std::endl;
            break;
        }

        case 10: {
            std::cout << list << std::endl;
            break;
        }
    }
}

int Util::dateDiff(std::vector<int> &d1, std::vector<int> &d2) {
    struct std::tm a = {0,0,0,d1[0],d1[1]-1,d1[2]-1900};
    struct std::tm b = {0,0,0,d2[0],d2[1]-1,d2[2]-1900};
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
    {
        double difference = std::difftime(y, x) / (60 * 60 * 24);
        return (int)difference;
    }
    return 0;
}
