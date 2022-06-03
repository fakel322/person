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
        PersonNode *_head;
        PersonNode *_end;
        int _size;
        PersonNode* merge(PersonNode *firstNode, PersonNode *secondNode);
        PersonNode* middle(PersonNode *head);
    public:
        PersonList();
        explicit PersonList(int size);
        ~PersonList();
        int size();

        PersonNode *getHead();
        PersonNode *getEnd();
        void resetEnd();
        void setHead(PersonNode *nhead);

        void add(Person&);
        PersonNode *sort(PersonNode *lhead);
        void addToSorted(Person&);
        PersonNode *insert(Person&, int pos);
        void save(std::ofstream* fout);
        void remove(std::string fullName, std::string birthDate, std::string phoneNumber);


        PersonNode& operator[](int index);
};

#endif