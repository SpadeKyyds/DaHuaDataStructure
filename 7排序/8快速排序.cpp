/**
 * 快速排序算法的表现取决于递归的深度，若每次划分越均匀，则递归深度越低，划分越不均匀，递归深度越深
 * 空间复杂度，最好O(n)，最坏O(logn) 时间复杂度，最好O(nlogn)，最坏O(n^2)，平均O(nlogn)
 * 快速排序算法是一个不稳定的算法
*/
#include <iostream>
using namespace std;

void Print(int array[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << " ";
    }
}

int Partition(int array[], int low, int high) {
    array[0] = array[low];
    while (low < high) {
        while (low < high && array[high] >= array[0]) { //注意这里一定要有low < high 不然若是个递增的序列就会出错
            --high;
        }
        array[low] = array[high];
        while (low < high && array[low] <= array[0]) {
            ++low;
        }
        array[high] = array[low];
    }
    array[low] = array[0];
    return low;
}

void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pivot_pos = Partition(array, low, high);
        QuickSort(array, low, pivot_pos - 1);
        QuickSort(array, pivot_pos + 1, high);
    }
}

int main() {
    int array[] = {-1, 9, 5, 8, 1, 4, 5, 2};
    int len = sizeof(array)/sizeof(array[0]);
    QuickSort(array, 1, 7);
    Print(array, len);
    return 0;
}