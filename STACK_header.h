Stack.h

struct Node {
	int date;
	Node* ptr;

};

struct Stack {
private:
	int size = 0;
	Node *head = new Node;
public:
	void add(int date);
	void remove();
	int show();
	void clear();
	~Stack();
	Stack(int* arr, int score);
	Stack();


};

Stack.cpp

#include "Header.h"
#include <iostream>

void Stack::add(int date) {
	if (size == 0) {
		head->date = date;
		size++;
	}
	else {
		Node* newNode = new Node;
		newNode->date = head->date;
		newNode->ptr = head->ptr;
		head->date = date;
		head->ptr = newNode;

		size++;
	}
}
void Stack::remove() {
	if (size == 0) {
		throw;
	}
	else if (size == 1) {
		size--;
	}else {
		std::cout << head->date << std::endl;
		Node* current = new Node;
		current = head;
		head = head->ptr;
		delete current;
		size--;
	}
}
int Stack::show() {
	if (size > 0) {
		return head->date;
	}
	else {
		throw;
	}
}

void Stack::clear() {
	while (size > 0) {
		remove();
	}
}

Stack::~Stack() {
	clear();
	delete head;
}

Stack::Stack() {


}

Stack::Stack(int* arr, int score) {
	for (int i = 0; i < score; ++i) {
		if (size == 0) {
			head->date = arr[i];
			size++;
		}
		else {
			Node* NewNode = new Node;
			NewNode->ptr = head->ptr;
			NewNode->date = head->date;
			head->ptr = NewNode;
			head->date = arr[i];
			size++;
		}
	}
}

main.cpp
