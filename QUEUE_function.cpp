#include "Queue.h"
#include<iostream>

void Queue::push_back(int date) {
    if (size == 0) {
        head->next = end;
        end->pref = head;
        end->date = date;
        head->date = date;
        size++;
    }else if (size == 1) {
        end->date = date;
        size++;
    }else {
        Node* NewNode = new Node;
        NewNode->pref = end->pref;
        end->pref->next = NewNode;
        NewNode->next = end;
        end->pref = NewNode;
        NewNode->date = end->date;
        end->date = date;
        size++;
    }
}
void Queue::pop_front() {
    if (size > 2) {
        Node* current = new Node;
        current = head;
        head = head->next;
        delete current;
        size--;
    }
    else if(size == 2){
        size--;
        head->date = end->date;
        
    }
    else {
        head->date = end->date;
        size--;
    }
    
}

int Queue::show() {
    if(size > 0) {
        return head->date;
    }
    else {
        throw;
    }
}

void Queue::clear(){
    while (size > 2) {
        pop_front();
    }
    if (size > 0) {
        size -= 2;
    }
}

Queue::~Queue() {
    clear();
    delete head;
    delete end;
}
