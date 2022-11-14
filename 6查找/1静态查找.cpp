#include <iostream>
using namespace std;
#define MAXSIZE 10

// 普通顺序查找
int Sequential_Search1(int arr[], int key) {
    for (int i = 0; i < MAXSIZE; ++i) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1; //返回-1则为查找失败
}

// 顺序查找优化 哨兵查找 
int Sequential_Search2(int arr[], int key) {
    int i = MAXSIZE - 1;
    arr[0] = key; //设置0为关键字值 称为哨兵
    while (arr[i] != key) {
        --i;
    }
    arr[0] = 0;
    return i; //返回0则为查找失败
}

// 折半查找 时间复杂度为O(logn) 要求序列有序
int Binary_Search(int arr[], int key) {
    int low = 0, high = MAXSIZE - 1;
    int mid;
    while (low <= high) {
        mid = (low + high)/2;
        if (arr[mid] < key) {
            low = mid + 1;
        } else if (arr[mid] > key) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

// 插值查找 对mid的值做出修改
int Interpolation_Search(int arr[], int key) {
    int low = 0, high = MAXSIZE - 1;
    int mid;
    while (low <= high) {
        mid = low + ((key - arr[low])*(high - low))/(arr[high] - arr[low]);
        if (arr[mid] < key) {
            low = mid + 1;
        } else if (arr[mid] > key) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int main() {
    int array[MAXSIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "Sequential_Search1: " << Sequential_Search1(array, 12) << endl;
    cout << "Sequential_Search2: " << Sequential_Search2(array, 6) << endl;
    cout << "Binary_Search: " << Binary_Search(array, 3) << endl;
    cout << "Interpolation_Search: " << Interpolation_Search(array, 4) << endl;
    return 0;
}