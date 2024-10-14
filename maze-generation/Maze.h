#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include "LinkedList.h"

struct Cell {
    int VertexNumber;
    LinkedList * VertexConnections;
    Cell * Origin;
};

struct VerticalEdge {
    Cell * UpVertex;
    Cell * BottomVertex;
    int EdgeNumber;
};

struct HorizontalEdge {
    Cell * LeftVertex;
    Cell * RightVertex;
    int EdgeNumber;
};
          
struct Edge {
    VerticalEdge * EdgeV;
    HorizontalEdge * EdgeH;
};

class Maze {
    private:
        int Rows, Columns;
        int * PriorityQueue;
        Edge * PriorityQueue2;
        Cell ** MazeArray;

        VerticalEdge ** EdgesV;
        HorizontalEdge ** EdgesH; 

    public:
        Maze();
        Maze(int NewRows, int NewColumns, int RandomValue = 0);

        int * ReturnPriorityQueue();

        ~Maze();

};

#endif