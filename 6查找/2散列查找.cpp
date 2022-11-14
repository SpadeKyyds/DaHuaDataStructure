#include <iostream>
using namespace std;
#define MAXSIZE 12
#define M 11
#define NULLKEY -32768

typedef struct {
    int* array;
    int len;
}HashTableNode,*HashTable;

void HashTableInit(HashTable H) {
    H->len = MAXSIZE;
    H->array = new int[MAXSIZE];
    // H->array = (int*)malloc(MAXSIZE*sizeof(int));
    for (int i = 0; i < H->len; ++i) {
        H->array[i] = NULLKEY;
    }
}

int HashFunc(int key) {
    return key % M; //这里被除数取11 取不大于哈希表表长的最大质数
}

void HashTableInsert(HashTable H, int key) {
    int address = HashFunc(key);
    while (H->array[address] != NULLKEY) {
        address = (address + 1) % M; //这里采用的是开放定址法线性探测
    }
    H->array[address] = key;
}

int KeySearch(HashTable H, int key) {
    int address = HashFunc(key);
    do {
        if (H->array[address] == key) {
            return address;
        }
        address = (address + 1) % M;
    } while (H->array[address] != NULLKEY && H->array[address] != key);
    return -1;
}

int main() {
    int array[] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    HashTableNode H;
    HashTableInit(&H);
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); ++i) {
        HashTableInsert(&H, array[i]);
    }

    int searchKey = 56;
    int searchAddress = KeySearch(&H, searchKey);
    cout << "Hello" << endl;
    cout << searchKey << "'s address in hash table is: " << searchAddress << endl;
    return 0;
}