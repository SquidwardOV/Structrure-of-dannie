Tree.h

  #pragma once
#include <iostream>

struct TNode {
    int Data;
    TNode* Left;
    TNode* Right;
    TNode* Parent;
};

class Tree {
public:
    Tree(TNode* root);
    ~Tree();
    void Insert(int value);
    void PrintTree();
    int GetLevel(TNode* node);
private:
    TNode* root;
    int MaxDepth(TNode* node);
    void PrintTree(TNode* node, int level, std::string prev_str, bool isLeft);
    void PrintT(TNode* node, int level);
};

Tree.cpp

#include "tree.h"

Tree::Tree(TNode* root)
    : root(root) {}

Tree::~Tree() {
    delete root;
}

void Tree::Insert(int value) {
    TNode* current = root;
    TNode* parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (value < current->Data)
            current = current->Left;
        else
            current = current->Right;
    }
    TNode* newNode = new TNode();
    newNode->Data = value;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    newNode->Parent = parent;
    
    if (parent == nullptr)
        root = newNode;
    else if (value < parent->Data)
        parent->Left = newNode;
    else
        parent->Right = newNode;
}

void Tree::PrintTree() {
    PrintTree(root, 0, "", false);
}

void Tree::PrintTree(TNode* node, int level, std::string prev_str, bool isLeft) {
    if (node != nullptr) {
        PrintTree(node->Right, level + 1, ".---", false);
        for (int i = 0; i < level; i++)
            std::cout << "    ";
        std::cout << prev_str << node->Data << std::endl;
        PrintTree(node->Left, level + 1, "`---", true);
    }
}
int Tree::GetLevel(TNode* node) {
    int level = 0;
    TNode* current = node;
    while (current->Parent != nullptr) {
        current = current->Parent;
        level++;
    }
    return level;
}

int Tree::MaxDepth(TNode* node) {
    if (node == nullptr)
        return 0;
    int leftDepth = MaxDepth(node->Left);
    int rightDepth = MaxDepth(node->Right);
    return std::max(leftDepth, rightDepth) + 1;
}

main.cpp
#include "tree.h"

int main() {
    // Создание объекта класса Tree
    TNode* root = new TNode();
    root->Data = 5;
    root->Left = nullptr;
    root->Right = nullptr;
    root->Parent = nullptr;
    Tree* myTree = new Tree(root);

    // Вставка вершин в дерево
    myTree->Insert(3);
    myTree->Insert(7);
    myTree->Insert(2);
    myTree->Insert(4);
    myTree->Insert(6);
    myTree->Insert(8);

    // Вывод дерева
    myTree->PrintTree();

    // Вывод уровней вершин
    std::cout << "Level of root: " << myTree->GetLevel(root) << std::endl;
    std::cout << "Level of node with value 3: " << myTree->GetLevel(root->Left) << std::endl;
    std::cout << "Level of node with value 8: " << myTree->GetLevel(root->Right->Right) << std::endl;

    // Освобождение памяти
    delete myTree;

    return 0;
}
  
