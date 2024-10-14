#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.cpp"
#include "MinBinaryHeap.cpp"
#include "MaxBinaryHeap.cpp"

template <typename T, typename T2, typename T3>
struct Graph {
    int NumberOfVertices;
    bool DirectedGraph;
    LinkedList<T, T2> ** Vertices;
    T3 ** Vertices2;

    Graph();
    Graph(int Size, bool IsDirected = false);

    void BuildVertices(T2 * Array);
    void BuildEdge(LinkedList<T, T2> * List, LinkedList<T, T2> * ListToConnect, int NewNumber = 0);
    void BuildEdge2(T3 * Heap, T3 * HeapToConnect, int NewNumber = 0);

    LinkedList<T, T2> * ReturnCastedPointer(void * Pointer);
    T3 * ReturnCastedPointer2(void * Pointer);

    void Print();
    void Print2();

    ~Graph();
};

#endif

