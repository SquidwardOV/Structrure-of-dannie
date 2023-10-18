.h

  #pragma once

template <typename T>
struct node
{
	node<T>* next;
	int value;
};

template <typename T>
struct Stack
{
	node<T>* head = new node;
	int size = 0;

	Stack(T* arr, T amount);

	Stack();

	~Stack();

	void add_node(T value);

	void delete_node();

	T print_top();

	void print_all();
};


.cpp

#include "Stack.h"
#include <iostream>

template <typename T>
Stack<T>::Stack(T* array, T amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (size == 0)
		{
			head->next = new node;
			(head->next)->value = array[i];
			(head->next)->next = nullptr;
			size++;
		}
		else
		{
			node* l = new node;
			l->next = head->next;
			l->value = head->value;
			head->next = l;
			head->value = array[i];
			size++;
		}
	}
}

template <typename T>
Stack<T>::Stack()
{
	head->next = nullptr;
}

template <typename T>
Stack<T>::~Stack()
{
	while (size != 0)
	{
		delete_node();
	}
}

template <typename T>
void Stack<T>::add_node(int value)
{
	if (head->next == nullptr && size == 0) 
	{
		head = new node;
		head->value = value;
		size++;
	}
	else 
	{
		node* l = new node;
		l->next = head->next;
		l->value = head->value;
		head->next = l;
		head->value = value;
		size++;
	}
}

template <typename T>
void Stack<T>::delete_node()
{
	if (head->next == nullptr) 
	{
		size--;
	}
	else 
	{
		node* l = new node;
		l = head;
		head = head->next;
		delete l;
		size--;
	}
}

template <typename T>
T Stack<T>::print_top()
{
	if (size == 0) 
	{
		return 0;
	}
	else 
	{
		return head->value;
	}

}

template <typename T>
void Stack<T>::print_all()
{
	node* l = head;
	while ((l->next) != nullptr)
	{
		std::cout << l->value;
		l = l->next;
	}
}


