#pragma once

class Node {
    private: 
        int data;
        Node * Next;
    public:
        // constructors
        Node();

        // accessors
        int getData( void );
        Node * getNext( void );

        // mutators
        void setData( int item );
        void setNext( Node * ptr );
};

