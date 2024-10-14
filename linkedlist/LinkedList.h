#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../Node.h"

template <typename NodeObject = void *, typename LinkedListChildren = void *>
struct LinkedList {
    Node<NodeObject> * Head;
    Node<NodeObject> * Tail;
    int Size;

    void * Pointer;

    LinkedList(LinkedListChildren * NewPointer = nullptr);
    LinkedList(LinkedList & OtherList);

    void InsertAtTail(Node<NodeObject> * NodeToAdd);
    void DeleteTail();
    void DeleteHead();
    void DeleteSpecificNode(Node<NodeObject> * NodeToDelete);
    void Clear();

    void Print();
    void ReversePrint();

    void PrintShared();
    void ReversePrintShared();

    LinkedListChildren * CastedPointer();

    ~LinkedList();
};

#endif