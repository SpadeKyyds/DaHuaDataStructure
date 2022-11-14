#include <iostream>
using namespace std;

typedef struct LinkStack
{
    int data;
    struct LinkStack* next;
}Node, *Stack;

void initStack(Stack& firstNodePtr)
{
    firstNodePtr = nullptr;
}

bool emptyJudge(Stack& firstNodePtr)
{
    return firstNodePtr;
}

void stackPrint(Stack& firstNodePtr)
{
    Node* p = firstNodePtr;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void stackPush(Stack& firstNodePtr, int element)
{
    if (firstNodePtr == nullptr) {
        firstNodePtr = (Node*) malloc(sizeof(struct LinkStack));
        firstNodePtr->data = element;
        // 这里这个nullptr很重要，对于栈来说就相当于尾节点的下一指针
        firstNodePtr->next = nullptr;
    } else {
        Node* p = (Node*) malloc(sizeof(struct LinkStack));
        p->data = element;
        p->next = firstNodePtr;
        // 这一句非常重要 以引用方式返回头结点指针
        firstNodePtr = p;
    }
}

void stackPop(Stack& firstNodePtr)
{
    if (firstNodePtr == nullptr) {
        cout << "The stack is empty!" << endl;
    } else {
        Node* p = firstNodePtr;
        firstNodePtr = firstNodePtr->next;
        free(p);
    }
}

void testAll()
{
    Stack s;
    initStack(s);

    stackPush(s, 1);
    stackPush(s, 2);
    stackPush(s, 3);
    stackPrint(s);

    stackPop(s);
    stackPop(s);
    stackPop(s);
    stackPrint(s);
}

int main()
{
    testAll();
    return 0;
}