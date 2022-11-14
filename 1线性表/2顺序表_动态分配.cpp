#include<iostream>
using namespace std;

typedef struct{
    int* data;
    int MaxSize;
    int length;
}SqList;

// size为想创建的数据空间大小
// len为想使用的空间大小
void initList(SqList& list, int size, int len)
{
    if (len > size) {
        cout << "Error! len > size!" << endl;
        return;
    }
    list.data = (int*) malloc(size*sizeof(int));
    list.MaxSize = size;
    list.length = len;

    int* p = list.data;
    for (int i = 0; i < list.length; ++i) {
        *p = i;
        ++p;
    }
}

void listPrint(SqList& list)
{
    int* p = list.data;
    for (int i = 0; i < list.length; ++i) {
        cout << *p << " ";
        ++p;
    }
    cout << endl;
}

bool listInsert(SqList& list, int position, int data)
{
    if (position < 1 || position > list.length + 1) {
        cout << "Error! Position out of range!" << endl;
        return false;
    }
    for (int i = list.length - 1; i >= position - 1; --i){
        list.data[i + 1] = list.data[i];
    }
    list.data[position - 1] = data;
    list.length++;
    return true;
}

bool listDelete(SqList& list, int position, int& value)
{
    if (position < 1 || position > list.length) {
        cout << "Error! Position out of range!" << endl;
        return false;
    }
    value = list.data[position - 1];
    for (int i = position - 1; i < list.length - 1; ++i) {
        list.data[i] = list.data[i + 1]; 
    }
    list.length--;
    return true;
}

int main()
{
    SqList l1;
    initList(l1, 10, 5);
    listPrint(l1);

    listInsert(l1, 2, 100);
    listPrint(l1);

    int value;
    listDelete(l1, 2, value);
    listPrint(l1);
    cout << value << endl;
}