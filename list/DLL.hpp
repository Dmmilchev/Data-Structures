#pragma once

#include <iostream>
#include <exception>

template <typename T>
class DLList {
private:

    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T data): data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

    void free();
    void copyFrom(const DLList& other);

public:
    // Constructors
    DLList();
    DLList(T data[], int size);
    DLList(const DLList& other);
    DLList& operator=(const DLList& other);

    // Move
    DLList(DLList&& other);
    DLList& operator=(DLList&& other);

    // Destructor
    ~DLList();

    T getLast() const;
    T getFirst() const;

    void popLast();
    void popFirst();

    void pushBack(T data);
    void pushFront(T data);

    void print() const;
};

template <typename T>
void DLList<T>::free()
{
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <typename T>
void DLList<T>::copyFrom(const DLList<T>& other)
{
    Node* iter = other.head;
    while (iter) {
        this->pushBack(iter->data);
        iter = iter->next;
    }
}

template <typename T>
DLList<T>::DLList() : head(nullptr), tail(nullptr) {}

template <typename T>
DLList<T>::DLList(T data[], int size) : head(nullptr), tail(nullptr){
    for(int i = 0; i < size; ++i)
        this->pushBack(data[i]);
}

template <typename T>
DLList<T>::DLList(const DLList<T>& other) { copyFrom(other); }

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
DLList<T>::DLList(DLList<T>&& other) 
{
    head = other.head;
    tail = other.tail;
}

template <typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& other)
{
    if (this != &other) {
        head = other.head;
        tail = other.tail;
    }
    return *this;
}

template <typename T>
DLList<T>::~DLList() { free(); }

template <typename T>
T DLList<T>::getLast() const 
{ 
    if (!tail) 
        throw std::logic_error("Empty list");
    return tail.data; 
}

template <typename T>
T DLList<T>::getFirst() const 
{
    if (!head) 
        throw std::logic_error("Empty list");
    return tail.data; 
}

template <typename T>
void DLList<T>::popLast() 
{
    if (!head)
        return;

    Node* tmp = tail;
    tail = tail->prev;
    delete tmp;
    tmp = nullptr;
    tail->next = nullptr;
}

template <typename T>
void DLList<T>::popFirst() 
{
    if(!head)
        return;
    
    if (head == tail)
        tail = nullptr;

    Node* tmp = head;
    head = head->next;
    delete tmp;
    tmp = nullptr;
    head->prev = nullptr;
}

template <typename T>
void DLList<T>::pushBack(T data)
{
    if (head == nullptr && tail == nullptr) {
        head = new Node(data);
        tail = head;
    } else {
        Node* tmp = new Node(data);
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
}

template <typename T>
void DLList<T>::pushFront(T data) 
{
    if (head == nullptr && tail == nullptr) {
        head = new Node(data);
        tail = head;
    } else {
        Node* tmp = new Node(data);
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }
}

template <typename T>
void DLList<T>::print() const 
{
    Node* iter = head;
    while (iter) {
        std::cout << iter->data << " ";
        iter = iter->next;
    }
    std::cout << std::endl;
}