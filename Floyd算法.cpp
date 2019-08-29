#include<stdio.h>

#include<stdlib.h>
#include<string.h>
#define INFINITY 65535       //无穷
#define MAXLIN 10

typedef struct Ver{           //顶点向量
    char dian[5];
}VRType;

typedef struct Graph{
    VRType vexs[MAXLIN];            //顶点向量数组
    int arcs[MAXLIN][MAXLIN];    //邻接矩阵
    int vexnum,arcnum;        //顶点和边的数目
}Graph;

int flag=0;
int flag1=0;

int LocateVex(Graph G,char cc[5])       //返回顶点在图中的位置
{
    for(int i=0;i<G.vexnum;i++)
        if(strcmp(G.vexs[i].dian,cc)==0)
            return i;
    return -1;
}

void InPut(Graph &G)        //输入图相关信息
{
    flag1=1; 
    int i,j,k,w;
    char aa[5],bb[5];
    
    printf("*****************************\n");
    printf("****   输入图相关信息!   ****\n");
    printf("*****************************\n");
    
    printf("请输入城市数:");
    scanf("%d",&G.vexnum);
    
    printf("请输入城市之间的路径数:");
    scanf("%d",&G.arcnum);
    
    printf("请输入所有城市名称(如:v1 v2 v3):");
    for(i=0;i<G.vexnum;i++)              
        scanf("%s",G.vexs[i].dian);
    
    for(i=0;i<G.vexnum;i++)                          //对邻接矩阵初始化  使开始所有城市之间都是不可达的
        for(j=0;j<G.vexnum;j++)
            G.arcs[i][j]=INFINITY;
    
    printf("请输入城市路径和路径长度:(如 v1 v2 4):\n");
    for(k=0;k<G.arcnum;k++)
    {
        printf("请输入----->");
        scanf("%s %s %d",aa,bb,&w);
        
        i=LocateVex(G,aa);
        j=LocateVex(G,bb);
        
        G.arcs[i][j]=w;
    }
    printf("输入完毕!\n");
}
void ShortestPath_FLOYD(Graph &G,int P[MAXLIN][MAXLIN][MAXLIN],int D[MAXLIN][MAXLIN])        //生成图相关信息
{
    if(flag1==0)
    {
        printf("未输入有关城市图的信息!请输入后再使用本功能!\n");
        return;
    }
    flag=1;
    printf("*****************************\n");
    printf("****   生成图相关信息!   ****\n");
    printf("*****************************\n");
    int u,v,w,i,j;
    for(v=0;v<G.vexnum;v++)                 //对当前已知各节点之间路径 进行初始化
        for(w=0;w<G.vexnum;w++)
        {
            D[v][w]=G.arcs[v][w];
            for(u=0;u<G.vexnum;u++)
                P[v][w][u]=-1;
            if(D[v][w]<INFINITY)           //两个城市之间相连
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
                    //更新D
                    D[v][w]=D[v][u]+D[u][w];
                    //更新P，从v到w的路径是从v到u，再从u到w
                    for(i=0;i<G.vexnum;i++)
                    {
                        if(P[v][u][i]!=-1)
                            P[v][w][i]=P[v][u][i];
                        else
                            break;
                    }
                    for(j=1;j<G.vexnum;j++)    //这里j不是从0开始的，因为v到u的最后一个顶点即是u
                    {
                        if(P[u][w][j]!=-1)
                            P[v][w][i++]=P[u][w][j];
                        else
                            break;
                    }
                }
        printf("操作完毕!\n");
}
void Look1(Graph &G)
{
    printf("城市的有向网邻接矩阵为:\n");
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++){
        	if(G.arcs[i][j] == INFINITY)
				printf("\t∞");
			else 
           		printf("\t%d",G.arcs[i][j]);
    	}
        printf("\n");
    }
}
void Look2(Graph &G)
{
    int n;
    
    printf("城市图的基本信息为:");
    printf("城市数为:%d\n",G.vexnum);
    printf("城市之间所有路径数为:%d\n",G.arcnum);
    printf("路径，是否相通，长度:\n");
    
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
void Look(Graph &G)         //查看图相关信息
{
    if(flag1==0)
    {
        printf("未输入有关城市图的信息!请输入后再使用本功能!\n");
        return;
    }
    int choice2;
    
    printf("*****************************\n");
    printf("****   查看图相关信息!   ****\n");
    printf("*****************************\n");
    
    while(true)
    {
        printf("\n-- 查看有向网邻接矩阵请输入 -->1\n");
        printf("-- 查看城市图基本信息请输入 -->2\n");
        printf("--      退出查看请输入      -->0\n");
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
void Refer(Graph &G,int P[MAXLIN][MAXLIN][MAXLIN],int D[MAXLIN][MAXLIN])            //查询图相关信息
{
    if(flag==0)
    {
        printf("图相关信息未生成!,请生成后在使用本功能!\n");
        return;
    }
    int i,j;
    printf("*****************************\n");
    printf("****   查询图相关信息!   ****\n");
    printf("*****************************\n");
    printf("任意两个城市之间最短路径长度及最短路径为:\n");     //输出任意两个城市之间的最短路径
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            if(i!=j)
            {
                if(D[i][j]!=INFINITY)
                {
                    printf("%s到%s的最短路径为:\t%d",G.vexs[i].dian,G.vexs[j].dian,D[i][j]);
                    printf("\t最短路径为:");
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
void OutPut()         //退出程序
{
    printf("*****************************\n");
    printf("****    感谢您的使用!    ****\n");
    printf("*****************************\n");
    return;
}
int main(int argc,char **argv){
    int choice;
    Graph G;
    int P[MAXLIN][MAXLIN][MAXLIN];  //P[v][w][i]表示 当前求得的顶点v到w的最短路径的第i+1个顶点  这是打印最短路径的关键
    int D[MAXLIN][MAXLIN];          //D[v][w]表示 当前求得的 顶点v到顶点w的最短路径的长度
    while(true){
		printf("\n-----欢迎使用弗洛伊德求城市最短路径的程序-----\n");    //主界面
        printf("-----输入城市图的相关信息   请输入:1\n");
        printf("-----生成城市图的相关信息   请输入:2\n");
        printf("-----查看城市图的相关信息   请输入:3\n");
        printf("-----查询城市图的相关信息   请输入:4\n");
        printf("-----退出此程序             请输入:0\n");
        printf("请输入您的操作选择:");
        while(scanf("%d",&choice))                                        //异常处理
        {
            if(choice<0||choice>4)
                printf("输入数字有误，请输入0~4之内的整数，请重新输入!\n");
            else
                break;
        }
        switch(choice)
        {
	        case 1:        InPut(G);      //完毕            输入城市图的相关信息 
	            break;
	        case 2:        ShortestPath_FLOYD(G,P,D);    //完毕         生成城市图的相关信息    
	            break;
	        case 3:        Look(G);     //完毕            查看城市图的相关信息
	            break;
	        case 4:        Refer(G,P,D);      //完毕      查询城市图的相关信息 
	            break;
	        case 0:        OutPut();    //完毕            退出此程序 
	            exit(0);
        }
    }
    return 0;
}


