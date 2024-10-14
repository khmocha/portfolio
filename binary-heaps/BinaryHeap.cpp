#include "BinaryHeap.h"
#include <iostream>

BinaryHeap::BinaryHeap() {
    Size = 0;
    CurrentSize = 0;
    NodeArray = nullptr;
}

BinaryHeap::BinaryHeap(int NewSize) {
    if (NewSize <= 0) {
        std::cerr << "Invalid Binary Heap Size" << std::endl;
        return;
    } 

    Size = NewSize;
    CurrentSize = 0;
    NodeArray = new HeapNode [Size];
}

void BinaryHeap::Insert(int Data) {
    if (CurrentSize == Size) {
        std::cerr << "There are no more available space for insertion" << std::endl;
        return;
    }

    NodeArray[CurrentSize].Data = Data;
    int CurrentIndex = CurrentSize;
    
    CurrentSize++;

    while (CurrentIndex > 0) {
        if (NodeArray[CurrentIndex].Data > NodeArray[(CurrentIndex - 1) / 2].Data) {
            std::swap(NodeArray[CurrentIndex], NodeArray[(CurrentIndex - 1) / 2]);
            CurrentIndex = (CurrentIndex - 1) / 2;
        } else {
            return;
        }
    }
    
    if (NodeArray[CurrentIndex].Data > NodeArray[(CurrentIndex - 1) / 2].Data) {
        std::swap(NodeArray[CurrentIndex], NodeArray[(CurrentIndex - 1) / 2]);
        CurrentIndex = (CurrentIndex - 1) / 2;
    }
}

void BinaryHeap::Insert(int Data, char Letter) {
    if (CurrentSize == Size) {
        std::cerr << "There are no more available space for insertion" << std::endl;
        return;
    }

    NodeArray[CurrentSize].Data = Data;
    NodeArray[CurrentSize].Letter = Letter;
    int CurrentIndex = CurrentSize;
    
    CurrentSize++;

    while (CurrentIndex > 0) {
        if (NodeArray[CurrentIndex].Data > NodeArray[(CurrentIndex - 1) / 2].Data) {
            std::swap(NodeArray[CurrentIndex], NodeArray[(CurrentIndex - 1) / 2]);
            CurrentIndex = (CurrentIndex - 1) / 2;
        } else {
            return;
        }
    }
    
    if (NodeArray[CurrentIndex].Data > NodeArray[(CurrentIndex - 1) / 2].Data) {
        std::swap(NodeArray[CurrentIndex], NodeArray[(CurrentIndex - 1) / 2]);
        CurrentIndex = (CurrentIndex - 1) / 2;
    }
}

void BinaryHeap::DeleteRoot(bool Heapifying, int HeapifyIndex) {
    if (CurrentSize == 0) {
        std::cerr << "There are no available root to delete" << std::endl;
        return;
    }

    int CurrentIndex = 0;

    if (Heapifying == false) {
        std::swap(NodeArray[0], NodeArray[--CurrentSize]);
    } else {
        CurrentIndex = HeapifyIndex;
    }

    int GreaterChild;
    int YoungerChild;

    while (CurrentIndex < CurrentSize) {
        if (CurrentIndex * 2 + 1 < CurrentSize && CurrentIndex * 2 + 2 < CurrentSize) {
            if (NodeArray[CurrentIndex * 2 + 1].Data > NodeArray[CurrentIndex * 2 + 2].Data) {
                GreaterChild = CurrentIndex * 2 + 1;
                YoungerChild = CurrentIndex * 2 + 2;
            } else {
                GreaterChild = CurrentIndex * 2 + 2;
                YoungerChild = CurrentIndex * 2 + 1;
            }

            if (NodeArray[CurrentIndex].Data < NodeArray[GreaterChild].Data) {
                std::swap(NodeArray[CurrentIndex], NodeArray[GreaterChild]);
            } else if (NodeArray[CurrentIndex].Data < NodeArray[YoungerChild].Data) {
                std::swap(NodeArray[CurrentIndex], NodeArray[YoungerChild]);
                GreaterChild = YoungerChild;
            } else {
                break;
            }

            CurrentIndex = GreaterChild;

        } else if (CurrentIndex * 2 + 1 < CurrentSize) {
            if (NodeArray[CurrentIndex].Data < NodeArray[CurrentIndex * 2 + 1].Data) {
                std::swap(NodeArray[CurrentIndex], NodeArray[CurrentIndex * 2 + 1]);
            } 
            break;

        } else {
            break;
        }
    }
}

void BinaryHeap::HeapSort() {
    int OriginalSize = CurrentSize;

    for (int i = 0; i < OriginalSize; i++) {
        DeleteRoot();
    }

    CurrentSize = OriginalSize;
}

void BinaryHeap::Heapify() {
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

void BinaryHeap::Print() {
    for (int i = 0; i < CurrentSize; i++) {
        std::cout << NodeArray[i].Data << " ";
    }

    std::cout << std::endl;
}

void BinaryHeap::PrintBoth() {
    for (int i = 0; i < CurrentSize; i++) {
        std::cout << NodeArray[i].Data << " " << NodeArray[i].Letter << std::endl;
    }
}

BinaryHeap::~BinaryHeap() {
    if (NodeArray != nullptr) {
        delete [] NodeArray;
        NodeArray = nullptr;
    }
}


