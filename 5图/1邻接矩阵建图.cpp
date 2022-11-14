#include <iostream>
#include <string>
using namespace std;

typedef string VertexType;
typedef int EdgeType;
#define MAXVERTEX 100
#define INFINITY 65535

typedef struct {
    VertexType vertex[MAXVERTEX];
    EdgeType edge[MAXVERTEX][MAXVERTEX];
    int nodeNum, edgeNum;
}MGraph, *MGraphPtr;

void MGraphCreate(MGraphPtr G) {
    cout << "Please input nodeNum and edgeNum: " << endl;
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
    for (int k = 0, i, j, w; k < G->edgeNum; ++k) {
        cout << "Please input the left, right index and weight of edge: " << endl;
        cin >> i >> j >> w;
        G->edge[i][j] = w;
        G->edge[j][i] = G->edge[i][j];
    }
}

int main() {
    MGraph g;
    MGraphCreate(&g);
    
    return 0;
}