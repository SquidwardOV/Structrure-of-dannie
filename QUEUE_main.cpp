#include"Queue.h"
#include <iostream>
#include <string>

int main(){
    Queue qe;
    qe.push_back(12);
    qe.push_back(13);
    qe.push_back(14);
    qe.push_back(15);
    qe.push_back(16);
    std::cout << qe.show() << std::endl;
    qe.pop_front();
    std::cout << qe.show() << std::endl;
    qe.pop_front();
    std::cout << qe.show() << std::endl;
    qe.pop_front();
    std::cout << qe.show() << std::endl;
    qe.pop_front();
    std::cout << qe.show() << std::endl;
    qe.pop_front();
}
