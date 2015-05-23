#ifndef LINKEDLISTELEMENT_H
#define LINKEDLISTELEMENT_H
#include <iostream>

template <typename T>
class LinkedListElement
{
public:
    LinkedListElement(T data, LinkedListElement *next = nullptr) {
        this->_data = data;
        this->_next = next;
    }
    LinkedListElement<T> *next() {
        return this->_next;
    }
    void setNext(LinkedListElement<T> *elem) {
        this->_next = elem;
    }
    T data() {
        return _data;
    }

private:
    LinkedListElement<T> *_next;
    T _data;
};
#endif // LINKEDLISTELEMENT_H

