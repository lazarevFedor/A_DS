#include "station.h"
using namespace std;


std::string SortStation::getStr() {
    string input;
    getline(cin, input);
    return input;
}


int SortStation::priority(char c) {
    switch (c){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case '(':
        case ')':
            return 0;
        case ' ':
            return 10;
        default:
            if (isdigit(c)) return -1;
            else if (c >= 'a' && c < 'z' || c >= 'A' && c <= 'Z') return -1;
            else return -2;
    }
}


std::string SortStation::toRPN(std::string &inputStr, bool &errorFlag) {
    auto* pStack = new Stack<string>();
    string output;
    string  current;
    int strlen = inputStr.length();
    for(int i = 0; i < strlen; i++){
        if(current == "sin" || current == "cos"){
            pStack->pushFront(current, 2);
            current.clear();
        }
        switch (priority(inputStr[i])) {
            case -1:
                current.push_back(inputStr[i]);
                break;
            case 0:
                if(!current.empty()) {
                    output += current + " ";
                    current.clear();
                }
                if(inputStr[i] == '('){
                    pStack->pushFront("(", 0);
                }
                else{
                    while(true){
                        if(pStack->head == nullptr){
                            errorFlag = true;
                            return " ";
                        }
                        if (pStack->head->data == "(") break;
                        output += pStack->head->data;
                        output.push_back(' ');
                        pStack->popFront();
                    }
                    pStack->popFront();
                }
                break;
            case 1:
            case 2:
            case 3:
                if(!current.empty()) {
                    output += current + " ";
                    current.clear();
                }
                if (pStack->head == nullptr || pStack->head->priority < priority(inputStr[i])){
                    pStack->pushFront(inputStr.substr(i,1), priority(inputStr[i]));
                }
                else{
                    while(pStack->head != nullptr && pStack->head->priority >= priority(inputStr[i])){
                        output += pStack->head->data;
                        output.push_back(' ');
                        pStack->popFront();
                    }
                    pStack->pushFront(inputStr.substr(i,1), priority(inputStr[i]));
                }
                break;
            case 10:
                if(!current.empty()) {
                    output += current + " ";
                    current.clear();
                }
                break;
        }
    }
    if(!current.empty()) {
        output += current + " ";
        current.clear();
    }
    while(pStack->head != nullptr){
        output += pStack->head->data;
        output.push_back(' ');
        pStack->popFront();
    }
    delete pStack;
    return output;
}


bool SortStation::calculate(string &output) {
    auto* pStack = new Stack<string>();
    string curr;
    double result = 0;
    double variable = 0;
    int strLen = output.length();

    for(int i = 0; i < strLen; i++){
        if(output[i] != ' '){
            switch(priority(output[i])){
                case -1:
                    curr.push_back(output[i]);
                    break;
                case 0:
                    return false;
                case 1:
                    case 2:
                    case 3:
                        if (pStack->head == pStack->tail){
                            cout << "\nОшибка ввода строки! Недостаточно операндов.\n";
                            return false;
                        }
                    if(!isdigit(pStack->head->data[0])){
                        variable = 1;
                    }
                    else variable = stod(pStack->head->data);
                    result = variable;
                    pStack->popFront();
                    if (output[i] == '/' && result == 0){
                        cout << "\nДеление на ноль невозможно!\n";
                        return false;
                    }
                    if(!isdigit(pStack->head->data[0])){
                        variable = 1;
                    }
                    else variable = stod(pStack->head->data);
                    result = operation(variable, result, output[i]);
                    pStack->popFront();
                    curr = to_string(result);
                    pStack->pushFront(curr, -1);
                    curr = "";
                    break;
                default:
                    cout << "\nОшибка ввода строки.";
                    return false;
            }
        }else{
            if (!curr.empty()) {
                if(curr == "sin"){
                    if (pStack->head == nullptr){
                        cout << "\nОшибка ввода строки! Недостаточно операндов.\n";
                        return false;
                    }
                    if(!isdigit(pStack->head->data[0])){
                        variable = 1;
                    } else variable = stod(pStack->head->data);
                    result = sin(variable);
                    pStack->popFront();
                    curr = to_string(result);
                    pStack->pushFront(curr, -1);
                }else if(curr == "cos"){
                    if (pStack->head == nullptr){
                        cout << "\nОшибка ввода строки! Недостаточно операндов.\n";
                        return false;
                    }
                    if(!isdigit(pStack->head->data[0])){
                        variable = 0;
                    }else variable = stod(pStack->head->data);
                    result = cos(variable);
                    pStack->popFront();
                    curr = to_string(result);
                    pStack->pushFront(curr, -1);
                }else{
                    pStack->pushFront(curr, -1);
                }
                curr = "";
            }
        }
    }
    if (pStack->head != pStack->tail){
        cout << "\nОшибка ввода! Недостаточно операций.\n";
        return false;
    }

    return true;
}


double SortStation::operation(double a, double b, char c) {
    switch (c){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            return 0;
    }
}