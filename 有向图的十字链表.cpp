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
	int tailvex,headvex;  //�û���β��ͷ�����λ��
	struct ArcBox *hlink, *tlink;  //�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType *info;  //�û��������Ϣ��ָ��
 
}ArcBox;//�����                                                                 
 
typedef struct VexNode{
	VertexType data;
	ArcBox *firstin, *firstout;  //�ֱ�ָ��ö���ĵ�һ���뻡�ͳ���
}VexNode;  //������
 
typedef struct  {
	VexNode xlist[MAX_VERTEX_NUM];  //��ͷ����
	int vexnum, arcnum;  //����ͼ�ĵ�ǰ�������ͻ���
}OLGraph;
 
int LocateVex(OLGraph &G, VertexType u){
	for(int i = 0; i < G.vexnum; ++i)
		if(strcmp(G.xlist[i].data, u) == 0)
			return i;
	return -1;
}
 
Status CreateDG(OLGraph &G){
	//����ʮ������洢��ʾ����������ͼG;
	int i,j,k;
	printf("����������ͼ�Ķ������Լ�����:");
	scanf("%d%d",&G.vexnum, &G.arcnum);
	
	printf("������%d�������ֵ��֮���пո����:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i) //�����ͷ����
	{
		getchar();
		scanf("%s",G.xlist[i].data);  //���붥��ֵ
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
	}
	
	VertexType v1,v2;
	ArcBox *p;
	printf("����������%d���������������������㣨�����ʽ:v1 v2<Enter>��\n",G.arcnum);
	for(k=0; k < G.arcnum; ++k)  //�������������ʮ������
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
		G.xlist[j].firstin = G.xlist[i].firstout = p;  //������뻡�ͳ�����ͷ�Ĳ���
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
	//��ָ��v�����
	int k = LocateVex(G,v);
	if(k<0)
		exit(OVERFLOW);
	int id=0;  //���
 
	ArcBox *pin = G.xlist[k].firstin;
	while(pin)  //�����
	{
		++id;
		pin = pin->hlink;
	}
	return id; //��������
}

int VexDegree2(OLGraph &G, VertexType v){
	//��ָ��v�ĳ���
	int k = LocateVex(G,v);
	if(k<0)
		exit(OVERFLOW);
	int od=0;  //��ȣ�����
	ArcBox *pout = G.xlist[k].firstout;
	while(pout)  //�����
	{
		++od;
		pout = pout->tlink;
	}
 
	return od; //����ĳ���
}

int VexDegree(OLGraph &G, VertexType v){
	//��ָ��v�Ķȣ����+����
	int id=0,od=0;  //��ȣ�����
	id=VexDegree1(G,v);
	od=VexDegree2(G,v);
	return id+od; //����Ķ�
}
 
int main(int argc,char **argv){
	OLGraph G;
	CreateDG(G);
 
	printf("���������ͼ�����л�:\n");
	DisplayArc(G);
	VertexType v;
	while(1)
	{
		printf("��������Ҫ��ȵĶ���:");
		scanf("%s",v);
		getchar();
		printf("����%s�Ķ�Ϊ:%d\n�������Ϊ:%d,����Ϊ:%d\n",v,VexDegree(G,v),VexDegree1(G,v),VexDegree2(G,v));
	}
	
	return 0;
}
