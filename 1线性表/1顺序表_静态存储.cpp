#include<iostream>
using namespace std;
#define MAXSIZE 10

typedef struct{
    int data[MAXSIZE];
    int length;
}SqList;

void initList(SqList& list, int len)
{
    if (len < 0 || len > MAXSIZE) {
        cout << "Error! out of range!" << endl;
        return;
    }

    for (int i = 0; i < len; ++i) {
        list.data[i] = 0;
    }
    list.length = len;
} 

void listPrint(SqList& list)
{
    for (int i = 0; i < list.length; ++i) {
        cout << list.data[i] << " ";
    }
    cout << endl;
}

int main()
{
    SqList l1;
    initList(l1, 5);
    listPrint(l1);

    return 0;
}