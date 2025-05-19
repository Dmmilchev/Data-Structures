#pragma once

#include "abstract_stack.hpp"

template <typename T>
class LStack : AbstractStack<T> {
private:

    struct Node {
        T data;
        Node* next = nullptr;

        Node(T data) : data(data), next(nullptr) {}
    };

    Node* head = nullptr;

    void free();

    void copyFrom(const LStack& other);

public:
    LStack();

    LStack(const LStack& other);

    LStack& operator=(const LStack& other);

    ~LStack();


    bool isEmpty() const override;

    void push(T e) override;

    T pop() override;

    T peek() const override;


};


template <typename T>
void LStack<T>::free()
{
    while (head) {
        Node* tmp = head;
        head = head->next;
        if (tmp == nullptr)
            std::cout << "yes";
        delete tmp;
    }
}

template <typename T>
void LStack<T>::copyFrom(const LStack<T>& other)
{
    if (other.isEmpty())
        return;

    Node* tmp = other.head;
    head = new Node(tmp->data);
    Node* curr = head; 
    tmp = tmp->next;
    while (tmp) {
        curr->next = new Node(tmp->data);
        curr = curr->next;
        tmp = tmp->next;
    }   
}

template <typename T>
LStack<T>::LStack() { }

template <typename T>
LStack<T>::LStack(const LStack<T>& other) { copyFrom(other); }

template <typename T>
LStack<T>& LStack<T>::operator=(const LStack<T>& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LStack<T>::~LStack() { free(); }


template <typename T>
bool LStack<T>::isEmpty() const { return head == nullptr; }

template <typename T>
void LStack<T>::push(T e)
{
    Node* n = new Node(e);
    n->next = head;
    head = n;
}

template <typename T>
T LStack<T>::pop()
{
    T data = head->data;
    Node* tmp = head;
    head = head->next;
    delete tmp;
    return data;
}

template <typename T>
T LStack<T>::peek() const { return head->data; }
