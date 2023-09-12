#include "Header.h"
#include <iostream>

int main() {
	Stack stk;
	stk.add(5);
	stk.add(6);
	stk.add(7);
	stk.add(4);

	std::cout << stk.show() << std::endl;
	stk.remove();
	std::cout << stk.show() << std::endl;
	stk.remove();
	std::cout << stk.show() << std::endl;
	stk.remove();
	std::cout << stk.show() << std::endl;
	stk.remove();
}
