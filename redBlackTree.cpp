#include "redBlackTree.h"

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() {
    null = new Node;
    null->isRed = false;
    null->left = nullptr;
    null->right = nullptr;
    root = null;
}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
    _deleteTree(root);
    delete null;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::add(Key key, Value value) {
    if (root == null) {
        root = new Node;
        root->key = key;
        root->value = value;
        root->left = null;
        root->right = null;
        root->parent = null;
        root->isRed = false;
    } else {
        _add(root, key, value);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(Key key) {
    if (root == null) {
        throw std::invalid_argument("A árvore está vazia, não há nada para remover");
    }
    _remove(root, key);
}

template <typename Key, typename Value>
Value RedBlackTree<Key, Value>::get(Key key) {
    Node* node = _get(root, key);
    if (node != null) {
        return node->value;
    }
    else {
        throw std::invalid_argument("Chave não encontrada");
    }
}

template <typename Key, typename Value>
std::vector<Value> RedBlackTree<Key, Value>::getByRange(Key minKey, Key maxKey) {
    std::vector<Value> result;
    _getByRange(root, minKey, maxKey, result);
    return result;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != null) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == null) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != null) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == null) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_fix(Node* node) {
    while (node != root && node->parent->isRed) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle->isRed) {
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    _rotateLeft(node);
                }

                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                _rotateRight(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;

            if (uncle->isRed) {
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    _rotateRight(node);
                }

                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                _rotateLeft(node->parent->parent);
            }
        }
    }

    root->isRed = false;
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_fixRemove(Node* node) {
    while (node != root && !node->isRed) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;

            if (sibling->isRed) {
                sibling->isRed = false;
                node->parent->isRed = true;
                _rotateLeft(node->parent);
                sibling = node->parent->right;
            }

            if (!sibling->left->isRed && !sibling->right->isRed) {
                sibling->isRed = true;
                node = node->parent;
            } else {
                if (!sibling->right->isRed) {
                    sibling->left->isRed = false;
                    sibling->isRed = true;
                    _rotateRight(sibling);
                    sibling = node->parent->right;
                }

                sibling->isRed = node->parent->isRed;
                node->parent->isRed = false;
                sibling->right->isRed = false;
                _rotateLeft(node->parent);
                node = root;
            }
        } else {
            Node* sibling = node->parent->left;

            if (sibling->isRed) {
                sibling->isRed = false;
                node->parent->isRed = true;
                _rotateRight(node->parent);
                sibling = node->parent->left;
            }

            if (!sibling->right->isRed && !sibling->left->isRed) {
                sibling->isRed = true;
                node = node->parent;
            } else {
                if (!sibling->left->isRed) {
                    sibling->right->isRed = false;
                    sibling->isRed = true;
                    _rotateLeft(sibling);
                    sibling = node->parent->left;
                }

                sibling->isRed = node->parent->isRed;
                node->parent->isRed = false;
                sibling->left->isRed = false;
                _rotateRight(node->parent);
                node = root;
            }
        }
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_add(Node* node, Key key, Value value) {
    if (key < node->key) {
        if (node->left != null) {
            _add(node->left, key, value);
        } else {
            Node* newNode = new Node;
            newNode->key = key;
            newNode->value = value;
            newNode->parent = node;
            newNode->left = null;
            newNode->right = null;
            newNode->isRed = true;

            node->left = newNode;

            _fix(newNode);
        }
    } else if (key > node->key) {
        if (node->right != null) {
            _add(node->right, key, value);
        } else {
            Node* newNode = new Node;
            newNode->key = key;
            newNode->value = value;
            newNode->parent = node;
            newNode->left = null;
            newNode->right = null;
            newNode->isRed = true;

            node->right = newNode;

            _fix(newNode);
        }
    } else {
        return;
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_remove(Node* node, Key key) {
    Node* current = node;
    while (current != null) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            break;
        }
    }

    if (current == null) {
        throw std::invalid_argument("Chave não encontrada");
    }

    Node* toRemove = current;

    if (toRemove->left != null && toRemove->right != null) {
        Node* successor = _getMin(toRemove->right);
        toRemove->key = successor->key;
        toRemove->value = successor->value;
        toRemove = successor;
    }

    Node* child = (toRemove->right != null) ? toRemove->right : toRemove->left;

    if (!toRemove->isRed) {
        if (child != null) {
            child->isRed = false;
        } else {
            _fixRemove(toRemove);
        }
    }

    if (toRemove->parent == null) {
        root = child;
    } else if (toRemove == toRemove->parent->left) {
        toRemove->parent->left = child;
    } else {
        toRemove->parent->right = child;
    }
    if (child != null) {
        child->parent = toRemove->parent;
    }

    delete toRemove;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::_getMin(Node* node) {
    while (node->left != null) {
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::_getMax(Node* node) {
    while (node->right != null) {
        node = node->right;
    }
    return node;
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::_get(Node* node, Key key) {
    if (node == null || key == node->key) {
        return node;
    }

    if (key < node->key) {
        return _get(node->left, key);
    } else {
        return _get(node->right, key);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_getByRange(Node* node, Key minKey, Key maxKey, std::vector<Value>& result) {
    // std::cout << node->key << " " << (node->key > maxKey) << " " << (node->key < minKey) << std::endl;
    if (node == null) {
        return;
    }

    if (node->key > maxKey) {
        _getByRange(node->left, minKey, maxKey, result);
    }
    else if (node->key < minKey) {
        _getByRange(node->right, minKey, maxKey, result);
    }
    else {
        _getByRange(node->left, minKey, maxKey, result);
        result.push_back(node->value);
        _getByRange(node->right, minKey, maxKey, result);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_deleteTree(Node* node) {
    if (node != null) {
        _deleteTree(node->left);
        _deleteTree(node->right);
        delete node;
    }
}

// Dentro da classe RedBlackTree

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::print() {
    _print(root);
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_print(Node* node) {
    if (node != null) {
        _print(node->left);
        std::cout << "Chave: " << node->key << ", Valor: " << node->value << ", Cor: " << (node->isRed ? "Vermelho" : "Preto") << std::endl;
        _print(node->right);
    }
}
