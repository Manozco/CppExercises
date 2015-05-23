#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "linkedlistelement.h"

template <typename T>
class LinkedList
{
public:
    LinkedList(){}
    LinkedListElement<T> *head() {
        return this->_head;
    }

    bool prependElement(LinkedListElement<T> *element) {
        element->setNext(this->_head);
        this->_head = element;
        return true;
    }

    bool prependElement(T data) {
        LinkedListElement<T> *elem = new LinkedListElement<T>(data);
        return this->prependElement(elem);
    }

    bool insertElement(T previousData, LinkedListElement<T> *element) {
        LinkedListElement<T> *cur_element = head();
        while (cur_element->data() != previousData) {
            cur_element = cur_element->next();
            if (nullptr == cur_element) {
                return false;
            }
        }
        element->setNext(cur_element->next());
        cur_element->setNext(element);
        return true;
    }

    bool deleteElement(T data) {
        LinkedListElement<T> *cur = this->head();
        if (nullptr == cur)
            return false;
        if (cur->data() == data) {
            // We want to delete the head
            _head = cur->next();
            delete cur;
            return true;
        }
        while (cur->next()) {
            if (cur->next()->data() == data) {
                LinkedListElement<T> *toDelete = cur->next();
                cur->setNext(cur->next()->next());
                delete toDelete;
                return true;
            }
            cur = cur->next();
        }
        return false;
    }

    void print() {

        LinkedListElement<T> *elem = this->head();
        while (elem) {
            std::cout << elem->data() << " ";
            elem = elem->next();
        }
        std::cout << std::endl;
    }

private:
    LinkedListElement<T> *_head;

};

#endif // LINKEDLIST_H
