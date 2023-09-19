Header.h

  
struct Node {
	int data;
	Node* next;
	Node* prev;
};

class LinkedList {
public:
	LinkedList();
	~LinkedList();
	void addFirst(int data);
	void Pushback(int data);
	void addAfter(int searchData, int data);
	void printList();
	void deleteHead();
	void deleteSearch(int data);
	void deleteAfter(int data);
	void clear();
	void search(int value);
	


private:
	Node* head;
};


function.cpp

  #include "header.h"

#include <iostream>

LinkedList::LinkedList()
{
    head = nullptr;
}

LinkedList::~LinkedList()
{
    clear();
}


void LinkedList::addFirst(int data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = head;
    newNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}

void LinkedList::addAfter(int searchData, int data)
{
    Node* current = head;
    while (current != nullptr) {
        if (current->data == searchData) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next != nullptr) {
                current->next->prev = newNode;
            }
            current->next = newNode;
        }
        current = current->next;
    }
}


void LinkedList::printList()
{
    Node* currentNode = head;
    while (currentNode != nullptr) {
        std::cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    std::cout << std::endl;
}

void LinkedList::Pushback(int data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (head == nullptr) {
        newNode->prev = nullptr;
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

void LinkedList::deleteHead()
{
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
    }
    else {
        std::cout << "List is empty!" << std::endl;
    }
}

void LinkedList::deleteSearch(int data)
{
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        else {
            current = current->next;
        }
    }
}

void LinkedList::deleteAfter(int data)
{
    Node* current = head;
    while (current != nullptr) {
        if (current->data == data && current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            delete temp;
        }
        current = current->next;
    }
}

void LinkedList::clear()
{
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}
void LinkedList::search(int value)
{
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            std::cout << "Element " << value << " found!" << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Element not found!" << std::endl;
}


main.cpp

  #include <iostream>
#include "Header.h"
#include <windows.h>

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    LinkedList list;
    int choice;

    do {

        std::cout << "Выберите задачу:" << std::endl;
        std::cout << "1. Добавить в начало" << std::endl;
        std::cout << "2. Добавить после заданного" << std::endl;
        std::cout << "3. Вывести лист на экран" << std::endl;
        std::cout << "4. Добавить в конец" << std::endl;
        std::cout << "5. Удалить голову" << std::endl;
        std::cout << "6. Удалить заданный элемент" << std::endl;
        std::cout << "7. Удалить после заданного" << std::endl;
        std::cout << "8. Найти элемент" << std::endl;
        std::cout << "9. Очистить" << std::endl;
        std::cout << "0. Завершить" << std::endl;
        std::cout << "Введите цифру: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int data;
            std::cout << "Введите элемент: ";
            std::cin >> data;
            list.addFirst(data);
            break;
        }
        case 2: {
            int searchData, data;
            std::cout << "Введите элемент, после которого будет осуществлено добавление: ";
            std::cin >> searchData;
            std::cout << "Введите элемент, который необходимо добавить: ";
            std::cin >> data;
            list.addAfter(searchData, data);
            break;
        }
        case 3: {
            list.printList();
            break;
        }
        case 4: {
            int data;
            std::cout << "Введите элемент: ";
            std::cin >> data;
            list.Pushback(data);
            break;
        }
        case 5: {
            list.deleteHead();
            break;
        }
        case 6: {
            int data;
            std::cout << "Введите элемент для удаления: ";
            std::cin >> data;
            list.deleteSearch(data);
            break;
        }
        case 7: {
            int data;
            std::cout << "Введите элемент, после которого будет удаляться следом идущий элемент: ";
            std::cin >> data;
            list.deleteAfter(data);
            break;
        }
        case 8: {
            int value;
            std::cout << "Введите элемент для поиска: ";
            std::cin >> value;
            list.search(value);
            break;
        }
        case 9: {
            list.clear();
            break;
        }
        case 0: {
            std::cout << "Завершение..." << std::endl;
            break;
        }
        default: {
            std::cout << "Некорректный выбор! Попробуйте ещё." << std::endl;
            break;
        }
        }

        std::cout << std::endl;

    } while (choice != 0);

    return 0;
}
