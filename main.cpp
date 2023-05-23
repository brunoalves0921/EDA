#include <iostream>
#include "redBlackTree.h"

int main() {
    RedBlackTree tree;

    // Adicionando elementos à árvore
    tree.add(10, 100);
    tree.add(5, 50);
    tree.add(15, 150);
    tree.add(3, 30);
    tree.add(7, 70);
    tree.add(12, 120);
    tree.add(18, 180);

    // Imprimindo a árvore
    std::cout << "Árvore Rubro-Negra:" << std::endl;
    tree.print();
    std::cout << std::endl;

    // Buscando elementos na árvore
    int key = 7;
    try {
        int value = tree.get(key);
        std::cout << "Chave " << key << ": " << value << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }

    key = 20;
    try {
        int value = tree.get(key);
        std::cout << "Chave " << key << ": " << value << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }

    // Removendo elementos da árvore
    try {
        key = 5;
        tree.remove(key);
        std::cout << "Removendo chave " << key << std::endl;
        key = 15;
        tree.remove(key);
        std::cout << "Removendo chave " << key << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }

    // Imprimindo a árvore após as remoções
    std::cout << "Árvore após remoções:" << std::endl;
    tree.print();
    std::cout << std::endl;

    return 0;
}
