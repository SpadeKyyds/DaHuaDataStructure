#include <iostream>
using namespace std;

void print(int array[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << " ";
    }
}

// 空间复杂度O(1)，时间复杂度未知，优于直接插入排序
// 希尔排序不稳定，仅适用于顺序表，不适用于链表
void ShellSort(int array[], int len) {
    int n = len - 1;
    int d, i, j;
    for (d = n/2; d >= 1; d = d/2) {
        for (i = d + 1; i <= n; ++i) { //这里i每次加1，步长为2时会造成反复横跳
            if (array[i] < array[i - d]) {
                array[0] = array[i];
                for (j = i - d; j > 0 && array[j] > array[0]; j -= d) {
                    array[j + d] = array[j];
                }
                array[j + d] = array[0];
            }
        }
    } 
}

int main() {
    int array[] = {-1, 0, 1, 2, 7, 4, 9, 8, 6, 3, 5};
    int len = sizeof(array)/sizeof(array[0]);
    ShellSort(array, len);
    print(array, len);
    return 0;
}