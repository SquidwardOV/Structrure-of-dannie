stack.h
  
#include <iostream>
#include <stack>
#include <string>

bool checkFormula(const std::string& formula);


stack.cpp

#include "stack.h"

bool isOpeningBracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool isClosingBracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

bool isMatchingBracket(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
        (opening == '[' && closing == ']') ||
        (opening == '{' && closing == '}');
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperand(char c) {
    return isalpha(c);
}

bool isSpace(char c) {
    return c == ' ';
}

bool checkFormula(const std::string& formula) {
    std::stack<char> bracketsStack;

    for (size_t i = 0; i < formula.length(); i++) {
        char c = formula[i];

        if (isOpeningBracket(c)) {
            bracketsStack.push(c);
        }
        else if (isClosingBracket(c)) {
            if (bracketsStack.empty() || !isMatchingBracket(bracketsStack.top(), c)) {
                return false;
            }
            bracketsStack.pop();
        }
        else if (isOperator(c)) {
            if (i == 0 || i == formula.length() - 1 || isOperator(formula[i - 1]) ||
                isOperator(formula[i + 1]) || isSpace(formula[i - 1]) || isSpace(formula[i + 1])) {
                return false;
            }
        }
        else if (isOperand(c)) {
            if ((i > 0 && isOperand(formula[i - 1])) || (i < formula.length() - 1 && isOperand(formula[i + 1]))) {
                return false;
            }
        }
        else if (!isSpace(c)) {  // Проверка на неправильные символы
            return false;
        }
    }

    return bracketsStack.empty();
}

main.cpp

#include <iostream>
#include <fstream>
#include "stack.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(1251);
    std::ifstream inputFile("input.txt");
    std::string formula;

    if (inputFile.is_open()) {
        std::getline(inputFile, formula);
        inputFile.close();

        if (checkFormula(formula)) {
            std::cout << "Формула записана верно!" << std::endl;
        }
        else {
            std::cout << "Формула записана неверно!" << std::endl;
        }
    }
    else {
        std::cout << "Ошибка открытия файла." << std::endl;
    }

    return 0;
}
