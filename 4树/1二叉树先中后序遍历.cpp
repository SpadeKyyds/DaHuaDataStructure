#include <iostream>
#include <string>
using namespace std;

// 树节点的建立
struct DataType
{
    int x;
    float y;
    string z;
};
typedef struct BinaryTreeNode
{
    // DataType data;
    string data;
    struct BinaryTreeNode* lchild;
    struct BinaryTreeNode* rchild;
    struct BinaryTreeNode* parent;
}TreeNode, *TreePtr;

void rootInit(TreePtr& root)
{
    root = new TreeNode;
    root->data = "first";
    root->lchild = nullptr;
    root->rchild = nullptr;
    root->parent = nullptr;
}

void childInsert(TreePtr parent, const string childType, const string data)
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

void preOrderTraverse(TreePtr& p)
{
    if (p != nullptr) {
        visitNode(p);
        preOrderTraverse(p->lchild);
        preOrderTraverse(p->rchild);
    }
}

void inOrderTraverse(TreePtr& p)
{
    if (p != nullptr) {
        inOrderTraverse(p->lchild);
        visitNode(p);
        inOrderTraverse(p->rchild);
    }
}

void postOrderTraverse(TreePtr& p)
{
    if (p != nullptr) {
        postOrderTraverse(p->lchild);
        postOrderTraverse(p->rchild);
        visitNode(p);
    }
}

int main()
{
    TreePtr root = nullptr;
    rootInit(root);
    childInsert(root, "left", "second");
    childInsert(root, "right", "third");
    childInsert(root->lchild, "right", "fourth");

    cout << "preOrderTraverse is: " << endl;
    preOrderTraverse(root);
    cout << endl;

    cout << "inOrderTraverse is: " << endl;
    inOrderTraverse(root);
    cout << endl;

    cout << "postOrderTraverse is: " << endl;
    postOrderTraverse(root);
    cout << endl;
    
    return 0;
}