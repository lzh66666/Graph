#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX_NUM 50
#define MAX_ARC_NUM 100
#define INFINITY INT_MAX
 
typedef char VertexType;
typedef enum{DG, DN, UDG, UDN}GraphKind;  //{����ͼ��������������ͼ��������}

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
 
/*��������ͼ���ڽӾ���*/
void create_G(Graph &G) {
    int i, j, k,weight;
    int v1, v2;
    char c1, c2;
    
    G.kind = UDG;
    printf("�����붥����� : ");
    scanf("%d", &G.vexnum);
    printf("�����뻡�ĸ��� : ");
    scanf("%d", &G.arcnum);
    getchar();
    for (i = 1; i <= G.vexnum; i++) {
        printf("�������%d������(char):", i);
        scanf("%c", &G.vexs[i]);
        getchar();
    }
 
    //��ʼ���ڽӾ���
    for (i = 1; i <= G.vexnum; i++) {
        for (j = 1; j <= G.vexnum; j++) {
            G.arcs[i][j] = INFINITY;
        }
    }
 
    //����ߵ���Ϣ�������ڽӾ���
    for (k = 1; k <= G.arcnum; k++) {
        printf("�������%d���� v1(char) v2(char) weight(int): ", k);
        scanf("%c %c %d", &c1, &c2,&weight);
        v1 = LocateVex(c1, G);
        v2 = LocateVex(c2, G);
        G.arcs[v1][v2] = G.arcs[v2][v1] = weight;
        getchar();
    }
}
/* ��ӡ�ڽӾ���Ͷ�����Ϣ*/
void print_G(Graph G) {
    int i, j;
    printf("\nͼ�Ķ������: %d\n\n" ,G.vexnum);
    printf("ͼ�Ļ���: %d\n",G.arcnum);
 
    printf("�������:");
    for (i = 1; i <= G.vexnum; i++)
        printf("%c   ", G.vexs[i]);
    printf("\n\n�ڽӾ���:\n\n" );
 
    for (i = 1; i <= G.vexnum; i++) {
        for (j = 1; j <= G.vexnum; j++) {
        	if(G.arcs[i][j] == INFINITY)
        		printf("��\t");
        	else
           		printf("%d\t", G.arcs[i][j]);
        }
        printf("\n");
    }
}
 
 
// ����߽ṹ��
typedef struct{
    int start;
    int end;
    int cost;
}Edge;

/*���ڽӾ���õ��ߵ���Ϣ */
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

 
/*���߰�Ȩֵ�Ӵ�С����*/
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

/*�ҳ�ָ���ڵ����������ͨ�������������ҳ�����ڵ���father�������±ꡣ*/ 
int find_mset(int father[],int v){
    int t = v;
    while(father[t] != -1)
        t = father[t];
    return t;
}
 
/*Kruskal�㷨����С������*/
void Kruskal_G(Graph G,Edge edge[]){
    int father[MAX_VEX_NUM];
    int i,count,vf1,vf2;
    // ��ʼ��father����
    for(i = 0;i < MAX_VEX_NUM;i++){
        father[i] = -1;
    }
    i = 0;
    count = 0; // ͳ�Ƽ�����С�����еı���,���n-1���� 
    // ���������������֮��ı�
    while(i < G.arcnum && count < G.vexnum-1){
        vf1 = find_mset(father,edge[i].start);
        vf2 = find_mset(father,edge[i].end);
        // ����������ڵ㲻����ͬһ����ͨ�����������ͬһ����ͨ����
        if (vf1 != vf2){
            father[vf2] = vf1;		//merge_mfset�ϲ� 
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
    
    printf("Kruskal�㷨���:\n");
    Kruskal_G(G,edge);
    return 0;
}
