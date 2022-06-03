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

PersonNode* PersonList::merge(PersonNode* a, PersonNode* b, bool sortType)
{
    if(a == nullptr) return b;
    if(b == nullptr) return a;

    PersonNode* c;

    if(Person::compare(a->data, b->data, sortType ? 0 : 1) == 0)
    {
        c = a;
        c->next = merge(a->next, b, sortType);
    }
    else
    {
        c = b;
        c->next = merge(a, b->next, sortType);
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

PersonNode* PersonList::sort_by(PersonNode* head, bool sortType)
{
    if(head == nullptr || head->next == nullptr)
        return head;
    PersonNode* mid = middle(head);
    PersonNode* a = head;
    PersonNode* b = mid->next;

    mid->next = nullptr;

    a = sort_by(a, sortType);
    b = sort_by(b, sortType);

    PersonNode* c = merge(a, b, sortType);
    return c;
}

void PersonList::sort(bool sortType)
{
    PersonNode* head = sort_by(this->_head, sortType);
    this->_head = head;
    this->_end = this->size() == 0 ? nullptr : &(*this)[this->size()-1];
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

std::ostream &operator<<(std::ostream &out, const PersonList &List) {
    PersonNode* current = List._head;
    while(current != nullptr){
        out << current->data.getFullName() << ", " << current->data.getBirthDate() << ", " << current->data.getNumber() << std::endl;
        current = current->next;
    }
    return out;
}
