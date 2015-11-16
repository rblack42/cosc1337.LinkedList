#include "Node.h"
#include <iostream>

/// constructors
Node::Node() {
    this->Next = NULL;
    this->data = 0;
}

/// accessors
int Node::getData( void ) {
    /// return data iten from this node
    return this->data;
}

Node * Node::getNext( void ) {
    /// return pointer to next node
    return this->Next;
}

/// mutators
void Node::setData( int item ) {
    /// update data item
    this->data = item;
}

void Node::setNext( Node * ptr ) {
    /// update pointer to next node
    this->Next = ptr;
}




