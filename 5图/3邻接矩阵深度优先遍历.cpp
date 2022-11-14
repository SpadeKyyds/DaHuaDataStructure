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

bool visitedFlagArray[MAXVERTEX];

void MGraphCreate(MGraphPtr G) {
    cout << "Please input nodeNum and edgeNum, saparate them with space: " << endl;
    cin >> G->nodeNum >> G->edgeNum;
    cout << "Please input vertex one by one, end with enter: " << endl;
    for (int i = 0; i < G->nodeNum; ++i) {
        cin >> G->vertex[i];
    }
    // 邻接边表的初始化
    for (int i = 0; i < G->nodeNum; ++i) {
        for (int j = 0; j < G->nodeNum; ++j) {
            G->edge[i][j] = INFINITY;
        }
    }
    // 邻接边表的建立
    for (int k = 0, i, j, w; k < G->edgeNum; ++k) {
        cout << "Please input the left, right index and weight of edge: " << endl;
        cin >> i >> j >> w;
        G->edge[i][j] = w;
        G->edge[j][i] = G->edge[i][j];
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

int main() {
    MGraph g;
    MGraphCreate(&g);
    DFSTraverse(&g);
    
    return 0;
}