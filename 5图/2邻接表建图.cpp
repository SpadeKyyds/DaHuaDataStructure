#include <iostream>
#include <string>
using namespace std;
#define MAXVERTEX 100
typedef string VertexType;

typedef struct EdgeListNode {
    int adjvex;
    struct EdgeListNode* next;
}EdgeNode;

typedef struct VertexListNode {
    VertexType info;
    EdgeNode* firstEdge;
}VertexNode, AdjList[MAXVERTEX];

typedef struct {
    AdjList adjList;
    int nodeNum, edgeNum;
}AdjListGraph;

void CreateAdjListGraph(AdjListGraph* G) {
    int i, j, k;
    EdgeNode* e;
    cout << "Please input nodeNum and edgeNum: " << endl;
    cin >> G->nodeNum >> G->edgeNum;
    // 顶点表初始化
    for (i = 0; i < G->nodeNum; ++i) {
        cout << "Please input node " << i << "'s info: " << endl;
        cin >> G->adjList[i].info;
        G->adjList[i].firstEdge = nullptr;
    }
    // 建立边表
    for (k = 0; k < G->edgeNum; ++k) {
        cout << "Please input the left and right index of edge and saparate them with space: " << endl;
        cin >> i >> j;
        e = new EdgeNode;
        e->adjvex = j;
        e->next = G->adjList[i].firstEdge;
        G->adjList[i].firstEdge = e;

        e = new EdgeNode;
        e->adjvex = i;
        e->next = G->adjList[j].firstEdge;
        G->adjList[j].firstEdge = e;
    }
}

int main() {
    AdjListGraph g;
    CreateAdjListGraph(&g);

    return 0;
}