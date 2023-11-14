Tree.h

#pragma once
#include <iostream>
#include <string>

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
    int GetLevel(TNode* node);
    void print();
private:
    struct Trunk
    {
        Trunk* prev;
        std::string str;

        Trunk(Trunk* prev, std::string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };

    // Вспомогательная функция для печати ветвей бинарного дерева
    void showTrunks(Trunk* p)
    {
        if (p == nullptr) {
            return;
        }

        showTrunks(p->prev);
        std::cout << p->str;
    }

    void printTree(TNode* root, Trunk* prev, bool isLeft)
    {
        if (root == nullptr) {
            return;
        }

        std::string prev_str = "    ";
        Trunk* trunk = new Trunk(prev, prev_str);

        printTree(root->Right, trunk, true);

        if (!prev) {
            trunk->str = "---";
        }
        else if (isLeft)
        {
            trunk->str = ".---";
            prev_str = "   |";
        }
        else {
            trunk->str = "`---";
            prev->str = prev_str;
        }

        showTrunks(trunk);
        std::cout << " " << root->Data << std::endl;

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->Left, trunk, false);
    }
    TNode* root;
    int MaxDepth(TNode* node);


};

Tree.cpp

#include "tree.h"
#include <string>

Tree::Tree(TNode* root)
    : root(root) {}

Tree::~Tree() {
    delete root;
}

void Tree::print() {
    printTree(root, nullptr, false);
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
    myTree->print();

    // Вывод уровней вершин
    std::cout << "Level of root: " << myTree->GetLevel(root) << std::endl;
    std::cout << "Level of node with value 3: " << myTree->GetLevel(root->Left) << std::endl;
    std::cout << "Level of node with value 8: " << myTree->GetLevel(root->Right->Right) << std::endl;

    // Освобождение памяти
    delete myTree;

    return 0;
}

