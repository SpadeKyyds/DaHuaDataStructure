#include <iostream>
using namespace std;

typedef struct BinarySearchTree
{
    int key;
    struct BinarySearchTree *lchild, *rchild;
}BSTNode, *BSTPtr;

/**二叉排序树的查找 二叉排序树：左子树节点值 < 根节点值 < 右子树节点值
 * 若树非空，则目标值与根节点值相比较：
 * 若相等，则查找成功 若小于根节点值，则在左子树继续查找 否则在右子树继续查找
 * 查找成功，返回节点指针 查找失败返回NULL
*/
// 时间复杂度为O(h)
BSTPtr DiGui_keySearch(BSTPtr p, const int targetData)
{
    while (p != nullptr) {
        if (p->key == targetData) {
            return p;
        } else if (p->key < targetData) {
            return DiGui_keySearch(p->lchild, targetData);
        } else {
            return DiGui_keySearch(p->rchild, targetData);
        }
    }
    return p;
}

// 时间复杂度为O(1)
BSTPtr NonDiGui_keySearch(BSTPtr p, const int targetData)
{
    while (p != nullptr && p->key != targetData) {
        if (p->key > targetData) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    return p;
}

// 查找指定数据前驱节点 并不是排序后的前驱 而是树形结构的双亲前驱
BSTPtr NonDiGui_parentKeySearch(BSTPtr p, const int targetData)
{    
    BSTPtr q = nullptr;
    while (p != nullptr && p->key != targetData) {
        if (p->key > targetData) {
            q = p;
            p = p->lchild;
        } else {
            q = p;
            p = p->rchild;
        }
    }
    if (p == nullptr && q != nullptr) {
        cout << "target data is not exist!" << endl;
        return nullptr;
    }
    return q;
}

// 查找指定数据排序后的 直接后继、前驱 但并未处理根节点T的情况
BSTPtr NonDiGui_priorNextKeySearch(BSTPtr T, const int targetData)
{
    BSTPtr p = NonDiGui_keySearch(T, targetData);
    BSTPtr parentPtr = NonDiGui_parentKeySearch(T, targetData);
    if (p == parentPtr->lchild) {
        if (p->rchild == nullptr) {
            return parentPtr;
        } else if (p->rchild->lchild == nullptr) {
            return p->rchild;
        } else {
            BSTPtr q = p->rchild->lchild;
            while (q->lchild != nullptr) {
                q = q->lchild;
            }
            return q;
        } //这里找的是p的后继
    } else if (p == parentPtr->rchild) {
        if (p->lchild == nullptr) {
            return parentPtr;
        } else if (p->lchild->rchild == nullptr) {
            return p->lchild;
        } else {
            BSTPtr q = p->lchild->rchild;
            while (q->rchild != nullptr) {
                q = q->rchild;
            }
            return q;
        } //这里找的是p的前驱
    } else if (parentPtr == nullptr) {
        if (p->rchild != nullptr) {
            BSTPtr q = p->rchild->lchild;
            while (q != nullptr) {
                q = q->lchild;
            }
            return q; //p没有父节点的情况找后继
        } else if (p->lchild != nullptr) {
            BSTPtr q = p->lchild->rchild;
            while (q != nullptr) {
                q = q->rchild;
            }
            return q; //p没有父节点的情况找前驱
        }
    }
    return nullptr;
}

/**
 * 二叉排序树的插入：
 * 若原二叉排序树为空，则直接插入节点，否则若关键字小于根节点值 则插入到左子树；若关键字大于根节点值，则插入到右子树
*/
void DiGui_keyInsert(BSTPtr& p, const int targetData)
{
    if (p == nullptr) {
        p = new BSTNode;
        p->key = targetData;
        p->lchild = p->rchild = nullptr;
    } else if (p->key > targetData) {
        DiGui_keyInsert(p->lchild, targetData);
    } else if (p->key < targetData) {
        DiGui_keyInsert(p->rchild, targetData);
    } else if (p->key == targetData) {
        cout << "The target data " << targetData << " is already exist!" << endl;
        return;
    }
}

// 非递归插入
void NonDiGui_keyInsert(BSTPtr& T, const int targetData)
{
    BSTPtr p = T; //指向需要插入的位置
    BSTPtr q = nullptr; //指向插入位置的父节点
    while (p != nullptr) {
        if (p->key < targetData) {
            q = p;
            p = p->rchild;
        } else if (p->key > targetData) {
            q = p;
            p = p->lchild;
        } else {
            cout << "The target data " << targetData << " is already exist!" << endl;
            return;
        }
    }
    p = new BSTNode;
    p->key = targetData;
    p->lchild = p->rchild = nullptr;
    if (q == nullptr) {
        T = p; //插入位置的父节点指针为空，表示此时插入节点为根节点，需要让根节点指针T指向新的数据存储地址
    } else if (q->key < p->key) {
        q->rchild = p;
    } else {
        q->lchild = p;
    }
}

// 数组作为函数参数传入的是指针 因此在此对数组求长度会出错
void BSTConstruct(BSTPtr& p, int data[], int length)
{
    p = nullptr;
    int i = 0;
    while (i < length) {
        NonDiGui_keyInsert(p, data[i]);
        ++i;
    }
}

void BSTDelete(BSTPtr& T, int targetData)
{
    BSTPtr targetPtr = NonDiGui_keySearch(T, targetData);
    BSTPtr parentPtr = NonDiGui_parentKeySearch(T, targetData);
    if (targetPtr == nullptr) {
        cout << "Target delete node is not exist!" << endl;
        return; //欲删除节点不存在
    } else if (targetPtr == T) {
        cout << "head can not be delete!" << endl;
        return;
    } else if (targetPtr->lchild == nullptr && targetPtr->rchild == nullptr) {
        if (parentPtr->lchild == targetPtr) {
            parentPtr->lchild = nullptr;
        } else if (parentPtr->rchild == targetPtr) {
            parentPtr->rchild = nullptr;
        }
        delete targetPtr; //删除节点为叶子节点
    } else if (targetPtr->lchild == nullptr && targetPtr->rchild != nullptr) {
        if (parentPtr->rchild == targetPtr) {
            parentPtr->rchild = targetPtr->rchild;
            delete targetPtr; //删除节点只有右孩子且删除节点为父节点右孩子
        } else {
            parentPtr->lchild = targetPtr->rchild;
            delete targetPtr; //删除节点只有右孩子且删除节点为父节点左孩子
        }
    } else if (targetPtr->rchild == nullptr && targetPtr->lchild != nullptr) {
        if (parentPtr->rchild == targetPtr) {
            parentPtr->rchild = targetPtr->lchild;
            delete targetPtr; //删除节点只有左孩子且删除节点为父节点右孩子
        } else {
            parentPtr->lchild = targetPtr->lchild;
            delete targetPtr; //删除节点只有左孩子且删除节点为父节点左孩子
        }
    } else if (targetPtr->lchild != nullptr && targetPtr->rchild != nullptr) {
        BSTPtr replacePtr = NonDiGui_priorNextKeySearch(T, targetData);
        int exchangeData = replacePtr->key;
        BSTDelete(T, replacePtr->key);
        targetPtr->key = exchangeData;
    }
}

void visitBSTNode(const BSTPtr& p)
{
    cout << p->key << " ";
}

void DiGui_inOrderTraverse(BSTPtr& p)
{
    if (p != nullptr) {
        DiGui_inOrderTraverse(p->lchild);
        visitBSTNode(p);
        DiGui_inOrderTraverse(p->rchild);
    }
}

int main()
{
    BSTPtr BSTree;
    int data[] = {13, 21, 7, 18, 2, 37, 5, 15, 20, 30, 45};
    int len = sizeof(data)/sizeof(data[0]);

    BSTConstruct(BSTree, data, len);
    DiGui_inOrderTraverse(BSTree);

    cout << endl << "After delete: " << endl;
    BSTDelete(BSTree, 13);  //13为根节点 此种情况暂未考虑到
    DiGui_inOrderTraverse(BSTree);

    return 0;
}