#ifndef HEAPSORT_H
#define HEAPSORT_H

struct HeapNode {
    int Data;
    char Letter;
};

class BinaryHeap {
    private:
    public:
        int Size;
        int CurrentSize;
        HeapNode * NodeArray;

        BinaryHeap();
        BinaryHeap(int NewSize);
        BinaryHeap(int NewSize, bool IsNodeArray);

        void Insert(int Data);
        void Insert(int Data, char Letter);
        void DeleteRoot(bool Heapifying = false, int HeapifyIndex = -1);
        void HeapSort();
        void Heapify();

        void Print();
        void PrintBoth();

        ~BinaryHeap();

};

#endif