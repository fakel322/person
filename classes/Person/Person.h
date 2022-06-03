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
        std::string _phoneNumber;
    public:
        Person();
        Person(std::ifstream* fin);
        void read();
        void read(std::ifstream* fin);
        void write();
        void write(std::ofstream* fout);
        bool check(std::string& fullName, std::string& birthDate, std::string& phoneNumber);
        static char compare(Person& person1, Person& person2, char type);
        std::string getFullName();
        std::string getNumber();
        std::string getBirthDate();
        int daysBeforeBirthday();
};


#endif //PERSON_H
