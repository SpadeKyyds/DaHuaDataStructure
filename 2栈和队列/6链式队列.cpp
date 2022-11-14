#include <iostream>
using namespace std;

typedef struct LinkQueue
{
    int data;
    struct LinkQueue* next;
}Node, *Queue;

typedef struct
{
    Queue front;
    Queue rear;
}*QueuePtr;

void initQueue(Queue& queue, QueuePtr& queuePtr)
{
    queue = Queue (malloc(sizeof(LinkQueue)));
    queue->next = nullptr;
    queuePtr->front = queue;
    queuePtr->rear = queue;
}

void queuePrint(const Queue& queue, const QueuePtr& queuePtr)
{
    Node* p = queuePtr->front;
    while (p != queuePtr->rear) {
        cout << p->next->data << " ";
        p = p->next;
    }
    cout << endl;
}

void pushQueue(Queue& queue, QueuePtr& queuePtr, const int data)
{
    Node* q = (Node*) (malloc(sizeof(LinkQueue)));
    q->data = data;
    q->next = nullptr;
    queuePtr->rear->next = q;
    queuePtr->rear = q;
}

void popQueue(Queue& queue, QueuePtr& queuePtr)
{
    if (queuePtr->front == queuePtr->rear) {
        cout << "Linked queue is empty, illegal operation!" << endl;
        return;
    } else if (queuePtr->front->next == queuePtr->rear) {
        queuePtr->rear = queue;
        free(queue->next);
    } else {
        Node* p = queuePtr->front->next;
        queuePtr->front->next = p->next;
        free(p);
    }
}

void testAll()
{
    Queue lq;
    QueuePtr ptr;
    initQueue(lq, ptr);
    
    pushQueue(lq, ptr, 12);
    pushQueue(lq, ptr, 34);
    pushQueue(lq, ptr, 56);
    queuePrint(lq, ptr);

    popQueue(lq, ptr);
    popQueue(lq, ptr);
    queuePrint(lq, ptr);
}

int main()
{
    testAll();
    return 0;
}