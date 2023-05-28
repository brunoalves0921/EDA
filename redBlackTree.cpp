#include "redBlackTree.h"

template <typename Key, typename Value>
RedBlackTree<Key, Value>::RedBlackTree() {
    null = new Node; // Cria um novo nó nulo
    null->isRed = false; // Define a cor do nó nulo como preto
    null->left = nullptr; // Define o filho esquerdo do nó nulo como nullptr
    null->right = nullptr; // Define o filho direito do nó nulo como nullptr
    root = null; // Define a raiz da árvore como o nó nulo
}

template <typename Key, typename Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
    _deleteTree(root); // Chama a função auxiliar _deleteTree para excluir todos os nós da árvore
    delete null; // Libera a memória alocada para o nó nulo
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::add(Key key, Value value) {
    if (root == null) { // Se a árvore estiver vazia
        root = new Node; // Cria um novo nó como raiz
        root->key = key; // Define a chave do nó raiz como a chave fornecida
        root->value = value; // Define o valor do nó raiz como o valor fornecido
        root->left = null; // Define o filho esquerdo do nó raiz como o nó nulo
        root->right = null; // Define o filho direito do nó raiz como o nó nulo
        root->parent = null; // Define o pai do nó raiz como o nó nulo
        root->isRed = false; // Define a cor do nó raiz como preto
    } else {
        _add(root, key, value); // Chama a função auxiliar _add para adicionar um novo nó à árvore
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(Key key) {
    if (root == null) {
        throw std::invalid_argument("A árvore está vazia, não há nada para remover");
    }
    _remove(root, key); // Chama a função auxiliar _remove para remover o nó com a chave fornecida da árvore
}

template <typename Key, typename Value>
Value RedBlackTree<Key, Value>::get(Key key) {
    Node* node = _get(root, key); // Chama a função auxiliar _get para obter o nó com a chave fornecida da árvore
    if (node != null) {
        return node->value; // Retorna o valor associado à chave encontrada
    }
    else {
        throw std::invalid_argument("Chave não encontrada");
    }
}

template <typename Key, typename Value>  // todos os valores tal que minKey <= key <= maxKey
std::vector<Value> RedBlackTree<Key, Value>::getByRange(Key minKey, Key maxKey) {
    std::vector<Value> result; // Cria um vetor para armazenar os valores dentro do intervalo
    _getByRange(root, minKey, maxKey, result); // Chama a função auxiliar _getByRange para obter os valores dentro do intervalo
    return result; // Retorna o vetor de valores encontrados
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_rotateLeft(Node* node) {
    Node* rightChild = node->right; // Obtém o filho direito do nó
    node->right = rightChild->left; // Define o filho direito do nó como o filho esquerdo do filho direito

    if (rightChild->left != null) {
        rightChild->left->parent = node; // Atualiza o pai do filho esquerdo do filho direito
    }

    rightChild->parent = node->parent; // Atualiza o pai do filho direito

    if (node->parent == null) {
        root = rightChild; // Se o nó for a raiz, atualiza a raiz da árvore
    } else if (node == node->parent->left) {
        node->parent->left = rightChild; // Se o nó for o filho esquerdo do pai, atualiza o filho esquerdo do pai
    } else {
        node->parent->right = rightChild; // Se o nó for o filho direito do pai, atualiza o filho direito do pai
    }

    rightChild->left = node; // Define o nó como filho esquerdo do filho direito
    node->parent = rightChild; // Define o pai do nó como o filho direito
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_rotateRight(Node* node) {
    Node* leftChild = node->left; // Obtém o filho esquerdo do nó
    node->left = leftChild->right; // Define o filho esquerdo do nó como o filho direito do filho esquerdo

    if (leftChild->right != null) {
        leftChild->right->parent = node; // Atualiza o pai do filho direito do filho esquerdo
    }

    leftChild->parent = node->parent; // Atualiza o pai do filho esquerdo

    if (node->parent == null) {
        root = leftChild; // Se o nó for a raiz, atualiza a raiz da árvore
    } else if (node == node->parent->right) {
        node->parent->right = leftChild; // Se o nó for o filho direito do pai, atualiza o filho direito do pai
    } else {
        node->parent->left = leftChild; // Se o nó for o filho esquerdo do pai, atualiza o filho esquerdo do pai
    }

    leftChild->right = node; // Define o nó como filho direito do filho esquerdo
    node->parent = leftChild; // Define o pai do nó como o filho esquerdo
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_fix(Node* node) {
    while (node != root && node->parent->isRed) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;

            if (uncle->isRed) {
                // Caso 1: O tio do nó é vermelho
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent; // Move para o avô do nó
            } else {
                if (node == node->parent->right) {
                    // Caso 2: O tio do nó é preto e o nó é um filho direito
                    node = node->parent;
                    _rotateLeft(node); // Rotaciona o nó para a esquerda
                }

                // Caso 3: O tio do nó é preto e o nó é um filho esquerdo
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                _rotateRight(node->parent->parent); // Rotaciona o avô do nó para a direita
            }
        } else {
            Node* uncle = node->parent->parent->left;

            if (uncle->isRed) {
                // Caso 1: O tio do nó é vermelho
                node->parent->isRed = false;
                uncle->isRed = false;
                node->parent->parent->isRed = true;
                node = node->parent->parent; // Move para o avô do nó
            } else {
                if (node == node->parent->left) {
                    // Caso 2: O tio do nó é preto e o nó é um filho esquerdo
                    node = node->parent;
                    _rotateRight(node); // Rotaciona o nó para a direita
                }

                // Caso 3: O tio do nó é preto e o nó é um filho direito
                node->parent->isRed = false;
                node->parent->parent->isRed = true;
                _rotateLeft(node->parent->parent); // Rotaciona o avô do nó para a esquerda
            }
        }
    }

    root->isRed = false; // Garante que a raiz seja preta
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_fixRemove(Node* node) {
    while (node != root && !node->isRed) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;

            if (sibling->isRed) {
                // Caso 1: O irmão do nó é vermelho
                sibling->isRed = false;
                node->parent->isRed = true;
                _rotateLeft(node->parent); // Rotaciona o pai do nó para a esquerda
                sibling = node->parent->right;
            }

            if (!sibling->left->isRed && !sibling->right->isRed) {
                // Caso 2: O irmão do nó é preto e ambos os filhos do irmão são pretos
                sibling->isRed = true;
                node = node->parent; // Move para o pai do nó
            } else {
                if (!sibling->right->isRed) {
                    // Caso 3: O irmão do nó é preto, o filho esquerdo do irmão é preto e o filho direito do irmão é vermelho
                    sibling->left->isRed = false;
                    sibling->isRed = true;
                    _rotateRight(sibling); // Rotaciona o irmão para a direita
                    sibling = node->parent->right;
                }

                // Caso 4: O irmão do nó é preto e o filho direito do irmão é preto
                sibling->isRed = node->parent->isRed;
                node->parent->isRed = false;
                sibling->right->isRed = false;
                _rotateLeft(node->parent); // Rotaciona o pai do nó para a esquerda
                node = root; // Termina o loop, pois a propriedade das cores está preservada
            }
        } else {
            Node* sibling = node->parent->left;

            if (sibling->isRed) {
                // Caso 1: O irmão do nó é vermelho
                sibling->isRed = false;
                node->parent->isRed = true;
                _rotateRight(node->parent); // Rotaciona o pai do nó para a direita
                sibling = node->parent->left;
            }

            if (!sibling->right->isRed && !sibling->left->isRed) {
                // Caso 2: O irmão do nó é preto e ambos os filhos do irmão são pretos
                sibling->isRed = true;
                node = node->parent; // Move para o pai do nó
            } else {
                if (!sibling->left->isRed) {
                    // Caso 3: O irmão do nó é preto, o filho direito do irmão é preto e o filho esquerdo do irmão é vermelho
                    sibling->right->isRed = false;
                    sibling->isRed = true;
                    _rotateLeft(sibling); // Rotaciona o irmão para a esquerda
                    sibling = node->parent->left;
                }

                // Caso 4: O irmão do nó é preto e o filho esquerdo do irmão é preto
                sibling->isRed = node->parent->isRed;
                node->parent->isRed = false;
                sibling->left->isRed = false;
                _rotateRight(node->parent); // Rotaciona o pai do nó para a direita
                node = root; // Termina o loop, pois a propriedade das cores está preservada
            }
        }
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_add(Node* node, Key key, Value value) {
    if (key < node->key) {
        if (node->left != null) { // Se existir um filho esquerdo, recursivamente chama _add nele
            _add(node->left, key, value);
        } else {
            Node* newNode = new Node; // Cria um novo nó
            newNode->key = key; // Define a chave do novo nó
            newNode->value = value; // Define o valor do novo nó
            newNode->parent = node; // Define o pai do novo nó como o nó atual
            newNode->left = null; // Define os filhos esquerdo e direito do novo nó como nulos
            newNode->right = null;
            newNode->isRed = true; // Define a cor do novo nó como vermelho

            node->left = newNode; // Define o filho esquerdo do nó atual como o novo nó

            _fix(newNode); // Chama a função _fix para restaurar as propriedades da árvore vermelho-preta
        }
    } else {
        if (node->right != null) { // Se existir um filho direito, recursivamente chama _add nele
            _add(node->right, key, value);
        } else {
            Node* newNode = new Node; // Cria um novo nó
            newNode->key = key; // Define a chave do novo nó
            newNode->value = value; // Define o valor do novo nó
            newNode->parent = node; // Define o pai do novo nó como o nó atual
            newNode->left = null; // Define os filhos esquerdo e direito do novo nó como nulos
            newNode->right = null;
            newNode->isRed = true; // Define a cor do novo nó como vermelho

            node->right = newNode; // Define o filho direito do nó atual como o novo nó

            _fix(newNode); // Chama a função _fix para restaurar as propriedades da árvore vermelho-preta
        }
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_remove(Node* node, Key key) {
    Node* current = node;
    while (current != null) {
        if (key < current->key) {
            current = current->left; // Se a chave a ser removida for menor, vai para o filho esquerdo
        } else if (key > current->key) {
            current = current->right; // Se a chave a ser removida for maior, vai para o filho direito
        } else {
            break; // Chave encontrada, sai do loop
        }
    }

    if (current == null) {
        throw std::invalid_argument("Chave não encontrada"); // Se o nó atual for nulo, a chave não foi encontrada
    }

    Node* toRemove = current;

    if (toRemove->left != null && toRemove->right != null) {
        Node* successor = _getMin(toRemove->right); // Encontra o sucessor do nó a ser removido
        toRemove->key = successor->key; // Copia a chave e o valor do sucessor para o nó a ser removido
        toRemove->value = successor->value;
        toRemove = successor; // Define o nó a ser removido como o sucessor
    }

    Node* child = (toRemove->right != null) ? toRemove->right : toRemove->left; // Encontra o filho do nó a ser removido

    if (!toRemove->isRed) {
        if (child != null) {
            child->isRed = false; // Se o nó a ser removido não for vermelho e tiver um filho, o filho se torna preto
        } else {
            _fixRemove(toRemove); // Chama a função _fixRemove para restaurar as propriedades da árvore vermelho-preta
        }
    }

    if (toRemove->parent == null) {
        root = child; // Se o nó a ser removido for a raiz, atualiza a raiz para o filho
    } else if (toRemove == toRemove->parent->left) {
        toRemove->parent->left = child; // Atualiza o ponteiro do pai para o filho apropriado
    } else {
        toRemove->parent->right = child;
    }
    if (child != null) {
        child->parent = toRemove->parent; // Atualiza o ponteiro do filho para o pai
    }

    delete toRemove; // Libera a memória do nó removido
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::_getMin(Node* node) {
    while (node->left != null) {
        node = node->left; // Percorre a árvore para a esquerda até encontrar o nó com a menor chave
    }
    return node; // Retorna o nó com a menor chave
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::_getMax(Node* node) {
    while (node->right != null) {
        node = node->right; // Percorre a árvore para a direita até encontrar o nó com a maior chave
    }
    return node; // Retorna o nó com a maior chave
}

template <typename Key, typename Value>
typename RedBlackTree<Key, Value>::Node* RedBlackTree<Key, Value>::_get(Node* node, Key key) {
    if (node == null || key == node->key) {
        return node; // Se o nó atual for nulo ou a chave for encontrada, retorna o nó atual
    }

    if (key < node->key) {
        return _get(node->left, key); // Se a chave for menor, procura no filho esquerdo
    } else {
        return _get(node->right, key); // Se a chave for maior, procura no filho direito
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_getByRange(Node* node, Key minKey, Key maxKey, std::vector<Value>& result) {
    if (node == null) {
        return; // Se o nó atual for nulo, retorna
    }

    if (node->key > maxKey) {
        _getByRange(node->left, minKey, maxKey, result); // Se a chave do nó atual for maior que a chave máxima, procura no filho esquerdo
    }
    else if (node->key < minKey) {
        _getByRange(node->right, minKey, maxKey, result); // Se a chave do nó atual for menor que a chave mínima, procura no filho direito
    }
    else {
        _getByRange(node->left, minKey, maxKey, result); // Se a chave do nó atual estiver dentro do intervalo, procura nos filhos esquerdo e direito
        result.push_back(node->value); // Adiciona o valor do nó atual ao resultado
        _getByRange(node->right, minKey, maxKey, result);
    }
}

template <typename Key, typename Value>
void RedBlackTree<Key, Value>::_deleteTree(Node* node) {
    if (node != null) {
        _deleteTree(node->left); // Deleta recursivamente o filho esquerdo
        _deleteTree(node->right); // Deleta recursivamente o filho direito
        delete node; // Deleta o nó atual
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
        _print(node->left); // Imprime recursivamente o filho esquerdo
        std::cout << "Chave: " << node->key << ", Valor: " << node->value << ", Cor: " << (node->isRed ? "Vermelho" : "Preto") << std::endl; // Imprime as informações do nó atual
        _print(node->right); // Imprime recursivamente o filho direito
    }
}
