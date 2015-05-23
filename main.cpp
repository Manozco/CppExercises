#include <iostream>
#include "src/linkedlist.h"
#include "src/binarysearchtree.h"

int main()
{
    LinkedList<int> *l = new LinkedList<int>;
    l->prependElement(3);
    l->prependElement(5);
    l->prependElement(6);
    l->insertElement(5, new LinkedListElement<int>(12));
    l->print();
    l->deleteElement(5);
    l->print();
    std::cout << "============" << std::endl;
    BinarySearchTree<int> t(5);
    t.insert(40);
    t.insert(60);
    t.insert(-10);
    t.insert(2);
    t.insert(91);
    t.insert(4);
    t.insert(6);
    t.insert(18);
    t.insert(17);
    t.insert(50);
    t.print();
    t.deleteNode(t.find(40), 0);
    std::cout << "==" << std::endl;
    t.print();

    return 0;
}

