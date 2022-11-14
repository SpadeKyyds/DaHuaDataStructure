// 主要为一个增删 改查比较简单
#include <iostream>
using namespace std;

typedef struct LinkStack
{
    int data;
    struct LinkStack* next;
}Node, *Stack;

bool initLinkStack(Stack& head)
{
    head = Stack (malloc(sizeof(struct LinkStack)));
    if (head == nullptr) {
        cout << "malloc defeat!" << endl;
        return false;
    } else {
        head->next = nullptr;
        return true;
    }
}

int stackLength(const Stack& head)
{
    int len = 0;
    Node* p = head->next;
    while (p != nullptr) {
        ++len;
        p = p->next;
    }
    // 传值没事，不同于传变量
    return len;
}

void stackPrint(const Stack& head)
{
    Node* p = head->next;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void pushStack(Stack& head, int element)
{
    Node* p;
    initLinkStack(p);
    p->data = element;
    p->next = head->next;
    head->next = p;
}

// 删除p节点后的节点
bool deleteNextNode(Stack& p)
{
    if (p->next == nullptr) {
        cout << "There is no node after this node!" << endl;
        return false;
    } else {
        Node* q = p->next;
        p->next = p->next->next;
        free(q);
        return true;
    }
}

// num为出栈个数
void popStack(Stack& head, int num)
{
    if (num < 0 || num > stackLength(head)) {
        cout << "Num is out of max range!" << endl;
        return;
    }
    while (num > 0) {
        deleteNextNode(head);
        --num;
    }
}

void testLinkStack()
{
    // 声明一个指向Stack类型的指针
    Stack headNodePtr;
    // 空表初始化
    initLinkStack(headNodePtr);

    pushStack(headNodePtr, 5);
    pushStack(headNodePtr, 4);
    pushStack(headNodePtr, 3);
    stackPrint(headNodePtr);
    cout << "Stack length is: " << stackLength(headNodePtr) << endl;

    popStack(headNodePtr, 1);
    stackPrint(headNodePtr);
}

int main()
{
    testLinkStack();
    return 0;
}