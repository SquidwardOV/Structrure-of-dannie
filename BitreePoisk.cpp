BiTree.h

  #pragma once
#include <iostream>
#include <time.h> 
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "compare_string.h"



enum ColorConsole {
    Blue = 1,
    Green = 2,
    Read = 12,
    White = 7
};
class Node {
public:
    std::string date;
    std::string color;
    int score;
    Node* right;
    Node* left;
    Node(std::string date) {
        color = "White";
        this->date = date;
        right = nullptr;
        left = nullptr;
        score = 1;
    }
};

class BiTree {
    Node* root;
    std::string found_str;
    char found_symbol;
    bool flag_found_str = 0;
    bool flag_found_symbol = 0;
    void add_more(std::string date, Node* Newroot);
    void remove_more(std::string date, Node* deleteNode);
    void paint_more_char(Node* left, Node* right);
    void paint_left_char(Node* left);
    void paint_right_char(Node* right);
    void paint_more_string(Node* left, Node* right);
    void paint_left_string(Node* left);
    void paint_right_string(Node* right);
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

  
    void showTrunks(Trunk* p)
    {
        if (p == nullptr) {
            return;
        }

        showTrunks(p->prev);
        std::cout << p->str;
    }

    void printTree(Node* root, Trunk* prev, bool isLeft)
    {
        if (root == nullptr) {
            return;
        }

        std::string prev_str = "    ";
        Trunk* trunk = new Trunk(prev, prev_str);

        printTree(root->right, trunk, true);

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
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (root->color == "Green") {
            SetConsoleTextAttribute(hConsole, Green);
            std::cout << " " << root->date << std::endl;
            SetConsoleTextAttribute(hConsole, White);
        }
        else if (root->color == "Blue") {
            SetConsoleTextAttribute(hConsole, Blue);
            std::cout << " " << root->date << std::endl;
            SetConsoleTextAttribute(hConsole, White);
        }
        else if (root->color == "Read") {
            SetConsoleTextAttribute(hConsole, Read);
            std::cout << " " << root->date << std::endl;
            SetConsoleTextAttribute(hConsole, White);
        }
        else {
            SetConsoleTextAttribute(hConsole, White);
            std::cout << " " << root->date << std::endl;
        }
        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->left, trunk, false);
    }

public:
    void add(std::string date);
    void remove(std::string date);
    void show();
    void paint();
    void FoundStr(std::string str);
    void FoundSymbol(char symbol);
    BiTree();
    ~BiTree();
};

BiTree.cpp

  #include "BiTree.h"

void BiTree::add(std::string date) {
	if (root == nullptr) {
		root = new Node(date);
	}
	else {
		add_more(date, root);
	}
}

void BiTree::add_more(std::string date, Node* newNode) {

	size_t pos = date.find_first_of(".,?!;:()[]{}");

	if (pos == std::string::npos) {
		
		if (compare_string(date, newNode->date) == 0) {
			if (newNode->right != nullptr) {
				add_more(date, newNode->right);
			}
			else {
				newNode->right = new Node(date);
			}
		}
		else if (compare_string(date, newNode->date) == 1) {
			if (newNode->left != nullptr) {
				add_more(date, newNode->left);
			}
			else {
				newNode->left = new Node(date);
			}
		}
		else {
			newNode->score++;
		}
	}
	else {

		std::string word = date.substr(0, pos);
		std::string punctuation = date.substr(pos, 1);

		if (compare_string(word, newNode->date) == 0) {
			if (newNode->right != nullptr) {
				add_more(word, newNode->right);
			}
			else {
				newNode->right = new Node(word);
			}
		}
		else if (compare_string(word, newNode->date) == 1) {
			if (newNode->left != nullptr) {
				add_more(word, newNode->left);
			}
			else {
				newNode->left = new Node(word);
			}
		}
		else {
			newNode->score++;
		}

		if (punctuation != newNode->date) {
			if (compare_string(punctuation, newNode->date) == 0) {
				if (newNode->right != nullptr) {
					add_more(punctuation, newNode->right);
				}
				else {
					newNode->right = new Node(punctuation);
				}
			}
			else if (compare_string(punctuation, newNode->date) == 1) {
				if (newNode->left != nullptr) {
					add_more(punctuation, newNode->left);
				}
				else {
					newNode->left = new Node(punctuation);
				}
			}
			else {
				newNode->score++;
			}
		}
	}
}
void BiTree::remove_more(std::string date, Node* deleteNode) {
	if (date == deleteNode->date) {
		if (deleteNode->score == 1) {
			if (deleteNode->left == nullptr && deleteNode->right != nullptr) {
				Node* current = deleteNode;
				deleteNode = deleteNode->right;
				delete current;
			}
			else if (deleteNode->right == nullptr && deleteNode->left != nullptr) {
				Node* current = deleteNode;
				deleteNode = deleteNode->left;
				delete current;
			}
			else {
				Node* current = deleteNode->left;
				while (current->right != nullptr) {
					current = current->right;
				}
				if (current->left != nullptr) {
					deleteNode->date = current->date;
					deleteNode->score = current->score;
					current = current->left;
				}
				else {
					deleteNode->date = current->date;
					deleteNode->score = current->score;
					delete current;
					current = nullptr;
				}
			}
		}
		else {
			deleteNode->score--;
		}
	}
	else if (date > deleteNode->date) {
		if (deleteNode->right != nullptr) {
			remove_more(date, deleteNode->right);
		}
		else {
			std::cout << "node not found" << std::endl;
		}
	}
	else {
		if (deleteNode->left != nullptr) {
			remove_more(date, deleteNode->left);
		}
		else {
			std::cout << "node not found" << std::endl;
		}
	}
}

void BiTree::remove(std::string date) {
	if (root == nullptr) {
		std::cout << "tree is empty" << std::endl;
	}
	else {
		remove_more(date, root);
	}
}

void BiTree::show() {
	paint();
	printTree(root, nullptr, false);
}

void BiTree::FoundStr(std::string str) {
	found_str = str;
	flag_found_str = 1;
	paint();
}

void BiTree::FoundSymbol(char symbol) {
	found_symbol = symbol;
	flag_found_symbol = 1;
	paint();
}


void BiTree::paint() {
	if (flag_found_str == 1) {
		if (root != nullptr) {
			if (root->date.find(found_str) != std::string::npos) {
				if (root->color == "Read") {

				}
				else if (root->color == "Blue") {
					root->color = "Read";
				}
				else {
					root->color = "Green";
				}

			}

			if (root->right == nullptr && root->left == nullptr) {
				return;
			}
			else if (root->right == nullptr) {
				paint_left_string(root->left);
			}
			else if (root->left == nullptr) {
				paint_right_string(root->left);
			}
			else {
				paint_more_string(root->right, root->left);
			}
		}
	}
	if (flag_found_symbol == 1) {
		if (root != nullptr) {
			if (root->date[0] == found_symbol) {
				if (root->color == "Read") {

				}
				else if (root->color == "Green") {
					root->color = "Read";
				}
				else {
					root->color = "Blue";
				}
			}
			if (root->right == nullptr && root->left == nullptr) {
				return;
			}
			else if (root->right == nullptr) {
				paint_left_char(root->left);
			}
			else if (root->left == nullptr) {
				paint_right_char(root->left);
			}
			else {
				paint_more_char(root->right, root->left);
			}
		}
	}
}

void BiTree::paint_more_string(Node* right, Node* left)
{
	if (right == nullptr && left == nullptr) {
		return;
	}
	else if (right == nullptr) {
		if (left->date.find(found_str) != std::string::npos) {
			if (left->color == "Read") {

			}
			else if (left->color == "Blue") {
				left->color = "Read";
			}
			else {
				left->color = "Green";
			}

		}
		return paint_left_string(left);
	}
	else if (left == nullptr) {
		if (right->date.find(found_str) != std::string::npos) {
			if (right->color == "Read") {

			}
			else if (right->color == "Blue") {
				right->color = "Read";
			}
			else {
				right->color = "Green";
			}
		}
		return paint_more_string(right->right, right->left);
	}
	else {
		if (right->date.find(found_str) != std::string::npos) {
			if (right->color == "Read") {

			}
			else if (right->color == "Blue") {
				right->color = "Read";
			}
			else {
				right->color = "Green";
			}
		}
		if (left->date.find(found_str) != std::string::npos) {
			if (left->color == "Read") {

			}
			else if (left->color == "Blue") {
				left->color = "Read";
			}
			else {
				left->color = "Green";
			}
		}
		return paint_more_string(right->right, right->left), paint_more_string(left->right, left->left);
	}
}


void BiTree::paint_right_string(Node* right)
{
	if (right->date.find(found_str) != std::string::npos) {
		if (right->color == "Read") {

		}
		else if (right->color == "Blue") {
			right->color = "Read";
		}
		else {
			right->color = "Green";
		}
	}
	if (right->right != nullptr && right->left != nullptr) {
		return paint_more_string(right->left, right->right);
	}
	else if (right->right != nullptr && right->left == nullptr) {
		return paint_right_string(right->right);
	}
	else if (right->right == nullptr && right->left != nullptr) {
		return paint_left_string(right->left);
	}
	else {

	}
}


void BiTree::paint_left_string(Node* left)
{
	if (left->date.find(found_str) != std::string::npos) {
		if (left->color == "Read") {

		}
		else if (left->color == "Blue") {
			left->color = "Read";
		}
		else {
			left->color = "Green";
		}
	}
	if (left->right != nullptr && left->left != nullptr) {
		return paint_more_string(left->left, left->right);
	}
	else if (left->right != nullptr && left->left == nullptr) {
		return paint_right_string(left->right);
	}
	else if (left->right == nullptr && left->left != nullptr) {
		return paint_left_string(left->left);
	}
	else {

	}
}

void BiTree::paint_more_char(Node* right, Node* left) {

	if (right == nullptr && left == nullptr) {
		return;
	}
	else if (right == nullptr) {
		if (left->date[0] == found_symbol) {
			if (left->color == "Read") {

			}
			else if (left->color == "Green") {
				left->color = "Read";
			}
			else {
				left->color = "Blue";
			}
		}
		return paint_left_char(left);
	}
	else if (left == nullptr) {
		if (right->date[0] == found_symbol) {
			if (right->color == "Read") {

			}
			else if (right->color == "Green") {
				right->color = "Read";
			}
			else {
				right->color = "Blue";
			}

		}
		return paint_more_char(right->right, right->left);
	}
	else {
		if (right->date[0] == found_symbol) {
			if (right->color == "Read") {

			}
			else if (right->color == "Green") {
				right->color = "Read";
			}
			else {
				right->color = "Blue";
			}

		}
		if (left->date[0] == found_symbol) {
			if (left->color == "Read") {

			}
			else if (left->color == "Green") {
				left->color = "Read";
			}
			else {
				left->color = "Blue";
			}
		}
		return paint_more_char(right->right, right->left), paint_more_char(left->right, left->left);
	}
}

void BiTree::paint_right_char(Node* right) {
	if (right->date[0] == found_symbol) {
		if (right->color == "Read") {

		}
		else if (right->color == "Green") {
			right->color = "Read";
		}
		else {
			right->color = "Blue";
		}

	}
	if (right->right != nullptr && right->left != nullptr) {
		return paint_more_char(right->left, right->right);
	}
	else if (right->right != nullptr && right->left == nullptr) {
		return paint_right_char(right->right);
	}
	else if (right->right == nullptr && right->left != nullptr) {
		return paint_left_char(right->left);
	}
	else {

	}
}

void BiTree::paint_left_char(Node* left) {
	if (left->date[0] == found_symbol) {
		if (left->color == "Read") {

		}
		else if (left->color == "Green") {
			left->color = "Read";
		}
		else {
			left->color = "Blue";
		}
	}
	if (left->right != nullptr && left->left != nullptr) {
		return paint_more_char(left->left, left->right);
	}
	else if (left->right != nullptr && left->left == nullptr) {
		return paint_right_char(left->right);
	}
	else if (left->right == nullptr && left->left != nullptr) {
		return paint_left_char(left->left);
	}
	else {

	}
}
BiTree::BiTree()
{

}


BiTree ::~BiTree() {

}


compare_string.h
#pragma once
#include <string>

bool compare_string(std::string left, std::string right);

compare_string.cpp

  #include "compare_string.h"
bool compare_string(std::string left, std::string right) {
	int size_right = right.size();
	int size_left = right.size();
	if (size_right > size_left) {
		for (int i = 0; i < size_left; ++i) {
			if (left[i] > right[i]) {
				return 0;
			}
			else if (left[i] < right[i]) {
				return 1;
			}
			else {

			}
		}
	}
	else {
		for (int i = 0; i < size_right; ++i) {
			if (left[i] > right[i]) {
				return 0;
			}
			else if (left[i] < right[i]) {
				return 1;
			}
			else {

			}
		}
	}
}

main.cpp

  #include <iostream>
#include <fstream>
#include "BiTree.h"
#include <Windows.h>

int main() {
    SetConsoleOutputCP(1251);
    BiTree tree;
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла." << std::endl;
        return 0;
    }

    std::string word;
    while (file >> word) {
        if (word.find(".") != std::string::npos) {
            word.erase(word.find("."));
        }
        if (word.find(",") != std::string::npos) {
            word.erase(word.find(","));
        }
        tree.add(word);
    }
    file.close();

    tree.show();

    tree.paint();

    std::string str;
    std::cout << "Введите слово для поиска: ";
    std::cin >> str;
    tree.FoundStr(str);

    char symbol;
    std::cout << "Введите символ для поиска: ";
    std::cin >> symbol;
    tree.FoundSymbol(symbol);

    tree.show();

    return 0;
}
