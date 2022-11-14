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
}StackNode, *StackPtr;

void initStack(StackPtr stackPtr)
{
    stackPtr->top = nullptr;
    stackPtr->count = 0;
}

void printStack(StackPtr stackPtr)
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
    // Node* p = (Node*)malloc(sizeof(LinkedStack));
    Node* p = new Node;
    p->data = value;
    p->next = stackPtr->top;
    stackPtr->top = p;
    ++stackPtr->count;
}

void popStack(StackPtr stackPtr, string& element)
{
    if (stackPtr->top == nullptr) {
        cout << "Invalid operator! Stack is empty!" << endl;
        return;
    }
    element = stackPtr->top->data;
    Node* p = stackPtr->top;
    stackPtr->top = p->next;
    --stackPtr->count;
    // free(p);
    delete p;
}

void testAll()
{
    StackNode s;
    string element;
    initStack(&s);

    pushStack(&s, "12");
    pushStack(&s, "34");
    printStack(&s);

    popStack(&s, element);
    cout << "Stack pop element is: " << element << endl;

    pushStack(&s, "56");

    printStack(&s);
}

int main()
{
    testAll();
    return 0;
}