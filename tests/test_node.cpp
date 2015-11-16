#include <catch.hpp>
#include "node.h"

TEST_CASE( "a new node has data set to zero and a NULL nest pointer" ) {
    Node node;
    REQUIRE( node.getData() == 0 );
    REQUIRE( node.getNext() == NULL );
}

TEST_CASE( "setting private data works" ) {
    Node node;
    node.setData( 5 );
    REQUIRE( node.getData() == 5 );
    Node * ptr = &node;
    node.setNext( ptr );
    REQUIRE( node.getNext()->getData() == 5 );
}


