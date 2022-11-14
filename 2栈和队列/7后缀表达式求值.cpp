#include <iostream>
#include <string>
using namespace std;

typedef struct LinkedStack
{
    string data;
    struct LinkedStack* next;
}Node, *Stack;

typedef struct Ptr
{
    Stack top;
    int count;
}PtrNode, *StackPtr;

void initStack(StackPtr stackPtr)
{
    stackPtr->top = nullptr;
    stackPtr->count = 0;
}

void printStack(const StackPtr stackPtr)
{
    Node* p = stackPtr->top;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl << "Stack length is: " << stackPtr->count << endl;
}

void pushStack(StackPtr stackPtr, const string& value)
{
    Node* p = new Node;
    p->next = stackPtr->top;
    stackPtr->top = p;
    p->data = value;
    ++stackPtr->count;
}

void popStack(StackPtr stackPtr, string& element)
{
    if (stackPtr->top == nullptr) {
        cout << "Invalid operator! Stack is empty!" << endl;
        return;
    }
    Node* p = stackPtr->top;
    element = p->data;
    stackPtr->top = p->next;
    --stackPtr->count;
    delete p;
}

string valueOperation(const string x, const string y, const string opera)
{
    if (opera == "+") {
        return to_string(stof(x) + stof(y));
    } else if (opera == "-") {
        return to_string(stof(x) - stof(y));
    } else if (opera == "*") {
        return to_string(stof(x) * stof(y));
    } else if (opera == "/" && stof(y) != 0) {
        return to_string(stof(x) / stof(y));
    } else {
        cout << "Invalid input!" << endl;
        return to_string(-999);
    }
}

string getPostfixExpressionValue()
{
    PtrNode s;
    string lvalue, rvalue, result;
    initStack(&s);

    string expression[15] = {"15","7","1","1","+","-","/","3","*","2","1","1","+","+","-"};
    for (int i = 0; i < 15; ++i) {
        if (expression[i] != "+" && expression[i] != "-" && expression[i] != "*" && expression[i] != "/") {
            pushStack(&s, expression[i]);
        }
        else {
            popStack(&s, rvalue);
            popStack(&s, lvalue);
            result = valueOperation(lvalue, rvalue, expression[i]);
            pushStack(&s, result);
        }
    }
    return (s.top->data);
}

int main()
{
    cout << "PostFixExpression ((15/(7-(1+1)))*3)-(2+(1+1)) 's value is: ";
    cout << getPostfixExpressionValue() << endl;
    return 0;
}