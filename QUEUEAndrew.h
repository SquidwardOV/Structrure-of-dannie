queue.h 

	
struct Node
{
	int data;
	Node* next;
	Node(int dat) {
		this->data = dat;
		this->next = nullptr;
	}
	Node() {
		this->data = 0;
		this->next = nullptr;
	}
};

struct Queue {


	int size;
	Node* head = new Node;
	Node* tail = new Node;



	Queue();
	Queue(int* arr, size_t size);

	int remove();
	void add(int a);
	int show();
	void clear();

	~Queue();

};


queue.cpp

#include "Header.h"


Queue::Queue() {
	head->data = 0;
	tail = head;
	tail->data = 0;
	size = 0;

}
Queue::Queue(int* arr, size_t size) {
	tail = head;
	tail->data = 0;
	for (size_t i = 0; i < size; i++) {
		add(arr[i]);
	}
}


int Queue::remove() {
	int temp = head->data;

	if (head->next != nullptr) {
		Node* NewNode = head->next;
		if (NewNode->next != nullptr) {
			head->next = NewNode->next;
			head->data = NewNode->next->data;
		}
		else {
			head->next = nullptr;
			head->data = 0;
			tail = head;
		}

		delete NewNode;
		size--;
	}
	return temp;
}

void Queue::add(int a) {
	Node* newData = new Node(a);

	if (size == 0) {
		head->data = newData->data;
		head->next = newData;

	}
	tail->next = newData;
	tail = newData;
	tail->data = newData->data;
	size++;
}

int Queue::show() {
	int res = -100000;
	if (size != 0) res = head->data;
	return res;
}

void Queue::clear() {
	while (head->next != nullptr) {
		remove();
	}
}

Queue::~Queue() {
	clear();
	tail = nullptr;
	delete tail;
	delete head;

}


main.cpp

#include "Header.h"
#include <iostream>

int main()
{
    Queue queue;
    queue.add(3);
    queue.add(4);
    queue.add(5);
    std::cout << queue.show() << std::endl;
    std::cout << queue.remove() << std::endl;
    std::cout << queue.show() << std::endl;
    std::cout << queue.remove() << std::endl;
    std::cout << queue.remove() << std::endl;
    std::cout << queue.remove() << std::endl << std::endl;
    size_t  size = 5;
    int* arr = new int[size];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = i;
    }
  
    Queue q2(arr, size);
    std::cout << q2.remove() << std::endl;
    std::cout << q2.remove() << std::endl;
    std::cout << q2.remove() << std::endl;
    std::cout << q2.remove() << std::endl;
    std::cout << q2.remove() << std::endl;
}
