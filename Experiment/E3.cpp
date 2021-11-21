#include <iostream>
using namespace std;

struct ArcNode //边节点
{
    int adjvex;       //该边指向的顶点位置
    ArcNode *nextarc; //指向下一条边的指针
    int weight;       //权重
};

typedef struct VNode //顶点
{
    int data;
    ArcNode *firstarc; //指向第一条依附于该顶点的边
} AdjList[7];

struct ALGraph //邻接表
{
    AdjList vertices;   //顶点
    int vexnum, arcnum; //当前顶点数边数
};
int LocateVex(ALGraph G, int vertex);

void CreateUDG(ALGraph &G, int verticesData[], int arcData[][3])
{
    G.vexnum = 7;
    G.arcnum = 9;
    for (size_t i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].data = verticesData[i];
        G.vertices[i].firstarc = nullptr; //初始化表头结点指针域为nullptr
    }
    int v1, v2, i, j;
    ArcNode *p1, *p2;
    for (size_t k = 0; k < G.arcnum; k++)
    {
        v1 = arcData[k][0];
        v2 = arcData[k][1];
        i = LocateVex(G, v1);
        j = LocateVex(G, v2); //确定v1和v2的位置
        p1 = new ArcNode;
        p1->adjvex = j;
        p1->weight = arcData[k][2];
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1; //将新节点*p1插入到vi的边表头
        p2 = new ArcNode;
        p2->adjvex = i;
        p2->weight = arcData[k][2];
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2; //将新节点*p2插入到vj的边表头
    }
}

int LocateVex(ALGraph G, int vertex)
{
    for (size_t i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data == vertex)
            return i;
}

int main()
{
    int verticesData[] = {0, 1, 2, 3, 4, 5, 6};
    int arcData[][3] = {{0, 1, 28}, {0, 5, 10}, {1, 6, 14}, {1, 2, 16}, {5, 4, 25}, {6, 4, 24}, {6, 3, 18}, {2, 3, 12}, {4, 3, 22}};
    ALGraph *G = new ALGraph;
    CreateUDG(*G, verticesData, arcData);
    printf("此图用邻接表表示为：\n");
    ArcNode *p;
    for (size_t i = 0; i < G->vexnum; i++)
    {
        cout << G->vertices[i].data;
        p = G->vertices[i].firstarc;
        while (p)
        {
            cout << " --" << p->weight << "-->" << p->adjvex << " ";
            p = p->nextarc;
        }
        cout << endl;
    }
}