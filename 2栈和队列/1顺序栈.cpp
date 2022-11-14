#include <iostream>
using namespace std;
#define MAXSIZE 10

typedef struct
{
    int data[MAXSIZE];
    int top;
}SqStack;

void initStack(SqStack& s)
{
    s.top = -1;
}

bool stackEmpty(SqStack& s)
{
    if (s.top == -1) {
        cout << "Stack is empty!" << endl;
        return true;
    } else {
        cout << "Stack is not empty!" << endl;
        return false;
    }
}

bool pushStack(SqStack& s, int value)
{
    if (s.top = MAXSIZE - 1) {
        cout << "Stack is full!" << endl;
        return false;
    } else {
        s.data[++s.top] = value;
        return true;
    }
}

bool popStack(SqStack& s, int& element)
{
    if (s.top == -1) {
        cout << "Stack is empty!" << endl;
        return false;
    } else {
        element = s.data[s.top--];
        return true;
    }
}

// 读取栈顶元素
bool getValue(const SqStack& s, int& element)
{
    if (s.top == -1) {
        cout << "Stack is empty!" << endl;
        return false;
    } else {
        element = s.data[s.top];
        return true;
    }
}

void testStack()
{
    SqStack s;
    initStack(s);
}

int main()
{
    testStack();
    return 0;
}