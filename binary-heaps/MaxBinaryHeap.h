#pragma once

#ifndef MAXBINARYHEAP_H
#define MAXBINARYHEAP_H

#include "Nodes.h"

template <typename T>
class MaxBinaryHeap {
    private:
    public:
        int Size;
        int CurrentSize;
        T * Array;

        MaxBinaryHeap();
        MaxBinaryHeap(int NewSize);

        void Insert(T Node);
        void DeleteRoot(bool Heapifying = false, int HeapifyIndex = -1);
        void HeapSort();
        void Heapify();

        void Print();

        ~MaxBinaryHeap();
};

#endif