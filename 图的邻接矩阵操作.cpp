#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20   //��󶥵���
#define MAX MAX_VERTEX_NUM
 
#define INFINITY INT_MAX
 
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

typedef int Status;
 
/*----------------�õ������ݽṹ---��-------------------*/
typedef char QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct  {
	QueuePtr front;  //��ͷ
	QueuePtr rear;  //��β
}LinkQueue;

Status InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
 
Status EnQueue(LinkQueue &Q, QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}
 
Status DeQueue(LinkQueue &Q, QElemType &e){
	if(Q.front == Q.rear)
		return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}
 
int EmptyQueue(LinkQueue &Q){
	if(Q.front == Q.rear )
		return TRUE;
	return FALSE;
}
 
/*---------------------���ݽṹ--ͼ-----------------*/
 
 
 
typedef int VRType;//�����ϵ����
typedef int InfoType;  
typedef char VertexType; //����ֵ����
typedef enum{DG, DN, UDG, UDN}GraphKind;  //{����ͼ��������������ͼ��������}

typedef struct ArcCell{
	VRType adj;  //VRType�Ƕ����ϵ���ͣ�����Ȩͼ����1��0��ʾ���ڷ�
				//�Դ�Ȩͼ����ΪȨֵ����
	InfoType *info;  //�û������Ϣ��ָ��
}ArcCell, AdjMatric[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 
typedef struct  {
	VertexType vexs[MAX_VERTEX_NUM];  //��������
	AdjMatric arcs;  //�ڽӾ���
	int vexnum, arcnum;  //ͼ�ĵ�ǰ�������뻡��
	GraphKind kind;  //ͼ�������־
}MGraph;
 
bool visited[MAX];  //���ʱ�־����
Status (*VisitFunc)(MGraph &G,int v);  //��������

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ͼ�Ļ������� >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 

int LocateVex(const MGraph &G, VertexType u){
	//��ʼ������ͼG���ڣ�u��G�ж�������ͬ����
	//�����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
	for(int i=0; i < G.vexnum; ++i)
	{
		if(u == (G.vexs[i]))
			return i;
	}
	return -1;
}

void DisplayVexValue(const MGraph &G){
	//��ʾ���еĶ���
	printf("����Ϊ��");
	for(int i=0; i < G.vexnum; ++i)
		printf("%c\t",G.vexs[i]);
	printf("\n");
}
 
void DisplayAdjMatrix(const MGraph &G){
	//����ڽӾ���
	printf("\n�ڽӾ���Ϊ��\n");
	for(int i=0; i<G.vexnum; ++i){
		for(int j=0; j<G.vexnum; ++j){
			if(G.arcs[i][j].adj==INFINITY){
				printf("��\t");
			}
			else{
				printf("%d\t",G.arcs[i][j].adj);
			}
		}
		printf("\n");
	}
}

Status PutVex(MGraph &G,int v, VertexType value){
	//��ʼ������ͼG���ڣ�v��G��ĳ����������
	//�����������v��ֵvalue
	if(v >= G.vexnum || v < 0)
		return ERROR;
	G.vexs[v] = value;
	return OK;
}

Status InsertVex(MGraph &G, VertexType v){
	//��ʼ������ͼG���ڣ�v��ͼGĳ����������ͬ������
	//�����������ͼG�������¶���v����ʱ�����ӹ�ϵ��
	int i;
	G.vexs[G.vexnum] = v;  //���ڶ���ֵ
	for(i=0; i <=G.vexnum; ++i)
	{
		if(G.kind%2==0)//ͼ
		{
			G.arcs[G.vexnum][i].adj = 0;
			G.arcs[i][G.vexnum].adj = 0;
		}
		else  //��
		{
			G.arcs[G.vexnum][i].adj = INFINITY;
			G.arcs[i][G.vexnum].adj = INFINITY;
		}
	}
	G.arcs[G.vexnum][i].info = NULL; //��ʼ���û��������Ϣ
	G.arcs[i][G.vexnum].info = NULL; //��ʼ���û��������Ϣ
	G.vexnum++;
	
	return OK;
}
 
Status DeleteVex(MGraph &G, VertexType v){
	//��ʼ������ͼG���ڣ�v��G��ĳ������
	//���������ɾ��G�ж���v������صĻ�
	int k = LocateVex(G,v);
	if(k == -1)
		return ERROR; //�޴˽��
	//1.�Ӷ���������ɾ���ö���
	int i,j;
	for(i=k; i < G.vexnum-1; ++i)
	{
		G.vexs[i] = G.vexs[i+1];
	}
 
	//2.ɾ���ߵĹ�ϵ
	for(i=k; i < G.vexnum-1; ++i)
	{
		for(j=0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = G.arcs[i+1][j].adj;
			//��Ϊû���軡�������Ϣ���Ͳ�����G.arcs[][].info��
		}
	}
	for(j=k; j < G.vexnum-1; ++j)
	{
		for(i=0; i < G.vexnum; ++i)
		{
			G.arcs[i][j].adj = G.arcs[i][j+1].adj;
			//��Ϊû���軡�������Ϣ���Ͳ�����G.arcs[][].info��
		}
	}
 
	--G.arcnum;  //������1
	--G.vexnum;  //��������1
	return OK;
}
 
Status InsertArc(MGraph &G, VertexType v, VertexType w){
	//��ʼ������ͼG���ڣ�v��w��G����������
	//�����������G������<v,w>����������ģ�������Գƻ�
	int k1= LocateVex(G,v);
	int k2= LocateVex(G,w);
	if(k1==-1 || k2==-1)
		return ERROR;  //ͼ�в�����v��w
	if(G.kind%2 == 1)//��
	{
		printf("������û���Ȩֵ:");
		scanf("%d",&G.arcs[k1][k2].adj);
	}
	else // ͼ
	{
		G.arcs[k1][k2].adj = 1;
	}
 
	if(G.kind > 1) //����
	{
		G.arcs[k2][k1].adj = G.arcs[k1][k2].adj;
	}
	++G.arcnum;  //������1
	return OK;
	
}
 
Status DeleteArc(MGraph &G, VertexType v, VertexType w){
	//��ʼ������ͼG���ڣ�v��w��G����������
	//�����������G��ɾ����<v,w>����������ģ���ɾ���Գƻ�
	int k1= LocateVex(G,v);
	int k2= LocateVex(G,w);
	if(k1==-1 || k2==-1)
		return ERROR;  //ͼ�в�����v��w
	if(G.kind%2 == 1)//��
	{
		G.arcs[k1][k2].adj = INFINITY;
	}
	else // ͼ
	{
		G.arcs[k1][k2].adj = 0;
	}
	
	if(G.kind > 1) //����
	{
		G.arcs[k2][k1].adj = G.arcs[k1][k2].adj;
	}
	--G.arcnum;  //������1
	return OK;
 
}

 //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ͼ�Ĵ���>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 
Status CreateDG(MGraph &G){
	//��������ͼ
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG
	printf("����������ͼ�Ķ����������:\n");
	scanf("%d%d",&G.vexnum, &G.arcnum);  
	int i,j;
	printf("������%d�������ֵ:\n",G.vexnum);
	getchar();//ȡ���������еĻس���
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%c",&G.vexs[i]);
	}
	//scanf("%*c"); //�����������еĻس���
	//char buffer = getchar(); //ȡ���������еĻس���
	for(i=0; i<G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;  //��ʾͼ
			G.arcs[i][j].info = NULL;  //��ʾ�ޱߵ������Ϣ
		}
	}
	int k;
	VertexType v1, v2;//�������ʱ�洢����
	for(k=0; k<G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ���:\n", k+1);
		getchar(); //ȡ���������еĻس���
		scanf("%c%c",&v1, &v2); //%*c  �����س���
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //�޴˶��㣬����ʧ�ܣ����س�����Ϣ
		G.arcs[i][j].adj = 1;
		//��Ϊ��û�������������Ϣ��G.arcs[i][j].info== NULL�����ֲ���
	}
	G.kind = DG;  //����ͼ
	return OK;
}
 
Status CreateDN(MGraph &G){
	//�������飨�ڽӾ��󣩱�ʾ��������������G
	printf("�������������Ķ������������\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	getchar();//ȡ���������еĻس���
	int i,j;
	printf("������%d�������ֵ:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)//���춥������
	{
		scanf("%c",&G.vexs[i]);
	}
	for(i=0; i<G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;  
			G.arcs[i][j].info = NULL;  //��ʾ�ޱߵ������Ϣ
		}
	}
	
	int k;
	VertexType v1, v2;//�������ʱ�洢����
	VRType w;  //�����ϵ����ʱ����Ȩֵ
	for(k=0; k<G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ��㼰Ȩֵ:\n", k+1);
		getchar();//ȡ���������еĻس���
		scanf("%c%c%d",&v1, &v2, &w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //�޴˶��㣬����ʧ�ܣ����س�����Ϣ
		G.arcs[i][j].adj = w;
		//��Ϊ��û�������������Ϣ��G.arcs[i][j].info== NULL�����ֲ���
	}
	G.kind = DN;  //������
	return OK;
}
 
Status CreateUDG(MGraph &G){
	//��������ͼ
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG
	printf("����������ͼ�Ķ����������:\n");
	scanf("%d%d",&G.vexnum, &G.arcnum);  
	int i,j;
	printf("������%d�������ֵ:\n",G.vexnum);
	getchar();//ȡ���������еĻس���
	for(i = 0; i < G.vexnum; ++i)
	{
		scanf("%c",&G.vexs[i]);
	}
	//scanf("%*c"); //�����������еĻس���
	//char buffer = getchar(); //ȡ���������еĻس���
	for(i=0; i<G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = 0;  //��ʾͼ
			G.arcs[i][j].info = NULL;  //��ʾ�ޱߵ������Ϣ
		}
	}
	int k;
	VertexType v1, v2;//�������ʱ�洢����
	for(k=0; k<G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ���:\n", k+1);
		getchar(); //ȡ���������еĻس���
		scanf("%c%c",&v1, &v2); //%*c  �����س���
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //�޴˶��㣬����ʧ�ܣ����س�����Ϣ
		G.arcs[i][j].adj = 1;
		G.arcs[j][i].adj = G.arcs[i][j].adj;  //�Գƻ�����Ϣ
		//��Ϊ��û�������������Ϣ��G.arcs[i][j].info== NULL�����ֲ���
	}
	G.kind = UDG;  //����ͼ
	return OK;
}
 
 
Status CreateUDN(MGraph &G){
	//�������飨�ڽӾ��󣩱�ʾ��������������G
	printf("�������������Ķ������������\n");
	scanf("%d %d",&G.vexnum, &G.arcnum);
	getchar();//ȡ���������еĻس���
	int i,j;
	printf("������%d�������ֵ:\n",G.vexnum);
	for(i=0; i<G.vexnum; ++i)//���춥������
	{
		scanf("%c",&G.vexs[i]);
	}
	for(i=0; i<G.vexnum; ++i)  //��ʼ���ڽӾ���
	{
		for(j=0; j<G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;  
			G.arcs[i][j].info = NULL;  //��ʾ�ޱߵ������Ϣ
		}
	}
 
	int k;
	VertexType v1, v2;//�������ʱ�洢����
	VRType w;  //�����ϵ����ʱ����Ȩֵ
	for(k=0; k<G.arcnum; ++k) //�����ڽӾ���
	{
		printf("�������%d���������Ķ��㼰Ȩֵ:\n", k+1);
		getchar();//ȡ���������еĻس���
		scanf("%c%c%d",&v1, &v2, &w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		if(i==-1 || j==-1)
			return ERROR;  //�޴˶��㣬����ʧ�ܣ����س�����Ϣ
		G.arcs[i][j].adj = w;
		//��Ϊ��û�������������Ϣ��G.arcs[i][j].info== NULL�����ֲ���
		G.arcs[j][i].adj = G.arcs[i][j].adj;  //��<v1,v2>�ĶԳƻ�<v2,v1>;
	}
	G.kind = UDN;  //������
	return OK;
}
 
Status CreateGraph(MGraph &G){
	//����ͼG
	printf("�����빹������ͣ�(0:����ͼ,1:��������2:����ͼ��3:������):");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
	case DG:return CreateDG(G);  //��������ͼ
	case DN:return CreateDN(G);  //����������
	case UDG:return CreateUDG(G);  //��������ͼ
	case UDN:return CreateUDN(G);  //����������
	default:return ERROR;
	}
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ͼ�ı���>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
VertexType GetVex(MGraph &G, int v){
	//��ʼ������ͼG���ڣ�v��G��ĳ����������
	//��������������ڣ��򷵻���ֵ,���򷵻ؿ�
	if(v >= G.vexnum || v < 0)
		return NULL;
	return G.vexs[v];
} 

 
int FirstAdjVex(MGraph &G, VertexType v){
	//��ʼ������ͼG���ڣ�v��G��ĳ������
	//�������������v�ĵ�һ���ڽӶ��㣬��������G��û���ڽӶ��㣬�򷵻�"��"
	int k = LocateVex(G,v);
	if(k == -1)//�޴˶���
		return -1;
	int adjValue = 0;
	if(G.kind == DN || G.kind == UDN)
		adjValue = INFINITY;
	
	for(int i=0; i < G.vexnum; ++i)
	{
		if(G.arcs[k][i].adj != adjValue)
			return i;
	}
	return -1;
}
 
int NextAdjVex(MGraph &G, VertexType v, VertexType w){
	//��ʼ������ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ���
	//�������������v�ģ������w�ģ���һ���ڽӶ��㡣��w��v�����һ���ڽӵ㣬�򷵻ء��ա�
	int k1=LocateVex(G,v);
	int k2=LocateVex(G,w);
 
	if(k1 == -1 || k2 == -1)//�޴˶���
	{
		return -1;
	}
	int adjValue = 0; 
	if(G.kind == DN || G.kind == UDN)
		adjValue = INFINITY;
	for(int i=k2+1; i < G.vexnum; ++i)
	{
		if(G.arcs[k1][i].adj != adjValue)
		{
			return i;
		}
	}
	return -1;
 
}

void DFS(MGraph &G, int v){
	//�ӵ�v����������ݹ��������ȱ���ͼG
	visited[v] = TRUE;
	VisitFunc(G,v);  //���ʵ�v������
	for(int w = FirstAdjVex(G,GetVex(G,v)); w >= 0; w = NextAdjVex(G,GetVex(G,v),GetVex(G,w)))
		if(!visited[w])
			DFS(G,w);  //��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}

void DFSTraverse(MGraph &G, Status(*Visit)(MGraph &G,int v)){//��ͼ��������ȱ���
	VisitFunc = Visit;  //ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
	for(int v=0; v < G.vexnum; ++v)
	{
		visited[v] = FALSE;  //���ʱ�־�����ʼ��
	}
	for(int v= 0; v < G.vexnum; ++v)
	{
		if(!visited[v])
			DFS(G,v);  //����δ���ʵĶ������DFS
	}
}
 
void BFSTraverse(MGraph &G, Status(*VisitVex)(MGraph &G,int v)){//��ͼ��������ȱ���
	int BFSvisited[MAX],i;
	for(i = 0; i<G.vexnum; ++i)
		BFSvisited[i] = FALSE;//��ʼ��������������,��ʼ�����Ϊδ���ʵı�־
	LinkQueue Q;
	InitQueue(Q); //��ʼ����������Q
	for(i=0; i < G.vexnum; ++i)
		if(!BFSvisited[i]){//���Ϊi�Ķ���δ����
			BFSvisited[i] = TRUE;
			VisitVex(G,i);
			EnQueue(Q,GetVex(G,i));//���Ϊi�Ķ������
			while(!EmptyQueue(Q)){
				QElemType u;
				DeQueue(Q,u);
				for(int w=FirstAdjVex(G,u); w >=0; w=NextAdjVex(G,u,GetVex(G,w)))
					if(!BFSvisited[w]){
						BFSvisited[w] = TRUE;
						VisitVex(G,w);
						EnQueue(Q,GetVex(G,w));
					}
			}
		}
}
 
Status VisitVex(MGraph &G,int v){
	//�������Ϊv�Ķ���
	printf("%3c",G.vexs[v]);
	return OK;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>��С������>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 

typedef struct closedg{
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

int minimum(closedge close,int n){
	int min=INFINITY,k=0,i;
    for(i=0;i<n;i++)
    {
        if(close[i].lowcost != 0 && close[i].lowcost < min)
        {
            min = close[i].lowcost;
            k = i;
        }
    }	
	return k; 
} 

void MiniSpanTree_PRIM(MGraph G,VertexType u){
	//������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߡ�
	//��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨�壺 
	closedge close;
	int k=LocateVex(G,u);
	for(int j=0;j<G.vexnum;++j){		//���������ʼ�� 
		if(j!=k){
			close[j].adjvex=u;
			close[j].lowcost=G.arcs[k][j].adj;
		}
	}
	close[k].lowcost=0;			//��ʼ��U={u}
	for(int i=1;i<G.vexnum;++i)		//ѡ������G.vexnum-1������ 
	{
		k=minimum(close,G.vexnum);			//���T����һ���ڵ㣺��k���� 
		//��ʱclose[k].lowcost=
			//Min{close[vi].lowcost | close[vi].lowcost>0,vi��V-U 
		printf("%c---->%d<----%c\n",close[k].adjvex,close[k].lowcost,G.vexs[k]);		//����������ı� 
		close[k].lowcost=0;			//��k���㲢��U�� 
		for(int j=0;j<G.vexnum;++j)
		{
			if(G.arcs[k][j].adj<close[j].lowcost)		//�µĶ��㲢��U������ѡ����С�ߡ�
			{
				close[j].adjvex=G.vexs[k];
				close[j].lowcost=G.arcs[k][j].adj;
			} 
		}
	} 
}
 
void Panel()
{
	//�����˵�
	printf("\n");
	printf("\t\t----------------------------------------------\n");
	printf("\t\t---------------------ͼ�Ĳ���-----------------\n\n");
	printf("\t\t     0-����ͼ              1-�鿴������Ϣ     \n");
	printf("\t\t     2-����ָ�������ֵ    3-���붥��         \n");
	printf("\t\t     4-ɾ������            5-���뻡           \n");
	printf("\t\t     6-ɾ����              7-������ȱ���ͼ   \n");
	printf("\t\t     8-������ȱ���ͼ      9-�鿴ͼ���ڽӾ��� \n");
	printf("\t\t     10-��С��������prim�㷨��     11-�˳�  \n\n");
	printf("\t\t---------------------ͼ�Ĳ���-----------------\n");
	printf("\t\t----------------------------------------------\n");
}
 
int main(int argc,char **argv){
	MGraph G;
	int n;
	int i;
	VertexType v,w;
	VertexType u;
	while(1)
	{
		Panel();
		printf("�����������:");
		scanf("%d",&n);
		getchar();
		switch(n)
		{
			case 0://����ͼ
				if(CreateGraph(G))
					printf("�����ɹ�\n");
				else
					printf("����ʧ��\n");
				break;
			case 1://�鿴������Ϣ
				DisplayVexValue(G);
				break;
			case 2://����ָ�������ֵ
				printf("��������Ķ������ţ�");
				scanf("%d",&i);
				getchar();
				printf("�����붥�����ֵ��");
				scanf("%c",&v);
				getchar();
				PutVex(G,i,v);
				break;
			case 3://���붥��
				printf("����������Ҫ���붥���ֵ��");
				scanf("%c",&v);
				getchar();
				InsertVex(G,v);
				break;
			case 4://ɾ������
				printf("����������Ҫɾ���Ķ����ֵ��");
				scanf("%c",&v);
				getchar();
				DeleteVex(G,v);
				break;
			case 5://���뻡
				printf("���룺�����뻡���������������ֵ��");
				scanf("%c%c",&v,&w);
				getchar();
				InsertArc(G,v,w);
				break;
			case 6://ɾ���� 
				printf("ɾ���������뻡���������������ֵ��");
				scanf("%c%c",&v,&w);
				getchar();
				DeleteArc(G,v,w);
				break;
			case 7://������ȱ���ͼ
				printf("������ȱ����Ľ��Ϊ��\n");
				DFSTraverse(G,VisitVex);
				printf("\n");
				break;
			case 8://������ȱ���ͼ
				printf("������ȱ����Ľ��Ϊ��\n");
				BFSTraverse(G,VisitVex);
				printf("\n");
				break;
			case 9://�鿴ͼ���ڽӾ���
				DisplayAdjMatrix(G);
				break;
			case 10://��С������ 
				if(G.kind==UDN){
					printf("��������Ҫ��ʼ�����Ķ���:\n");
//					getchar();
					scanf("%c",&u); 
					MiniSpanTree_PRIM(G,u);
					}
				break;
			case 11://�˳�
				exit(OVERFLOW);
				break;
			default:
				printf("�޴˲���\n");	
		}
	}
	return 0;
}
