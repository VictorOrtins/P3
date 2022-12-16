#ifndef _SIMPLE_NODE_INT_
#define _SIMPLE_NODE_INT_

class SimpleNodeInt{
    private:
        int value;
        SimpleNodeInt *next;

    public:
        SimpleNodeInt(int v = 0, SimpleNodeInt* n = nullptr);
        int getValue();
        void setValue(int v);
        SimpleNodeInt* getNext();
        void setNext(SimpleNodeInt* n);
};

#endif