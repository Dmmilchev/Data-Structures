#pragma once

template <typename T>
class AbstractStack {
public:

    virtual bool isEmpty() const = 0;

    virtual void push(T e) = 0;

    virtual T pop() = 0;

    virtual T peek() const = 0;
    
};