#pragma once

#ifndef AVLTREE_H
#define AVLTREE_H

#include "../Node/Node.cpp"
#include <vector>

// NodeData contains the child members of Node and AVLData contains the child members of AVLTree
template<typename NodeData, typename AVLData>
class AVLTree {
    private: 
        bool IsShallowCopy;

        void PerformLLRotation(Node<NodeData> * CurrentNode);
        void PerformRRRotation(Node<NodeData> * CurrentNode);
        void PerformLRRotation(Node<NodeData> * CurrentNode);
        void PerformRLRotation(Node<NodeData> * CurrentNode);

        void CheckRotations(Node<NodeData> * CurrentNode, std::string Path = "");
        void PerformRotations(Node<NodeData> * CurrentNode, std::string & Path);
        void UpdateHeight(Node<NodeData> * CurrentParent, Node<NodeData> * CurrentNode, std::string & Path);

        void BuildIncreasingArray(Node<NodeData> * CurrentNode, std::vector<Node<NodeData> *> & IncreasingArray);
    public:
        AVLData * P;
        Node<NodeData> * Root;

        AVLTree(AVLData * NewPointer = nullptr);

        void Insert(int Number, Node<NodeData> ** CurrentNode, Node<NodeData> * PreviousNode = nullptr);

        void FindLeftMaximum(Node<NodeData> * CurrentNode, Node<NodeData> ** CurrentMaximum);

        Node<NodeData> * FindKthLargest(int K);
        Node<NodeData> * Find(int Number, Node<NodeData> * CurrentNode);

        void Delete(int Number);
        void Print(Node<NodeData> * CurrentNode);
};

#endif
