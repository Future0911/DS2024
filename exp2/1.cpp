#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cctype>

using namespace std;

// 栈数据结构
template<typename T>
class Stack {
private:
    vector<T> elements;

public:
    void push(const T& element) {
        elements.push_back(element);
    }

    void pop() {
        if (elements.empty()) {
            throw out_of_range("Stack<>::pop(): empty stack");
        }
        elements.pop_back();
    }

    T top() const {
        if (elements.empty()) {
            throw out_of_range("Stack<>::top(): empty stack");
        }
        return elements.back();
    }

    bool empty() const {
        return elements.empty();
    }
};

// 计算器类
class Calculator {
public:
    double evaluate(const string& expression) {
        Stack<double> values;
        Stack<char> ops;
        istringstream iss(expression);
        char token;

        while (iss >> token) {
            if (isdigit(token) || token == '.') {
                iss.putback(token);
                double value;
                iss >> value;
                values.push(value);
            }
            else if (token == '(') {
                ops.push(token);
            }
            else if (token == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    applyOperation(values, ops);
                }
                if (!ops.empty()) ops.pop(); // Pop the '('
            }
            else if (isOperator(token)) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                    applyOperation(values, ops);
                }
                ops.push(token);
            }
            else if (isFunction(token)) {
                string func(1, token);
                iss >> token; // Get the next character (should be '(')
                if (token != '(') {
                    throw invalid_argument("Invalid function usage: " + func);
                }
                values.push(applyFunction(func, values));
            }
            else {
                throw invalid_argument("Invalid token: " + string(1, token));
            }
        }

        while (!ops.empty()) {
            applyOperation(values, ops);
        }

        return values.top();
    }

private:
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isFunction(char c) {
        return c == 's' || c == 'c' || c == 't' || c == 'l'; // sin, cos, tan, log
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    void applyOperation(Stack<double>& values, Stack<char>& ops) {
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        char op = ops.top(); ops.pop();

        switch (op) {
        case '+': values.push(left + right); break;
        case '-': values.push(left - right); break;
        case '*': values.push(left * right); break;
        case '/':
            if (right == 0) throw runtime_error("Division by zero");
            values.push(left / right);
            break;
        default: throw invalid_argument("Invalid operator");
        }
    }

    double applyFunction(const string& func, Stack<double>& values) {
        double value = values.top(); values.pop();
        if (func == "sin") return sin(value);
        else if (func == "cos") return cos(value);
        else if (func == "tan") return tan(value);
        else if (func == "log") return log(value);
        else throw invalid_argument("Unknown function: " + func);
    }
};

int main() {
    Calculator calc;
    string expression;

    cout << "Enter an expression (e.g., 3 + 5 * ( 2 - 8 ) or sin(1) + log(10)): ";
    getline(cin, expression);

    try {
        double result = calc.evaluate(expression);
        cout << "Result: " << result << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
