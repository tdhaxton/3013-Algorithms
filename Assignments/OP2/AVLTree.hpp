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
        {
            return 0;
        }
        comparisons++;
        node->comps++;
        return height(node->left) - height(node->right);
    }

    Node* rotateRight(Node* y) {
        comparisons++;
        y->comps++;
        Node* x = y->left;
        comparisons++;
        y->comps++;
        Node* T2 = x->right;

        // Perform rotation
        comparisons++;
        y->comps++;
        x->right = y;
        comparisons++;
        y->comps++;
        y->left = T2;

        // Update heights
        static_cast<AVLNode*>(y)->height = max(height(y->left), height(y->right)) + 1;
        static_cast<AVLNode*>(x)->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    Node* rotateLeft(Node* x) {
        comparisons++;
        x->comps++;
        Node* y = x->right;
        comparisons++;
        x->comps++;
        Node* T2 = y->left;

        // Perform rotation
        comparisons++;
        x->comps++;
        y->left = x;
        comparisons++;
        x->comps++;
        x->right = T2;

        // Update heights
        static_cast<AVLNode*>(x)->height = max(height(x->left), height(x->right)) + 1;
        static_cast<AVLNode*>(y)->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    Node* insert(Node* &node, int key) override {
        // 1. Perform the normal BST insertion
        if (!node)
        {
            return new AVLNode(key);
        }

        if (key < node->key)
        {
            comparisons++;
            node->comps++;
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            comparisons++;
            node->comps++;
            node->right = insert(node->right, key);
        }
        else
        {
            comparisons++;
            node->comps++;
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
        {
            comparisons = comparisons + 2;
            node->comps = node->comps + 2;
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->key)
        {
            comparisons = comparisons = 2;
            node->comps = node->comps + 2;
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            comparisons = comparisons + 2;
            node->comps = node->comps + 2;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            comparisons = comparisons + 2;
            node->comps = node->comps + 2;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        comparisons++;
        node->comps++;
        return node;
    }

public:
    void insert(int key) override {
        root = insert(root, key);
    }
};
