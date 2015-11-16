#include <catch.hpp>
#include "List.h"

TEST_CASE( "a new list returns a length of zero" ) {
    List list;
    REQUIRE( list.getSize() == 0 );
}

TEST_CASE( "adding an item increases the size by one" ) {
    List list;
    int size = list.getSize();
    list.addItem( 5 );
    REQUIRE( list.getSize() == size + 1 );
}

TEST_CASE( "adding a new node to empty list" ) {
    List list;
    list.addItem( 4 );
    REQUIRE( list.getList()->getNext() == NULL );
    REQUIRE( list.getList()->getData() == 4 );
}

TEST_CASE( "creating a list produces right list" ) {
    List list;
    list.addItem( 1 );
    list.addItem( 2 );
    list.addItem( 3 );
    list.addItem( 4 );
    REQUIRE( list.toString() == "4 3 2 1 " );
}
