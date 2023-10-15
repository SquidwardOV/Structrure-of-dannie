stack.h
#include <string> 

bool isOperator(char c);
bool isOperand(char c);
bool isLeftParenthesis(char c);
bool isRightParenthesis(char c);
int getPrecedence(char c);
std::string infixToPostfix(std::string infixExpr);
bool checkInfixToPostfix(std::string infixExpr);
bool hasConsecutiveOperands(std::string infixExpr);
bool hasUnconnectedLetters(std::string infixExpr);
bool hasConsecutiveOperators(std::string infixExpr);

stack.cpp

#include "stack.h" 
#include <stack> 
#include <unordered_map> 

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isOperand(char c) {
    return (isalnum(c) && !isdigit(c));
}

bool isLeftParenthesis(char c) {
    return (c == '(');
}

bool isRightParenthesis(char c) {
    return (c == ')');
}

int getPrecedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    return 0;
}

std::string infixToPostfix(std::string infixExpr) {
    std::stack<char> operators;
    std::string postfixExpr = "";

    for (char c : infixExpr) {
        if (isOperand(c)) {
            postfixExpr += c;
        }
        else if (isOperator(c)) {
            while (!operators.empty() && !isLeftParenthesis(operators.top()) && getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfixExpr += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
        else if (isLeftParenthesis(c)) {
            operators.push(c);
        }
        else if (isRightParenthesis(c)) {
            while (!operators.empty() && !isLeftParenthesis(operators.top())) {
                postfixExpr += operators.top();
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        if (isOperator(operators.top())) {
            postfixExpr += operators.top();
        }
        operators.pop();
    }

    return postfixExpr;
}

bool checkInfixToPostfix(std::string infixExpr) {
    std::stack<char> brackets;
    for (char c : infixExpr) {
        if (isLeftParenthesis(c)) {
            brackets.push(c);
        }
        else if (isRightParenthesis(c)) {
            if (brackets.empty() || !isLeftParenthesis(brackets.top())) {
                return false;
            }
            brackets.pop();
        }
    }
    if (!brackets.empty()) {
        return false;
    }

    std::string postfixExpr = infixToPostfix(infixExpr);
    return !postfixExpr.empty();
}

bool hasConsecutiveOperands(std::string infixExpr) {
    for (size_t i = 0; i < infixExpr.size() - 1; i++) {
        if (isOperand(infixExpr[i]) && isOperand(infixExpr[i + 1])) {
            return true;
        }
    }
    return false;
}

bool hasUnconnectedLetters(std::string infixExpr) {
    for (size_t i = 0; i < infixExpr.size() - 1; i++) {
        if (isalpha(infixExpr[i]) && isalpha(infixExpr[i + 1])) {
            return true;
        }
    }
    return false;
}

bool hasConsecutiveOperators(std::string infixExpr) {
    for (size_t i = 0; i < infixExpr.size() - 1; i++) {
        if (isOperator(infixExpr[i]) && isOperator(infixExpr[i + 1])) {
            return true;
        }
    }
    return false;
}


/*Функция `checkInfixToPostfix` проверяет, может ли данное инфиксное выражение быть преобразовано в постфиксное выражение.Она принимает строку `infixExpr`, представляющую инфиксное выражение, и возвращает булевое значение `true`, если инфиксное выражение может быть преобразовано в постфиксное, и `false` в противном случае.

Алгоритм работы функции следующий :

1. Создается пустой стек `brackets` для проверки скобок в инфиксном выражении.

2. Происходит итерация по каждому символу `c` из инфиксного выражения `infixExpr`.

3. Если символ `c` является левой скобкой `(`, он помещается в стек `brackets`.

4. Если символ `c` является правой скобкой `)`, происходит следующее :
-Если стек `brackets` пустой или верхний элемент стека не является левой скобкой `(`, возвращается `false`, так как скобки не согласованы.
- Иначе, удаляется левая скобка из стека `brackets`.

5. После прохождения всех символов инфиксного выражения, проверяется, остались ли незакрытые левые скобки в стеке `brackets`. Если они остались, возвращается `false`.

6. Происходит преобразование инфиксного выражения в постфиксное выражение с помощью функции `infixToPostfix` и сохраняется в строку `postfixExpr`.

7. Если полученное постфиксное выражение `postfixExpr` пустое, возвращается `false`, так как не удалось преобразовать инфиксное выражение в постфиксное.

8. Возвращается `true`, если не было обнаружено несогласованных скобок и инфиксное выражение было успешно преобразовано в постфиксное выражение.

Функция `checkInfixToPostfix` используется для проверки, может ли данное инфиксное выражение быть преобразовано в постфиксное выражение.Она обеспечивает, что скобки в инфиксном выражении согласованы, и вызывает функцию `infixToPostfix` для фактического преобразования инфиксного выражения в постфиксное.







Функция `infixToPostfix` преобразует инфиксное выражение в постфиксное выражение.Она принимает строку `infixExpr`, представляющую инфиксное выражение, и возвращает строку `postfixExpr`, содержащую постфиксное выражение.

Алгоритм работы функции следующий :

1. Создается пустой стек операторов `operators` и пустая строка `postfixExpr` для хранения постфиксного выражения.

2. Происходит итерация по каждому символу `c` из инфиксного выражения `infixExpr`.

3. Если символ `c` является операндом(буквой или цифрой), он добавляется в `postfixExpr`.

4. Если символ `c` является оператором, происходит следующее :
-Пока стек операторов не пустой и верхний элемент стека не является левой скобкой `(` и приоритет оператора на вершине стека больше или равен приоритету оператора `c`, извлекаем оператор из стека и добавляем его в `postfixExpr`.
- После этого оператор `c` помещается на вершину стека `operators`.

5. Если символ `c` является левой скобкой `(`, он помещается на вершину стека `operators`.

6. Если символ `c` является правой скобкой `)`, происходит следующее :
-Пока стек операторов не пустой и верхний элемент стека не является левой скобкой `(`, извлекаем оператор из стека и добавляем его в `postfixExpr`.
- После этого удаляем левую скобку `(` из стека.

7. После прохождения всех символов инфиксного выражения, извлекаем все операторы из стека `operators` и добавляем их в `postfixExpr` (если они являются операторами).

8. Возвращаем полученное постфиксное выражение `postfixExpr`.

Эта функция используется для преобразования инфиксного выражения в постфиксное выражение, что упрощает его дальнейший анализ и вычисление.*/

main.cpp

  #include "stack.h" 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <windows.h> 

int main() {

    SetConsoleOutputCP(1251);
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string infixExpr;
        std::getline(file, infixExpr);

        if (checkInfixToPostfix(infixExpr) && !hasConsecutiveOperands(infixExpr) && !hasUnconnectedLetters(infixExpr) && !hasConsecutiveOperators(infixExpr)) {
            std::cout << "Данная инфиксная форма может быть переведена в постфиксную" << std::endl;
        }
        else {
            std::cout << "Ошибка: данная инфиксная форма не может быть переведена в постфиксную" << std::endl;
        }
    }
    else {
        std::cout << "Ошибка открытия файла." << std::endl;
    }
    file.close();

    return 0;
}
