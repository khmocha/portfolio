#pragma once

#ifndef MINBINARYHEAP_H
#define MINBINARYHEAP_H

#include "../Node.h"

template <typename NodeObject = void *, typename MinBinaryHeapChildren = void *>
class MinBinaryHeap {
    private:
    public:
        int Size;
        int CurrentSize;
        Node<NodeObject> ** Array;

        void * Pointer;

        MinBinaryHeap();
        MinBinaryHeap(int NewSize, void * NewPointer = nullptr);

        void Insert(Node<NodeObject> * NodeToInsert);
        void DeleteRoot(bool Heapifying = false, int HeapifyIndex = -1);
        void HeapSort();
        void Heapify();

        void Print();

        MinBinaryHeapChildren * ReturnCastedPointer();
        void SetCastedPointer(MinBinaryHeapChildren * NewData);

        ~MinBinaryHeap();
};

#endif