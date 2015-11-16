#pragma once
#include "Node.h"
#include <string>
using namespace std;


class List {
    private: 
        int size;
        Node * list;
    public:
        // constructors
        List();

        // accessors
        int getSize( void );
        Node * getList( void );
        string toString( void );
        void print( void );

        // mutators
        void addItem( int item );
};

