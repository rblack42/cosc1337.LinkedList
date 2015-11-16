#include <iostream>
using namespace std;
#include "List.h"

int main( int argc, char *argv[] ) {
    cout << "I-35 Simulator" << endl;

    List list;
    list.addItem(1);
    list.addItem(2);
    list.print();
}
