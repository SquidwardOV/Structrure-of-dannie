template <typename T>
class Stack {
private:
	template <typename T>
	class Node {
	public:
		T date;
		Node* ptr;
	};
	int size = 0;
	Node<T>* head = new Node<T>;
public:

	void add(T date);
	T show();
	void remove();
	void clear();
	Stack(T* arr, int score);
	Stack();
	~Stack();
};

template <typename T>
Stack<T>::Stack(T* arr, int score) {
	for (int i = 0; i < score; ++i) {
		if (size == 0) {
			head->date = arr[i];
			size++;
		}
		else {
			Node<T>* NewNode = new Node<T>;
			NewNode->ptr = head->ptr;
			NewNode->date = head->date;
			head->ptr = NewNode;
			head->date = arr[i];
			size++;
		}
	}
}

template <typename T>
Stack<T>::Stack() {

}


template <typename T>
void Stack<T>::add(T date) {
	if (head->ptr == nullptr && size == 0) {
		head = new Node<T>;
		head->date = date;
		size++;
	}
	else {
		Node<T>* NewNode = new Node<T>;
		NewNode->ptr = head->ptr;
		NewNode->date = head->date;
		head->ptr = NewNode;
		head->date = date;
		size++;
	}
}

template <typename T>
void Stack<T>::remove() {
	if (head->ptr == nullptr) {
		size--;
	}
	else {
		Node<T>* CurrentNode = new Node<T>;
		CurrentNode = head;
		head = head->ptr;
		delete CurrentNode;
		size--;
	}
}

template <typename T>
void Stack<T>::clear() {
	while (size > 0) {
		remove();
	}
}

template <typename T>
T Stack<T>::show() {
	if (size == 0) {
		throw;
	}
	else {
		return head->date;
	}

}

template <typename T>
Stack<T>::~Stack() {
	clear();
}


#include "Stack.h"
#include <iostream>
#include <windows.h>

struct Raccoon {
    std::string name;
    int age;
    double weight;

    Raccoon(std::string n, int a, double w) : name(n), age(a), weight(w) {}
    Raccoon(){}
};

int main() {
    SetConsoleOutputCP(1251);
    Stack<Raccoon> raccoon_stack;
    raccoon_stack.add(Raccoon("Роки", 3, 4.5));
    raccoon_stack.add(Raccoon("Глеб", 2, 3.8));
    raccoon_stack.add(Raccoon("Бандит", 4, 5.2));

    std::cout << "Енот в начале стека: " << raccoon_stack.show().name << std::endl;

    raccoon_stack.remove();
    std::cout << "Новый енот в начале: " << raccoon_stack.show().name << std::endl;

    raccoon_stack.clear();
    std::cout << "Стэк очищен" << std::endl;

    return 0;
}
