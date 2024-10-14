#pragma once

#include "MaxBinaryHeap.h"

template <typename T>
MaxBinaryHeap<T>::MaxBinaryHeap() {
    Size = 0;
    CurrentSize = 0;
    Array = nullptr;
}

template <typename T>
MaxBinaryHeap<T>::MaxBinaryHeap(int NewSize) {
    if (NewSize <= 0) {
        std::cerr << "Invalid Binary Heap Size" << std::endl;
        return;
    } 

    Size = NewSize;
    CurrentSize = 0;
    Array = new T [Size];
}

template <typename T>
void MaxBinaryHeap<T>::Insert(T Node) {
    if (CurrentSize == Size) {
        std::cerr << "There are no more available space for insertion" << std::endl;
        return;
    }

    Array[CurrentSize] = Node;
    int CurrentIndex = CurrentSize;
    
    CurrentSize++;

    while (CurrentIndex > 0) {
        if (Array[CurrentIndex].Number > Array[(CurrentIndex - 1) / 2].Number) {
            std::swap(Array[CurrentIndex], Array[(CurrentIndex - 1) / 2]);
            CurrentIndex = (CurrentIndex - 1) / 2;
        } else {
            return;
        }
    }
    
    if (Array[CurrentIndex].Number > Array[(CurrentIndex - 1) / 2].Number) {
        std::swap(Array[CurrentIndex], Array[(CurrentIndex - 1) / 2]);
        CurrentIndex = (CurrentIndex - 1) / 2;
    }
}

template <typename T>
void MaxBinaryHeap<T>::DeleteRoot(bool Heapifying, int HeapifyIndex) {
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
            if (Array[CurrentIndex * 2 + 1].Number > Array[CurrentIndex * 2 + 2].Number) {
                GreaterChild = CurrentIndex * 2 + 1;
                YoungerChild = CurrentIndex * 2 + 2;
            } else {
                GreaterChild = CurrentIndex * 2 + 2;
                YoungerChild = CurrentIndex * 2 + 1;
            }

            if (Array[CurrentIndex].Number < Array[GreaterChild].Number) {
                std::swap(Array[CurrentIndex], Array[GreaterChild]);
            } else if (Array[CurrentIndex].Number < Array[YoungerChild].Number) {
                std::swap(Array[CurrentIndex], Array[YoungerChild]);
                GreaterChild = YoungerChild;
            } else {
                break;
            }

            CurrentIndex = GreaterChild;

        } else if (CurrentIndex * 2 + 1 < CurrentSize) {
            if (Array[CurrentIndex].Number < Array[CurrentIndex * 2 + 1].Number) {
                std::swap(Array[CurrentIndex], Array[CurrentIndex * 2 + 1]);
            } 
            break;

        } else {
            break;
        }
    }
}

template <typename T>
void MaxBinaryHeap<T>::HeapSort() {
    int OriginalSize = CurrentSize;

    for (int i = 0; i < OriginalSize; i++) {
        DeleteRoot();
    }

    CurrentSize = OriginalSize;
}

template <typename T>
void MaxBinaryHeap<T>::Heapify() {
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

template <typename T>
void MaxBinaryHeap<T>::Print() {
    for (int i = 0; i < CurrentSize; i++) {
        Array[i].Print();
    }

    std::cout << std::endl;
}

template <typename T>
MaxBinaryHeap<T>::~MaxBinaryHeap() {
    if (Array != nullptr) {
        delete [] Array;
        Array = nullptr;
    }
}
