/**
 * 无向图的邻接多重表存储以及打印输出
*/

#include <iostream>
#include <string>
using namespace std;
#define MAXVEXNUM 4
#define MAXEDGENUM (MAXVEXNUM*(MAXVEXNUM - 1))/2
typedef int VertexType;
typedef int WeightType;

const VertexType vexDataString[MAXVEXNUM] = {0, 1, 2, 3};

// 边表节点
typedef struct EdgeListNode
{
    VertexType iVex;
    EdgeListNode* iLink;
    VertexType jVex;
    EdgeListNode* jLink;
    // WeightType weight;
}Edge, *EdgePtr;

// 定点表节点
typedef struct VertexArrayNode
{
    VertexType vexData;
    EdgeListNode* edgeListHeadPtr;
}VertexNode, *VertexNodePtr, VertexArray[MAXVEXNUM];

// 无向图，此结构体可不需要
typedef struct undirectedGraph
{
    VertexArray adjacencyMultilist;
    int vertexNum = MAXVEXNUM;
    int edgeNum = MAXEDGENUM;
}undirectedGraph, *undirectedGraphPtr;

void edgeInsert(undirectedGraphPtr& G, int index1, int index2)
{
    if ((index1 < 0 || index1 > MAXVEXNUM - 1) || (index2 < 0 || index2 > MAXVEXNUM - 1)) {
        cout << "Error! Invalid node index!" << endl;
        return;
    }
    EdgePtr p = new Edge;
    p->iVex = index1;
    p->jVex = index2;

    // 此处相当于链表的插入 指向边表中边的指针总数为边的两倍
    EdgePtr p1 = G->adjacencyMultilist[index1].edgeListHeadPtr;
    if (p1 == nullptr) {
        G->adjacencyMultilist[index1].edgeListHeadPtr = p;
        p->iLink = nullptr;
    } else {
        G->adjacencyMultilist[index1].edgeListHeadPtr = p;
        p->iLink = p1;
    }

    EdgePtr p2 = G->adjacencyMultilist[index2].edgeListHeadPtr;
    if (p2 == nullptr) {
        G->adjacencyMultilist[index2].edgeListHeadPtr = p;
        p->jLink = nullptr;
    } else {
        G->adjacencyMultilist[index2].edgeListHeadPtr = p;
        p->jLink = p2;
    }
}

void createUndirectedGraph(undirectedGraphPtr& G)
{
    // 建立顶点表信息 边表的头指针全设置为nullptr
    for (int i = 0; i < MAXVEXNUM; ++i) {
        G->adjacencyMultilist[i].vexData = vexDataString[i];
        G->adjacencyMultilist[i].edgeListHeadPtr = nullptr;
    }
    // 建立边表信息
    char Switch;
    int index1, index2;
    while (1) {
        cout << "Do you want to insert edge? (y or n)" << endl;
        cin >> Switch;
        if (Switch == 'y') {
            cout << "Please input index1 and index2: " << endl;
            cin >> index1 >> index2;
            edgeInsert(G, index1, index2);
        } else {
            break;
        }
    }
}

// void edgeDelete(undirectedGraphPtr& G, int index1, int index2)
// {
//     EdgePtr currentPtr = G->adjacencyMultilist[index1].edgeListHeadPtr;
//     EdgePtr priorPtr = currentPtr;
//     if (currentPtr->iVex == index1 && currentPtr->jVex == index2) {
        
//     }
// }

// 这里形参可以不用引用，因为改变的是指针指向的数据
void printUndirectedGraph(undirectedGraphPtr& G)
{
    for (int i = 0; i < G->vertexNum; ++i) {
        EdgePtr edge = G->adjacencyMultilist[i].edgeListHeadPtr;
        cout << G->adjacencyMultilist[i].vexData << "->";
        while (edge) {
            cout << edge->iVex << "|" << edge->jVex << "->";
            if (G->adjacencyMultilist[i].vexData == edge->iVex) {
                edge = edge->iLink;
            } else {
                edge = edge->jLink;
            }
        }
        cout << "nullptr" << endl;
    }
}

int main()
{
    undirectedGraph G;
    undirectedGraphPtr gPtr = &G;
    
    createUndirectedGraph(gPtr);
    printUndirectedGraph(gPtr);
    return 0;
}