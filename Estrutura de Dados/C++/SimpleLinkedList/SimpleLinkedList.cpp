#include "SimpleLinkedList.h"
#include <stdlib.h>

bool SimpleLinkedList::isEmpty(){
    if (size == 0){
        return true;
    }

    return false;
}

bool SimpleLinkedList::checkValidPosition(int position){
    return position > 0 && position <= size;
}

void SimpleLinkedList::sizePlus(int update){
    size += update;
}

int SimpleLinkedList::getSize(){
    return size;
}

void SimpleLinkedList::setSize(int s){
    size = s;
}

SimpleNodeInt* SimpleLinkedList::getHead(){
    return head;
}

void SimpleLinkedList::setHead(SimpleNodeInt* h){
    head = h;
}

int SimpleLinkedList::valueInPosition(int position){
    SimpleNodeInt *aux{head};
    if (checkValidPosition(position)){
        return -1;
    }

    //position = 3
    for(int i = 1; i < position; i++){
        aux = aux->getNext(); //aux 1
    }

    return aux->getValue();
}

int* SimpleLinkedList::positionsOfValue(int value){
    SimpleNodeInt *aux{head};
    int* array_of_positions{(int*)malloc(sizeof(int)*10)};
    int array_count{0};
    int position_count{0};

    while(aux->getNext() != nullptr){
        if (aux->getValue() == value){
            array_of_positions[array_count] = position_count;
            array_count++;
        }

        // aux = (*aux).getNext();
        aux = aux->getNext();
        position_count++;
    }

    return array_of_positions;
}

bool SimpleLinkedList::insertBeggining(int value){
    // SimpleNodeInt* aux{head};


    std::cout << "At insert beggining" << std::endl;

    SimpleNodeInt *newHead = new SimpleNodeInt(10, head);

    head = newHead;
    sizePlus(1);

    return true;
}

std::string SimpleLinkedList::printList(){
    std::cout << "At print list" << std::endl;
    SimpleNodeInt* aux{head};
    std::string ret{};
    ret+= "[ ";

    while(aux->getNext() != nullptr){
        ret+= aux->getValue() + " ";
        aux = aux->getNext();
    }

    // std::cout << aux->getValue() + " " + aux->getNext()->getValue() << aux->getNext()->getNext()->getValue() << std::endl;

    // // ret+= aux->getValue() + " ";
    // // aux = aux->getNext();

    // // ret+= aux->getValue() + " ";
    // // aux = aux->getNext();

    // // ret+= aux->getValue() + " ";
    // // aux = aux->getNext();

    ret += " ]";

    return ret;
}



