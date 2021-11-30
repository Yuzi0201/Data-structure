#include <iostream>
#include <queue>
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
    return -1;
}

int FirstAdjVex(ALGraph *G, int v);
int NextAdjVex(ALGraph *G, int v, int w);

void DFS(ALGraph *G, int v) //Depth First Search
{
    static bool visited[7] = {false};
    cout << v << " ";
    visited[v] = 1;
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
            DFS(G, w);
    }
}

int FirstAdjVex(ALGraph *G, int v)
{
    return G->vertices[v].firstarc->adjvex;
}

int NextAdjVex(ALGraph *G, int v, int w)
{
    ArcNode *p = G->vertices[v].firstarc;
    while (p->adjvex != w)
        p = p->nextarc;
    if (!p->nextarc)
        return -1;             //下一条边是空的了
    return p->nextarc->adjvex; //此时p就是w的节点，返回下一个的序号
}

void BFS(ALGraph *G, int v) //Breadth First Search
{
    cout << v << " ";
    static bool visited[7] = {false};
    visited[v] = true; //第v个（也就是第0个节点已访问）
    queue<int> q;
    q.push(v);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
            if (!visited[w])
            {
                cout << w << " ";
                visited[w] = true;
                q.push(w);
            }
    }
}

typedef struct
{
    int head;
    int tail;
    int lowcost;
    bool selected = false;
} Edge[9]; //克鲁斯卡尔算法的辅助数组，记录边的信息

ArcNode *NextVex(ALGraph *G, int v, int w)
{
    ArcNode *p = G->vertices[v].firstarc;
    while (p->adjvex != w)
        p = p->nextarc;
    if (!p->nextarc)
        return nullptr; //下一条边是空的了
    return p->nextarc;  //此时p就是w的节点，返回下一边
}

void InitAndSortEdge(ALGraph *G, Edge e[])
{
    int v = 0;
    static bool visited[7][7] = {false}; //边的访问矩阵
    int vex = 0;
    queue<int> q;
    q.push(v);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (ArcNode *v = G->vertices[u].firstarc; v; v = NextVex(G, u, v->adjvex))
            if (!visited[v->adjvex][u] && !visited[u][v->adjvex]) //此边指向的点到u和u到此边指向的点都未访问过
            {
                //cout << v->weight << " ";//for debug
                e[vex]->lowcost = v->weight;
                e[vex]->head = u;
                e[vex]->tail = v->adjvex;
                vex++;
                visited[u][v->adjvex] = true; //u到此边指向的点已访问
                q.push(v->adjvex);
            }
    } //↑提取边的权重的部分
    for (size_t i = 0; i < 9 - 1; i++)
    {
        for (size_t j = 0; j < 9 - 1 - i; j++)
        {
            if (e[j]->lowcost > e[j + 1]->lowcost)
                swap(e[j], e[j + 1]);
        }
    } //按照边的权重进行冒泡排序
}

bool All_connected(bool connected[])
{
    for (size_t i = 0; i < 7; i++)
    {
        if (!connected[i])
            return false;
    }
    return true;
}

void MiniSpanTree_Kruskal(ALGraph *G)
{
    Edge e[9];
    InitAndSortEdge(G, e);                 //提取所有边的权重并排序
    int Vexset[7] = {0, 1, 2, 3, 4, 5, 6}; //表示连通分量，初始时各顶点自成连通分量
    for (size_t i = 0; i < 9; i++)
    {
        int vs1 = Vexset[e[i]->head];
        int vs2 = Vexset[e[i]->tail];
        if (Vexset[e[i]->head] != Vexset[e[i]->tail]) //如果两个顶点属于不同的连通分量，则连接
        {
            e[i]->selected = true;
            //cout << e[i]->head << " " << e[i]->tail << "    ";//for debug
            for (size_t j = 0; j < 7; j++) //将尾顶点所属的连通分量的所有点合并入头顶点的连通分量
                if (Vexset[j] == vs2)
                    Vexset[j] = vs1;
        }
    }
    //cout << endl;
    int head = e[0]->head;
    cout << head;
    bool visted[7] = {false};
    visted[head] = true;
    while (!All_connected(visted))
    {
        for (size_t i = 0; i < 9; i++)
        {
            if (e[i]->selected && (e[i]->head == head || e[i]->tail == head))
            {
                int next = e[i]->head == head ? e[i]->tail : e[i]->head; //确定哪一端是线头
                cout << "--" << e[i]->lowcost << "--> " << next;
                visted[next] = true;
                head = next;
                e[i]->selected = false;
                break;
            }
        }
    }
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
    printf("深度优先遍历为：\n");
    int v = 0;
    DFS(G, v);
    printf("\n广度优先遍历为：\n");
    BFS(G, v);
    printf("\n最小生成树为：\n");
    MiniSpanTree_Kruskal(G);
}