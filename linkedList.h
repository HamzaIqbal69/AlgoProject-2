#include <iostream>
#include "Node.h"

using namespace std;

class linkedList
{
        Node *front;
        int listSize;
        linkedList();
        void insertFront(int elem[2]);
        void deleteIndex(int index);
};
