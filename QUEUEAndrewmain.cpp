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

