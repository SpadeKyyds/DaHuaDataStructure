/**
 * 归并排序的空间复杂度O(n)，时间复杂度O(nlogn)
 * 稳定的排序
*/
#include <iostream>
using namespace std;
int array2[7]; //辅助数组

void Print(int array[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << " ";
    }
}

// 将[low, mid]和[mid+1, high]的两个有序序列归并在一起
void Merge(int array[], int low, int mid, int high) {
    int i, j, k;
    for (k = low; k <= high; ++k) {
        array2[k] = array[k];
    }
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; ++k) {
        if (array2[i] <= array2[j]) { //这里这个=保证了排序的稳定性
            array[k] = array2[i++];
        } else {
            array[k] = array2[j++];
        }
    }
    while (i <= mid) {
        array[k++] = array2[i++];
    }
    while (j <= high) {
        array[k++] = array2[j++];
    }
}

void MergeSort(int array[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(array, low, mid);
        MergeSort(array, mid + 1, high);
        Merge(array, low, mid, high);
    }
}

int main() {
    int array1[] = {9, 5, 8, 1, 4, 5, 2};
    int len = sizeof(array1)/sizeof(array1[0]);
    MergeSort(array1, 0, 6);
    Print(array1, len);
    return 0;
}