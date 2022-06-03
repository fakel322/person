#include "PersonList.h"

PersonNode::PersonNode() {
    this->next = nullptr;
}

PersonList::PersonList() {
    this->_head = nullptr;
    this->_end = nullptr;
    this->_size = 0;
}

PersonList::PersonList(int size) {
    this->_head = nullptr;
    this->_size = 0;
    Person a;
    for (int i = 0; i < size; i++)
    {
        this->add(a);
    }
}

PersonList::~PersonList(){
    this->remove("*", "*", "*");
}

void PersonList::add(Person& person) {
    PersonNode* node = new(PersonNode);
    node->data = person;
    if(this->_head == nullptr)
    {
        this->_head = node;
        this->_end = node;
        this->_head->next = nullptr;
    }
    else
    {
        _end->next = node;
        this->_end = node;
        this->_end->next = nullptr;
    }
    this->_size++;
}

int PersonList::size() {
    return this->_size;
}

PersonNode& PersonList::operator[](const int index) {
    if ((index > this->_size - 1) or (index < 0)){
        throw "OUT_OF_BOUNDS";
    }
    else {
        PersonNode *current = this->_head;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return *current;
    }
}

PersonNode* PersonList::merge(PersonNode* a, PersonNode* b)
{
    if(a == nullptr) return b;
    if(b == nullptr) return a;

    PersonNode* c;

    if(Person::compare(a->data, b->data, 1) == 0)
    {
        c = a;
        c->next = merge(a->next, b);
    }
    else
    {
        c = b;
        c->next = merge(a, b->next);
    }

    return c;
}

PersonNode* PersonList::middle(PersonNode* head)
{
    if(head == nullptr || head->next == nullptr)
        return head;

    PersonNode* fast = head;
    PersonNode* slow = head;

    while(fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next;
        if(fast->next == nullptr)
            break;

        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}

PersonNode* PersonList::sort(PersonNode* head)
{
    if(head == nullptr || head->next == nullptr)
        return head;
    PersonNode* mid = middle(head);
    PersonNode* a = head;
    PersonNode* b = mid->next;

    mid->next = nullptr;

    a = sort(a);
    b = sort(b);
    PersonNode* c = merge(a, b);

    return c;
}

void PersonList::addToSorted(Person& person) {
    PersonNode *current = this->_head;
    for(int i = 0; i < this->size(); i++){
        if(Person::compare(person, current->data, 1) > 0){
            this->insert(person,i);
            return;
        }
        current = current->next;
    }
    this->add(person);
}

PersonNode *PersonList::insert(Person& person, int pos) {
    auto *node = new(PersonNode);
    node->data = person;
    if((pos != 0) && (pos != this->_size)) {
        PersonNode *rel = &(*this)[pos - 1];
        node->next = rel->next;
        rel->next = node;
        return rel->next;
    }
    else{
        if(pos == 0) {
            node->next = this->_head;
            this->_head = node;
            return this->_head;
        }
        else {
            this->add(person);
        }
    }
}

void PersonList::remove(std::string fullName, std::string birthDate, std::string phoneNumber) {
    while((this->_head != nullptr) && (this->_head->data.check(fullName, birthDate, phoneNumber))){
        auto* temp = this->_head->next;
        delete(this->_head);
        this->_head = temp;
        this->_size--;
    }
    if (this->_head == nullptr) return;
    PersonNode* current = this->_head;
    while((current!=nullptr) and (current->next!=nullptr)){
        if(current->next->data.check(fullName, birthDate, phoneNumber)){
            auto* temp = current->next->next;
            delete(current->next);
            current->next = temp;
            this->_size--;
        }
        else {
            current = current->next;
        }
    }
}

void PersonList::save(std::ofstream* fout) {
    PersonNode* current = this->_head;
    for (int i = 0; i < this->size()-1; i++){
        current->data.write(fout);
        current = current->next;
    }
    this->_end->data.write(fout);
}

PersonNode *PersonList::getHead(){
    return this->_head;
}

void PersonList::setHead(PersonNode *nhead) {
    this->_head = nhead;
    return;
}

void PersonList::resetEnd(){
    this->_end = this->size() == 0 ? nullptr : &(*this)[this->size()-1];
}

PersonNode *PersonList::getEnd(){
    return this->_end;
}