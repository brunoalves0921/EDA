#ifndef redBlackTree
#define redBlackTree

#include <stdlib.h>
#include <iostream>

class RedBlackTree{
    public:
        RedBlackTree();
        ~RedBlackTree();
        void add(int key, int value);
        void remove(int key);
        void print();
        int get(int key);
    private:
        struct Node{
            int key;
            int value;
            Node *left;
            Node *right;
            Node *parent;
            bool isRed;
        };
        Node *root;
        Node *null;
        void _add(Node *node, int key, int value);
        void _remove(Node *node, int key);
        void _print(Node *node);
        void _rotateLeft(Node *node);
        void _rotateRight(Node *node);
        void _fix(Node *node);
        void _fixRemove(Node *node);
        Node* _getMin(Node *node);
        Node* _getMax(Node *node);
        Node* _get(Node *node, int key);
        void _deleteTree(Node *node);
};

#endif