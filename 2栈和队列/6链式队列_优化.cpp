#include <iostream>
using namespace std;

typedef struct LinkedQueue
{
    string data;
    struct LinkedQueue* next;
}QueueNode, *QueuePtr;

typedef struct AssistantQueuePointer
{
    QueuePtr front;
    QueuePtr rear;
}AssPtr;

void queueInit(AssPtr& ptr, QueuePtr head)
{
    ptr.front = head;
    ptr.rear = head;
}

void queuePrint(AssPtr& ptr)
{
    QueuePtr p = ptr.front;
    while (p != ptr.rear) {
        cout << p->next->data << " ";
        p = p->next;
    }
    cout << endl;
}

void pushQueue(AssPtr& ptr, const string data)
{
    QueuePtr p = new QueueNode;
    p->data = data;
    p->next = nullptr;
    ptr.rear->next = p;
    ptr.rear = p;
}

void popQueue(AssPtr& ptr)
{
    if (ptr.front == ptr.rear) {
        cout << "Error! Queue is empty!" << endl;
    } else if (ptr.front->next == ptr.rear) {
        QueueNode* p = ptr.rear;
        ptr.front->next = nullptr;
        ptr.rear = ptr.front;
        delete p;
    } else {
        QueueNode* p = ptr.front->next;
        ptr.front->next = p->next;
        delete p;
    }
}

int main()
{
    QueueNode head;
    AssPtr ptr;
    queueInit(ptr, &head);

    pushQueue(ptr, "1");
    pushQueue(ptr, "2");
    pushQueue(ptr, "3");

    popQueue(ptr);
    popQueue(ptr);

    queuePrint(ptr);
}