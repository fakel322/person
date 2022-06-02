#include "Person.h"
#include "classes/Util/Util.h"
#include <iostream>
#include <vector>

void Person::read()
{
    std::string name, surname, middleName, birthDate;

    std::cout << "Enter person's name:";
    std::cin >> name;

    while(!Util::checkName(name, "Invalid name, try again."))
    {
        std::cin >> name;
    }
    this->_name = name;

    std::cout << "Enter person's surname:";
    std::cin >> surname;

    while(!Util::checkName(surname, "Invalid surname, try again."))
    {
        std::cin >> surname;
    }
    this->_surname = surname;

    std::cout << "Enter person's middle name:";
    std::cin >> middleName;

    while(!Util::checkName(middleName, "Invalid middle name, try again."))
    {
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
    std::cout << "Name: " << this->_name << std::endl;
    std::cout << "Surname: " << this->_surname << std::endl;
    std::cout << "Middle name: " << this->_middleName << std::endl;
    std::cout << "Birth: " << this->_birthDay << '.' << this->_birthMonth << '.' << this->_birthYear << "\n\n";
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