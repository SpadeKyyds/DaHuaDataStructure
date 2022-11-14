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
void threadTreeNode(ThreadPtr& p, ThreadPtr& pre)
{
    // cout << "recursive inorder traverse: ";
    // 递归方法中序遍历
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
        threadTreeNode(p, pre);
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

void BiTreeThread(ThreadPtr& root, ThreadPtr& pre)
{
    cout << "inThread is: " << endl;
    inThread(root, pre);
    cout << endl;
    if (pre->rchild == nullptr) {
        pre->rtag = 1;
    }
}

/**在中序线索二叉树中找到指定节点的中序后继next
 * 若p->rtag == 1, 则next = p->rchild;
 * 若p->rtag == 0, 则p有右孩子节点，next = p的右子树中最左下角节点
 */

// 找到以p为根的子树中，第一个被中序遍历的节点
ThreadPtr firstInOrderTraverseNode(ThreadPtr p)
{
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

// 在中序线索二叉树中找到节点p的后继节点
ThreadPtr findNextNode(ThreadPtr p)
{
    if (p->rtag == 0) {
        return firstInOrderTraverseNode(p->rchild);
    } else {
        return p->rchild;
    }
}

// 非递归实现中序遍历
void non_recursiveInOrderTraverseNode(ThreadPtr root)
{
    cout << "non_recursive inorder traverse: ";
    for (ThreadPtr p = firstInOrderTraverseNode(root); p != nullptr; p = findNextNode(p)) {
        cout << p->data << " ";
    }
    cout << endl;
}

/**在中序线索二叉树中找到指定节点p的中序前驱pre
 * 若p->ltag == 1，则pre = p->lchild;
 * 若p->ltag == 0，则pre = p的左子树中最右下节点
 */

// 找到以p为根的子树中，最后一个被中序遍历的节点
ThreadPtr lastInorderTraverseNode(ThreadPtr p)
{
    while (p->rtag == 0) {
        p = p->rchild;
    }
    return p;
}

// 在中序线索二叉树中找到节点p的前驱节点
ThreadPtr findPreNode(ThreadPtr p)
{
    if (p->ltag == 0) {
        return lastInorderTraverseNode(p->lchild);
    } else {
        return p->lchild;
    }
}

// 对中序线索二叉树进行逆向中序遍历
void revNon_recursiveInOrderTraverseNode(ThreadPtr root)
{
    cout << "revNon_recursiveInOrderTraverse: ";
    for (ThreadPtr p = lastInorderTraverseNode(root); p != nullptr; p = findPreNode(p)) {
        cout << p->data << " ";
    }
    cout << endl;
}

int main()
{
    ThreadPtr root = nullptr;
    ThreadPtr pre = nullptr;
    BiTreeContruct(root);
    BiTreeThread(root, pre);
    non_recursiveInOrderTraverseNode(root);
    revNon_recursiveInOrderTraverseNode(root);

    return 0;
}