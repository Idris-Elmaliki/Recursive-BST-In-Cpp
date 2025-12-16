#include <iostream>

class Node {
public: 
    Node* left;
    Node* right;  

    int value; 

    Node(const int& data)
    : value(data) {
        left = nullptr; 
        right = nullptr; 
    }
};

class rBST {
    Node* root; 
    int length;

    bool rContains(Node* currentNode, const int& value) {
        if(currentNode == nullptr) {
            return false; 
        }

        if(currentNode->value == value) {
            return true; 
        }

        if(currentNode->value > value) {
            return rContains(currentNode->left, value); 
        }
        else {
            return rContains(currentNode->right, value);
        }
    }

    Node* rInsert(Node* currentNode, const int& value) {
        if(currentNode == nullptr) {
            length++; 
            return new Node(value); 
        }
        
        if(currentNode->value > value) {
            currentNode->left = rInsert(currentNode->left, value); 
        }
        else {
            currentNode->right = rInsert(currentNode->right, value); 
        }

        return currentNode; 
    }

    int minVlaue(Node* currentNode) {
        while(currentNode->left != nullptr) {
            currentNode = currentNode->left; 
        }

        return currentNode->value; 
    }

    Node* rDelete(Node* currentNode, const int& value) {
        if(currentNode == nullptr)
            return nullptr; 

        if(currentNode->value > value) {
            currentNode->left = rDelete(currentNode->left, value); 
        }
        else if(currentNode->value < value) {
            currentNode->right = rDelete(currentNode->right, value); 
        }
        else {
            if(currentNode->left == nullptr && currentNode->right == nullptr) {
                delete currentNode; 
                return nullptr; 
            }
            else if(currentNode->left == nullptr) {
                Node* temp = currentNode->right; 
                delete currentNode; 

                return temp; 
            }
            else if(currentNode->right == nullptr) {
                Node* temp = currentNode->left; 
                delete currentNode; 

                return temp; 
            }
            else {
                int subTreeMin = minVlaue(currentNode->right); 
                currentNode->value = subTreeMin; 

                currentNode->right = rDelete(currentNode->right, value); 
            }
        }
        
        return currentNode; 
    }

    void DestroyRecursive(Node* node){
        if (node) {
            DestroyRecursive(node->left);
            DestroyRecursive(node->right);
            delete node;
        }
    }

public: 
    rBST()
    : length(0)
    {
        root = nullptr;
    }

    rBST(const int& value)
    :length(1) 
    {
        root = new Node(value); 
    }

    bool rContains(const int& value) {
        return rContains(root, value); 
    }

    void rInsert(const int& value) {
        if(root == nullptr)
            root = new Node(value); 
        else 
            rInsert(root, value); 
    }

    void rDelete(const int& value) {
        root = rDelete(root, value); 
        length--; 
    }

    int size() {
        return length; 
    }

    ~rBST() {
        DestroyRecursive(root); 
    }
};
