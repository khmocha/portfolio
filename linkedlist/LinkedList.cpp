#pragma once

#include "LinkedList.h"

template <typename NodeObject, typename LinkedListChildren>
LinkedList<NodeObject, LinkedListChildren>::LinkedList(LinkedListChildren * NewPointer) {
    Pointer = NewPointer;
    Head = nullptr;
    Tail = Head;
    Size = 0;
}

template <typename NodeObject, typename LinkedListChildren>
LinkedList<NodeObject, LinkedListChildren>::LinkedList(LinkedList & OtherList) {
    if (OtherList.Pointer != nullptr) {
        LinkedListChildren * CastedPointer = (LinkedListChildren *) OtherList.Pointer;
        Pointer = new LinkedListChildren(*CastedPointer);
    } else {
        Pointer = nullptr;
    }

    Head = nullptr;
    Tail = nullptr;
    Size = 0;

    Node<NodeObject> * CurrentOtherNode = nullptr;
    Node<NodeObject> * CurrentNode = nullptr;

    if (OtherList.Head != nullptr) {
        Head = new Node<NodeObject>(*OtherList.Head);
        CurrentOtherNode = OtherList.Head->Next;
        CurrentNode = Head->Next;

    } else {
        return;
    }

    Node<NodeObject> * PreviousNode = Head;
    
    while (CurrentOtherNode->Next != nullptr) {
        CurrentNode = new Node<NodeObject>(*CurrentOtherNode);  
        PreviousNode->Next = CurrentNode;
        CurrentNode->Previous = PreviousNode;
        PreviousNode = CurrentNode;

        CurrentNode = CurrentNode->Next;
        CurrentOtherNode = CurrentOtherNode->Next;
    }

    Tail = new Node<NodeObject>(*OtherList.Tail);
    PreviousNode->Next = Tail;
    Tail->Previous = PreviousNode;

    Size = OtherList.Size;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::InsertAtTail(Node<NodeObject> * NodeToAdd) {
    Node<NodeObject> * NewNode = NodeToAdd;

    if (Head != nullptr) {
        Tail->Next = NewNode;
        NewNode->Previous = Tail;
        Tail = NewNode;
    } else {
        Head = NewNode;
        Tail = Head;
    }

    Size++;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::DeleteTail() {
    if (Tail == nullptr) {
        std::cerr << "No tail to delete" << std::endl;
        return;
    }

    Node<NodeObject> * PreviousNode = Tail->Previous;

    if (Head == Tail) {
        delete Head;
        Head = nullptr;
    } else {
        delete Tail;
        PreviousNode->Next = nullptr;
    }

    Tail = nullptr;
    Tail = PreviousNode;

    Size--;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::DeleteHead() {
    if (Head == nullptr) {
        std::cerr << "No head to delete" << std::endl;
        return;
    }

    Node<NodeObject> * NextNode = Head->Next;

    if (Tail == Head) {
        delete Tail;
        Tail = nullptr;
    } else {
        delete Head;
        NextNode->Previous = nullptr;
    }

    Head = nullptr;
    Head = NextNode;

    Size--;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::DeleteSpecificNode(Node<NodeObject> * NodeToDelete) {
    if (Head == nullptr) {
        std::cerr << "No nodes to delete" << std::endl;
        return;
    }

    Node<NodeObject> * NextNode;
    Node<NodeObject> * PreviousNode;

    if (Head == NodeToDelete) {
        NextNode = Head->Next;
        delete Head;

        if (Tail == Head) {
            Head = nullptr;
            Tail = nullptr;
        } else {
            Head = NextNode;
            Head->Previous = nullptr;
        }
    } else if (Tail == NodeToDelete) {
        PreviousNode = Tail->Previous;
        delete Tail;
        Tail = PreviousNode;
        Tail->Next = nullptr;
        
    } else {
        NextNode = NodeToDelete->Next;
        PreviousNode = NodeToDelete->Previous;

        PreviousNode->Next = NextNode;
        NextNode->Previous = PreviousNode;

        delete NodeToDelete;
        NodeToDelete = nullptr;
    }

    Size--;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::Clear() {
    Node<NodeObject> * CurrentNode = Head;
    Node<NodeObject> * NextNode;
    
    while (CurrentNode != nullptr) {
        NextNode = CurrentNode->Next;

        delete CurrentNode;
        CurrentNode = nullptr;

        CurrentNode = NextNode;
    }

    Head = nullptr;
    Tail = Head;
    Size = 0;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::Print() {
    Node<NodeObject> * CurrentNode = Head;
    NodeObject * ClassPointer;

    while (CurrentNode != nullptr) {
        ClassPointer = CurrentNode->CastedPointer();
        ClassPointer->Print();
        CurrentNode = CurrentNode->Next;
    }

    std::cout << std::endl;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::ReversePrint() {
    Node<NodeObject> * CurrentNode = Tail;
    NodeObject * ClassPointer;

    while (CurrentNode != nullptr) {
        ClassPointer = CurrentNode->CastedPointer();
        ClassPointer->Print();
        CurrentNode = CurrentNode->Previous;
    }

    std::cout << std::endl;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::PrintShared() {
    Node<NodeObject> * CurrentNode = Head;

    while (CurrentNode != nullptr) {
        std::cout << CurrentNode->CastedPointer()->Number << " ";

        CurrentNode = CurrentNode->Next;
    }

    std::cout << std::endl;
}

template <typename NodeObject, typename LinkedListChildren>
void LinkedList<NodeObject, LinkedListChildren>::ReversePrintShared() {
    Node<NodeObject> * CurrentNode = Tail;

    while (CurrentNode != nullptr) {
        std::cout << CurrentNode->CastedPointer()->Number << " ";

        CurrentNode = CurrentNode->Previous;
    }
    
    std::cout << std::endl;
}

template <typename NodeObject, typename LinkedListChildren>
LinkedListChildren * LinkedList<NodeObject, LinkedListChildren>::CastedPointer() {
    return (LinkedListChildren *) Pointer;
}

template <typename NodeObject, typename LinkedListChildren>
LinkedList<NodeObject, LinkedListChildren>::~LinkedList() {
    Node<NodeObject> * CurrentNode = Head;
    Node<NodeObject> * NextNode;
    
    while (CurrentNode != nullptr) {
        NextNode = CurrentNode->Next;
        
        delete CurrentNode;

        CurrentNode = NextNode;
    }

    if (Pointer != nullptr) {
        delete (LinkedListChildren *) Pointer;
        Pointer = nullptr;
    }
}
