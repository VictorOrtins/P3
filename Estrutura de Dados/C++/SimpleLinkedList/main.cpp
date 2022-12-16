#include <iostream>
#include "classes.h"

using std::cout;
using std::endl;

int main(void){

    // SimpleNodeInt node1;
    // node1.setValue(50);

    // SimpleNodeInt* node2 = new SimpleNodeInt();
    // node2->setValue(100);

    // node1.setNext(node2);
    // node2->setNext(&node1);

    // cout << "Node1 value: " << node1.getValue() << endl;
    // cout << "Node1 next: " << node1.getNext() << endl;
    // cout << "Node1 memory location: " << &node1 << endl;
    // cout << "Node2 value: " << node2->getValue() << endl;
    // cout << "Node2 next: " << node2->getNext() << endl;
    // cout << "Node2 memory location: " << &(*node2) << endl;

    SimpleLinkedList list;
    list.insertBeggining(10);
    list.insertBeggining(5);
    list.insertBeggining(3);

    cout << list.printList() << endl;

    return 0;
}