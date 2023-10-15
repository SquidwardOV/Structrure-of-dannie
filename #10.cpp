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
    std::stack<char> bracketsStack; //создание стека для хранения открывающих скобок.

    for (size_t i = 0; i < formula.length(); i++) {
        char c = formula[i];

        if (isOpeningBracket(c)) { //если текущий символ является открывающей скобкой, он помещается в стек `bracketsStack
            bracketsStack.push(c);
        }
        else if (isClosingBracket(c)) { //Eсли текущий символ является закрывающей скобкой, выполняется следующая проверка:

            
            if (bracketsStack.empty() || !isMatchingBracket(bracketsStack.top(), c)) {
                return false; // Если стек пустой или верхний элемент стека не соответствует текущей закрывающей скобке, возвращается `false`, так как это неправильная формула.
            }                   //  - В противном случае, верхний элемент стека удаляется.
            bracketsStack.pop(); 
        }
        else if (isOperator(c)) { // если текущий символ является оператором, выполняется следующая проверка:
            if (i == 0 || i == formula.length() - 1 || isOperator(formula[i - 1]) ||
                isOperator(formula[i + 1]) || isSpace(formula[i - 1]) || isSpace(formula[i + 1])) {
                return false; //- Если текущий оператор находится в начале или конце формулы, или перед ним или после него находится оператор, или перед ним или после него находится пробел, возвращается `false`, так как это неправильная формула.
            }
        }
        else if (isOperand(c)) { //если текущий символ является операндом, выполняется следующая проверка:

            if ((i > 0 && isOperand(formula[i - 1])) || (i < formula.length() - 1 && isOperand(formula[i + 1]))) {
                return false; //-Если текущий операнд находится между двумя операндами, возвращается `false`, так как это неправильная формула.
            }
        }
        else if (!isSpace(c)) {  // если текущий символ не является пробелом и не попадает ни в одну из предыдущих категорий (открывающая/закрывающая скобка, оператор или операнд), возвращается `false`, так как это неправильная формула
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
