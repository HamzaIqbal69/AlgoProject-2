#include "linkedList.h"

linkedList::linkedList()
{
    front = nullptr;
    listSize = 0;
}

void linkedList::insertFront(int elem[2])
{
    Node* newNode = new Node(elem);
    newNode->next = front;
    front = newNode;
    listSize++;

}