#pragma once

#include "MinBinaryHeap.h"

template <typename NodeObject, typename MinBinaryHeapChildren>
MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::MinBinaryHeap() {
    Pointer = nullptr;
    Size = 0;
    CurrentSize = 0;
    Array = nullptr;
}

template <typename NodeObject, typename MinBinaryHeapChildren>
MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::MinBinaryHeap(int NewSize, void * NewPointer) {
    if (NewSize <= 0) {
        std::cerr << "Invalid Binary Heap Size" << std::endl;
        return;
    } 

    Size = NewSize;
    CurrentSize = 0;
    Array = new Node<NodeObject> * [Size];

    for (int i = 0; i < Size; i++) {
        Array[i] = new Node<NodeObject>();
    }

    if (NewPointer != nullptr) {
        Pointer = NewPointer;
    } else if (typeid(MinBinaryHeapChildren) == typeid(void *)) {
        Pointer = nullptr;
    } else {
        Pointer = new MinBinaryHeapChildren();
    }
}

template <typename NodeObject, typename MinBinaryHeapChildren>
void MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::Insert(Node<NodeObject> * NodeToInsert) {
    if (CurrentSize == Size) {
        std::cerr << "There are no more available space for insertion" << std::endl;
        return;
    }

    Array[CurrentSize] = NodeToInsert;
    int CurrentIndex = CurrentSize;
    
    CurrentSize++;

    while (CurrentIndex > 0) {
        if (Array[CurrentIndex]->ReturnCastedPointer()->Number < Array[(CurrentIndex - 1) / 2]->ReturnCastedPointer()->Number) {
            std::swap(Array[CurrentIndex], Array[(CurrentIndex - 1) / 2]);
            CurrentIndex = (CurrentIndex - 1) / 2;
        } else {
            return;
        }
    }
    
    if (Array[CurrentIndex]->ReturnCastedPointer()->Number < Array[(CurrentIndex - 1) / 2]->ReturnCastedPointer()->Number) {
        std::swap(Array[CurrentIndex], Array[(CurrentIndex - 1) / 2]);
        CurrentIndex = (CurrentIndex - 1) / 2;
    }
}

template <typename NodeObject, typename MinBinaryHeapChildren>
void MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::DeleteRoot(bool Heapifying, int HeapifyIndex) {
    if (CurrentSize == 0) {
        std::cerr << "There are no available root to delete" << std::endl;
        return;
    }

    int CurrentIndex = 0;

    if (Heapifying == false) {
        std::swap(Array[0], Array[--CurrentSize]);
    } else {
        CurrentIndex = HeapifyIndex;
    }

    int GreaterChild;
    int YoungerChild;

    while (CurrentIndex < CurrentSize) {
        if (CurrentIndex * 2 + 1 < CurrentSize && CurrentIndex * 2 + 2 < CurrentSize) {
            if (Array[CurrentIndex * 2 + 1]->ReturnCastedPointer()->Number < Array[CurrentIndex * 2 + 2]->ReturnCastedPointer()->Number) {
                GreaterChild = CurrentIndex * 2 + 1;
                YoungerChild = CurrentIndex * 2 + 2;
            } else {
                GreaterChild = CurrentIndex * 2 + 2;
                YoungerChild = CurrentIndex * 2 + 1;
            }

            if (Array[CurrentIndex]->ReturnCastedPointer()->Number > Array[GreaterChild]->ReturnCastedPointer()->Number) {
                std::swap(Array[CurrentIndex], Array[GreaterChild]);
            } else if (Array[CurrentIndex]->ReturnCastedPointer()->Number > Array[YoungerChild]->ReturnCastedPointer()->Number) {
                std::swap(Array[CurrentIndex], Array[YoungerChild]);
                GreaterChild = YoungerChild;
            } else {
                break;
            }

            CurrentIndex = GreaterChild;

        } else if (CurrentIndex * 2 + 1 < CurrentSize) {
            if (Array[CurrentIndex]->ReturnCastedPointer()->Number > Array[CurrentIndex * 2 + 1]->ReturnCastedPointer()->Number) {
                std::swap(Array[CurrentIndex], Array[CurrentIndex * 2 + 1]);
            } 
            break;

        } else {
            break;
        }
    }
}

template <typename NodeObject, typename MinBinaryHeapChildren>
void MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::HeapSort() {
    int OriginalSize = CurrentSize;

    for (int i = 0; i < OriginalSize; i++) {
        DeleteRoot();
    }

    CurrentSize = OriginalSize;
}

template <typename NodeObject, typename MinBinaryHeapChildren>
void MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::Heapify() {
    if (CurrentSize == 0) {
        std::cerr << "No available data to heapify" << std::endl;
        return;
    }

    int EndingParentSize = 0;
    int Multiplier = 1;

    while (EndingParentSize < CurrentSize) {
        EndingParentSize += Multiplier;
        Multiplier *= 2;
    }

    EndingParentSize -= (Multiplier / 2);

    for (int i = EndingParentSize - 1; i > -1; i--) {
        DeleteRoot(true, i);
    }
}

template <typename NodeObject, typename MinBinaryHeapChildren>
void MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::Print() {
    for (int i = 0; i < CurrentSize; i++) {
        Array[i]->ReturnCastedPointer()->Print();
    }

    std::cout << std::endl;
}

template <typename NodeObject, typename MinBinaryHeapChildren>
MinBinaryHeapChildren * MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::ReturnCastedPointer() {
    return (MinBinaryHeapChildren *) Pointer;
}

template <typename NodeObject, typename MinBinaryHeapChildren>
void MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::SetCastedPointer(MinBinaryHeapChildren * NewData) {
    if (Pointer != nullptr) {
        delete (MinBinaryHeapChildren *) Pointer;
    }

    Pointer = NewData;
}

template <typename NodeObject, typename MinBinaryHeapChildren>
MinBinaryHeap<NodeObject, MinBinaryHeapChildren>::~MinBinaryHeap() {
    if (Array != nullptr) {
        for (int i = 0; i < Size; i++) {
            delete Array[i];
            Array[i] = nullptr;
        }

        delete [] Array;
        Array = nullptr;
    }
}