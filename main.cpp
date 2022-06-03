#include "classes/Person/Person.h"
#include "classes/Util/Util.h"
#include "classes/PersonList/PersonList.h"
#include <iostream>
#include <map>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::map<std::string, int> commands = {
            { "help", 0 }, { "clear", 1 }, { "load", 2 },
            { "save", 3 }, { "add", 4 }, { "sort", 5 },
            { "find", 6 }, { "delete", 7 }, { "exit", 8 }, { "birthday", 9 },
            { "write", 10 },
    };
    std::cout << "Type help to see command list\n";
    PersonList list;

    while(std::cin) {
        int type;
        std::string command;

        std::cin >> command;
        try {
            type = commands.at(command);
        } catch (std::out_of_range&) {
            type = -1;
        }

        Util::execute(type, list);
    }
}
