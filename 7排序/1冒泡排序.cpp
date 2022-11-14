#include <iostream>
using namespace std;
#define MAXSIZE 9

typedef struct {
    int array[MAXSIZE];
    int len;
}DataTable, *DataTablePtr;

void DataTableInit(DataTablePtr D, int (&array)[MAXSIZE]) {
    D->len = sizeof(array)/sizeof(array[0]);
    for (int i = 0; i < D->len; ++i) {
        D->array[i] = array[i];
    }
}

void DataTablePrint(DataTablePtr D) {
    for (int i = 0; i < D->len; ++i) {
        cout << D->array[i] << " ";
    }
}

void swap (int& a, int& b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// 伪冒泡排序 只是简单的数字交换 效率低下
void BubbleSort0(DataTablePtr D) {
    for (int i = D->len - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (D->array[i] < D->array[j]) {
                swap(D->array[i], D->array[j]);
            }
        }
    }
}

// 正宗冒泡排序
void BubbleSort1(DataTablePtr D ) {
    for (int i = 0; i < D->len - 1; ++i) {
        for (int j = D->len - 1; j > i; --j) {
            if (D->array[j - 1] > D->array[j]) {
                swap(D->array[j], D->array[j - 1]);
            }
        }
    }
}

// 冒泡排序算法改进，避免了在有序的情况下还进行比较
// 核心思想：外层和内层循环顺序相反，内层循环每次从最后一个数开始，两两相邻的数进行比较，小的数往前冒
// 随着外层循环越往后，冒泡区间越来越小。改进的地方主要是如果序列已经有序，通过flag变量可及时终止比较
// 空间复杂度O(1),时间复杂度O(n^2)
// 稳定，既适用于顺序表，也适用于链表
void BubbleSort2(DataTablePtr D) {
    bool flag = true;
    for (int i = 0; i < D->len - 1 && flag; ++i) {
        flag = false; //说明序列已经有序，不需要再遍历
        for (int j = D->len - 1; j > i; --j) {
            if (D->array[j] < D->array[j - 1]) {
                swap(D->array[j], D->array[j - 1]);
                flag = true;
            }
        }
    }
}

int main() {
    int array[MAXSIZE] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    DataTable dataTable;
    DataTableInit(&dataTable, array);
    BubbleSort1(&dataTable);
    DataTablePrint(&dataTable);
    return 0;
}