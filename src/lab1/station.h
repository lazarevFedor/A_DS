#ifndef A_DS_STATION_H
#define A_DS_STATION_H

#include <string>
#include <iostream>


class SortStation {
public:
    std::string getStr();

    int priority(char c);

    double operation(double a, double b, char c);

    bool calculate(std::string &output);

    std::string toRPN(std::string &inputStr, bool &errorFlag);
};


//StackNode class
template<typename Type> class StackNode {
public:
    Type data;
    int priority;
    StackNode* next;
    StackNode(Type &inputData, int inputPriority);
};


//StackNode constructor
template<typename Type> StackNode<Type>::StackNode(Type &inputData, int inputPriority) {
    data = inputData;
    priority = inputPriority;
    next = nullptr;
}


//Stack class
template<typename Type> class Stack {
public:
    StackNode<Type>* head, * tail;

    Stack();

    ~Stack();

    void popFront();

    void pushFront(Type data, int inputPriority);
};


//Stack constructor and destructor
template<typename Type> Stack<Type>::Stack(): head(nullptr), tail(nullptr){}


template<typename Type> Stack<Type>::~Stack() {
    while(head != nullptr) popFront();
}


//Stack methods
template<typename Type> void Stack<Type>::pushFront(Type data, int inputPriority) {
    auto* node = new StackNode<Type>(data, inputPriority);
    node->next = head;
    head = node;
    if (tail == nullptr) tail = node;
}


template<typename Type> void Stack<Type>::popFront() {
    if (head == nullptr) return;
    if (head == tail){
        delete tail;
        head = tail = nullptr;
        return;
    }
    StackNode<Type>* node = head;
    head = node->next;
    delete node;
}


#endif
