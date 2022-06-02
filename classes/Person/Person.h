#ifndef PERSON_H
#define PERSON_H
#include <iostream>

class Person {
    private:
        int _birthDay;
        int _birthMonth;
        int _birthYear;
        std::string _name;
        std::string _surname;
        std::string _middleName;
    public:
        void read();
        void write();
        static char compare(Person &person1, Person &person2, char type);
};


#endif //PERSON_H
