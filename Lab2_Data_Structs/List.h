//
//  List.h
//  Lab2_Data_Structs
//
//  Created by Freddy Hernandez on 1/18/23.
//

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
    Node<T>* l_head;
    Node<T>* l_tail;
    int l_count;
    
public:
    List();
    List(const T data);
    List(const List& copy);
    List(List&& move) noexcept;
    ~List();

    List& operator=(const List& copy);
    List& operator=(List&& move) noexcept;
    explicit operator bool() const;

    void Append(const T data);
    void Prepend(const T data);
    void RemoveLast();
    void RemoveFirst();
    void Extract(const T data);
    void InsertAfter(const T data, const T after);
    void InsertBefore(const T data, const T before);
    void Purge() noexcept;

    T& Last();
    T Last() const;
    T& First();
    T First() const;

    Node<T>* getHead();
    Node<T>* getTail();
    bool isEmpty() const noexcept;
    size_t Size() const noexcept;
    bool operator==(const List<T>& rhs) const noexcept;
};

template <typename T>
List<T>::List() : l_head(nullptr), l_tail(nullptr), l_count(0) { }

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
    return l_head != nullptr;
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
    if (l_head == nullptr)
        return;

    if (l_head->n_data == data)
    {
        Node<T>* temp = l_head;
        l_head = l_head->next_ptr;
        if (l_head == nullptr)
            l_tail = nullptr;
        delete temp;
        l_count--;
        return;
    }

    Node<T>* current = l_head;
    while (current->next_ptr != nullptr && current -> next_ptr -> n_data != data)
        current = current->next_ptr;

    if (current->next_ptr == nullptr)
        return;

    Node<T>* temp = current->next_ptr;
    current->next_ptr = current->next_ptr->next_ptr;
    if (current->next_ptr == nullptr)
        l_tail = current;
    delete temp;
    l_count--;
}


template<typename T>
void List<T>::InsertAfter(const T data, const T after)
{
    if (l_head == nullptr)
        return;

    Node<T>* current = l_head;
    while (current != nullptr && current->n_data != after)
        current = current->next_ptr;

    if (current == nullptr)
        return;

    Node<T>* newNode = new Node<T>(data);
    newNode->next_ptr = current->next_ptr;
    current->next_ptr = newNode;
    if (current == l_tail)
        l_tail = newNode;
    l_count++;
}

template<typename T>
void List<T>::InsertBefore(const T data, const T before)
{
    if (l_head == nullptr)
        return;

    if (l_head->n_data == before)
    {
        Prepend(data);
        return;
    }

    Node<T>* current = l_head;
    while (current->next_ptr != nullptr && current -> next_ptr -> n_data != before)
        current = current->next_ptr;

    if (current->next_ptr == nullptr)
        return;

    Node<T>* newNode = new Node<T>(data);
    newNode->next_ptr = current->next_ptr;
    current->next_ptr = newNode;
    l_count++;
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
        return l_head == nullptr;
}

template<typename T>
size_t List<T>::Size() const noexcept
{
    return l_count;
}


template<typename T>
bool List<T>::operator==(const List<T>& rhs) const noexcept {
    if (Size() != rhs.Size()) {
        return false;
    }

    Node<T>* lhs_current = l_head;
    Node<T>* rhs_current = rhs.l_head;
    while (lhs_current != nullptr) {
        if (lhs_current->data != rhs_current->data) {
            return false;
        }
        lhs_current = lhs_current->next;
        rhs_current = rhs_current->next;
    }
    return true;
}


#endif //LIST_TEMPLATE_H
