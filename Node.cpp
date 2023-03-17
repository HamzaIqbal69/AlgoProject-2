/** @file Node.cpp   */
#include "Node.h"
#include <cstddef>

Node::Node(int anItem[2]) 
{
    item[0] = anItem[0];
    item[1] = anItem[1];
    next = nullptr;
} // end constructor