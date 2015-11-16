#include "List.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/// Constructors
List::List() {
    /// default constructor
    size = 0;
    list = NULL;
}

/// Accessors
int List::getSize( void ) {
    /// return number of items in the list
    return size;
}

Node * List::getList( void ) {
    /// return pointer to first nod ein the list
    return this->list;
}

void List::print( void ) {
    /// print list data to stdout
    cout << "List:";
    Node * ptr = list;
    while( ptr != NULL ) {
        cout << ptr->getData() << " ";
        ptr = ptr->getNext();
    }
    cout << endl;
}

string List::toString( void ) {
    /// returns a space separated string with list contents
    stringstream ss;
    Node * ptr = list;
    while( ptr != NULL ) {
        ss << ptr->getData() << " ";
        ptr = ptr->getNext();
    }
    return ss.str();
}

// mutators
void List::addItem( int item ) {
    /// add new item to the list in front
    Node * n = new Node;            // create new node
    n->setData( item );             // save the item
    n->setNext( this->list );       // node point to old list
    this->list = n;                 // list points to new node
    this->size += 1;                // increase list size
}



