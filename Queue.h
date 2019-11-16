#ifndef CPPQUEUE_QUEUE_H
#define CPPQUEUE_QUEUE_H

#include "DoubleLinkedList.h"
#include <cstddef>

template <typename line>
class Queue
{
    DoublyLinkedList<line> underlying_list;

public:
    Queue() = default;

    void enqueue(line& elem)
    {
        underlying_list.addBack(elem);
    }

    void dequeue()
    {
        underlying_list.removeFront();
    }

    const typename DoublyLinkedList<line>::Node* front() const
    {
        return this->underlying_list.front();
    }

    int size() const
    {
        return underlying_list.size();
    }

    bool empty() const
    {
        return underlying_list.size() == 0;
    }
};


#endif
