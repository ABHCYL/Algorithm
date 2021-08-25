//一般的dijkstra
#include<cstdio>
#include<queue>
#include<vector>
#define MAXN 100010
using namespace std;
struct edge
{
    int x,y,val;
    edge(int xx,int yy,int v){x=xx,y=yy,val=v;}
};
vector<edge>v[MAXN];
struct disnode
{
    int id,dis;
    disnode(int i,int s){id=i,dis=s;}
    bool operator<(const disnode&c)const{return dis>c.dis;}
};
int n,m,sta,goal;
int x,y,val;
priority_queue<disnode>q;
int dis[MAXN];//all point to stapoint 's distance
bool f[MAXN];//f[i]=1 means the shortest path from sta to i is found
void dijkstra()
{
    for(int i=0;i<=n;i++)dis[i]=1<<30;
    dis[sta]=0;
    q.push(disnode(sta,dis[sta]));
    while (!q.empty())
    {
        disnode u=q.top();q.pop();
        if(f[u.id])continue;
        f[u.id]=1;
        int sz=v[u.id].size();
        for(int i=0;i<sz;++i)
        {
            if(dis[v[u.id][i].y]>dis[u.id]+v[u.id][i].val)
            {
                dis[v[u.id][i].y]=dis[u.id]+v[u.id][i].val;
                q.push(disnode(v[u.id][i].y,dis[v[u.id][i].y]));
            }
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    scanf("%d%d%d",&n,&m,&sta);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&x,&y,&val);
        v[x].push_back(edge(x,y,val));
        //v[y].push_back(edge(y,x,val));
    }
    dijkstra();
    for(int i=1;i<=n;++i)
    printf("%d ",dis[i]);
}

//特殊的dijkstra
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
struct edge
{
    int x,y,val,cost;
    edge(int xx,int yy,int v,int c){x=xx,y=yy,val=v,cost=c;}
};
vector<edge>v[501];
struct disnode
{
    int id,dis;
    disnode(int i,int s){id=i,dis=s;}
    bool operator<(const disnode&c)const{return dis>c.dis;}
};
int n,m,sta,goal;
int x,y,val,cost;
priority_queue<disnode>q;
int dis[501];//all point to startpoint 's distance
int pay[501];//it means dp array
bool f[501];//f[i]=1 means the shortest path from sta to i is found
void dijkstra()
{
    for(int i=0;i<=n;i++)dis[i]=pay[i]=1<<30;
    dis[sta]=pay[sta]=0;
    q.push(disnode(sta,dis[sta]));
    while (!q.empty())
    {
        disnode u=q.top();q.pop();
        if(f[u.id])continue;
        f[u.id]=1;
        int sz=v[u.id].size();
        for(int i=0;i<sz;++i)
        {
            if(dis[v[u.id][i].y]>dis[u.id]+v[u.id][i].val)
            {
                dis[v[u.id][i].y]=dis[u.id]+v[u.id][i].val;
                pay[v[u.id][i].y]=pay[u.id]+v[u.id][i].cost;
                q.push(disnode(v[u.id][i].y,dis[v[u.id][i].y]));
            }
            else if(dis[v[u.id][i].y]==dis[u.id]+v[u.id][i].val&&pay[v[u.id][i].y]>pay[u.id]+v[u.id][i].cost)
            {
                pay[v[u.id][i].y]=pay[u.id]+v[u.id][i].cost;
            }
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    scanf("%d%d%d%d",&n,&m,&sta,&goal);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d%d",&x,&y,&val,&cost);
        v[x].push_back(edge(x,y,val,cost));
        v[y].push_back(edge(y,x,val,cost));
    }
    dijkstra();
    printf("%d %d",dis[goal],pay[goal]);
}