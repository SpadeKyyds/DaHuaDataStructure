#include <iostream>
using namespace std;

void print(int array[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << " ";
    }
}

// 自己写的,并非真正的直接插入算法,效率较低
void SimpleInsertSort(int array[], int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j > 0; --j) {
            int temp = array[j];
            if (array[j - 1] > temp) {
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
    }
}

// 核心思想：默认第一个元素即为一个有序的序列，从第二个数开始，比较和相邻前一个数的大小关系，若比前一个数大则不做改变
// 有序序列长度加一,若比前一个数小,则将其存于临时变量中,将前面有序序列的所有比之大的元素往后移一个长度,最后插入
// 空间复杂度O(1)，时间复杂度O(n^2)，算法稳定，不适用于链表，总体优于简单选择排序
void InsertSort(int array[], int len) {
    int i, j, temp;
    for (i = 1; i < len; ++i) {
        if (array[i] < array[i - 1]) {
            temp = array[i];
            for (j = i - 1; j >= 0 && array[j] > temp; --j) {
                array[j + 1] = array[j];
            }
            array[j + 1] = temp;
        }
    }
}

// 直接插入带哨兵
void InsertSort1(int array[], int len) {
    int i, j;
    for (i = 2; i < len; ++i) {
        if (array[i] < array[i - 1]) {
            array[0] = array[i];
            for (j = i - 1; array[j] > array[0]; --j) {
                array[j + 1] = array[j];
            }
            array[j + 1] = array[0];
        }
    }
}

// 折半插入带哨兵
void InsertSort2(int array[], int len) {
    int i, j, mid, low, high;
    for (i = 2; i < len; ++i) {
        if (array[i] < array[i - 1]) {
            array[0] = array[i];
            // 查找开始移动位置
            low = 1;
            high = i - 1;
            while (low <= high) {
                mid = (low + high) / 2;
                if (array[0] < array[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } //出循环时，mid指向的数据位置即需要右移数据开始位置，移动区间[low, i - 1]或[high + 1, i - 1]
            // 进行元素移动与插入
            for (j = i; j > low; --j) {
                array[j] = array[j - 1];
            }
            array[low] = array[0]; //这里也是low或者high+1 不要搞错成mid
        }
    }
}

int main() {
    int array[] = {3, 4, 0, 9, 1, 8, 7, 6, 2, 5};
    int array1[] = {-1, 3, 4, 0, 9, 1, 8, 7, 6, 2, 5};
    int len = sizeof(array)/sizeof(array[0]);
    int len1 = sizeof(array1)/sizeof(array1[0]);
    InsertSort(array, len);
    print(array, len);
    cout << endl;

    InsertSort2(array1, len1);
    print(array1, len1);
}