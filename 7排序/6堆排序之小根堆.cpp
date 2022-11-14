#include <iostream>
using namespace std;

void Swap(int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// index为目标调整节点索引
void HeapAdjust(int array[], int index, int len) {
    int n = len - 1, i;
    array[0] = array[index]; //在一开始就将需要下坠的数据存入哨兵
    for (i = 2*index; i <= n; i *= 2) {
        if (i < n && array[i + 1] < array[i]) {
            ++i;
        }
        if (array[0] <= array[i]) { //这里千万注意是array[0]，而不是array[index]
            break; //因为底下节点是已经建立好的大根堆，若下坠的节点在该层不需要交换，即可跳出循环，将哨兵的值给到此位置即可
        } else {
            array[index] = array[i];
            index = i; //这里非常重要，以孩子节点为根继续往下索引
        }
    }
    array[index] = array[0]; //最后将哨兵中存留的数据给到它应该待的位置
}

void HeapSort(int array[], int len) {
    for (int i = (len - 1)/2; i > 0; --i) {
        HeapAdjust(array, i, len);
    }
    for (int j = len - 1; j > 1; --j) {
        Swap(array[1], array[j]);
        HeapAdjust(array, 1, j);
    }
}

void Print(int array[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << " ";
    }
}

int main() {
    int array[] = {-1, 50, 10, 90, 30, 70, 40, 80, 60, 20}; //这里len = 10
    int len = sizeof(array)/sizeof(array[0]);
    HeapSort(array, len);
    Print(array, len);
    return 0;
}