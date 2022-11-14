#include <iostream>
using namespace std;

typedef struct HeightBalancedBinarySortTree {
    int data;
    int bf;
    HeightBalancedBinarySortTree *lchild, *rchild;
}AVLNode, *AVLTree;

// 右旋
void R_Rotate(AVLTree* root) {
    AVLTree L = (*root)->lchild;
    (*root)->lchild = L->rchild;
    L->rchild = *root;
    *root = L;
}

// 左旋
void L_Rotate(AVLTree* root) {
    AVLTree R = (*root)->rchild;
    (*root)->rchild = R->lchild;
    R->lchild = *root;
    *root = R;
}

// LL与LR
void Left_Balance(AVLTree* root) {
    AVLTree root_lchild = (*root)->lchild;
    AVLTree root_lchild_rchild = root_lchild->rchild;
    switch (root_lchild->bf) {
        case 1:
            root_lchild->bf = (*root)->bf = 0;
            R_Rotate(root);
            break;    
        case -1:            
            switch (root_lchild_rchild->bf) {
                case 1:
                    (*root)->bf = -1;
                    root_lchild->bf = 0;
                    break;
                case 0:
                    (*root)->bf = root_lchild->bf = 0;
                    break;
                case -1:
                    (*root)->bf = 0;
                    root_lchild->bf = 1;
                    break;
            }
            root_lchild_rchild->bf = 0;
            // L_Rotate(&root_lchild); //解引用出来是个局部变量，错！
            L_Rotate(&(*root)->lchild);
            R_Rotate(root);
            break;
    }
}

// RR与RL
void Right_Balance(AVLTree* root) {
    AVLTree root_rchild = (*root)->rchild;
    AVLTree root_rchild_lchild = root_rchild->lchild;
    switch (root_rchild->bf) {
        case -1:
            (*root)->bf = root_rchild->bf = 0;
            L_Rotate(root);
            break;
        case 1:
            switch (root_rchild_lchild->bf) {
                case -1:
                    (*root)->bf = 1;
                    root_rchild = 0;
                    break;
                case 0:
                    (*root)->bf = root_rchild->bf = 0;
                    break;
                case 1:
                    (*root)->bf = 0;
                    root_rchild->bf = -1;
                    break;
            }
            root_rchild_lchild->bf = 0;
            R_Rotate(&(*root)->rchild);
            L_Rotate(root);
            break;
    }
}

bool AVL_Insert(AVLTree* T, int e, bool* taller) {
    if (!*T) {
        *T = new AVLNode;
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = nullptr;
        (*T)->bf = 0;
        *taller = true;
    } else {
        if ((*T)->data == e) {
            *taller = false;
            return false;
        }
        if ((*T)->data > e) {
            if (!AVL_Insert(&(*T)->lchild, e, taller)) {
                return false;
            }
            if (*taller) {
                switch ((*T)->bf) {
                    case 1:
                        Left_Balance(T);
                        *taller = false;
                        break;
                    case 0:
                        (*T)->bf = 1;
                        *taller = true;
                        break;
                    case -1:
                        (*T)->bf = 0;
                        *taller = false;
                        break;
                }
            }
        } else {
            if (!AVL_Insert(&(*T)->rchild, e, taller)) {
                return false;
            }
            if (*taller) {
                switch ((*T)->bf) {
                    case 1:
                        (*T)->bf = 0;
                        *taller = false;
                        break;
                    case 0:
                        (*T)->bf = -1;
                        *taller = true;
                        break;
                    case -1:
                        Right_Balance(T);
                        *taller = false;
                        break;
                }
            }
        }
    }
    return true;
}

void visitNode(AVLTree T) {
    cout << T->data << " ";
}

// 递归中序遍历二叉排序树
void AVL_Print(AVLTree T) {
    if (T) {
        AVL_Print(T->lchild);
        visitNode(T);
        AVL_Print(T->rchild);
    }
}

int main() {
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    AVLTree T = nullptr;
    bool taller = 0;
    for (int i = 0; i < 10; ++i) {
        AVL_Insert(&T, a[i], &taller);
    }

    cout << "递归中序遍历AVL后: " << endl;
    AVL_Print(T);
    return 0;
}