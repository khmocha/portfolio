#include "AVLTree.cpp"

struct NodeData {
    int Number;
    int LeftHeight;
    int RightHeight;
    Node<NodeData> * LeftChild;
    Node<NodeData> * RightChild;
    Node<NodeData> * Parent;

    NodeData(int NewNumber = 0) {
        Number = NewNumber;
        LeftChild = nullptr;
        RightChild = nullptr;
        Parent = nullptr;

        LeftHeight = 0;
        RightHeight = 0;
    }
};

int main() {
    srand(0);

    AVLTree<NodeData, void *> Tree = AVLTree<NodeData, void *>(); 

    int InsertArray[10] = {300, 200, 400, 100, 250, 305, 500, 600, 505, 1000};
    int N = 10;

    int DeleteArray[10] = {400, 200, 500, 100, 305, 600, 250, 300, 505, 1000};
    int D = 10;

    for (int i = 0; i < N; i++) {
        Tree.Insert(InsertArray[i], &Tree.Root);
    }

    int KthLargest = N;
    Node<NodeData> * KthNode = Tree.FindKthLargest(KthLargest);

    std::cout << KthLargest<< "th Largest Number is: " << KthNode->P->Number << "\n\n";

    Tree.Print(Tree.Root);
    std::cout << "\n";

    for (int i = 0; i < D; i++) {
        Tree.Delete(DeleteArray[i]);

        Tree.Print(Tree.Root);
        std::cout << "\n";
    }
}