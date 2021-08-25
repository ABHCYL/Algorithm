邻接矩阵
type graph[MAXN][MAXN];

邻接表的简单写法
struct edge
{
    int x,y,val;
    edge(int xx,int yy,int vv){x=xx,y=yy,val=vv;}
};
vector<edge>v;//存边
vector<edge>v[MAXN];//存点
for(auto i:v[u]); //遍历u的邻居节点

链式前向星
struct edge
{
    int  u,v,w, next;
}e[maxn<<1];
int head[maxn];
void add(int u,int v,int w) //加边
{
    e[cnt++].u= u ;
    e[cnt].v = v;
    e[cnt].w = w ;
    e[cnt].next = head[u];
    head[u]=cnt;
}
for(int i =head[u];i;i=e[i].next); //遍历