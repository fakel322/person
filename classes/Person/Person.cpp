#include "Person.h"
#include "classes/Util/Util.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

void Person::read()
{
    std::string name, surname, middleName, birthDate, number;

    std::cout << "Enter person's name:";
    std::cin >> name;

    while(!Util::checkName(name))
    {
        std::cout << "Invalid name, try again.\n";
        std::cin >> name;
    }
    this->_name = name;

    std::cout << "Enter person's surname:";
    std::cin >> surname;

    while(!Util::checkName(surname))
    {
        std::cout << "Invalid surname, try again.\n";
        std::cin >> surname;
    }
    this->_surname = surname;

    std::cout << "Enter person's middle name:";
    std::cin >> middleName;

    while(!Util::checkName(middleName))
    {
        std::cout << "Invalid middle name, try again.";
        std::cin >> middleName;
    }
    this->_middleName = middleName;

    std::cout << "Enter person's birth date:";
    std::cin >> birthDate;

    while(!Util::checkBirth(birthDate))
    {
        std::cout << "Invalid birthdate, try again." << std::endl;
        std::cin >> birthDate;
    }

    std::cout << "Enter person's phone number:";
    std::cin >> number;

    while(!Util::checkNumber(number))
    {
        std::cout << "Invalid phone number, try again." << std::endl;
        std::cin >> number;
    }
    this->_phoneNumber = number;

    std::vector<int> birthNums = Util::birthNumsFrom(birthDate);
    this->_birthDay = birthNums[0];
    this->_birthMonth = birthNums[1];
    this->_birthYear = birthNums[2];
}

void Person::write()
{
    if(this->_name.empty() || this->_surname.empty() || !this->_birthDay || !this->_birthMonth || !this->_birthYear)
    {
        std::cout << "Person not initialized" << std::endl;
        return;
    }
    std::cout << this->getFullName() << ", " << this->getBirthDate() << ", " << this->getNumber() << std::endl;
}

char Person::compare(Person &person1, Person &person2, char type) {
    if (type == 0) //LEXER
    {
        return (
            person1._surname == person2._surname ?
            person1._name == person2._name ?
            person1._middleName == person2._middleName ?
            (char)-1 :
            (char)(person1._middleName > person2._middleName) :
            (char)(person1._name > person2._middleName) :
            (char)(person1._surname > person2._surname)
        );
    }
    else //BIRTH
    {
        return (
                person1._birthYear == person2._birthYear ?
                person1._birthMonth == person2._birthMonth ?
                person1._birthDay == person2._birthDay ?
                (char)-1 :
                (char)(person1._birthDay < person2._birthDay) :
                (char)(person1._birthMonth < person2._birthMonth) :
                (char)(person1._birthYear < person2._birthYear)
        );
    }
}

bool Person::check(std::string& fullName, std::string& birthDate, std::string& phoneNumber) {
    if(fullName != "*" && fullName != this->getFullName()) return false;
    if(birthDate != "*" && birthDate != this->getBirthDate()) return false;
    if(phoneNumber != "*" && phoneNumber != this->getNumber()) return false;

    return true;
}

std::string Person::getFullName() {
    return this->_surname + " " + this->_name + " " + this->_middleName;
}

std::string Person::getBirthDate() {
    return (this->_birthDay > 10 ? std::to_string(this->_birthDay) : ("0" + std::to_string(this->_birthDay))) + "."
        + (this->_birthMonth > 10 ? std::to_string(this->_birthMonth) : ("0" + std::to_string(this->_birthMonth))) + "."
        + std::to_string(this->_birthYear);
}

std::string Person::getNumber() {
    return this->_phoneNumber;
}

void Person::read(std::ifstream* fin){
    std::string data;
    if (fin->is_open())
    {
        std::getline(*fin, data);

        int start = 0;
        int end = data.find(' ');

        std::string surname = data.substr(start, end - start);
        if(!Util::checkName(surname)) return;
        this->_surname = surname;
        start = end + 1;
        end = data.find(' ', start);

        std::string name = data.substr(start, end - start);
        if(!Util::checkName(name)) return;
        this->_name = name;
        start = end + 1;
        end = data.find(", ", start);

        std::string midName = data.substr(start, end - start);
        if(!Util::checkName(midName)) return;
        this->_middleName = midName;
        start = end + 2;
        end = data.find(", ", start);

        std::string birthDate = data.substr(start, end - start);
        if(!Util::checkBirth(birthDate)) return;
        std::vector<int> birthNums = Util::birthNumsFrom(birthDate);
        this->_birthDay = birthNums[0];
        this->_birthMonth = birthNums[1];
        this->_birthYear = birthNums[2];
        start = end + 2;
        end = data.find(", ", start);

        std::string phoneNumber = data.substr(start, end - start);
        if(!Util::checkNumber(phoneNumber)) return;
        this->_phoneNumber = phoneNumber;
    }
    else {
        std::cout << "Unable to open the file.";
    }
}

void Person::write(std::ofstream* fout){
    if (fout->is_open()){
        *fout << this->getFullName() << ", " << this->getBirthDate() << ", " << this->getNumber() << std::endl;
    }
    else
    {
        std::cout << "Unable to open the file";
    }
}

Person::Person(std::ifstream* fin) {
    this->read(fin);
}

Person::Person() {
    this->_name = "";
    this->_surname = "";
    this->_middleName = "";
}

int Person::daysBeforeBirthday() {
    std::vector<int> birthNums = Util::birthNumsFrom(this->getBirthDate());
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    int year = now->tm_mon+1 < birthNums[1] ? now->tm_year :
            now->tm_mon+1 == birthNums[1] && now ->tm_mday <= birthNums[0] ? now->tm_year :
            now->tm_year + 1;
    birthNums[2] = year+1900;
    std::vector<int> todayNums = { now->tm_mday, now->tm_mon+1, now->tm_year+1900 };

    return Util::dateDiff(todayNums, birthNums);
}
