// 共享栈：两个栈顶指针，分别往中间移动
#include <iostream>
using namespace std;
#define MAXSIZE 10

typedef struct
{
    int data[MAXSIZE];
    int top;
    int rear;
}SqStack;

void initStack(SqStack& s)
{
    s.rear = -1;
    s.top = MAXSIZE;
}

bool fullJudge(SqStack& s)
{
    if (s.rear + 1 == s.top) {
        cout << "Share stack is full!" << endl;
        return true;
    } else {
        return false;
    }
}

bool topPushStack(SqStack&s, int value)
{
    if (s.rear + 1 == s.top) {
        cout << "Share stack is full!" << endl;
        return false;
    } else {
        s.data[--s.top] = value;
        return true;
    }
}

bool rearPushStack(SqStack&s, int value)
{
    if (s.rear + 1 == s.top) {
    cout << "Share stack is full!" << endl;
    return false;
    } else {
        s.data[++s.rear] = value;
        return true;
    }
}

// 逻辑上清空了就可以，数据存储在栈区，函数执行完毕系统自动回收
bool topPopStack(SqStack& s, int element)
{
    if (s.top  == MAXSIZE && s.rear == -1) {
        cout << "Share stack is full!" << endl;
        return false;
    } else {
        element = s.data[--s.top];
        return true;
    }
}

bool rearPopStack(SqStack& s, int& element)
{
    if (s.top  == MAXSIZE && s.rear == -1) {
        cout << "Share stack is full!" << endl;
        return false;
    } else {
        element = s.data[++s.top];
        return true;
    }
}

void testShareStack()
{
    SqStack s;
    initStack(s);
}

int main()
{
    testShareStack();
    return 0;
}