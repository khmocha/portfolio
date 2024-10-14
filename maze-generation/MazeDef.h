#ifndef MAZEDEF_H
#define MAZEDEF_H

#include "Maze.h"

Graph::Graph() {
    Rows = 0;
    Columns = 0;

    GraphArray = nullptr;
    PriorityQueue = nullptr;
    Paths = nullptr;
}

Graph::Graph(int NewRows, int NewColumns) {
    srand(1118);

    Rows = NewRows;
    Columns = NewColumns;

    Paths = new LinkedList * [1000];
    
    for (int i = 0; i < 1000; i++) {
        Paths[i] = new LinkedList();
    }

    GraphArray = new Cell * [Rows];

    for (int i = 0; i < Rows; i++) {
        GraphArray[i] = new Cell [Columns];
    }

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            GraphArray[i][j].VertexNumber = (i * Columns) + j;

            std::cout << GraphArray[i][j].VertexNumber << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    int PQSize = (Rows * (Columns - 1)) + ((Rows - 1) * Columns);
    int CurrentIndex = 0;
    PriorityQueue = new Node [PQSize];

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            GraphArray[i][j].VertexConnections = new LinkedList();

            if (j < Columns - 1) {
                int SourceVertex = GraphArray[i][j].VertexNumber;
                int Vertex = GraphArray[i][j + 1].VertexNumber;
                int RandomNum = (rand() % 19) + 1;
                (*GraphArray[i][j].VertexConnections) += Node(Vertex, SourceVertex, RandomNum);
                Enqueue(PriorityQueue, CurrentIndex, PQSize, Node(Vertex, SourceVertex, RandomNum));
            }

            if (i < Rows - 1) {
                int SourceVertex = GraphArray[i][j].VertexNumber;
                int Vertex = GraphArray[i + 1][j].VertexNumber;
                int RandomNum = (rand() % 19) + 1;
                (*GraphArray[i][j].VertexConnections) += Node(Vertex, SourceVertex, RandomNum);
                Enqueue(PriorityQueue, CurrentIndex, PQSize, Node(Vertex, SourceVertex, RandomNum));
            }

            //std::cout << GraphArray[i][j].VertexNumber << ": ";
            std::cout << (*GraphArray[i][j].VertexConnections) << "   ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    //PrintPQ(PriorityQueue, PQSize);

    /*for (int i = 0; i < PQSize; i++) {
        Dequeue(PriorityQueue, PQSize, CurrentIndex);
        PrintPQ(PriorityQueue, PQSize);
    }*/
}

Cell ** Graph::ReturnGraphArray() {
    return GraphArray;
}

Node * Graph::ReturnPriorityQueue() {
    return PriorityQueue;
}

LinkedList ** Graph::ReturnPaths() {
    return Paths;
}

Graph::~Graph() {
    for (int i = 0; i < 100; i++) {
        delete Paths[i];
        Paths[i] = nullptr;
    }

    delete Paths;
    Paths = nullptr;

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            delete GraphArray[i][j].VertexConnections;
            GraphArray[i][j].VertexConnections = nullptr;
        }

        delete [] GraphArray[i];
        GraphArray[i] = nullptr;
    }

    delete [] GraphArray;
    GraphArray = nullptr;

    delete [] PriorityQueue;
    PriorityQueue = nullptr;
}

#endif