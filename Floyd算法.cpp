#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#define INFINITY 65535       //����
#define MAXLIN 10

typedef struct Ver{           //��������
    char dian[5];
}VRType;

typedef struct Graph{
    VRType vexs[MAXLIN];            //������������
    int arcs[MAXLIN][MAXLIN];    //�ڽӾ���
    int vexnum,arcnum;        //����ͱߵ���Ŀ
}Graph;

int flag=0;
int flag1=0;

int LocateVex(Graph G,char cc[5])       //���ض�����ͼ�е�λ��
{
    for(int i=0;i<G.vexnum;i++)
        if(strcmp(G.vexs[i].dian,cc)==0)
            return i;
    return -1;
}

void InPut(Graph &G)        //����ͼ�����Ϣ
{
    flag1=1; 
    int i,j,k,w;
    char aa[5],bb[5];
    
    printf("*****************************\n");
    printf("****   ����ͼ�����Ϣ!   ****\n");
    printf("*****************************\n");
    
    printf("�����������:");
    scanf("%d",&G.vexnum);
    
    printf("���������֮���·����:");
    scanf("%d",&G.arcnum);
    
    printf("���������г�������(��:v1 v2 v3):");
    for(i=0;i<G.vexnum;i++)              
        scanf("%s",G.vexs[i].dian);
    
    for(i=0;i<G.vexnum;i++)                          //���ڽӾ����ʼ��  ʹ��ʼ���г���֮�䶼�ǲ��ɴ��
        for(j=0;j<G.vexnum;j++)
            G.arcs[i][j]=INFINITY;
    
    printf("���������·����·������:(�� v1 v2 4):\n");
    for(k=0;k<G.arcnum;k++)
    {
        printf("������----->");
        scanf("%s %s %d",aa,bb,&w);
        
        i=LocateVex(G,aa);
        j=LocateVex(G,bb);
        
        G.arcs[i][j]=w;
    }
    printf("�������!\n");
}
void ShortestPath_FLOYD(Graph &G,int P[MAXLIN][MAXLIN][MAXLIN],int D[MAXLIN][MAXLIN])        //����ͼ�����Ϣ
{
    if(flag1==0)
    {
        printf("δ�����йس���ͼ����Ϣ!���������ʹ�ñ�����!\n");
        return;
    }
    flag=1;
    printf("*****************************\n");
    printf("****   ����ͼ�����Ϣ!   ****\n");
    printf("*****************************\n");
    int u,v,w,i,j;
    for(v=0;v<G.vexnum;v++)                 //�Ե�ǰ��֪���ڵ�֮��·�� ���г�ʼ��
        for(w=0;w<G.vexnum;w++)
        {
            D[v][w]=G.arcs[v][w];
            for(u=0;u<G.vexnum;u++)
                P[v][w][u]=-1;
            if(D[v][w]<INFINITY)           //��������֮������
            {
                P[v][w][0]=v;
                P[v][w][1]=w;
            }
        }

    for(u=0;u<G.vexnum;u++)
        for(v=0;v<G.vexnum;v++)
            for(w=0;w<G.vexnum;w++)
                if(D[v][u] < INFINITY && D[u][w] < INFINITY && D[v][u]+D[u][w] < D[v][w])
                {
                    //����D
                    D[v][w]=D[v][u]+D[u][w];
                    //����P����v��w��·���Ǵ�v��u���ٴ�u��w
                    for(i=0;i<G.vexnum;i++)
                    {
                        if(P[v][u][i]!=-1)
                            P[v][w][i]=P[v][u][i];
                        else
                            break;
                    }
                    for(j=1;j<G.vexnum;j++)    //����j���Ǵ�0��ʼ�ģ���Ϊv��u�����һ�����㼴��u
                    {
                        if(P[u][w][j]!=-1)
                            P[v][w][i++]=P[u][w][j];
                        else
                            break;
                    }
                }
        printf("�������!\n");
}
void Look1(Graph &G)
{
    printf("���е��������ڽӾ���Ϊ:\n");
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++){
        	if(G.arcs[i][j] == INFINITY)
				printf("\t��");
			else 
           		printf("\t%d",G.arcs[i][j]);
    	}
        printf("\n");
    }
}
void Look2(Graph &G)
{
    int n;
    
    printf("����ͼ�Ļ�����ϢΪ:");
    printf("������Ϊ:%d\n",G.vexnum);
    printf("����֮������·����Ϊ:%d\n",G.arcnum);
    printf("·�����Ƿ���ͨ������:\n");
    
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
        {
            if(G.arcs[i][j]==INFINITY)
                n=0;
            else
                n=1;
            printf("\t(%s,%s),%d,%d",G.vexs[i].dian,G.vexs[j].dian,n,G.arcs[i][j]);
        }
        printf("\n");
    }
}
void Look(Graph &G)         //�鿴ͼ�����Ϣ
{
    if(flag1==0)
    {
        printf("δ�����йس���ͼ����Ϣ!���������ʹ�ñ�����!\n");
        return;
    }
    int choice2;
    
    printf("*****************************\n");
    printf("****   �鿴ͼ�����Ϣ!   ****\n");
    printf("*****************************\n");
    
    while(true)
    {
        printf("\n-- �鿴�������ڽӾ��������� -->1\n");
        printf("-- �鿴����ͼ������Ϣ������ -->2\n");
        printf("--      �˳��鿴������      -->0\n");
        scanf("%d",&choice2);
        switch(choice2)
        {
        case 1:        
			Look1(G);
            break;
        case 2:
		    Look2(G);
            break;
        case 0: 
			return;
        }
    }
    
}
void Refer(Graph &G,int P[MAXLIN][MAXLIN][MAXLIN],int D[MAXLIN][MAXLIN])            //��ѯͼ�����Ϣ
{
    if(flag==0)
    {
        printf("ͼ�����Ϣδ����!,�����ɺ���ʹ�ñ�����!\n");
        return;
    }
    int i,j;
    printf("*****************************\n");
    printf("****   ��ѯͼ�����Ϣ!   ****\n");
    printf("*****************************\n");
    printf("������������֮�����·�����ȼ����·��Ϊ:\n");     //���������������֮������·��
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            if(i!=j)
            {
                if(D[i][j]!=INFINITY)
                {
                    printf("%s��%s�����·��Ϊ:\t%d",G.vexs[i].dian,G.vexs[j].dian,D[i][j]);
                    printf("\t���·��Ϊ:");
                    for(int k=0;k<G.vexnum;k++)
                    {
                        if(P[i][j][k]!=-1)
                            printf("  %s",G.vexs[P[i][j][k]].dian);
                        else
                            break;
                    }
                    printf("\n");
                }
            }
        }
    }
    printf("\n");
}
void OutPut()         //�˳�����
{
    printf("*****************************\n");
    printf("****    ��л����ʹ��!    ****\n");
    printf("*****************************\n");
    return;
}
int main(int argc,char **argv){
    int choice;
    Graph G;
    int P[MAXLIN][MAXLIN][MAXLIN];  //P[v][w][i]��ʾ ��ǰ��õĶ���v��w�����·���ĵ�i+1������  ���Ǵ�ӡ���·���Ĺؼ�
    int D[MAXLIN][MAXLIN];          //D[v][w]��ʾ ��ǰ��õ� ����v������w�����·���ĳ���
    while(true){
		printf("\n-----��ӭʹ�ø���������������·���ĳ���-----\n");    //������
        printf("-----�������ͼ�������Ϣ   ������:1\n");
        printf("-----���ɳ���ͼ�������Ϣ   ������:2\n");
        printf("-----�鿴����ͼ�������Ϣ   ������:3\n");
        printf("-----��ѯ����ͼ�������Ϣ   ������:4\n");
        printf("-----�˳��˳���             ������:0\n");
        printf("���������Ĳ���ѡ��:");
        while(scanf("%d",&choice))                                        //�쳣����
        {
            if(choice<0||choice>4)
                printf("������������������0~4֮�ڵ�����������������!\n");
            else
                break;
        }
        switch(choice)
        {
	        case 1:        InPut(G);      //���            �������ͼ�������Ϣ 
	            break;
	        case 2:        ShortestPath_FLOYD(G,P,D);    //���         ���ɳ���ͼ�������Ϣ    
	            break;
	        case 3:        Look(G);     //���            �鿴����ͼ�������Ϣ
	            break;
	        case 4:        Refer(G,P,D);      //���      ��ѯ����ͼ�������Ϣ 
	            break;
	        case 0:        OutPut();    //���            �˳��˳��� 
	            exit(0);
        }
    }
    return 0;
}


