/**算法思想
 * 初始化一个辅助队列
 * 根节点入队
 * 若队列非空，则队头节点出队，并在队尾插入该节点左右孩子节点（若有）
 * 重复步骤三，直至队列为空
 */
#include <iostream>
#include <string>
using namespace std;

typedef struct BinaryTreeNode
{
    string data;
    struct BinaryTreeNode* lchild;
    struct BinaryTreeNode* rchild;
    struct BinaryTreeNode* parent;
}TreeNode, *TreePtr;

typedef struct LinkedQueue
{
    TreePtr treePtr;
    struct LinkedQueue* next;
}QueueNode, *QueuePtr;

typedef struct AssistantQueuePointer
{
    QueuePtr front;
    QueuePtr rear;
}AssPtr;

// 队列接口函数
void queueInit(AssPtr& ptr, QueuePtr head)
{
    head->treePtr = nullptr;
    head->next = nullptr;
    ptr.front = head;
    ptr.rear = head;
}

void queuePrint(AssPtr& ptr)
{
    QueuePtr p = ptr.front;
    while (p != ptr.rear) {
        cout << p->next->treePtr->data << " ";
        p = p->next;
    }
    cout << endl;
}

void pushQueue(AssPtr& ptr, TreePtr& root)
{
    QueuePtr p = new QueueNode;
    p->treePtr = root;
    p->next = nullptr;
    ptr.rear->next = p;
    ptr.rear = p;
}

void popQueue(AssPtr& ptr, TreePtr& return_treePtr)
{
    if (ptr.front == ptr.rear) {
        cout << "Error! Queue is empty!" << endl;
    } else if (ptr.front->next == ptr.rear) {
        QueueNode* p = ptr.rear;
        ptr.front->next = nullptr;
        ptr.rear = ptr.front;
        return_treePtr = p->treePtr;
        delete p;
    } else {
        QueueNode* p = ptr.front->next;
        ptr.front->next = p->next;
        return_treePtr = p->treePtr;
        delete p;
    }
}

// 树接口函数 
void rootInit(TreePtr& root)
{
    root = new TreeNode;
    root->data = "first";
    root->lchild = nullptr;
    root->rchild = nullptr;
    root->parent = nullptr;
}

void childInsert(TreePtr& parent, const string childType, const string data)
{
    TreePtr child = new TreeNode;
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

void visitNode(TreePtr& p)
{
    cout << p->data << " ";
}

void levelTraverse(AssPtr& ptr, TreePtr& pointer)
{
    TreePtr return_treePtr = nullptr;
    pushQueue(ptr, pointer);
    while (ptr.front != ptr.rear) {
        visitNode(ptr.front->next->treePtr);
        popQueue(ptr, return_treePtr);
        if (return_treePtr->lchild != nullptr) {
            pushQueue(ptr, return_treePtr->lchild);
        }
        if (return_treePtr->rchild != nullptr) {
            pushQueue(ptr, return_treePtr->rchild);
        }
    }
}

int main()
{
    // 队列初始化
    QueueNode head;
    AssPtr ptr;
    queueInit(ptr, &head);
    
    // 树初始化及构建
    TreePtr root = nullptr;
    rootInit(root);
    childInsert(root, "left", "second");
    childInsert(root, "right", "third");
    childInsert(root->lchild, "right", "fourth");
    
    // 层次遍历
    levelTraverse(ptr, root);
    return 0;
}