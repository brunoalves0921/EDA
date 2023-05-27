#ifndef redBlackTree
#define redBlackTree

#include <stdlib.h>
#include <iostream>
#include <vector>

template <typename Key, typename Value>
class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();
    void add(Key key, Value value);
    void remove(Key key);
    void print();
    Value get(Key key);
    std::vector<Value> getByRange(Key minKey, Key maxKey);

private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node* parent;
        bool isRed;
    };

    Node* root;
    Node* null;

    void _add(Node* node, Key key, Value value);
    void _remove(Node* node, Key key);
    void _print(Node* node);
    void _rotateLeft(Node* node);
    void _rotateRight(Node* node);
    void _fix(Node* node);
    void _fixRemove(Node* node);
    Node* _getMin(Node* node);
    Node* _getMax(Node* node);
    Node* _get(Node* node, Key key);
    void _deleteTree(Node* node);
    void _getByRange(Node* node, Key minKey, Key maxKey, std::vector<Value>& result);
};

#endif