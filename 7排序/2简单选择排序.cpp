#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// 核心思想：每次选择出下标以后区间内的最小值，置于下标位置，最后一个数不需要排序
// 适用于顺序表的同时也适用于链表
// 空间复杂度O(1),时间复杂度O(n^2)，不管怎样都要进行n-1趟排序，但总体性能还是略优于冒泡
// 不稳定
void SelectSort(int array[], int len) {
    int min;
    for (int i = 0; i < len - 1; ++i) {
        min = i;
        for (int j = i + 1; j < len; ++j) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(array[min], array[i]);
        }
    }
}

void print(int array[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << " ";
    }
}

int main() {
    int array[] = {3, 4, 0, 9, 1, 8, 7, 6, 2, 5};
    int len = sizeof(array)/sizeof(array[0]);
    SelectSort(array, len);
    print(array, len);
}