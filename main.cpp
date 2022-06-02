#include "classes/Person/Person.h"
#include <iostream>

int main()
{
    Person person1, person2;
    person1.read();
    person2.read();

    person1.write();
    person2.write();
    std::cout << (int)Person::compare(person1, person2, 0) << std::endl;
}
