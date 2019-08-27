#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef char InfoType;
typedef char VertexType[MAX_VERTEX_NUM];

typedef enum{unvisited, visited}VisitIf;

typedef struct EBox{
	VisitIf mark;  //访问标记
	int ivex, jvex;  //该边依附的两个顶点的位置
	struct EBox *ilink, *jlink;  //分别指向依附这两个顶点的下一条边
	InfoType *info;  //该边信息指针
}EBox;//边结点
 
typedef struct VexBox{
	VertexType data;
	EBox *firstedge;  //指向第一条依附该顶点的边
}VexBox;  //顶点结点
 
typedef struct {
	VexBox adjmulist[MAX_VERTEX_NUM];  
	int vexnum, edgenum;  //无向图的当前顶点数和边数
}AMLGraph;  //图
 
int LocateVex(AMLGraph &G, VertexType v){
	for(int i=0; i < G.vexnum; ++i)
	{
		if(strcmp(G.adjmulist[i].data, v) == 0)
			return i;
	}
	return -1;
}
 
void CreateUDG(AMLGraph &G){
	//采用邻接多重表存储表示，构造无向图G
	printf("\n创建无向图...\n\n");
	printf("请输入图的顶点个数与边数:");
	scanf("%d%d",&G.vexnum, &G.edgenum);
	int k,i,j;
	printf("请输入%d个顶点的值，之间用空格隔开:\n",G.vexnum);
	for(k=0; k < G.vexnum; ++k)
	{
		getchar();
		scanf("%s",G.adjmulist[k].data);
		G.adjmulist[k].firstedge = NULL;
	}
	printf("请输入%d条边所依附的顶点，格式(V1 V2<Enter>):\n",G.edgenum);
	VertexType v1,v2;
	EBox *p;
	for(k=0; k < G.edgenum; ++k)
	{
		getchar();
		scanf("%s%s",v1,v2);
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		if(i<0 || j < 0)
			exit(OVERFLOW);
			
		p = (EBox *)malloc(sizeof(EBox));
		if(!p)
			exit(OVERFLOW);
		
		p->ivex = i;  //对边结点开始赋值(mark,ivex,jvex,ilink,jlink,info)
		p->jvex = j;
		
		p->ilink = G.adjmulist[i].firstedge;  
		p->jlink = G.adjmulist[j].firstedge;
		
		p->info = NULL;
		p->mark = unvisited;
		G.adjmulist[i].firstedge = G.adjmulist[j].firstedge = p; //顶点指向其第一条依附的边
 
	}
	printf("恭喜，创建成功!\n");
}
 
void DisplayEdge(AMLGraph G){
	//输出各边
	int k;
	EBox *p;
	for(k=0; k < G.vexnum; ++k)
	{
		p = G.adjmulist[k].firstedge;
		while(p)
		{
			if(p->mark == unvisited)
			{
				printf("(%s,%s) ",G.adjmulist[p->ivex].data, G.adjmulist[p->jvex].data);
				p->mark = visited;
			}
			p=p->ilink;
		}
		printf("\n");
	}
	printf("\n");
 
	for(k=0; k < G.vexnum; ++k)  //将访问标志重新置为未访问的
	{
		p = G.adjmulist[k].firstedge;
		while(p)
		{
			if(p->mark == visited)
			{
				p->mark = unvisited;
			}
			p=p->ilink;
		}
	}
}
 
int main(int argc,char **argv){
	AMLGraph G;
	CreateUDG(G);
	DisplayEdge(G);
	return 0;
}
