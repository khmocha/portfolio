#pragma once

#include "Graph.h"

template<typename T, typename T2, typename T3>
Graph<T, T2, T3>::Graph() {
    NumberOfVertices = 0;
    DirectedGraph = false;
    Vertices = nullptr;
    Vertices2 = nullptr;
}

template<typename T, typename T2, typename T3>
Graph<T, T2, T3>::Graph(int Size, bool IsDirected) {
    NumberOfVertices = Size;
    DirectedGraph = IsDirected;
    Vertices = new LinkedList<T, T2> * [NumberOfVertices];
    Vertices2 = new T3 * [NumberOfVertices];
}

template<typename T, typename T2, typename T3>
void Graph<T, T2, T3>::BuildVertices(T2 * Array) {
    for (int i = 0; i < NumberOfVertices; i++) {
        Vertices[i] = new LinkedList<T, T2>(Array[i]);
    }

    for (int i = 0; i < NumberOfVertices; i++) {
        Vertices2[i] = new T3(NumberOfVertices, Array[i]);
    }
}

template<typename T, typename T2, typename T3>
void Graph<T, T2, T3>::BuildEdge(LinkedList<T, T2> * List, LinkedList<T, T2> * ListToConnect, int NewNumber) {
    List->InsertAtTail(new T(NewNumber, (void *) ListToConnect));

    if (DirectedGraph == false) {
        ListToConnect->InsertAtTail(new T(NewNumber, (void *) List));
    }
}

template<typename T, typename T2, typename T3>
void Graph<T, T2, T3>::BuildEdge2(T3 * Heap, T3 * HeapToConnect, int NewNumber) {
    Heap->Insert(T(NewNumber, (void *) HeapToConnect));

    if (DirectedGraph == false) {
        HeapToConnect->Insert(T(NewNumber, (void *) Heap));
    }
}

template<typename T, typename T2, typename T3>
LinkedList<T, T2> * Graph<T, T2, T3>::ReturnCastedPointer(void * Pointer) {
    LinkedList<T, T2> * CastedPointer = (LinkedList<T, T2> *) Pointer;

    return CastedPointer;
}

template<typename T, typename T2, typename T3>
T3 * Graph<T, T2, T3>::ReturnCastedPointer2(void * Pointer) {
    T3 * CastedPointer = (T3 *) Pointer;

    return CastedPointer;
}

template<typename T, typename T2, typename T3>
void Graph<T, T2, T3>::Print() {
    for (int i = 0; i < NumberOfVertices; i++) {
        T * CurrentNode = Vertices[i]->Head;

        std::cout << "LinkedList " << Vertices[i]->Identifier << ": ";

        while (CurrentNode != nullptr) {
            LinkedList<T, T2> * LinkedListPointer = ReturnCastedPointer((void *) CurrentNode->Pointer);

            std::cout << LinkedListPointer->Identifier << "(" << CurrentNode->Number << ") ";

            CurrentNode = CurrentNode->Next;
        }

        std::cout << "\n";
    }
    std::cout << std::endl;
}

template<typename T, typename T2, typename T3>
void Graph<T, T2, T3>::Print2() {
    for (int i = 0; i < NumberOfVertices; i++) {
        std::cout << "Heap " << Vertices2[i]->Identifier << ": ";

        for (int j = 0; j < Vertices2[i]->CurrentSize; j++) {
            T3 * HeapPointer = ReturnCastedPointer2((void *) Vertices2[i]->Array[j].Pointer);

            std::cout << HeapPointer->Identifier << "(" << Vertices2[i]->Array[j].Number << ") ";
        }

        std::cout << "\n";
    }
    std::cout << std::endl;
}

template<typename T, typename T2, typename T3>
Graph<T, T2, T3>::~Graph() {
    for (int i = 0; i < NumberOfVertices; i++) {
        delete Vertices[i];
        delete Vertices2[i];
    }

    delete [] Vertices;
    delete [] Vertices2;
}