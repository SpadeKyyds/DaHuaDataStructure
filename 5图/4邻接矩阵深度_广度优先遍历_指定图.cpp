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
typedef struct {
    VertexType vertex[MAXVERTEX];
    EdgeType edge[MAXVERTEX][MAXVERTEX];
    int nodeNum, edgeNum;
}MGraph, *MGraphPtr;

typedef struct {
    int nodeInfo[MAXVERTEX]; //这里队列足够大，有一定浪费空间，只存节点的下标
    int front, rear;
}Queue;

bool visitedFlagArray[MAXVERTEX];

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

void MGraphCreate(MGraphPtr G) {
    G->nodeNum = 11;
    G->edgeNum = 13;
    G->vertex[0] = "v0";
    G->vertex[1] = "v1";
    G->vertex[2] = "v2";
    G->vertex[3] = "v3";
    G->vertex[4] = "v4";
    G->vertex[5] = "v5";
    G->vertex[6] = "v6";
    G->vertex[7] = "v7";
    G->vertex[8] = "v8";
    G->vertex[9] = "v9";
    G->vertex[10] = "v10";
    // 邻接边表的初始化
    for (int i = 0; i < G->nodeNum; ++i) {
        for (int j = 0; j < G->nodeNum; ++j) {
            G->edge[i][j] = INFINITY;
        }
    }
    // 邻接边表的建立
    G->edge[0][1] = 1;
    G->edge[0][4] = 1;
    G->edge[1][5] = 1;
    G->edge[2][3] = 1;
    G->edge[2][5] = 1;
    G->edge[2][6] = 1;
    G->edge[3][6] = 1;
    G->edge[3][7] = 1;
    G->edge[5][6] = 1;
    G->edge[6][7] = 1;
    G->edge[8][9] = 1;
    G->edge[8][10] = 1;
    G->edge[9][10] = 1;
    for (int i = 0; i < G->nodeNum; ++i) {
        for (int j = 0; j < G->nodeNum; ++j) {
            G->edge[j][i] = G->edge[i][j];
        }
    }
}

void visit(MGraphPtr G, int i) {
    cout << G->vertex[i] << " ";
}

void DFS(MGraphPtr G, int i) {
    visitedFlagArray[i] = TRUE;
    visit(G, i);
    for (int j = 0; j < G->nodeNum; ++j) {
        if (G->edge[i][j] != INFINITY && !visitedFlagArray[j]) {
            DFS(G, j);
        }
    }
}

void DFSTraverse(MGraphPtr G) {
    int i;
    for (i = 0; i < G->nodeNum; ++i) {
        visitedFlagArray[i] = FALSE;
    }
    for (i = 0; i < G->nodeNum; ++i) {
        if (!visitedFlagArray[i]) {
            DFS(G, i);
        }
    }
}

void BFSTraverse(MGraphPtr G) {
    int i, j, backValue;
    Queue Q; //定义一个辅助队列
    initQueue(&Q);
    for (i = 0; i < G->nodeNum; ++i) {
        visitedFlagArray[i] = FALSE;
    }
    for (i = 0; i < G->nodeNum; ++i) {
        if (!visitedFlagArray[i]) {
            visitedFlagArray[i] = TRUE;
            visit(G, i);
            enQueue(&Q, i);
            while(!queueEmpty(&Q)) {
                deQueue(&Q, backValue);
                for (j = 0; j < G->nodeNum; ++j) {
                    if (!visitedFlagArray[j] && G->edge[backValue][j] != INFINITY) {
                        visitedFlagArray[j] = TRUE;
                        visit(G, j);
                        enQueue(&Q, j);
                    }
                }
            }
        }
    }
}

int main() {
    MGraph g;
    MGraphCreate(&g);
    cout << "This is DFS traverse: " << endl;
    DFSTraverse(&g);
    cout << endl;
    cout << "This is BFS traverse: " << endl;
    BFSTraverse(&g);
    return 0;
}