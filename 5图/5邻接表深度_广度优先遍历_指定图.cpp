/**
 * 本代码基于的图为：边上的权值都默认为1，非连通
 * v0---v1   v2---v3
 * |    |  / |  / |
 * v4   v5---v6---v7
 * 
 * v8---v9
 *  \   /
 *   v10
 * 
 * DFS:v0 v1 v5 v2 v3 v6 v7 v4 v8 v9 v10
 * BFS:v0 v1 v4 v5 v2 v6 v3 v7 v8 v9 v10
*/

#include <iostream>
#include <string>
using namespace std;
#define MAXVERTEX 100
#define INFINITY 65535
#define TRUE 1
#define FALSE 0
typedef string VertexType;
typedef int EdgeType;

// 此为邻接矩阵图的结构
typedef struct MatrixGraph{
    VertexType vertex[MAXVERTEX];
    EdgeType edge[MAXVERTEX][MAXVERTEX];
    int nodeNum, edgeNum;
}MGraph, *MGraphPtr;

// 辅助队列结构体
typedef struct AssistantQueue{
    int nodeInfo[MAXVERTEX]; //这里队列足够大，有一定浪费空间，只存节点的下标
    int front, rear;
}Queue;

// 邻接表图结构之边表
typedef struct EdgeListNode {
    int adjvex; //此对应为顶点在顶点表中的下标
    struct EdgeListNode* next;
}EdgeNode;

// 邻接表图结构之顶点表
typedef struct VertexListNode {
    VertexType info;
    EdgeNode* firstEdge;
}VertexNode, AdjList[MAXVERTEX];

// 邻接表图结构之图
typedef struct {
    AdjList adjList;
    int nodeNum, edgeNum;
}AdjListGraph;

bool visitedFlagArray[MAXVERTEX]; //辅助数组，节点被访问过置TRUE

// 队列的系列接口函数
void initQueue(Queue* Q) {
    Q->front = Q->rear = 0;
}

bool queueEmpty(Queue* Q) {
    return (Q->front == Q->rear);
}

bool queueFull(Queue* Q) {
    return ((Q->rear + 1) % MAXVERTEX == Q->front);
}

int queueLength(Queue* Q) {
    return (Q->rear - Q->front + MAXVERTEX) % MAXVERTEX;
}

bool enQueue(Queue* Q, int element) {
    if (queueFull(Q)) {
        return false;
    } else {
        Q->nodeInfo[Q->rear] = element;
        Q->rear = (Q->rear + 1) % MAXVERTEX;
        return true;
    }
}

bool deQueue(Queue* Q, int& backValue) {
    if (queueEmpty(Q)) {
        return false;
    } else {
        backValue = Q->nodeInfo[Q->front];
        Q->front = (Q->front + 1) % MAXVERTEX;
        return true;
    }
}

// 图的邻接矩阵创建，目的是为了辅助图的邻接表创建
void CreateMGraph(MGraph* MG) {
    MG->nodeNum = 11;
    MG->edgeNum = 13;
    MG->vertex[0] = "v0";
    MG->vertex[1] = "v1";
    MG->vertex[2] = "v2";
    MG->vertex[3] = "v3";
    MG->vertex[4] = "v4";
    MG->vertex[5] = "v5";
    MG->vertex[6] = "v6";
    MG->vertex[7] = "v7";
    MG->vertex[8] = "v8";
    MG->vertex[9] = "v9";
    MG->vertex[10] = "v10";
    // 邻接边表的初始化
    for (int i = 0; i < MG->nodeNum; ++i) {
        for (int j = 0; j < MG->nodeNum; ++j) {
            MG->edge[i][j] = INFINITY;
        }
    }
    // 邻接边表的建立
    MG->edge[0][1] = 1;
    MG->edge[0][4] = 1;
    MG->edge[1][5] = 1;
    MG->edge[2][3] = 1;
    MG->edge[2][5] = 1;
    MG->edge[2][6] = 1;
    MG->edge[3][6] = 1;
    MG->edge[3][7] = 1;
    MG->edge[5][6] = 1;
    MG->edge[6][7] = 1;
    MG->edge[8][9] = 1;
    MG->edge[8][10] = 1;
    MG->edge[9][10] = 1;
    for (int i = 0; i < MG->nodeNum; ++i) {
        for (int j = 0; j < MG->nodeNum; ++j) {
            MG->edge[j][i] = MG->edge[i][j];
        }
    }
}

// 通过图的邻接矩阵创建图的邻接表
void CreateAdjListGraph(AdjListGraph* LG, MGraph* MG) {
    int i, j;
    EdgeNode* e;
    LG->nodeNum = MG->nodeNum;
    LG->edgeNum = MG->edgeNum;
    // 顶点表初始化
    for (i = 0; i < LG->nodeNum; ++i) {
        LG->adjList[i].info = MG->vertex[i];
        LG->adjList[i].firstEdge = nullptr;
    }
    // 建立边表
    for (i = 0; i < LG->nodeNum; ++i) {
        for (j = LG->nodeNum - 1; j >= 0; --j) {
            if (MG->edge[i][j] != INFINITY) {
                e = new EdgeNode;
                e->adjvex = j;
                e->next = LG->adjList[i].firstEdge;
                LG->adjList[i].firstEdge = e;
            }
        }
    }
}

// 节点访问函数，打印节点信息
void visit(AdjListGraph* LG, int i) {
    cout << LG->adjList[i].info << " ";
}

// 邻接表形式存储的图的深度优先遍历
void DFS(AdjListGraph* LG, int i) {
    EdgeNode* p = LG->adjList[i].firstEdge;
    visitedFlagArray[i] = TRUE;
    visit(LG, i);
    while (p) {
        if (!visitedFlagArray[p->adjvex]) {
            DFS(LG, p->adjvex);
        }
        p = p->next;
    }
}

void DFSTraverse(AdjListGraph* LG) {
    int i;
    for (i = 0; i < LG->nodeNum; ++i) {
        visitedFlagArray[i] = FALSE;
    }
    for (i = 0; i < LG->nodeNum; ++i) {
        if (!visitedFlagArray[i]) {
            DFS(LG, i);
        }
    }
}

// 邻接表形式存储的图的广度优先遍历
void BFSTraverse(AdjListGraph* LG) {
    int i, backValue;
    Queue Q;
    EdgeNode* p;
    initQueue(&Q);
    for (i = 0; i < LG->nodeNum; ++i) {
        visitedFlagArray[i] = FALSE;
    }
    for (i = 0; i < LG->nodeNum; ++i) {
        if (!visitedFlagArray[i]) {
            visitedFlagArray[i] = TRUE;
            visit(LG, i);
            enQueue(&Q, i);
            while (!queueEmpty(&Q)) {
                deQueue(&Q, backValue);
                p = LG->adjList[backValue].firstEdge;
                while (p) {
                    if (!visitedFlagArray[p->adjvex]) {
                        visitedFlagArray[p->adjvex] = TRUE;
                        visit(LG, p->adjvex);
                        enQueue(&Q, p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
}

int main() {
    MGraph MG;
    AdjListGraph LG;
    CreateMGraph(&MG);
    CreateAdjListGraph(&LG, &MG);

    cout << "This is DFS traverse of adjacent list graph: " << endl;
    DFSTraverse(&LG);
    cout << endl;
    cout << "This is BFS traverse of adjacent list graph: " << endl;
    BFSTraverse(&LG);
    return 0;
}