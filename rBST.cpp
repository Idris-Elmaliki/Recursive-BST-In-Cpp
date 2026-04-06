#include <iostream>

// Node represents a single element in the BST
class Node {
public: 
    Node* left;   // pointer to left child
    Node* right;  // pointer to right child  
    int value;    // value stored in the node

    // Constructor initializes node with value and null children
    Node(const int& data)
    : value(data) {
        left = nullptr; 
        right = nullptr; 
    }
};

class rBST {
    Node* root;   // root of the tree
    int length;   // number of nodes in the tree

    // Recursive search for a value in the tree
    bool rContains(Node* currentNode, const int& value) {
        if(currentNode == nullptr) {
            return false; // reached end → not found
        }

        if(currentNode->value == value) {
            return true; // value found
        }

        // Traverse left or right depending on comparison
        if(currentNode->value > value) {
            return rContains(currentNode->left, value); 
        }
        else {
            return rContains(currentNode->right, value);
        }
    }

    // Recursive insert into BST
    Node* rInsert(Node* currentNode, const int& value) {
        if(currentNode == nullptr) {
            length++; 
            return new Node(value); // insert new node here
        }
        
        // Place value in correct subtree
        if(currentNode->value > value) {
            currentNode->left = rInsert(currentNode->left, value); 
        }
        else {
            currentNode->right = rInsert(currentNode->right, value); 
        }

        return currentNode; // return unchanged root
    }

    // Finds minimum value in a subtree (leftmost node)
    int minVlaue(Node* currentNode) {
        while(currentNode->left != nullptr) {
            currentNode = currentNode->left; 
        }
        return currentNode->value; 
    }

    // Recursive delete operation
    Node* rDelete(Node* currentNode, const int& value) {
        if(currentNode == nullptr)
            return nullptr; // value not found

        // Traverse to find the node
        if(currentNode->value > value) {
            currentNode->left = rDelete(currentNode->left, value); 
        }
        else if(currentNode->value < value) {
            currentNode->right = rDelete(currentNode->right, value); 
        }
        else {
            // Case 1: no children (leaf)
            if(currentNode->left == nullptr && currentNode->right == nullptr) {
                delete currentNode; 
                return nullptr; 
            }
            // Case 2: only right child
            else if(currentNode->left == nullptr) {
                Node* temp = currentNode->right; 
                delete currentNode; 
                return temp; 
            }
            // Case 3: only left child
            else if(currentNode->right == nullptr) {
                Node* temp = currentNode->left; 
                delete currentNode; 
                return temp; 
            }
            // Case 4: two children
            else {
                // Replace with smallest value from right subtree
                int subTreeMin = minVlaue(currentNode->right); 
                currentNode->value = subTreeMin; 

                // Delete the duplicate node from right subtree
                currentNode->right = rDelete(currentNode->right, subTreeMin); 
            }
        }
        
        return currentNode; 
    }

    // Recursively deletes all nodes (used in destructor)
    void DestroyRecursive(Node* node){
        if (node) {
            DestroyRecursive(node->left);
            DestroyRecursive(node->right);
            delete node;
        }
    }

public: 
    // Default constructor
    rBST()
    : length(0)
    {
        root = nullptr;
    }

    // Constructor with an initial value
    rBST(const int& value)
    : length(1) 
    {
        root = new Node(value); 
    }

    // Public wrapper function for the recursive search
    bool rContains(const int& value) {
        return rContains(root, value); 
    }

    // Public insert
    void rInsert(const int& value) {
        if(root == nullptr)
            root = new Node(value); 
        else 
            rInsert(root, value); 
    }

    // Public delete
    void rDelete(const int& value) {
        root = rDelete(root, value); 
        length--; // assumes value existed
    }

    // Returns number of nodes
    int size() {
        return length; 
    }

    // Destructor cleans up all allocated memory
    ~rBST() {
        DestroyRecursive(root); 
    }
};