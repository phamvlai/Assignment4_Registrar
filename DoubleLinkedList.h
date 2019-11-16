#ifndef CPPQUEUE_DOUBLELINKEDLIST_H
#define CPPQUEUE_DOUBLELINKEDLIST_H

#include "ListInterface.h"
#include <cstddef>

template <typename line>
class DoublyLinkedList: public List<line>
{
public:
    DoublyLinkedList()
    {
        this->length = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    typename List<line>::Node* front() const
    {
        return this->head; //returns the head
    }

    int size() const
    {
        return this->length; //returns the length
    }

    bool empty() const
    {
        return this->length == 0; //if empty, set length to 0
    }

    void addFront(const line& elem) //function to add to the front of the list
    {
        if (this->length == 0)
        {
            this->head = new typename List<line>::Node(elem, nullptr, nullptr);
            this->tail = this->head;
            this->length = 1;

            return;
        }

        typename List<line>::Node *prev_head = this->head;

        this->head = new typename List<line>::Node(elem, nullptr, this->head);
        prev_head->prev = this->head;

        this->length++;
    }

    void addBack(const line& elem) //function to add to the back of the list
    {
        if (this->length == 0)
        {
            this->head = new typename List<line>::Node(elem, nullptr, nullptr);
            this->tail = this->head;
            this->length = 1;

            return;
        }

        typename List<line>::Node *prev_tail = this->tail;
        this->tail = new typename List<line>::Node(elem, this->tail, nullptr);
        prev_tail->next = this->tail;

        this->length++;
    }

    void removeFront() //function to remove from the front of the list
    {
        if (this->length == 0)
        {
            return;
        }

        typename List<line>::Node *prev_head = this->head;
        this->head = this->head->next;
        if (this->head != nullptr)
        {
            this->head->prev = nullptr;
        }


        delete prev_head;
        this->length--;
    }

    void removeBack() //function to remove from the back of the list
    {
        if (this->length == 0)
        {
            return;
        }

        typename List<line>::Node *prev_tail = this->tail;
        this->tail = this->tail->prev;
        if (this->tail != nullptr)
        {
            this->tail->next = nullptr;
        }

        delete prev_tail;
        this->length--;
    }
};


#endif
