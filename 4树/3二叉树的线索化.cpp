/*这里的前驱节点指的是中序遍历序列的前一节点 并不是对应节点的父节点*/
#include <iostream>
#include <string>
using namespace std;

// 树节点的建立
typedef struct BinaryThreadTreeNode
{
    string data;
    struct BinaryThreadTreeNode* lchild;
    struct BinaryThreadTreeNode* rchild;
    struct BinaryThreadTreeNode* parent;
    int ltag, rtag;
}ThreadNode, *ThreadPtr;

void rootInit(ThreadPtr& root)
{
    root = new ThreadNode;
    root->data = "A";
    root->lchild = nullptr;
    root->rchild = nullptr;
    root->parent = nullptr;
    root->ltag = root->rtag = 0;
}

void childInsert(ThreadPtr& parent, const string childType, const string data)
{
    ThreadPtr child = new ThreadNode;
    child->parent = parent;
    if (childType == "left") {
        parent->lchild = child;
    } else {
        parent->rchild = child;
    }
    child->lchild = nullptr;
    child->rchild = nullptr;
    child->data = data;
}

// 针对于每一个节点 分别处理该节点的前驱和后继
void visitNode(ThreadPtr& p, ThreadPtr& pre)
{
    cout << p->data << " ";
    if (p->lchild == nullptr) {
        p->lchild = pre;
        p->ltag = 1;
    }
    if (pre != nullptr && pre->rchild == nullptr) {
        pre->rchild = p;
        pre->rtag = 1;
    }
    pre = p;
}

// 中序线索化
void inThread(ThreadPtr& p, ThreadPtr& pre)
{
    if (p != nullptr) {
        inThread(p->lchild, pre);
        visitNode(p, pre);
        inThread(p->rchild, pre);
        /**先序遍历要防止爱的魔力转圈圈问题 中序后序均无需考虑
         * visitNode(p, pre);
         * if (p->ltag == 0)
         * {
         *      inThread(p->lchild, pre);
         * }
         * inThread(p->rchild, pre);
         */
    }
}

void BiTreeContruct(ThreadPtr& root)
{
    
    rootInit(root);
    childInsert(root, "left", "B");
    childInsert(root, "right", "C");
    childInsert(root->lchild, "left", "D");
    childInsert(root->lchild, "right", "E");
    childInsert(root->rchild, "left", "F");
    childInsert(root->lchild->lchild, "right", "G");
}

void BiTreePrint(ThreadPtr& root, ThreadPtr& pre)
{
    cout << "inThread is: " << endl;
    inThread(root, pre);
    cout << endl;
    if (pre->rchild == nullptr) {
        pre->rtag = 1;
    }
}

int main()
{
    ThreadPtr root = nullptr;
    ThreadPtr pre = nullptr;
    BiTreeContruct(root);
    BiTreePrint(root, pre);

    return 0;
}