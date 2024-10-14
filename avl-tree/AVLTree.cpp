#pragma once

#include "AVLTree.h"

template <typename NodeData, typename AVLData> 
AVLTree<NodeData, AVLData>::AVLTree(AVLData * NewPointer) {
    IsShallowCopy = false;

    P = NewPointer;
    Root = nullptr;
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::PerformLLRotation(Node<NodeData> * CurrentNode) {
    Node<NodeData> * LeftNode = CurrentNode->P->LeftChild;
    Node<NodeData> * LLNode = LeftNode->P->LeftChild;
    Node<NodeData> * LRNode = LeftNode->P->RightChild;
    Node<NodeData> * CurrentNodeParent = CurrentNode->P->Parent;

    LeftNode->P->RightChild = CurrentNode;
    LeftNode->P->Parent = CurrentNodeParent;

    if (CurrentNodeParent != nullptr) {
        if (CurrentNodeParent->P->LeftChild ==  CurrentNode) {
            CurrentNodeParent->P->LeftChild = LeftNode;
        } else {
            CurrentNodeParent->P->RightChild = LeftNode;
        }
    } else {
        Root = LeftNode;
    }

    CurrentNode->P->LeftChild = LRNode;

    if (LRNode != nullptr) {
        LRNode->P->Parent = CurrentNode;

        if (LRNode->P->LeftHeight >= LRNode->P->RightHeight) {
            CurrentNode->P->LeftHeight = LRNode->P->LeftHeight + 1;
        } else {
            CurrentNode->P->LeftHeight = LRNode->P->RightHeight + 1;
        }
    } else {
        CurrentNode->P->LeftHeight = 0;
    }

    if (CurrentNode->P->LeftHeight >= CurrentNode->P->RightHeight) {
        LeftNode->P->RightHeight = CurrentNode->P->LeftHeight + 1;
    } else {
        LeftNode->P->RightHeight = CurrentNode->P->RightHeight + 1;
    }

    CurrentNode->P->Parent = LeftNode;
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::PerformRRRotation(Node<NodeData> * CurrentNode) {
    Node<NodeData> * RightNode = CurrentNode->P->RightChild;
    Node<NodeData> * RRNode = RightNode->P->RightChild;
    Node<NodeData> * RLNode = RightNode->P->LeftChild;
    Node<NodeData> * CurrentNodeParent = CurrentNode->P->Parent;

    RightNode->P->LeftChild = CurrentNode;
    RightNode->P->Parent = CurrentNodeParent;

    if (CurrentNodeParent != nullptr) {
        if (CurrentNodeParent->P->LeftChild == CurrentNode) {
            CurrentNodeParent->P->LeftChild = RightNode;
        } else {
            CurrentNodeParent->P->RightChild = RightNode;
        }
    } else {
        Root = RightNode;
    }

    CurrentNode->P->RightChild = RLNode;

    if (RLNode != nullptr) {
        RLNode->P->Parent = CurrentNode;

        if (RLNode->P->LeftHeight >= RLNode->P->RightHeight) {
            CurrentNode->P->RightHeight = RLNode->P->LeftHeight + 1;
        } else {
            CurrentNode->P->RightHeight = RLNode->P->RightHeight + 1;
        }
    } else {
        CurrentNode->P->RightHeight = 0;
    }

    if (CurrentNode->P->LeftHeight >= CurrentNode->P->RightHeight) {
        RightNode->P->LeftHeight = CurrentNode->P->LeftHeight + 1;
    } else {
        RightNode->P->LeftHeight = CurrentNode->P->RightHeight + 1;
    }

    CurrentNode->P->Parent = RightNode;
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::PerformLRRotation(Node<NodeData> * CurrentNode) {
    Node<NodeData> * LeftNode = CurrentNode->P->LeftChild;
    Node<NodeData> * LRNode = LeftNode->P->RightChild;
    Node<NodeData> * LRLNode = LRNode->P->LeftChild;
    Node<NodeData> * LRRNode = LRNode->P->RightChild;
    Node<NodeData> * CurrentNodeParent = CurrentNode->P->Parent;

    LRNode->P->LeftChild = LeftNode;
    LRNode->P->RightChild = CurrentNode;
    LRNode->P->Parent = CurrentNodeParent;

    if (CurrentNodeParent != nullptr) {
        if (CurrentNodeParent->P->LeftChild == CurrentNode) {
            CurrentNodeParent->P->LeftChild = LRNode;
        } else {
            CurrentNodeParent->P->RightChild = LRNode;
        }
    } else {
        Root = LRNode;
    }

    LeftNode->P->Parent = LRNode;
    LeftNode->P->RightChild = LRLNode;

    if (LRLNode != nullptr) {
        LRLNode->P->Parent = LeftNode;

        if (LRLNode->P->LeftHeight >= LRLNode->P->RightHeight) {
            LeftNode->P->RightHeight = LRLNode->P->LeftHeight + 1;
        } else {
            LeftNode->P->RightHeight = LRLNode->P->RightHeight + 1;
        }
    } else {
        LeftNode->P->RightHeight = 0;
    }

    if (LeftNode->P->LeftHeight >= LeftNode->P->RightHeight) {
        LRNode->P->LeftHeight = LeftNode->P->LeftHeight + 1;
    } else {
        LRNode->P->LeftHeight = LeftNode->P->RightHeight + 1;
    }

    CurrentNode->P->Parent = LRNode;
    CurrentNode->P->LeftChild = LRRNode;

    if (LRRNode != nullptr) {
        LRRNode->P->Parent = CurrentNode;

        if (LRRNode->P->LeftHeight >= LRRNode->P->RightHeight) {
            CurrentNode->P->LeftHeight = LRRNode->P->LeftHeight + 1;
        } else {
            CurrentNode->P->LeftHeight = LRRNode->P->RightHeight + 1;
        }
    } else {
        CurrentNode->P->LeftHeight = 0;
    }

    if (CurrentNode->P->LeftHeight >= CurrentNode->P->RightHeight) {
        LRNode->P->RightHeight = CurrentNode->P->LeftHeight + 1;
    } else {
        LRNode->P->RightHeight = CurrentNode->P->RightHeight + 1;
    }
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::PerformRLRotation(Node<NodeData> * CurrentNode) {
    Node<NodeData> * RightNode = CurrentNode->P->RightChild;
    Node<NodeData> * RLNode = RightNode->P->LeftChild;
    Node<NodeData> * RLLNode = RLNode->P->LeftChild;
    Node<NodeData> * RLRNode = RLNode->P->RightChild;
    Node<NodeData> * CurrentNodeParent = CurrentNode->P->Parent;

    RLNode->P->LeftChild = CurrentNode;
    RLNode->P->RightChild = RightNode;
    RLNode->P->Parent = CurrentNodeParent;

    if (CurrentNodeParent != nullptr) {
        if (CurrentNodeParent->P->LeftChild == CurrentNode) {
            CurrentNodeParent->P->LeftChild = RLNode;
        } else {
            CurrentNodeParent->P->RightChild = RLNode;
        }
    } else {
        Root = RLNode;
    }

    CurrentNode->P->Parent = RLNode;
    CurrentNode->P->RightChild = RLLNode;

    if (RLLNode != nullptr) {
        RLLNode->P->Parent = CurrentNode;

        if (RLLNode->P->LeftHeight >= RLLNode->P->RightHeight) {
            CurrentNode->P->RightHeight = RLLNode->P->LeftHeight + 1;
        } else {
            CurrentNode->P->RightHeight = RLLNode->P->RightHeight + 1;
        }
    } else {
        CurrentNode->P->RightHeight = 0;
    }

    if (CurrentNode->P->LeftHeight >= CurrentNode->P->RightHeight) {
        RLNode->P->LeftHeight = CurrentNode->P->LeftHeight + 1;
    } else {
        RLNode->P->LeftHeight = CurrentNode->P->RightHeight + 1;
    }

    RightNode->P->Parent = RLNode;
    RightNode->P->LeftChild = RLRNode;

    if (RLRNode != nullptr) {
        RLRNode->P->Parent = RightNode;

        if (RLRNode->P->LeftHeight >= RLRNode->P->RightHeight) {
            RightNode->P->LeftHeight = RLRNode->P->LeftHeight + 1;
        } else {
            RightNode->P->LeftHeight = RLRNode->P->RightHeight + 1;
        }
    } else {
        RightNode->P->LeftHeight = 0;
    }

    if (RightNode->P->LeftHeight >= RightNode->P->RightHeight) {
        RLNode->P->RightHeight = RightNode->P->LeftHeight + 1;
    } else {
        RLNode->P->RightHeight = RightNode->P->RightHeight + 1;
    }
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::PerformRotations(Node<NodeData> * CurrentNode, std::string & Path) {
    std::string RotationType = "";
    RotationType += Path[Path.length() - 1];
    RotationType += Path[Path.length() - 2];

    if (RotationType == "00") {
        PerformLLRotation(CurrentNode);
    } else if (RotationType == "11") { 
        PerformRRRotation(CurrentNode);
    } else if (RotationType == "01") {
        PerformLRRotation(CurrentNode);
    } else {
        PerformRLRotation(CurrentNode);
    }
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::UpdateHeight(Node<NodeData> * CurrentParent, Node<NodeData> * CurrentNode, std::string & Path) {
    if (CurrentParent != nullptr) {
        if (CurrentParent->P->LeftChild == CurrentNode) {
            Path += "0";

            if (CurrentParent->P->LeftHeight < Path.length()) {
                CurrentParent->P->LeftHeight++;
            }
        } else {
            Path += "1";

            if (CurrentParent->P->RightHeight < Path.length()) {
                CurrentParent->P->RightHeight++;
            }
        }
    } 
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::CheckRotations(Node<NodeData> * CurrentNode, std::string Path) {
    Node<NodeData> * OriginalNode = CurrentNode;
    Node<NodeData> * OriginalNodeParent = OriginalNode->P->Parent;
    Node<NodeData> * CurrentParent;
    int NodeHeight;

    for (int i = 0; i < 2; i++) {
        CurrentParent = CurrentNode->P->Parent; 
        
        if (CurrentParent == nullptr) {
            return;
        }

        UpdateHeight(CurrentParent, CurrentNode, Path);
        CurrentNode = CurrentParent;
    }

    int OtherHeight;
    Node<NodeData> * OtherCurrentNode;
    
    while (true) {
        NodeHeight = Path.length();

        if (CurrentNode->P->LeftHeight - CurrentNode->P->RightHeight > 1 || CurrentNode->P->LeftHeight - CurrentNode->P->RightHeight < -1) {
            return PerformRotations(CurrentNode, Path);
        }

        CurrentParent = CurrentNode->P->Parent;

        if (CurrentParent == nullptr) {
            return;
        }

        UpdateHeight(CurrentParent, CurrentNode, Path);
        CurrentNode = CurrentParent;
    }
}

/* Always initiialize CurrentNode with the Root of the AVLTree
PreviousNode should always be initialized as nullptr */
template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::Insert(int Number, Node<NodeData> ** CurrentNode, Node<NodeData> * PreviousNode) {
    if (Root == nullptr) {
        Root = new Node<NodeData>(new NodeData(Number));
        *CurrentNode = Root;

    } else if (*CurrentNode == nullptr) {
        *CurrentNode = new Node<NodeData>(new NodeData(Number));
        (*CurrentNode)->P->Parent = PreviousNode;

    } else if (Number <= (*CurrentNode)->P->Number) {
        return Insert(Number, &(*CurrentNode)->P->LeftChild, *CurrentNode);

    } else {
        return Insert(Number, &(*CurrentNode)->P->RightChild, *CurrentNode);
    }   

    CheckRotations(*CurrentNode, "");
}


// Traverse through the AVL Tree in increasing order to build the sorted array for retrieving Kth largest element
template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::BuildIncreasingArray(Node<NodeData> * CurrentNode, std::vector<Node<NodeData> *> & IncreasingArray) {
    if (CurrentNode == nullptr) {
        return;
    }

    BuildIncreasingArray(CurrentNode->P->LeftChild, IncreasingArray);

    IncreasingArray.push_back(CurrentNode);

    BuildIncreasingArray(CurrentNode->P->RightChild, IncreasingArray);
}

// Finds the KthLargest element in the AVLTree
template <typename NodeData, typename AVLData> 
Node<NodeData> * AVLTree<NodeData, AVLData>::FindKthLargest(int K) {
    if (K < 1) {
        std::cerr << "Invalid K value\n";
        return nullptr;
    }

    std::vector<Node<NodeData> *> IncreasingArray = std::vector<Node<NodeData> *>();

    BuildIncreasingArray(Root, IncreasingArray);

    return (IncreasingArray[IncreasingArray.size() - K]);
}

// Always initialize CurrentNode as the Root of the AVLTree
template <typename NodeData, typename AVLData> 
Node<NodeData> * AVLTree<NodeData, AVLData>::Find(int Number, Node<NodeData> * CurrentNode) {
    if (CurrentNode == nullptr || Number == CurrentNode->P->Number) {
        return CurrentNode;
    }

    if (Number <= CurrentNode->P->Number) {
        return Find(Number, CurrentNode->P->LeftChild);
    } 

    return Find(Number, CurrentNode->P->RightChild);
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::FindLeftMaximum(Node<NodeData> * CurrentNode, Node<NodeData> ** CurrentMaximum) {
    if (CurrentNode == nullptr) {
        return;
    }

    if (CurrentNode->P->Number > (*CurrentMaximum)->P->Number) {
        *CurrentMaximum = CurrentNode;
    } 

    FindLeftMaximum(CurrentNode->P->RightChild, CurrentMaximum);
}

template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::Delete(int Number) {
    Node<NodeData> * NodeFound = Find(Number, Root);

    if (NodeFound == nullptr) {
        std::cerr << "Node of number " << Number << " does not exist in the AVLTree\n";
        return;
    } 

    Node<NodeData> * NodeParent = (NodeFound)->P->Parent;
    Node<NodeData> * StartingParent = NodeParent;
    Node<NodeData> * PreviousNode = NodeFound;

    if (NodeParent == nullptr) {
        Root = nullptr;
    }

    if (NodeParent != nullptr) {
        if (NodeParent->P->LeftChild == NodeFound) {
            NodeParent->P->LeftHeight--;
        } else {
            NodeParent->P->RightHeight--;
        }
    }

    // If the node being deleted contains no children
    if (NodeFound->P->LeftChild == nullptr && NodeFound->P->RightChild == nullptr) {
        NodeFound->P->LeftHeight--;
        NodeFound->P->RightHeight--;

        while (NodeParent != nullptr) {
            if (NodeParent->P->LeftChild == PreviousNode) {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->LeftHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->LeftHeight = PreviousNode->P->RightHeight + 1;
                }

                if (NodeParent->P->LeftHeight - NodeParent->P->RightHeight > 1 || NodeParent->P->LeftHeight - NodeParent->P->RightHeight < -1) {
                    if (NodeParent->P->RightChild->P->LeftChild != nullptr) {
                        PerformRLRotation(NodeParent);
                        break;
                    } else {
                        PerformRRRotation(NodeParent);
                        break;
                    }
                }
            } else {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->RightHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->RightHeight = PreviousNode->P->RightHeight + 1;
                }

                if (NodeParent->P->LeftHeight - NodeParent->P->RightHeight > 1 || NodeParent->P->LeftHeight - NodeParent->P->RightHeight < -1) {
                    std::cout << NodeParent->P->Number << "\n";
                    if (NodeParent->P->LeftChild->P->RightChild != nullptr) {
                        PerformLRRotation(NodeParent);
                        break;
                    } else {
                        PerformLLRotation(NodeParent);
                        break;
                    }
                }
            }

            PreviousNode = NodeParent;
            NodeParent = NodeParent->P->Parent;
        }

        if (StartingParent != nullptr) {
            if (StartingParent->P->LeftChild == NodeFound) {
                StartingParent->P->LeftChild = nullptr;
            } else {
                StartingParent->P->RightChild = nullptr;
            }
        }

    // If the node being deleted contains both children
    } else if (NodeFound->P->LeftChild != nullptr && NodeFound->P->RightChild != nullptr) {
        Node<NodeData> * LeftMaximumNode = NodeFound->P->LeftChild;
        FindLeftMaximum(NodeFound->P->LeftChild, &LeftMaximumNode);

        Node<NodeData> * LeftMaxParent = LeftMaximumNode->P->Parent;
        NodeParent = LeftMaxParent;
        PreviousNode = LeftMaximumNode;

        while (NodeParent != NodeFound->P->Parent) {
            if (NodeParent->P->LeftChild == PreviousNode) {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->LeftHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->LeftHeight = PreviousNode->P->RightHeight + 1;
                }
            } else {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->RightHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->RightHeight = PreviousNode->P->RightHeight + 1;
                }
            }
            
            PreviousNode = NodeParent;
            NodeParent = NodeParent->P->Parent;
        }

        Node<NodeData> * PreviousNodeParent = PreviousNode->P->Parent;
        Node<NodeData> * PreviousLeftNode = PreviousNode->P->LeftChild;
        Node<NodeData> * PreviousRightNode = PreviousNode->P->RightChild;

        if (LeftMaxParent->P->RightChild == LeftMaximumNode) {
            LeftMaxParent->P->RightChild = nullptr;
            LeftMaxParent->P->RightHeight = 0;
        } else {
            LeftMaxParent->P->LeftChild = nullptr;
            LeftMaxParent->P->LeftHeight = 0;
        }

        LeftMaximumNode->P->LeftHeight = PreviousNode->P->LeftHeight;
        LeftMaximumNode->P->RightHeight = PreviousNode->P->RightHeight;
        LeftMaximumNode->P->Parent = PreviousNodeParent;

        if (PreviousLeftNode != LeftMaximumNode) {
            LeftMaximumNode->P->LeftChild = PreviousLeftNode;
        } 

        if (PreviousRightNode != LeftMaximumNode) {
            LeftMaximumNode->P->RightChild = PreviousRightNode;
        }

        if (PreviousNodeParent != nullptr) {
            if (PreviousNodeParent->P->LeftChild == PreviousNode) {
                PreviousNodeParent->P->LeftChild = LeftMaximumNode;
            } else {
                PreviousNodeParent->P->RightChild = LeftMaximumNode;
            }
        } else {
            Root = LeftMaximumNode;
        }

        if (PreviousLeftNode != LeftMaximumNode) {
            PreviousLeftNode->P->Parent = LeftMaximumNode;
        }

        if (PreviousRightNode != LeftMaximumNode) {
            PreviousRightNode->P->Parent = LeftMaximumNode;
        }

        if (LeftMaximumNode->P->LeftChild != nullptr) {
            if (LeftMaximumNode->P->LeftChild->P->LeftHeight >= LeftMaximumNode->P->LeftChild->P->RightHeight) {
                LeftMaximumNode->P->LeftHeight = LeftMaximumNode->P->LeftChild->P->LeftHeight + 1;
            } else {
                LeftMaximumNode->P->LeftHeight = LeftMaximumNode->P->LeftChild->P->RightHeight + 1;
            }
        } else {
            LeftMaximumNode->P->LeftHeight = 0;
        }

        if (LeftMaximumNode->P->RightChild != nullptr) {
            if (LeftMaximumNode->P->RightChild->P->LeftHeight >= LeftMaximumNode->P->RightChild->P->RightHeight) {
                LeftMaximumNode->P->RightHeight = LeftMaximumNode->P->RightChild->P->LeftHeight + 1;
            } else {
                LeftMaximumNode->P->RightHeight = LeftMaximumNode->P->RightChild->P->RightHeight + 1;
            }
        } else {
            LeftMaximumNode->P->RightHeight = 0;
        }

        if (LeftMaximumNode->P->LeftHeight - LeftMaximumNode->P->RightHeight > 1 || LeftMaximumNode->P->LeftHeight - LeftMaximumNode->P->RightHeight < -1) {
            if (LeftMaximumNode->P->LeftHeight >= LeftMaximumNode->P->RightHeight) {
                if (LeftMaximumNode->P->LeftChild->P->RightChild != nullptr) {
                    PerformLRRotation(LeftMaximumNode);
                } else {
                    PerformLLRotation(LeftMaximumNode);
                }
            } else {
                if (LeftMaximumNode->P->RightChild->P->LeftChild != nullptr) {
                    PerformRLRotation(LeftMaximumNode);
                } else {
                    PerformRRRotation(LeftMaximumNode);
                }
            }
        }

        NodeParent = LeftMaximumNode->P->Parent;
        PreviousNode = LeftMaximumNode;

        while (NodeParent != nullptr) {
            if (NodeParent->P->LeftChild == PreviousNode) {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->LeftHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->LeftHeight = PreviousNode->P->RightHeight + 1;
                }
            } else {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->RightHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->RightHeight = PreviousNode->P->RightHeight + 1;
                }
            }

            if (LeftMaximumNode->P->LeftHeight - LeftMaximumNode->P->RightHeight > 1 || LeftMaximumNode->P->LeftHeight - LeftMaximumNode->P->RightHeight < -1) {
                if (LeftMaximumNode->P->LeftHeight >= LeftMaximumNode->P->RightHeight) {
                    if (LeftMaximumNode->P->LeftChild->P->RightChild != nullptr) {
                        PerformLRRotation(NodeParent);
                    } else {
                        PerformLLRotation(NodeParent);
                    }
                } else {
                    if (LeftMaximumNode->P->RightChild->P->LeftChild != nullptr) {
                        PerformRLRotation(NodeParent);
                    } else {
                        PerformRRRotation(NodeParent);
                    }
                }
            }

            PreviousNode = NodeParent;
            NodeParent = NodeParent->P->Parent;
        }

    // If the node being deleted contains either children but NOT both
    } else {
        if (NodeParent != nullptr) {
            if (NodeParent->P->LeftChild == NodeFound) {
                if (NodeFound->P->LeftChild != nullptr) {
                    NodeParent->P->LeftChild = NodeFound->P->LeftChild;
                    NodeFound->P->LeftChild->P->Parent = NodeParent;
                    PreviousNode = NodeFound->P->LeftChild;
                } else {
                    NodeParent->P->LeftChild = NodeFound->P->RightChild;
                    NodeFound->P->RightChild->P->Parent = NodeParent;
                    PreviousNode = NodeFound->P->RightChild;
                }
            } else {
                if (NodeFound->P->LeftChild != nullptr) {
                    NodeParent->P->RightChild = NodeFound->P->LeftChild;
                    NodeFound->P->LeftChild->P->Parent = NodeParent;
                    PreviousNode = NodeFound->P->LeftChild;
                } else {
                    NodeParent->P->RightChild = NodeFound->P->RightChild;
                    NodeFound->P->RightChild->P->Parent = NodeParent;
                    PreviousNode = NodeFound->P->RightChild;
                }
            }
        }

        while (NodeParent != nullptr) {
            if (NodeParent->P->LeftChild == PreviousNode) {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->LeftHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->LeftHeight = PreviousNode->P->RightHeight + 1;
                }

                if (NodeParent->P->LeftHeight - NodeParent->P->RightHeight > 1 || NodeParent->P->LeftHeight - NodeParent->P->RightHeight < - 1) {
                    PerformRRRotation(NodeParent);
                    break;
                }
            } else {
                if (PreviousNode->P->LeftHeight >= PreviousNode->P->RightHeight) {
                    NodeParent->P->RightHeight = PreviousNode->P->LeftHeight + 1;
                } else {
                    NodeParent->P->RightHeight = PreviousNode->P->RightHeight + 1;
                }

                if (NodeParent->P->LeftHeight - NodeParent->P->RightHeight > 1 || NodeParent->P->LeftHeight - NodeParent->P->RightHeight < - 1) {
                    PerformLLRotation(NodeParent);
                    break;
                }
            }

            PreviousNode = NodeParent;
            NodeParent = NodeParent->P->Parent;
        }
    }

    delete NodeFound;
    NodeFound = nullptr;
}

// Always initiialize CurrentNode with the Root of the AVLTree
template <typename NodeData, typename AVLData> 
void AVLTree<NodeData, AVLData>::Print(Node<NodeData> * CurrentNode) {
    if (CurrentNode != nullptr) {
        std::cout << CurrentNode->P->Number << " LeftHeight: " << CurrentNode->P->LeftHeight << 
        " RightHeight: " << CurrentNode->P->RightHeight << "\n";
    } else {
        return;
    }

    Print(CurrentNode->P->LeftChild);
    Print(CurrentNode->P->RightChild);
}

