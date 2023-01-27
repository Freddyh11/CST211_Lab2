#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::move;

#include "Node.h"
#include "Exceptions.h"

template<typename T>class List {
private:
    
    Node<T>* l_head; // pointer to the head of the list
    Node<T>* l_tail; // pointer to the tail of the list
    int l_count; // number of nodes in the list
    
public:
    
    List(); // default constructor
    List(const T data); // parameterized constructor
    List(const List& copy); // copy constructor
    List(List&& move) noexcept; // move constructor
    ~List(); // deconstructor
    
    
    List& operator=(const List& copy); //copy assignment operator
    List& operator=(List&& move) noexcept; //move assignment operator
    explicit operator bool() const; // T if list is empty, otherwise F
    

    void Append(const T data); // put T data at the end of the list
    void Prepend(const T data); // put T data at the end of the list
    void RemoveLast(); // remove the last node of the list
    void RemoveFirst(); // remove the first node of the list
    void Extract(const T data); // remove the node that equals T data
    void InsertAfter(const T data, const T after); //insert T data after T after
    void InsertBefore(const T data, const T before); //insert T data before T before
    void Purge() noexcept; // delete all of the nodes in the list
    
    
    T& Last(); // return the address of the last element
    T Last() const; // return the value of the last element
    T& First(); // return the address of the first element
    T First() const; // return the value of the value element
    
    Node<T>* getHead(); // return the pointer to the head of the list
    Node<T>* getTail(); // return the pointer to the tail of the list
    bool isEmpty() const noexcept; // T if list is empty, otherwise F
    size_t Size() const noexcept; // return the size of the list
    bool operator==(const List<T>& rhs) const noexcept; // compare if 2 lists are equal
    
};



template <typename T>
List<T>::List() : l_head(nullptr), l_tail(nullptr), l_count(0) {} // initializing everything null/0

template <typename T>
List<T>::List(const T data)
{
    l_head = new Node<T>;
        l_tail = new Node<T>;
        l_head->next_ptr = l_tail;
        l_tail->prev_ptr = l_head;
        l_head->n_data = data;
        l_tail->n_data = data;
        l_head->prev_ptr = nullptr;
        l_tail->next_ptr = nullptr;
    l_count = 1;
    
}

template<typename T>
List<T>::List(const List& copy)
{
    l_count = copy.l_count;
    if (copy.l_head == nullptr)
    {
        l_head = nullptr;
        l_tail = nullptr;
    }
    else
    {
        Node<T>* current = copy.l_head;
        l_head = new Node<T>(current->n_data);
        Node<T>* newCurrent = l_head;
        current = current->next_ptr;
        while (current != nullptr)
        {
            newCurrent->next_ptr = new Node<T>(current->n_data);
            newCurrent = newCurrent->next_ptr;
            current = current->next_ptr;
        }
        l_tail = newCurrent;
    }
}


template<typename T>
List<T>::List(List&& move) noexcept
{
    l_count = move.l_count;
    l_head = move.l_head;
    l_tail = move.l_tail;
    move.l_count = 0;
    move.l_head = nullptr;
    move.l_tail = nullptr;
}


template<typename T>
List<T>::~List()
{
    Purge();
}

template<typename T>
List<T>& List<T>::operator=(const List& copy)
{
    if (this == &copy)
        return *this;

    Purge();

    l_count = copy.l_count;
    if (copy.l_head == nullptr)
    {
        l_head = nullptr;
        l_tail = nullptr;
    }
    else
    {
        Node<T>* current = copy.l_head;
        l_head = new Node<T>(current->n_data);
        Node<T>* newCurrent = l_head;
        current = current->next_ptr;
        while (current != nullptr)
        {
            newCurrent->next_ptr = new Node<T>(current->n_data);
            newCurrent = newCurrent->next_ptr;
            current = current->next_ptr;
        }
        l_tail = newCurrent;
    }
    return *this;
}


template<typename T>
List<T>& List<T>::operator=(List&& move) noexcept
{
    if (this == &move)
        return *this;

    Purge();

    l_count = move.l_count;
    l_head = move.l_head;
    l_tail = move.l_tail;
    move.l_count = 0;
    move.l_head = nullptr;
    move.l_tail = nullptr;

    return *this;
}


template<typename T>
List<T>::operator bool() const
{
    return l_head != nullptr; //make sure to check if head is not null and return that
}


template<typename T>
void List<T>::Append(const T data)
{
    if (l_head == nullptr)
    {
        l_head = new Node<T>(data);
        l_tail = l_head;
    }
    else
    {
        l_tail->next_ptr = new Node<T>(data);
        l_tail = l_tail->next_ptr;
    }
    l_count++;
}

template<typename T>
void List<T>::Prepend(const T data)
{
    Node<T>* newNode = new Node<T>(data);
    newNode->next_ptr = l_head;
    l_head = newNode;
    if (l_tail == nullptr)
    {
        l_tail = l_head;
    }
    l_count++;
}


template<typename T>
void List<T>::RemoveLast()
{
    if (l_head == nullptr)
        return;

    if (l_head == l_tail)
    {
        delete l_head;
        l_head = nullptr;
        l_tail = nullptr;
    }
    else
    {
        Node<T>* current = l_head;
        while (current->next_ptr != l_tail)
            current = current->next_ptr;

        delete l_tail;
        current->next_ptr = nullptr;
        l_tail = current;
    }
    l_count--;
}


template<typename T>
void List<T>::RemoveFirst()
{
    if (l_head == nullptr)
        return;

    Node<T>* temp = l_head;
    l_head = l_head->next_ptr;
    if (l_head == nullptr)
        l_tail = nullptr;
    delete temp;
    l_count--;
}


template<typename T>
void List<T>::Extract(const T data)
{
    if (isEmpty()) {
        throw Exception("IS EMPTY");
        return;
    }
    if (l_head->n_data == data) {
        RemoveFirst();
        return;
    }
    if (l_tail->n_data == data) {
        RemoveLast();
        return;
    }
    Node<T>* current_node = l_head->next_ptr;
    Node<T>* previous_node = l_head;
    while (current_node != nullptr) {
        if (current_node->n_data == data) {
            previous_node->next_ptr = current_node->next_ptr;
            current_node->next_ptr = nullptr;
            delete current_node;
            l_count--;
            return;
        }
        previous_node = current_node;
        current_node = current_node->next_ptr;
    }
    throw Exception("Data not found in the list");
}



template<typename T>
void List<T>::InsertAfter(const T data, const T after) {
    if (isEmpty()) {
        
        throw Exception("Cannot insert after an element in an empty list");
    }

    Node<T>* current_node = l_head;
    while (current_node != nullptr) {
        if (current_node->n_data == after) {
            
            Node<T>* new_node = new Node<T>(data);
            new_node->next_ptr = current_node->next_ptr;
            current_node->next_ptr = new_node;
            if (current_node == l_tail) {
                l_tail = new_node;
            }
            l_count++;
            return;
        }
        current_node = current_node->next_ptr;
    }
    
    throw Exception("Cannot insert after an element that is not in the list");
}

template<typename T>
void List<T>::InsertBefore(const T data, const T before) {
    if (isEmpty()) {
        // If the list is empty, we cannot insert before any elements
        throw Exception("Cannot insert before an element in an empty list");
    }

    if (l_head->n_data == before) {
        // If the element to insert before is the first element, use the Prepend method
        Prepend(data);
        return;
    }

    Node<T>* current_node = l_head->next_ptr;
    Node<T>* previous_node = l_head;
    while (current_node != nullptr) {
        if (current_node->n_data == before) {
            // We found the element to insert before
            Node<T>* new_node = new Node<T>(data);
            previous_node->next_ptr = new_node;
            new_node->next_ptr = current_node;
            l_count++;
            return;
        }
        previous_node = current_node;
        current_node = current_node->next_ptr;
    }
    // If we reach this point, we did not find the element to insert before
    throw Exception("Cannot insert before an element that is not in the list");
}


template<typename T>
void List<T>::Purge() noexcept
{
    Node<T>* current = l_head;
    while (current != nullptr)
    {
        Node<T>* next = current->next_ptr;
        delete current;
        current = next;
    }
    l_head = nullptr;
    l_tail = nullptr;
    l_count = 0;
}


template<typename T>
T& List<T>::Last()
{
    if(isEmpty()){ //check if empty
        throw Exception("List is empty"); // if empty throw
    }
    return l_tail->n_data;
}

template<typename T>
T List<T>::Last() const
{
    return l_tail->n_data;
}

template<typename T>
T& List<T>::First()
{
    if (isEmpty()) { // check if empty
        throw Exception("List is empty."); //throw
    }
    return l_head->n_data;
}

template<typename T>
T List<T>::First() const
{
   
    return l_head->n_data;
}

template <typename T>
Node<T>* List<T>::getHead()
{
    return l_head;
}

template <typename T>
Node<T>* List<T>::getTail()
{
    return l_tail;
}

template<typename T>
bool List<T>::isEmpty() const noexcept
{
    return l_head == nullptr && l_tail == nullptr ; // check if head, tial are nullptr -> dont hold anything
}


template<typename T>
size_t List<T>::Size() const noexcept
{
    size_t l_count = 0;
        Node<T>* current_node = l_head;
        while (current_node) {
            l_count++;
            current_node = current_node->next_ptr;
        }
        return l_count;
}


template<typename T>
bool List<T>::operator==(const List<T>& rhs) const noexcept
{
    if (l_count != rhs.l_count) {
        return false;
    }
    Node<T>* current_node = l_head;
    Node<T>* rhs_current_node = rhs.l_head;
    while (current_node) {
        if (current_node->data != rhs_current_node->data) {
            return false;
        }
        current_node = current_node->next;
        rhs_current_node = rhs_current_node->next;
    }
    return true;
}


#endif //LIST_TEMPLATE_H
