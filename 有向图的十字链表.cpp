#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_VERTEX_NUM 20
#define OVERFLOW -2
#define OK 1

typedef int Status;
typedef char VertexType[MAX_VERTEX_NUM];
typedef char InfoType;

typedef struct ArcBox{
	int tailvex,headvex;  //该弧的尾和头顶点的位置
	struct ArcBox *hlink, *tlink;  //分别为弧头相同和弧尾相同的弧的链域
	InfoType *info;  //该弧的相关信息的指针
 
}ArcBox;//弧结点                                                                 
 
typedef struct VexNode{
	VertexType data;
	ArcBox *firstin, *firstout;  //分别指向该顶点的第一条入弧和出弧
}VexNode;  //顶点结点
 
typedef struct  {
	VexNode xlist[MAX_VERTEX_NUM];  //表头向量
	int vexnum, arcnum;  //有向图的当前顶点数和弧数
}OLGraph;
 
int LocateVex(OLGraph &G, VertexType u){
	for(int i = 0; i < G.vexnum; ++i)
		if(strcmp(G.xlist[i].data, u) == 0)
			return i;
	return -1;
}
 
Status CreateDG(OLGraph &G){
	//采用十字链表存储表示，构造有向图G;
	int i,j,k;
	printf("请输入有向图的顶点数以及弧数:");
	scanf("%d%d",&G.vexnum, &G.arcnum);
	
	printf("请输入%d个顶点的值，之间有空格隔开:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i) //构造表头向量
	{
		getchar();
		scanf("%s",G.xlist[i].data);  //输入顶点值
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
	}
	
	VertexType v1,v2;
	ArcBox *p;
	printf("请依次输入%d条弧各自依附的两个顶点（输入格式:v1 v2<Enter>）\n",G.arcnum);
	for(k=0; k < G.arcnum; ++k)  //输入各弧并构造十字链表
	{
		getchar();
		scanf("%s%s",v1,v2);
		
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));
		if(!p)
			exit(OVERFLOW);
		
		p->tailvex = i;
		p->headvex = j;
		
		p->hlink = G.xlist[j].firstin;
		p->tlink = G.xlist[i].firstout;
		
		p->info = NULL;
		G.xlist[j].firstin = G.xlist[i].firstout = p;  //完成在入弧和出弧链头的插入
	}
	getchar();
	return OK;
}
 
void DisplayArc(OLGraph &G){
	ArcBox *p;
	for(int i=0; i < G.vexnum; ++i)
	{
		p=G.xlist[i].firstout;
		while(p)
		{
			printf("<%s,%s> ",G.xlist[p->tailvex].data, G.xlist[p->headvex].data);
			p = p->tlink;
		}
		printf("\n"); 
	}
	printf("\n");
}
 
int VexDegree1(OLGraph &G, VertexType v){
	//求指点v的入度
	int k = LocateVex(G,v);
	if(k<0)
		exit(OVERFLOW);
	int id=0;  //入度
 
	ArcBox *pin = G.xlist[k].firstin;
	while(pin)  //求入度
	{
		++id;
		pin = pin->hlink;
	}
	return id; //顶点的入度
}

int VexDegree2(OLGraph &G, VertexType v){
	//求指点v的出度
	int k = LocateVex(G,v);
	if(k<0)
		exit(OVERFLOW);
	int od=0;  //入度，出度
	ArcBox *pout = G.xlist[k].firstout;
	while(pout)  //求出度
	{
		++od;
		pout = pout->tlink;
	}
 
	return od; //顶点的出度
}

int VexDegree(OLGraph &G, VertexType v){
	//求指点v的度：入度+出度
	int id=0,od=0;  //入度，出度
	id=VexDegree1(G,v);
	od=VexDegree2(G,v);
	return id+od; //顶点的度
}
 
int main(int argc,char **argv){
	OLGraph G;
	CreateDG(G);
 
	printf("输入该有向图的所有弧:\n");
	DisplayArc(G);
	VertexType v;
	while(1)
	{
		printf("请输入你要求度的顶点:");
		scanf("%s",v);
		getchar();
		printf("顶点%s的度为:%d\n其中入度为:%d,出度为:%d\n",v,VexDegree(G,v),VexDegree1(G,v),VexDegree2(G,v));
	}
	
	return 0;
}
