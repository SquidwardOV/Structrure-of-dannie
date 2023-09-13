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
