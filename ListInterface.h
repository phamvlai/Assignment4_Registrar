#ifndef CPPQUEUE_LISTINTERFACE_H
#define CPPQUEUE_LISTINTERFACE_H

#include <cstdint>
#include <cstddef>

template <typename line>
class List
{
public:
    struct Node
    {
        line elem;
        Node *prev;
        Node *next;

        Node() = delete;
        Node(const line& elem, Node *prev, Node *next)
        {
            this->elem = elem;
            this->prev = prev;
            this->next = next;
        }
    };

    Node *head;
    Node *tail;
    int length;

public:
    virtual bool empty() const = 0;
    virtual void addFront(const line& elem) = 0;
    virtual void addBack(const line& elem) = 0;
    virtual void removeFront() = 0;
    virtual void removeBack() = 0;
};

#endif
