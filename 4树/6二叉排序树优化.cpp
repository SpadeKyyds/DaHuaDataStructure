#include <iostream>
using namespace std;
typedef int Datatype;

typedef struct BinarySortTree {
    Datatype data;
    BinarySortTree *lchild, *rchild;
}BSTNode, *BSTree;

/**T为根节点指针，对T虽有改变，但只是原T的一个复制品，key为索引值
 * prior为key值节点的父节点 初始值为nullptr
 * current为key值节点指针
*/
bool BST_Search(BSTree T, const Datatype key, BSTree prior, BSTree& current) {
    if (!T) {
        current = prior; //若查找不成功，则返回路径上最后一个访问的节点指针 
        return false;
    } else if (key < T->data) {
        return BST_Search(T->lchild, key, T, current);
    } else if (key > T->data) {
        return BST_Search(T->rchild, key, T, current);
    } else {
        current = T; //查找成功返回目标节点指针
        return true;
    }
}

// 这里对根节点以引用的方式传入 是为了防止空树情况下 根节点指针在函数执行完毕会销毁
// main函数中根节点指针与树失去联系 若树已有根节点 可不使用引用方式传入
bool BST_Insert(BSTree& T, const Datatype key) {
    BSTree current, newNode;
    if (!BST_Search(T, key, nullptr, current)) {
        newNode = new BSTNode;
        newNode->data = key;
        newNode->lchild = newNode->rchild = nullptr;
        if (!current) {
            T = newNode;
        } else if (current->data > newNode->data) {
            current->lchild = newNode;
        } else {
            current->rchild = newNode;
        }
        return true;
    } else {
        return false; //树中已有相同数据节点 不重复插入
    }
}

bool Delete_Action(BSTree* T) {
    BSTree temp, ptr;
    BSTree* p = T;

// *T = (*T)->lchild;改变的是实际的树中的指向节点的指针的值，并不是一个复制品
// T = &(*T)->lchild;此举实际改变的是T的值，*T解引用出来虽然是(*T)->lchild
// 但并不是对树中指向lchild的指针的改变，而是另一份复制品，树中的指向关系并未发生改变
    if ((*T)->rchild == nullptr) { //删除只有左孩子的节点，叶子节点也包含在内
        temp = *T;
        *T = (*T)->lchild;
        delete temp;
    } else if ((*T)->lchild == nullptr) { //删除只有右孩子的节点
        temp = *T;
        *T = (*T)->rchild;
        delete temp;
    }
    /**删除左右孩子均有的节点*/
    /**书上的可执行代码*/
    // else {
    //     ptr = *T;
    //     temp = (*T)->lchild;
    //     while (temp->rchild) {
    //         ptr = temp;
    //         temp = temp->rchild;
    //     }
    //     (*T)->data = temp->data;
    //     if (ptr != *T) {
    //         ptr->rchild = temp->lchild;
    //     } else {
    //         ptr->lchild = temp->lchild;
    //     }
    //     delete temp;
    // }
    /**自己实现的，寻找到左子树中最右下角节点，该节点一定没有右孩子，问题转化为删除只有左孩子的节点*/
    else {
        p = &(*p)->lchild; //p为左子树中最右下角节点 *p实际操作的就是树中的指针
        while ((*p)->rchild) {
            p = &(*p)->rchild;
        }
        (*T)->data = (*p)->data;
        // Delete_Action(p);
        temp = *p;
        *p = (*p)->lchild;
        delete temp;
    }
    
    return true;
}

/**这里使用BSTree* T，通过指向 指向节点的指针 的指针，即二重指针
 * 不断改变的是指向节点指针的地址，根节点指针并不会改变，遍历的时候不会出错
 * 通过对指向节点指针的指针进行解引用操作，即得到指向节点的指针
 * 由每次对形参T传入的值&(*T)->rchild可得，*T即为树中的指针，并不是复制品
*/
bool BST_Delete(BSTree* T, Datatype key) {
    if (!(*T)) {
        return false; // *T == nullptr时，即树中不存在目标值时
    } else if ((*T)->data == key) {
        return Delete_Action(T);
    } else if ((*T)->data < key) {
        return BST_Delete(&(*T)->rchild, key);
    } else {
        return BST_Delete(&(*T)->lchild, key);
    }
}

void visitNode(BSTree T) {
    cout << T->data << " ";
}

// 递归中序遍历二叉排序树
void BST_Print(BSTree T) {
    if (T) {
        BST_Print(T->lchild);
        visitNode(T);
        BST_Print(T->rchild);
    }
}

int main() {
    Datatype array[] = {2, 5, 3, 6, 0, 76, 34, 56, 9};
    // Datatype array[] = {40, 30, 20, 35, 32, 50};
    int size = sizeof(array)/sizeof(array[0]);
    BSTree T = nullptr;
    for (int i = 0; i < size; ++i) {
        BST_Insert(T, array[i]);
    }
    BST_Print(T);
    cout << endl;

    // BST_Delete(&T, 40);
    BST_Delete(&T, 2);
    BST_Print(T);
    cout << endl;

    return 0;
}