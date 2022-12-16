#ifndef _SIMPLE_LINKED_LIST_H_
#define _SIMPLE_LINKED_LIST_H_

#include "SimpleNodeInt.h"
#include <string>
#include <iostream>

class SimpleLinkedList{
    private:
        SimpleNodeInt* head;
        int size;

    public:
        SimpleLinkedList(): head{nullptr}, size{0}{std::cout << "No args constructor" << std::endl;};
        bool isEmpty();

        int valueInPosition(int position);
        int* positionsOfValue(int value);
        bool insert(int value, int position);
        bool remove(int position);
        std::string printList();        

        bool insertBeggining(int value);
    
        void sizePlus(int update);
        bool checkValidPosition(int position);
        SimpleNodeInt* getHead();
        void setHead(SimpleNodeInt* h);
        int getSize();
        void setSize(int s);
};

#endif