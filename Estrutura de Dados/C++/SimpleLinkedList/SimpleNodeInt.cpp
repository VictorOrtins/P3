#include "SimpleNodeInt.h"

SimpleNodeInt::SimpleNodeInt(int v, SimpleNodeInt* n){
    value = v;
    next = n;
}

void SimpleNodeInt::setValue(int v){
    value = v;
}

int SimpleNodeInt::getValue(){
    return value;
}

void SimpleNodeInt::setNext(SimpleNodeInt* n){
    next = n;
}

SimpleNodeInt* SimpleNodeInt::getNext(){
    return next;
}


