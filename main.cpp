#include <iostream>
#include "src/linkedlist.h"
#include "src/bsearchtree.h"
#include "src/rbtree.h"
#include <time.h>
#include "src/prettyprintrbtree.h"

int main()
{
//    LinkedList<int> *l = new LinkedList<int>;
//    l->prependElement(3);
//    l->prependElement(5);
//    l->prependElement(6);
//    l->insertElement(5, new LinkedListElement<int>(12));
//    l->print();
//    l->deleteElement(5);
//    l->print();
//    std::cout << "============" << std::endl;
//    RBTree<int> t(5);
    RBTree<int> t;
    srand (1);
    for (int i = 0; i < 18; i++) {
//        t.insert(rand());
        t.insert(i);
    }
//    t.insert(40);
//    t.insert(60);
//    t.insert(-10);
//    t.insert(2);
//    t.insert(91);
//    t.insert(4);
//    t.insert(6);
//    t.insert(18);
//    t.insert(17);
//    t.insert(50);
    printPretty(&t, 1, 0, std::cout);
//    std::cout << t.min()->data() << std::endl;
//    std::cout << t.max()->data() << std::endl;
    t.deleteNode(t.find(11));
    printPretty(&t, 1, 0, std::cout);
//    t.print();
//    t.deleteNode(t.find(40), 0);
//    std::cout << "==" << std::endl;
//    t.print();

    return 0;
}

