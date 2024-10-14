#include <iostream>

#include "LinkedListDef.h"

void Enqueue(Node * PQ, int & CurrentIndex, int Size, Node VertexConnection) {
    if (CurrentIndex == Size) {
        std::cout << "Queue is full!" << std::endl;
        return;
    }

    PQ[CurrentIndex] = VertexConnection;

    int TempIndex = CurrentIndex;
    int Divider;

    if (TempIndex % 2 == 0) { // right child
        Divider = TempIndex/2 - 1;
        while (PQ[TempIndex].InDegree > PQ[Divider].InDegree && TempIndex > 0) {
            std::swap(PQ[TempIndex], PQ[Divider]);
            TempIndex = Divider;

            if (TempIndex % 2 != 0) { // left child
                Divider = TempIndex/2;
            } else {
                Divider = TempIndex/2 - 1;
            }
        }
    } else { // left child
        Divider = TempIndex/2;
        while (PQ[TempIndex].InDegree > PQ[Divider].InDegree && TempIndex > 0) {
            std::swap(PQ[TempIndex], PQ[Divider]);
            TempIndex = Divider;

            if (TempIndex % 2 == 0) { // right child
                Divider = TempIndex/2 - 1;
            } else {
                Divider = TempIndex/2;
            }
        }
    }

    CurrentIndex++;

}

void Dequeue(Node * PQ, int Size, int & CurrentIndex) {
    if (CurrentIndex == 0) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    std::swap(PQ[0], PQ[CurrentIndex - 1]);

    PQ[CurrentIndex - 1].Integer = 0;
    PQ[CurrentIndex - 1].InDegree = 0;
    PQ[CurrentIndex - 1].Source = 0;

    CurrentIndex--;
    //std::cout << CurrentIndex << std::endl;
    
    //std::cout << "PQ[0]: " << PQ[0] << std::endl;

    //std::cout << CurrentIndex << std::endl;
    int TempIndex = 0;
    int Divider;

    if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 1].InDegree && PQ[TempIndex].InDegree < PQ[2 * TempIndex + 2].InDegree) {
        if (PQ[(2 * TempIndex) + 1].InDegree > PQ[(2* TempIndex) + 2].InDegree) { // left is greater than right
            Divider = 2 * TempIndex + 1;
        } else {
            Divider = 2 * TempIndex + 2;
        }
    } else {
        if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 1].InDegree) {
            Divider = 2 * TempIndex + 1;
        } else if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 2].InDegree) {
            Divider = 2 * TempIndex + 2;
        } else {
            return;
        }
    }

    if (Divider >= Size || Divider < 0) {
        return;
    }

    //std::cout << PQ[Divider] << std::endl;

    while (PQ[TempIndex].InDegree < PQ[Divider].InDegree) {
        if (Divider >= Size || Divider < 0) {
            return;
        }
        //std::cout << PQ[TempIndex] << " " << PQ[Divider] << std::endl;

        if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 1].InDegree && PQ[TempIndex].InDegree < PQ[2 * TempIndex + 2].InDegree) {

            if (PQ[(2 * TempIndex) + 1].InDegree >= PQ[(2 * TempIndex) + 2].InDegree) { // left is greater than right
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 1]);
                TempIndex = 2 * TempIndex + 1;
                Divider = 2 * TempIndex + 1;
            } else {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 2]);
                TempIndex = 2 * TempIndex + 2;
                Divider = 2 * TempIndex + 2;
            }
        } else {
            if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 1].InDegree) {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 1]);
                TempIndex = 2 * TempIndex + 1;
                Divider = 2 * TempIndex + 1;
            } else if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 2].InDegree) {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 2]);
                TempIndex = 2 * TempIndex + 2;
                Divider = 2 * TempIndex + 2;
            } else {
                //std::cout << std::endl;
                return;
            }
        }

        if (Divider >= Size || Divider < 0) {
            return;
        }

        if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 1].InDegree && PQ[TempIndex].InDegree < PQ[2 * TempIndex + 2].InDegree) {
            if (PQ[(2 * TempIndex) + 1].InDegree > PQ[(2* TempIndex) + 2].InDegree) { // left is greater than right
                Divider = 2 * TempIndex + 1;
            } else {
                Divider = 2 * TempIndex + 2;
            }
        } else {
            if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 1].InDegree) {
                Divider = 2 * TempIndex + 1;
            } else if (PQ[TempIndex].InDegree < PQ[2 * TempIndex + 2].InDegree) {
                Divider = 2 * TempIndex + 2;
            } else {
                //std::cout << std::endl;
                return;
            }
        }

        if (Divider >= Size || Divider < 0) {
            return;
        }
    }
}

void PrintPQ(Node * PQ, int Size) {
    for (int i = 0; i < Size; i++) {
        std::cout << PQ[i].InDegree << " ";
    }

    std::cout << std::endl;
}



/*What is the worst-case time complexity of your solution for a Priority Que of size n?
log(n) for searching -> deleting and inserting
retrieving k-min k-max -> O(1)
nlog(n) for heap sort
*/