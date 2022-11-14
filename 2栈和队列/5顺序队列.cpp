#include <iostream>
using namespace std;
#define MAXSIZE 4

typedef struct Queue
{
    int data[MAXSIZE];
    int front, rear;  //front指向队头元素位置 rear指向队尾元素下一位置
}SqQueue;

void initQueue(SqQueue& queue)
{
    queue.front = 0;
    queue.rear = 0;
}

int queueLength(const SqQueue& queue)
{
    return (queue.rear - queue.front + MAXSIZE) % MAXSIZE;
}

void queuePrint(const SqQueue& queue)
{
    if (queue.front <= queue.rear) {
        for (int i = queue.front; i < queue.rear; ++i) {
            cout << queue.data[i] << " ";
        }
        cout << endl;
    } else {
        for (int i = queue.front; i < MAXSIZE; ++i) {
            cout << queue.data[i] << " ";
        }
        for (int i = 0; i < queue.rear; ++i) {
            cout << queue.data[i] << " ";
        }
        cout << endl;
    }
}

bool pushQueue(SqQueue& queue, int element)
{
    if ((queue.rear + 1) % MAXSIZE == queue.front) {
        cout << "Queue is full!" << endl;
        return false;
    } else {
        queue.data[queue.rear] = element;
        // 循环队列
        queue.rear  = (queue.rear + 1) % MAXSIZE;
        return true;
    }
}

bool popQueue(SqQueue& queue, int& value)
{
    if (queue.rear == queue.front) {
        cout << "Queue is empty!" << endl;
        return false;
    } else {
        value = queue.data[queue.front];
        queue.front = (queue.front + 1) % MAXSIZE;
        return true;
    }
}


void testAll()
{
    SqQueue q;
    int value;
    initQueue(q);

    pushQueue(q, 12);
    pushQueue(q, 34);
    pushQueue(q, 56);

    queuePrint(q);
    cout << "Queue length is: " << queueLength(q) << endl;

    cout << "***************Queue pop operation****************" << endl;

    popQueue(q, value);
    cout << "Queue pop value is: " << value << endl;
    popQueue(q, value);
    cout << "Queue pop value is: " << value << endl;

    cout << "***************Queue push operation***************" << endl;
    pushQueue(q, 666);
    pushQueue(q, 777);
    
    queuePrint(q);
    cout << "Queue length is: " << queueLength(q) << endl;
}

int main()
{
    testAll();
}