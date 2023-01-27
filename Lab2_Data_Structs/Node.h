//
//  Node.h
//  Lab2_Data_Structs
//
//  Created by Freddy Hernandez on 1/18/23.
//

#ifndef NODETEMPLATE_H
#define NODETEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template<typename T>class Node {
private:
    T n_data;
    Node<T>* next_ptr;
    Node<T>* prev_ptr;

    template<typename U> friend class List;
    
public:
    Node();
    Node(const Node& copy);
    Node(Node&& copy) noexcept;
    Node(const T data);
    Node(const T data, Node<T>* next, Node<T>* prev);
    ~Node() = default;

    Node<T>& operator=(const Node& copy);
    Node<T>& operator=(Node&& copy) noexcept;

    T& Value() noexcept;
    T Value() const noexcept;
    void Value(const T data);

    Node<T>* Next() noexcept;
    Node<T>* Next() const noexcept;
    Node<T>* Previous() noexcept;
    Node<T>* Previous() const noexcept;
    void Next(Node<T>* const next) noexcept;
    void Previous(Node<T>* const previous) noexcept;
};

template<typename T>
Node<T>::Node() : n_data{}, next_ptr(nullptr), prev_ptr(nullptr) {}

template<typename T>
Node<T>::Node(const Node& copy): n_data(copy.n_data), next_ptr(copy.next_ptr), prev_ptr(copy.prev_ptr) {}

template<typename T>
Node<T>::Node(Node&& copy) noexcept
    : n_data(std::move(copy.n_data)), next_ptr(copy.next_ptr), prev_ptr(copy.prev_ptr) {
    copy.next_ptr = nullptr;
    copy.prev_ptr = nullptr;
}

template<typename T>
Node<T>::Node(const T data) : n_data(data), next_ptr(nullptr), prev_ptr(nullptr) {}

template<typename T>
Node<T>::Node(const T data, Node<T>* next, Node<T>* prev) : n_data(data), next_ptr(next), prev_ptr(prev) {}


template<typename T>
Node<T>& Node<T>::operator=(const Node& copy) {
    if (this != &copy) {
        n_data = copy.n_data;
        next_ptr = copy.next_ptr;
        prev_ptr = copy.prev_ptr;
    }
    return *this;
}

template<typename T>
Node<T>& Node<T>::operator=(Node&& copy) noexcept {
    if (this != &copy) {
        n_data = std::move(copy.n_data);
        next_ptr = copy.next_ptr;
        prev_ptr = copy.prev_ptr;
        copy.next_ptr = nullptr;
        copy.prev_ptr = nullptr;
    }
    return *this;
}

template<typename T>
T& Node<T>::Value() noexcept {
    return n_data;
}

template<typename T>
T Node<T>::Value() const noexcept {
    return n_data;
}

template<typename T>
void Node<T>::Value(const T data) {
    n_data = data;
}

template<typename T>
Node<T>* Node<T>::Next() noexcept {
    return next_ptr;
}

template<typename T>
Node<T>* Node<T>::Next() const noexcept {
    return next_ptr;
}

template<typename T>
Node<T>* Node<T>::Previous() noexcept {
    return prev_ptr;
}

template<typename T>
Node<T>* Node<T>::Previous() const noexcept {
    return prev_ptr;
}

template<typename T>
void Node<T>::Next(Node<T>* const next) noexcept {
    next_ptr = next;
}

template<typename T>
void Node<T>::Previous(Node<T>* const previous) noexcept {
    prev_ptr = previous;
}



#endif //NODE_TEMPLATE_H

