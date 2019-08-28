#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX_NUM 50
#define MAX_ARC_NUM 100
#define INFINITY INT_MAX
 
typedef char VertexType;
typedef enum{DG, DN, UDG, UDN}GraphKind;  //{有向图，有向网，无向图，无向网}

typedef struct {
    VertexType vexs[MAX_VEX_NUM];
    int arcs[MAX_VEX_NUM][MAX_VEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
}Graph;

int LocateVex(char vex, Graph G) {
    int i;
    for (i = 1; i <= G.vexnum; i++) {
        if (G.vexs[i] == vex) {
            return i;
        }
    }
    return 0;
}
 
/*创建无向图的邻接矩阵*/
void create_G(Graph &G) {
    int i, j, k,weight;
    int v1, v2;
    char c1, c2;
    
    G.kind = UDG;
    printf("请输入顶点个数 : ");
    scanf("%d", &G.vexnum);
    printf("请输入弧的个数 : ");
    scanf("%d", &G.arcnum);
    getchar();
    for (i = 1; i <= G.vexnum; i++) {
        printf("请输入第%d个顶点(char):", i);
        scanf("%c", &G.vexs[i]);
        getchar();
    }
 
    //初始化邻接矩阵
    for (i = 1; i <= G.vexnum; i++) {
        for (j = 1; j <= G.vexnum; j++) {
            G.arcs[i][j] = INFINITY;
        }
    }
 
    //输入边的信息，建立邻接矩阵
    for (k = 1; k <= G.arcnum; k++) {
        printf("请输入第%d个弧 v1(char) v2(char) weight(int): ", k);
        scanf("%c %c %d", &c1, &c2,&weight);
        v1 = LocateVex(c1, G);
        v2 = LocateVex(c2, G);
        G.arcs[v1][v2] = G.arcs[v2][v1] = weight;
        getchar();
    }
}
/* 打印邻接矩阵和顶点信息*/
void print_G(Graph G) {
    int i, j;
    printf("\n图的顶点个数: %d\n\n" ,G.vexnum);
    printf("图的弧数: %d\n",G.arcnum);
 
    printf("顶点输出:");
    for (i = 1; i <= G.vexnum; i++)
        printf("%c   ", G.vexs[i]);
    printf("\n\n邻接矩阵:\n\n" );
 
    for (i = 1; i <= G.vexnum; i++) {
        for (j = 1; j <= G.vexnum; j++) {
        	if(G.arcs[i][j] == INFINITY)
        		printf("∞\t");
        	else
           		printf("%d\t", G.arcs[i][j]);
        }
        printf("\n");
    }
}
 
 
// 定义边结构体
typedef struct{
    int start;
    int end;
    int cost;
}Edge;

/*由邻接矩阵得到边的信息 */
void init_edge(Graph G,Edge edge[]){
    int i,j;
    int count = 0;
    for(i = 1; i <= G.vexnum;i++){
        for (j = i;j <= G.vexnum;j++){
            if(G.arcs[i][j] != INFINITY){
                edge[count].start = i;
                edge[count].end = j;
                edge[count].cost = G.arcs[i][j];
                count++;
            }
        }
    }
}

 
/*将边按权值从大到小排序*/
void sort_edge(Edge edge[],int arcnum){
    int i,j;
    Edge temp;
    for(i = 0; i < arcnum - 1;i++){
        for (j = i+1;j < arcnum;j++){
            if(edge[i].cost > edge[j].cost){
                temp = edge[i];
                edge[i] = edge[j];
                edge[j] = temp;
            }
        }
    }
}

/*找出指定节点的所属的连通分量，这里是找出其根节点在father数组中下标。*/ 
int find_mset(int father[],int v){
    int t = v;
    while(father[t] != -1)
        t = father[t];
    return t;
}
 
/*Kruskal算法求最小生成树*/
void Kruskal_G(Graph G,Edge edge[]){
    int father[MAX_VEX_NUM];
    int i,count,vf1,vf2;
    // 初始化father数组
    for(i = 0;i < MAX_VEX_NUM;i++){
        father[i] = -1;
    }
    i = 0;
    count = 0; // 统计加入最小生树中的边数,最多n-1条边 
    // 遍历任意两个结点之间的边
    while(i < G.arcnum && count < G.vexnum-1){
        vf1 = find_mset(father,edge[i].start);
        vf2 = find_mset(father,edge[i].end);
        // 如果这两个节点不属于同一个连通分量，则加入同一个连通分量
        if (vf1 != vf2){
            father[vf2] = vf1;		//merge_mfset合并 
            count++;
            printf("(%c,%c,%d)\n",G.vexs[edge[i].start],G.vexs[edge[i].end],edge[i].cost);
        }
        i++;
    }
}

int main(int argc,char **argv) {
    Graph G;
    Edge edge[MAX_ARC_NUM];
    
    create_G(G);
    print_G(G);
    
    init_edge(G,edge);
    sort_edge(edge,G.arcnum);
    
    printf("Kruskal算法结果:\n");
    Kruskal_G(G,edge);
    return 0;
}
