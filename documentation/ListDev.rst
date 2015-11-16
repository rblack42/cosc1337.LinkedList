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

And the implementation:

..  literalinclude::    ../lib/List.cpp
    :caption: lib/List.cpp (3)
    :linenos:

Now we get a passing test! We have completed our first cycle using :term:`TDD`!

Cycle 2: Creating Nodes for the List
************************************

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

..  note::

    From here on, we will not show the failing tests. Trust me, they failed!

Here is the specification of our node class:

..  literalinclude::    ../includes/Node.h 
    :caption: includes/Node.h
    :linenos:

And the implementation file:

..  literalinclude::    ../lib/Node.cpp
    :caption: lib/Node.cpp
    :linenos:

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
methods to set and get those attributes. Here are the tests we will need for
these additions:

..  literalinclude::    ../tests/test_node.cpp
    :linenos:

There are a few interesting point to make about this code. The data access
routines will be pretty simple, and standard ``get`` and ``set`` methods are
all we need. For the ``Next`` attribute, the test is a bit trickier. What is
going on here is fairly easy to understand. We are making the ``Next``
attribute point back to the node it is part of. That makes a loop and if we ask
what data item is in the "next" node, we should see the value in the current
node. Look closely at the way the access is set up and make sure you can follow
it:

    * ``Node * ptr`` sets up a pointer variable

    * `= &node`` sets that pointer to the address of the ``node`` object.

    * ``node.setNext( ptr )`` sets the ``Next`` attribute so it points back to
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

Note that we set up a routine that adds a new ``item``, not a new ``node``.
When you build a data container like this, you should hide the details about
how the container is actually working from the user. That way, if needed, you
can change the entire implementation of your container with out changing the
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

And the required implementation code:

..  literalinclude::    ../lib/List.cpp
    :linenos:

In this code, we create a new ``Node`` object using ``dynamic memory``. The
``new`` operator asks the operating system for a chunk of memory big enough to
hold the object, and gets back the address of that memory chunk. We will
initialize that new (unnamed) object, then hook it to the front of the list. By
copying the old ``list`` attribute from the ``List`` object into the ``Next``
attribute in the new object we attach any old list to this node. That is
exactly what we want if this list is to become the new first item.

Cycle 5: Walking the List
*************************

Now that we have a way to add items to the front of the list, we are in a
position to "walk" the list, visiting each node in order. We can print this
list our and read it, but to test the new method, we need to do something
different.

C++ has a string "sstream" class we can use to construct a string as we walk
the list. We can then print this new string out, or compare it to what we want
to prove it contains. 

Here is a test to make sure the list holds the required data:

..  literalinclude::    ../tests/test_list.cpp
    :linenos:


Here is the new code we need to add to the list class:

..  literalinclude::    ../lib/List.cpp
    :linenos:

Note that the string we produce using this ``toString()`` method will be the nodes in reverse. There will also be a trailing space at the end of the string generated. 

Wrapping Up
***********

At this point we have a basic linked list class that we can use as a basis for
our simulator. Of course, we need to alter the list to make it hold the
vehicles we will be simulating. That is easy to do, but requires copying this
``List`` class and changing the data type of the data item. That is simple
enough to do, but it raises an interesting point.

What if we want to build a bunch of linked lists, each holding a different
data type? Do we have to copy and edit this class a bunch of times?

Actually, no!

We can use a feature of C++ called ``templates`` to create a generic linked
list class that we can use to create all of the special lists we need.  This is
not formally part of this course, but here is what it will look like:












