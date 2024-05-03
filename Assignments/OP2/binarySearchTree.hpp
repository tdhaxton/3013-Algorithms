#pragma once
#include <iostream>
#include <sstream>

using namespace std;


struct Node {
    int key;
    Node *left;
    Node *right;
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {

protected:
    Node *root;
    int comps = 0;

    void toDotFormat(Node *node, std::stringstream &stream) const {
        if (!node) return;

        // Output the node itself
        stream << "    " << node->key << " [label=\"" << node->key << "\"];\n";

        // Output the connection to the left child if it exists
        if (node->left) {
            stream << "    " << node->key << " -- " << node->left->key << ";\n";
            toDotFormat(node->left, stream);
        }
        // else {                           //! lines 32 - 34 and 41 - 43 added to try to get nullptr symbols in graphviz online
        //     stream << "    " << node->key << " -- " << -node->key << " [label=\"\" shape=point] ;\n";
        // }

        // Output the connection to the right child if it exists
        if (node->right) {
            stream << "    " << node->key << " -- " << node->right->key << ";\n";
            toDotFormat(node->right, stream);
        }
        // else {
        //     stream << "    " << node->key << " -- " << -node->key << " [label=\"\" shape=point] ;\n";
        // }
    }

    int treeHeight(Node* node) {
        if(!node) {
            return 0;
        }
        return 1 + max(treeHeight(node->left), treeHeight(node->right));
        
    }

    // Function to insert a new key into the BST
    virtual Node *insert(Node *&node, int key) {
        comps++;
        if (!node) {
            node = new Node(key);
        } else if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    // Function to do inorder traversal of BST
    void inorder(Node *node) {
        if (node != nullptr) {
            inorder(node->left);                //! Segmentation fault here; removed leaf and then branch w/2 children and 4 additional ancestors
            std::cout << node->key << " ";      //! Segmentation fault here; cut right child of root, terminal only outputs left children of root
            inorder(node->right);
        }
    }

    // find the in-order successor
    Node *inOrderNode(Node *node) {
        Node *current = node;

        // find the leftmost leaf
        while (current != NULL && current->left != NULL)
            current = current->left;

        return current;
    }

    // Function to search a given key in a given BST
    bool search(Node *node, int key) {  //! removing bst.inorder output results in segmentation fault here
        comps++;    
        // Base Cases: root is null or key is present at root
        if (!node)
            return false;
        
        else {
            if (node->key == key)
                return true;

            // Key is greater than root's key
            else if (node->key < key)
                return search(node->right, key);

            // Key is smaller than root's key
            else
                return search(node->left, key);
        }
    }

    // Function to delete a node from the BST
    virtual Node* remove(Node* &node, int key) {
        comps++;
        // Returns if the tree is empty
        if (!node)
            return node;

        // Find the node to be deleted
        if (key < node->key) {
            node->left = remove(node->left, key);
            return node;
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
            return node;
        }
        else {
            // If key is same as root's key, then this is the node to be deleted
            // Node with only one child or no child
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // // Node with two children: Get the inorder successor
            // // (smallest in the right subtree)
            // Node* succParent = node;
            // Node* succ = node->right;
            // while (succ->left != NULL) {
            //     succParent = succ;
            //     succ = succ->left;
            // }

            // // Copy the inorder successor's content to this node
            // node->key = succ->key;

            // // Delete the inorder successor
            // if (succParent->left == succ)
            //     succParent->left = succ->right;
            // else
            //     succParent->right = succ->right;
            
            // delete succ;
            // return node;
            if (!node->left)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            // If the node has two children
            Node *temp = inOrderNode(node->right);
            // Place the in-order successor in position of the node to be deleted
            node->key = temp->key;
            // Delete the in-order successor
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}
    virtual void insert(int key) {
        insert(root, key);
    }

    void inorder() {
        inorder(root);
    }

    virtual void remove(int key) {
        root = remove(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    int treeHeight(){
        return treeHeight(root);
    }

    std::string toDotFormat() const {
        std::stringstream stream;
        stream << "graph BST {\n";
        stream << "    node [fontname=\"Helvetica\"];\n";

        if (!root) {
            stream << "\n";
        } else {
            toDotFormat(root, stream);
        }

        stream << "}\n";
        return stream.str();
    }

    int getComps(){
        return comps;
    }
};
