#include "../DataStructures/MinBinaryHeap.cpp"
#include "../DataStructures/Graph.cpp"

template<typename T, typename T2, typename T3>
void CalculateShortestPath(LinkedList<T, T2> * CurrentPath, Graph<T, T2, T3> & Graph, T3 * CurrentVertex) {
    std::cout << "Current Vertex: " << CurrentVertex->Identifier << "\n";
    if (CurrentVertex->Identifier == 'B') {
        return;
    }

    int ShortestDistance = 0;
    T ClosestNode;
    T3 * ClosestVertex;

    for (int i = 0; i < CurrentVertex->CurrentSize; i++) {
        ClosestNode = CurrentVertex->Array[i];
        ClosestVertex = (T3 *) ClosestNode.Pointer;

        if (ClosestVertex->Visited == false && ClosestVertex->Number == 0) {
            ClosestVertex->Number = ClosestNode.Number;
            std::cout << ClosestVertex->Number << "\n";
        }
        //std::cout << ClosestVertex->Number << "\n";
    }

    for (int i = 0; i < CurrentVertex->CurrentSize; i++) {
        ClosestNode = CurrentVertex->Array[i];
        ClosestVertex = (T3 *) ClosestNode.Pointer;

        if (ClosestVertex->Visited == false) {
            ShortestDistance = ClosestNode.Number;
            break;
        }
    }

    //std::cout << "Closest Vertex: " << ClosestVertex->Identifier << "\n";
    //std::cout << "Shortest Distance: " << ShortestDistance << "\n";
    std::cout << "Original Path Dist: " << ClosestVertex->Number << "\n\n";

    std::cout << ClosestNode.Number << " " << CurrentPath->Tail->Number << "\n";
    std::cout << "New Dist: " << ClosestNode.Number + CurrentPath->Tail->Number << "\n\n";

    T3 * TailVertex = (T3 *) CurrentPath->Tail->Pointer;

    ClosestNode.Number += CurrentPath->Tail->Number;
    CurrentPath->InsertAtTail(new T(ClosestNode));


    //ClosestNode.Number += CurrentPath->Tail->Number;
    //CurrentPath->InsertAtTail(new T(ClosestNode));
    //CurrentVertex->DeleteRoot();

    ClosestVertex = (T3 *) CurrentVertex->Array[0].Pointer;
    ShortestDistance = CurrentVertex->Array[0].Number;

    //std::cout << "New Closest Vertex: " << ClosestVertex->Identifier << "\n";
    //std::cout << "New Shortest Distance: " << ShortestDistance << "\n\n";

    std::cout << "Current Path:\n";
    T * CurrentNode = CurrentPath->Head;
    T3 * Vertex;

    while (CurrentNode != nullptr) {
        Vertex = (T3 *) CurrentNode->Pointer;
        std::cout << Vertex->Identifier << CurrentNode->Number << " -> ";
        CurrentNode = CurrentNode->Next;
    }

    CurrentVertex->Visited = true;

    std::cout << std::endl << std::endl;

    CalculateShortestPath(CurrentPath, Graph, (T3 *) CurrentPath->Tail->Pointer);
}

int main() {
    int NumVertices = 7;

    Graph<NodeV5, char, MinBinaryHeap<NodeV5, char>> NewGraph = Graph<NodeV5, char, MinBinaryHeap<NodeV5, char>>(NumVertices);
    char Array[NumVertices] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    NewGraph.BuildVertices(Array);

    NewGraph.BuildEdge2(NewGraph.Vertices2[0], NewGraph.Vertices2[2], 3); // A<->C (3)
    NewGraph.BuildEdge2(NewGraph.Vertices2[0], NewGraph.Vertices2[5], 2); // A<->F (2)

    NewGraph.BuildEdge2(NewGraph.Vertices2[2], NewGraph.Vertices2[5], 2); // C<->F (2)
    NewGraph.BuildEdge2(NewGraph.Vertices2[2], NewGraph.Vertices2[3], 4); // C<->D (4)
    NewGraph.BuildEdge2(NewGraph.Vertices2[2], NewGraph.Vertices2[4], 1); // C<->E (1)

    NewGraph.BuildEdge2(NewGraph.Vertices2[3], NewGraph.Vertices2[1], 1); // D<->B (1)

    NewGraph.BuildEdge2(NewGraph.Vertices2[4], NewGraph.Vertices2[1], 2); // E<->B (2)

    NewGraph.BuildEdge2(NewGraph.Vertices2[5], NewGraph.Vertices2[4], 3); // F<->E (3)
    NewGraph.BuildEdge2(NewGraph.Vertices2[5], NewGraph.Vertices2[6], 5); // F<->G (5)
    NewGraph.BuildEdge2(NewGraph.Vertices2[5], NewGraph.Vertices2[1], 6); // F<->B (6)


    NewGraph.BuildEdge2(NewGraph.Vertices2[6], NewGraph.Vertices2[1], 2); // G<->B (2)
    
    NewGraph.Print2();

    LinkedList<NodeV5, char> * CurrentPath = new LinkedList<NodeV5, char>();

    CurrentPath->InsertAtTail(new NodeV5(0, (void *) NewGraph.Vertices2[0]));

    CalculateShortestPath(CurrentPath, NewGraph, NewGraph.Vertices2[0]);

    NodeV5 * CurrentNode = CurrentPath->Head;
    MinBinaryHeap<NodeV5, char> * Vertex;

    while (CurrentNode != nullptr) {
        Vertex = (MinBinaryHeap<NodeV5, char>  *) CurrentNode->Pointer;
        std::cout << Vertex->Identifier << CurrentNode->Number << " -> ";
        CurrentNode = CurrentNode->Next;
    }

    return 0;
}