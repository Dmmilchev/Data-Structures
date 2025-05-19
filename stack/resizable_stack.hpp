#pragma once

#include <stdexcept>
#include "abstract_stack.hpp"

template <typename T>
class RStack : AbstractStack<T>{
private:
    T* data = nullptr;
    unsigned int size = 0;
    unsigned int capacity = 0;

    void resize();
    void free();
    void copyFrom(const RStack& other);

public:
    RStack();
    RStack(unsigned capacity);
    RStack(const RStack& other);
    RStack& operator=(const RStack& other);
    ~RStack();
    RStack(RStack&& other);
    RStack& operator=(RStack&& other);

    bool isEmpty() const override;
    void push(T e) override;
    T pop() override;
    T peek() const override;

};

template <typename T>
RStack<T>::RStack() : RStack(16) {}

template <typename T>
void RStack<T>::resize()
{
    T* newData = new T[capacity * 2];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];

    free();
    data = newData;
    capacity *= 2;
}

template <typename T>
void RStack<T>::free() { delete[] data; }

template <typename T>
void RStack<T>::copyFrom(const RStack& other) 
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

// template <typename T>
// RStack<T>::RStack() : RStack(16) {}

template <typename T>
RStack<T>::RStack(unsigned capacity) 
{
    size = 0; 
    this->capacity = capacity;
    data = new T[capacity];
}

template <typename T>
RStack<T>::RStack(const RStack& other) { copyFrom(other); }

template <typename T>
RStack<T>& RStack<T>::operator=(const RStack<T>& other) 
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
RStack<T>::~RStack() { free(); }

template <typename T>
RStack<T>::RStack(RStack<T>&& other)
{
    capacity = other.capacity;
    size = other.size;
    data = other.data;

    other.data = nullptr;
    other.size = 0;
}

template <typename T>
RStack<T>& RStack<T>::operator=(RStack<T>&& other) 
{
    if (this != &other){
        capacity = other.capacity;
        size = other.size;
        data = other.data;

        other.data = nullptr;
        other.size = 0;    
    }
    return *this;
}

template <typename T>
bool RStack<T>::isEmpty() const { return size == 0; }

template <typename T>
void RStack<T>::push(T e)
{
    if (size == capacity) 
        resize();
    data[size++] = e;
}

template <typename T>
T RStack<T>::pop() 
{
    if (isEmpty())
        throw std::logic_error("Stack is empty");
    
    return data[--size];
}

template <typename T>
T RStack<T>::peek() const
{
    if (isEmpty())
        throw std::logic_error("Stack is empty");
    
    return data[size - 1];
}
