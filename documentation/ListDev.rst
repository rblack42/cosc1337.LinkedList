TDD Linked List Development
###########################

Assuming the testing framework is in place, we are ready to start development
of the Linked List class. 

Cycle 1: Starting the Linked List Class
***************************************

Following the :term:`TDD` mantra, we write a test we know will fail. This is
simple, since we have not written anything yet. Let's start off by building a
new list. By itself, that is not much to test, so we will add one method that
will return the number of items in the list. With that method in place, we can
test that the number of items in a new list is zero:

..  literalinclude::    ../tests/test_list.cpp
    :caption: tests/test_list.cpp (1)
    :linenos:
    :lines: 1-7

As we would expect, this test fails:

..  code-block:: text

    $ make
    g++ -c -std=c++11 -MMD -Iincludes tests/test_list.cpp -o tests/test_list.o
    tests/test_list.cpp:2:18: fatal error: List.h: No such file or directory
    compilation terminated.

We can fix this error by adding the header for the class:

..  literalinclude::    ../includes/List.h
    :caption: includes/List.h
    :linenos:
    :lines: 1-6, 8-10

This time, we get a different error. (The compiler complains about a missing
reference.) We set up the header, but did not actually add the implementation
for the ``getSize()`` method. This is called a "red to red" error, and it means
we have more work to do to get this test to pass. 

Here is the missing implementation code:

..  literalinclude::    ../lib/List.cpp
    :caption: lib/List.cpp (1)
    :linenos:
    :lines: 1-7

..  code-block:: text

    $ tests

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    tests is a Catch v1.2.1 host application.
    run with -? for options

    ------------------------------------------------------------------------------
     a new list returns a length of zero
    ------------------------------------------------------------------------------
    tests/test_list.cpp:4
    ..............................................................................

    tests/test_list.cpp:6: FAILED:
     REQUIRE( list.getSize() == 0 )
    with expansion:
     1988925645 (0x768c98cd) == 0
    ==============================================================================
    test cases: 2 | 1 passed | 1 failed
    assertions: 2 | 1 passed | 1 failed

Another "red-to-red" error! The problem here should be apparent. We failed to
initialize the ``size`` variable. Trying to do this in the header file will
generate an error, since C++ is not keen on letting you do that. So, the
correct solution is to set up a default constructor where we can do this
initialization. We will need that later anyway!

..  literalinclude::    ../includes/List.h
    :caption: includes/List.h (2)
    :linenos:
    :lines: 6-7

And the implementation:

..  literalinclude::    ../lib/List.cpp
    :caption: lib/List.cpp (3)
    :linenos:
    :lines: 3-5

Now we get a passing test! We have completed our first cycle using :term:`TDD`!

Cycle 2: Adding Nodes to the List
*********************************

The whole point in building a linked list is to create a place to store data
that can grow as we need more room. We will store the data in objects we create
from another class. By tradition, this one is called the Node class.

To keep this example simple, our first node class will store a simple integer.
However, to create the linked list, each node will need to hold a pointer to
another node, creating the link in our linked list.

To test this new node, we will build a test similar to the one we set up for
the list. This time, we will set the data value to zero, and initialize our
link to ``NULL`` which means "points to nothing""

Here is the first test for our node class:

..  literalinclude::    ../tests/test_node.cpp
    :caption: tests/test_node.cpp
    :linenos:
    :lines: 1-8

..  note::

    From here on, we will not show the failing tests. Trust me, they failed!

Here is the specification of our node class:

..  literalinclude::    ../includes/Node.h 
    :caption: includes/Node.h
    :linenos:
    :lines: 1-11

And the implementation file:

..  literalinclude::    ../lib/Node.cpp
    :caption: lib/Node.cpp
    :linenos:
    :lines: 1-15

Here is out test run now:

..  code-block:: text

    $ tests
    ===============================================================================
    All tests passed (4 assertions in 3 test cases)

Not bad! We have two cycles completed, and we have a total of four passing tests (counting the sanity check we did initially!)

However, we do not have any nodes hooked into our list yet, so we need to begin actually building the list!

Cycle 3: Accessing Node Private Attributes
******************************************

Since we made the attributes of our Node objects private, we will need to add
methods to set and get those attributes. Here are the tests we will need for these additions:

..  literalinclude::    ../tests/test_node.cpp
    :linenos:
    :lines: 10-17

There are a few interesting point to make about this code. The data access
routines will be pretty simple, and standard ``get`` and ``set`` methods are
all we need. For the ``Next`` attribute, the test is a bit trickier. What is
going on here is fairly easy to understand. We are making the ``Next``
attribute point back to the node it is part of. That makes a loop and if we ask
what data item is in the "next" node, we should see the value in the current
node. Look closely at the way the access is set up and make sure you can follow
it:

    * ``Node * ptr`` sets up a pointer variable

    * `e= &node`` sets that pointer to the address of the ``node`` object.

    * ``node.setNext( ptr )`` sets the ``Next`` attribute so it pouints back to
      this node

    * ``node.getNext()`` retrieves a pointer to a Node. 

    * ``->getData()`` follows the pointer, and asks for the ``data`` attribute
      in that object

    * Finally, we check to make sure we see our own value, the one we set
      earlier.

Phew! But the test works, and that is what is important!

Adding these methods is pretty simple. Here are the new prototypes:

..  literalinclude::    ../includes/Node.h
    :linenos:

And here is the code to make these methods work:

..  literalinclude::    ../lib/Node.cpp
    :linenos:

Cycle 4: Adding a Node to the List Front
****************************************

We will start off adding items to our list by building a method that will add a
node to the front of the list. At this point in the development, we need to get
serious about thinking through what might be going on when we call this new
method. For instance, the list is either going to be empty, or there will
already be nodes hooked into the list. We must deal with both cases. Also, we
need to make sure that our list accurately tracks the number of nodes it is
managing as new nodes are added!  Let's create a test that checks to see that
the size of the list grows as we add a node:

..  literalinclude::    ../tests/test_list.cpp
    :caption: tests/test_list.cpp (3)
    :linenos:
    :lines: 9-14

Note that we set up a routine that adds a new ``item``, not a new ``node``.
Building a data container like this needs to hide the details about how the
container is actually working from the user. That way, if needed, you can
change the entire implementation of your container with out changing the
interface to that container! (We might need to change its name, though, if it
is no longer a list!)

To make this test pass, we need to create the ``addItem()`` method. This method
will need to do several things:

    * Create a Node object

    * Save the data item in it

    * Hook the new Node object into the list

    * hook what whatever was in the list previously to the end of this new node

That last step is critical, We need to check to see if there is something
already in the list, and hang on to it while we add this new node to the list.
We can tel is anything is in the list by checking the list management object.
Wait! We have not added an attribute to that object to hold the list of nodes!

..  literalinclude::    ../includes/List.h
    :linenos:







