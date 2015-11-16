#include <iostream>
using namespace std;

template<class T>
class Node {
    public:
        T data;
        Node<T> * next;
        Node<T>(const T& d):data(d), next() {}
        Node<T>(const Node<T>& copyNode) : data(copyNode.data), next() {}
    private:
        Node<T>& operator=(const Node<T>&);
};

template<class T>
class LinkedList {
public:

    Node<T> * head;
    Node<T> * tail;

    LinkedList(const LinkedList& LL);
    LinkedList& operator=(LinkedList byValList);
    LinkedList(): head(NULL), tail(NULL) {}
    LinkedList(Node<T> * newNode) : head(newNode), tail(newNode) {}
    ~LinkedList();

    static LinkedList<int> sumLists(const LinkedList<int>& LL1, LinkedList<int>& LL2);

    void insertToTail(T val);
    void insertToHead(T val);
    void print();
    void printBackwards();
};

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& LL) : head(NULL), tail(NULL) {
    const Node<T> * curr = LL.head;

    if (!head && curr) {
        head = new Node<T>(curr->data);
        tail = head;
        curr = curr->next;
    }

    while (curr) {
        Node<T> * newNode = new Node<T>(curr->data);
        tail->next = newNode;
        tail = newNode;
        curr = curr->next;
    }
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList byValList) {
    std::swap(head, byValList.head);
    return *this;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T> * curr = head;
    while (head) {
        head = head->next;
        delete curr;
        curr = head;
    }
}

template<class T>
void LinkedList<T>::insertToTail(T val) {
    Node<T> * newNode = new Node<T>(val);
    if (tail == NULL) {
        newNode->next = tail;
        tail = newNode;
        head = newNode;
        return;
    }
    tail->next = newNode;
    tail = tail->next;
}

template<class T>
void LinkedList<T>::insertToHead(T val) {
    Node<T> * newNode = new Node<T>(val);
    newNode->next = head;
    head = newNode;
    if (head->next == NULL)
        tail = newNode;
}

template<class T>
void LinkedList<T>::print() {
    Node<T> * curr = head;
    while (curr) {
        cout<<curr->data<<" --> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}

template<class T>
void LinkedList<T>::printBackwards() {
    Node<T> * curr;
    LinkedList ReversedList(new Node<T>(head->data));
    curr = head->next;
    while (curr) {
        ReversedList.insertToHead(curr->data);
        curr = curr->next;
    }

    curr = ReversedList.head;
    while (curr) {
        cout<<curr->data<<" --> ";
        curr = curr->next;
    }
    cout<<"NULL\n";
}

template<class T>
LinkedList<int> LinkedList<T>::sumLists(const LinkedList<int>& LL1, LinkedList<int>& LL2) {
    Node<T>* curr1 = LL1.head;
    Node<T>* curr2 = LL2.head;

    LinkedList<int> ResultList;

    int newData;
    int carry = 0;

    while (curr1 && curr2) {
        newData = (curr1->data + curr2->data + carry) % 10;
        carry = (curr1->data + curr2->data + carry) / 10;
        ResultList.insertToTail(newData);

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    while (curr1 || curr2) {
        if (carry) {
            if (curr1)
                ResultList.insertToTail(curr1->data + carry);
            if (curr2)
                ResultList.insertToTail(curr2->data + carry);
            carry = 0;
            continue;
        }
        if (curr1) {
            ResultList.insertToTail(curr1->data);
            curr1 = curr1->next;
        }
        if (curr2) {
            ResultList.insertToTail(curr2->data + carry);
            curr2 = curr2->next;

        }


    }

    return ResultList;
}

int main()
{
    LinkedList<int> LL1(new Node<int>(7));
    LL1.insertToTail(1);
    LL1.insertToTail(6);
    LL1.insertToTail(5);
    LL1.insertToTail(4);

    LinkedList<int> LL2(new Node<int>(5));
    LL2.insertToTail(9);
    LL2.insertToTail(2);

    LinkedList<int> LL = LL1.sumLists(LL1, LL2);
    LL.print();
    LL2.print();
    LL = LL2;
    LL.print();
    LL2.print();

    return 0;
}
