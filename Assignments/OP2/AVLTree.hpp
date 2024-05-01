#pragma once
#include "binarySearchTree.hpp"

struct AVLNode : Node {
    int height;
    AVLNode(int key) : Node(key), height(1) {}
};

class AVLTree : public BinarySearchTree {
protected:
    int height(Node* node) {
        if (!node) return 0;
        return static_cast<AVLNode*>(node)->height;
    }

    int getBalance(Node* node) {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        static_cast<AVLNode*>(y)->height = max(height(y->left), height(y->right)) + 1;
        static_cast<AVLNode*>(x)->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        static_cast<AVLNode*>(x)->height = max(height(x->left), height(x->right)) + 1;
        static_cast<AVLNode*>(y)->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    Node* insert(Node* &node, int key) override {
        comps++;
        // 1. Perform the normal BST insertion
        if (!node)
            return new AVLNode(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        // 2. Update height of this ancestor node
        static_cast<AVLNode*>(node)->height = 1 + max(height(node->left), height(node->right));

        // 3. Get the balance factor of this ancestor node to check whether
        // this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Function to delete a node from the AVL tree
    Node* remove(Node* &root, int key) override {
        comps++;
        // Perform standard BST delete
        if (root == nullptr)
            return root;

        if (key < root->key) {
            root->left = remove(root->left, key);
        } else if (key > root->key) {
            root->right = remove(root->right, key);
        } else {
            // Node to be deleted found
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                // Node with two children: Get the inorder successor
                Node* temp = root->right;
                while (temp->left != nullptr)
                    temp = temp->left;
                root->key = temp->key;
                root->right = remove(root->right, temp->key);
            }
        }

        // If the tree had only one node, then return
        if (root == nullptr)
            return root;

        // Update height of the current node
        static_cast<AVLNode*>(root)->height = 1 + max(height(root->left), height(root->right));

        // Get balance factor and balance the tree if needed
        int balance = getBalance(root);

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

public:
    // Public insert method
    void insert(int key) override {
        root = insert(root, key);
    }

    // Public delete method
    void remove(int key) override {
        root = remove(root, key);
    }
};
