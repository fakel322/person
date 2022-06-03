#ifndef PERSONLIST_H
#define PERSONLIST_H

#include "../Person/Person.h"
#include <vector>

struct PersonNode {
    PersonNode();

    Person data;
    PersonNode* next;
};

class PersonList {
    private:
        PersonNode* _head;
        PersonNode* _end;
        int _size;
        PersonNode* merge(PersonNode* firstNode, PersonNode* secondNode, bool sortType);
        PersonNode* middle(PersonNode* head);
        PersonNode* sort_by(PersonNode* head, bool sortType);
    public:
        PersonList();
        explicit PersonList(int size);
        ~PersonList();
        int size();

        void add(Person&);
        void sort(bool sortType);
        void save(std::ofstream* fout);
        void remove(std::string fullName, std::string birthDate, std::string phoneNumber);
        friend std::ostream& operator<<(std::ostream &out, const PersonList &List);

        PersonNode& operator[](int index);
};

#endif