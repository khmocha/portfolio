#include <iostream>

#include "Maze.h"

void Enqueue(Edge * PQ, int & CurrentIndex, int Size, HorizontalEdge * EdgeH) {
    if (CurrentIndex == Size) {
        std::cout << "Queue is full!" << std::endl;
        return;
    }

    PQ[CurrentIndex].EdgeH = EdgeH;

    int TempIndex = CurrentIndex;
    int Divider;

    CurrentIndex++;

    std::cout << "CI: " << CurrentIndex << std::endl;
    

    if (TempIndex % 2 == 0) { // right child
        std::cout << "A" << std::endl;
        Divider = TempIndex/2 - 1;
        if (Divider < 0 || Divider >= Size) {
            return;
        }
        std::cout << PQ[TempIndex].EdgeH << std::endl;
        std::cout << PQ[Divider].EdgeH << std::endl;
        std::cout << Divider << std::endl;

        while (PQ[TempIndex].EdgeH->EdgeNumber > PQ[Divider].EdgeH->EdgeNumber && TempIndex > 0) {
            std::swap(PQ[TempIndex], PQ[Divider]);
            TempIndex = Divider;

            if (TempIndex % 2 != 0) { // left child
                Divider = TempIndex/2;
            } else {
                Divider = TempIndex/2 - 1;
            }

            if (Divider < 0 || Divider >= Size) {
                return;
            }
        }
    } else { // left child
        std::cout << "B" << std::endl;
        Divider = TempIndex/2;

        if (Divider < 0 || Divider >= Size) {
            return;
        }

        while (PQ[TempIndex].EdgeH->EdgeNumber > PQ[Divider].EdgeH->EdgeNumber && TempIndex > 0) {
            std::swap(PQ[TempIndex], PQ[Divider]);
            TempIndex = Divider;

            if (TempIndex % 2 == 0) { // right child
                Divider = TempIndex/2 - 1;
            } else {
                Divider = TempIndex/2;
            }

            if (Divider < 0 || Divider >= Size) {
                return;
            }
        }
    }

}

void Enqueue(Edge * PQ, int & CurrentIndex, int Size, VerticalEdge * EdgeV) {
    if (CurrentIndex == Size) {
        std::cout << "Queue is full!" << std::endl;
        return;
    }

    PQ[CurrentIndex].EdgeV = EdgeV;

    int TempIndex = CurrentIndex;
    int Divider;
    
    CurrentIndex++;

    //std::cout << "CI: " << CurrentIndex << std::endl;

    if (TempIndex % 2 == 0) { // right child
        //std::cout << "D" << std::endl;
        Divider = TempIndex/2 - 1;

        //std::cout << "Divider: " << Divider << std::endl;
        if (Divider < 0 || Divider >= Size) {
            //std::cout << "Hey baby boyyyy" << std::endl;
            return;
        }

        //std::cout << PQ[TempIndex].EdgeV->EdgeNumber << std::endl;
        //std::cout << PQ[Divider].EdgeV << std::endl;
        while (PQ[TempIndex].EdgeV->EdgeNumber > PQ[Divider].EdgeV->EdgeNumber && TempIndex > 0) {
            //std::cout << "B" << std::endl;
            std::swap(PQ[TempIndex], PQ[Divider]);
            TempIndex = Divider;

            if (TempIndex % 2 != 0) { // left child
                Divider = TempIndex/2;
            } else {
                Divider = TempIndex/2 - 1;
            }

            if (Divider < 0 || Divider >= Size) {
                return;
            }
        }
    } else { // left child
        Divider = TempIndex/2;
        //std::cout << "D" << std::endl;

        if (Divider < 0 || Divider >= Size) {
            //std::cout << "hey daddy" << std::endl;
            return;
        }

        //std::cout << PQ[TempIndex].EdgeV->EdgeNumber << std::endl;
        //std::cout << PQ[Divider].EdgeV->EdgeNumber << std::endl;

        while (PQ[TempIndex].EdgeV->EdgeNumber > PQ[Divider].EdgeV->EdgeNumber && TempIndex > 0) {
            //std::cout << "C" << std::endl;
            std::swap(PQ[TempIndex], PQ[Divider]);
            //std::cout << "E" << std::endl;

            TempIndex = Divider;

            if (TempIndex % 2 == 0) { // right child
                Divider = TempIndex/2 - 1;
            } else {
                Divider = TempIndex/2;
            }
            //std::cout << "F" << std::endl;
            //std::cout << Divider << std::endl;
            if (Divider < 0 || Divider >= Size) {
                return;
            }
        }
    }
}

void DequeueH(Edge * PQ, int Size, int & CurrentIndex) {
    if (CurrentIndex == 0) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    std::swap(PQ[0], PQ[CurrentIndex - 1]);

    PQ[CurrentIndex - 1].EdgeH->EdgeNumber = 0;

    CurrentIndex--;
    //std::cout << CurrentIndex << std::endl;
    
    //std::cout << "PQ[0]: " << PQ[0] << std::endl;

    //std::cout << CurrentIndex << std::endl;
    int TempIndex = 0;
    int Divider;

    if (PQ[TempIndex].EdgeH->EdgeNumber < PQ[2 * TempIndex + 1].EdgeH->EdgeNumber  && PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeH->EdgeNumber ) {
        if (PQ[(2 * TempIndex) + 1].EdgeH->EdgeNumber  > PQ[(2* TempIndex) + 2].EdgeH->EdgeNumber ) { // left is greater than right
            Divider = 2 * TempIndex + 1;
        } else {
            Divider = 2 * TempIndex + 2;
        }
    } else {
        if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeH->EdgeNumber ) {
            Divider = 2 * TempIndex + 1;
        } else if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeH->EdgeNumber ) {
            Divider = 2 * TempIndex + 2;
        } else {
            return;
        }
    }

    //std::cout << PQ[Divider] << std::endl;

    while (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[Divider].EdgeH->EdgeNumber ) {
        if (Divider >= Size) {
            return;
        }
        //std::cout << PQ[TempIndex] << " " << PQ[Divider] << std::endl;

        if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeH->EdgeNumber  && PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeH->EdgeNumber ) {

            if (PQ[(2 * TempIndex) + 1].EdgeH->EdgeNumber  >= PQ[(2 * TempIndex) + 2].EdgeH->EdgeNumber) { // left is greater than right
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 1]);
                TempIndex = 2 * TempIndex + 1;
                Divider = 2 * TempIndex + 1;
            } else {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 2]);
                TempIndex = 2 * TempIndex + 2;
                Divider = 2 * TempIndex + 2;
            }
        } else {
            if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeH->EdgeNumber ) {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 1]);
                TempIndex = 2 * TempIndex + 1;
                Divider = 2 * TempIndex + 1;
            } else if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeH->EdgeNumber ) {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 2]);
                TempIndex = 2 * TempIndex + 2;
                Divider = 2 * TempIndex + 2;
            } else {
                //std::cout << std::endl;
                return;
            }
        }

        if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeH->EdgeNumber  && PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeH->EdgeNumber ) {
            if (PQ[(2 * TempIndex) + 1].EdgeH->EdgeNumber  > PQ[(2* TempIndex) + 2].EdgeH->EdgeNumber ) { // left is greater than right
                Divider = 2 * TempIndex + 1;
            } else {
                Divider = 2 * TempIndex + 2;
            }
        } else {
            if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeH->EdgeNumber ) {
                Divider = 2 * TempIndex + 1;
            } else if (PQ[TempIndex].EdgeH->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeH->EdgeNumber ) {
                Divider = 2 * TempIndex + 2;
            } else {
                //std::cout << std::endl;
                return;
            }
        }
    }
}

void DequeueV(Edge * PQ, int Size, int & CurrentIndex) {
    if (CurrentIndex == 0) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    std::swap(PQ[0], PQ[CurrentIndex - 1]);

    PQ[CurrentIndex - 1].EdgeV->EdgeNumber = 0;

    CurrentIndex--;
    //std::cout << CurrentIndex << std::endl;
    
    //std::cout << "PQ[0]: " << PQ[0] << std::endl;

    //std::cout << CurrentIndex << std::endl;
    int TempIndex = 0;
    int Divider;

    if (PQ[TempIndex].EdgeV->EdgeNumber < PQ[2 * TempIndex + 1].EdgeV->EdgeNumber  && PQ[TempIndex].EdgeV->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeV->EdgeNumber ) {
        if (PQ[(2 * TempIndex) + 1].EdgeV->EdgeNumber  > PQ[(2* TempIndex) + 2].EdgeV->EdgeNumber ) { // left is greater than right
            Divider = 2 * TempIndex + 1;
        } else {
            Divider = 2 * TempIndex + 2;
        }
    } else {
        if (PQ[TempIndex].EdgeV->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeV->EdgeNumber ) {
            Divider = 2 * TempIndex + 1;
        } else if (PQ[TempIndex].EdgeV->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeV->EdgeNumber ) {
            Divider = 2 * TempIndex + 2;
        } else {
            return;
        }
    }

    //std::cout << PQ[Divider] << std::endl;

    while (PQ[TempIndex].EdgeV->EdgeNumber  < PQ[Divider].EdgeV->EdgeNumber ) {
        if (Divider >= Size) {
            return;
        }
        //std::cout << PQ[TempIndex] << " " << PQ[Divider] << std::endl;

        if (PQ[TempIndex].EdgeV->EdgeNumber  < PQ[2 * TempIndex + 1].EdgeV->EdgeNumber  && PQ[TempIndex].EdgeV->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeV->EdgeNumber ) {

            if (PQ[(2 * TempIndex) + 1].EdgeV->EdgeNumber  >= PQ[(2 * TempIndex) + 2].EdgeV->EdgeNumber) { // left is greater than right
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 1]);
                TempIndex = 2 * TempIndex + 1;
                Divider = 2 * TempIndex + 1;
            } else {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 2]);
                TempIndex = 2 * TempIndex + 2;
                Divider = 2 * TempIndex + 2;
            }
        } else {
            if (PQ[TempIndex].EdgeV->EdgeNumber < PQ[2 * TempIndex + 1].EdgeV->EdgeNumber ) {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 1]);
                TempIndex = 2 * TempIndex + 1;
                Divider = 2 * TempIndex + 1;
            } else if (PQ[TempIndex].EdgeV->EdgeNumber < PQ[2 * TempIndex + 2].EdgeV->EdgeNumber ) {
                std::swap(PQ[TempIndex], PQ[2 * TempIndex + 2]);
                TempIndex = 2 * TempIndex + 2;
                Divider = 2 * TempIndex + 2;
            } else {
                //std::cout << std::endl;
                return;
            }
        }

        if (PQ[TempIndex].EdgeV->EdgeNumber < PQ[2 * TempIndex + 1].EdgeV->EdgeNumber  && PQ[TempIndex].EdgeV->EdgeNumber  < PQ[2 * TempIndex + 2].EdgeV->EdgeNumber ) {
            if (PQ[(2 * TempIndex) + 1].EdgeV->EdgeNumber  > PQ[(2* TempIndex) + 2].EdgeV->EdgeNumber ) { // left is greater than right
                Divider = 2 * TempIndex + 1;
            } else {
                Divider = 2 * TempIndex + 2;
            }
        } else {
            if (PQ[TempIndex].EdgeV->EdgeNumber < PQ[2 * TempIndex + 1].EdgeV->EdgeNumber ) {
                Divider = 2 * TempIndex + 1;
            } else if (PQ[TempIndex].EdgeV->EdgeNumber < PQ[2 * TempIndex + 2].EdgeV->EdgeNumber ) {
                Divider = 2 * TempIndex + 2;
            } else {
                //std::cout << std::endl;
                return;
            }
        }
    }
}

void PrintPQ(Edge * PQ, int Size) {
    for (int i = 0; i < Size; i++) {
        //std::cout << PQ[i].EdgeH << " " << PQ[i].EdgeV << std::endl;
        if (PQ[i].EdgeH != nullptr) {
            //std::cout << "AAA" << std::endl;
            std::cout << PQ[i].EdgeH->EdgeNumber << " ";
        } else if (PQ[i].EdgeV != nullptr) {
            //std::cout << "BBB" << std::endl;
            std::cout << PQ[i].EdgeV->EdgeNumber << " ";
        }
    }
    std::cout << std::endl;
}



/*What is the worst-case time complexity of your solution for a Priority Que of size n?
log(n) for searching -> deleting and inserting
retrieving k-min k-max -> O(1)
nlog(n) for heap sort
*/