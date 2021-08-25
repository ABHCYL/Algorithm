#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 110
using namespace std;
int n,m;
struct edge
{
    int to,val;
    edge(int t,int v){to=t,val=v;}
};
vector<edge>v[MAXN],e[MAXN];
queue<int>q;
int x,y,val;
int in[MAXN],out[MAXN],earlist[MAXN],last[MAXN];
int d[MAXN][MAXN];
int ear()
{
    for(int i=1;i<=n;++i)if(!in[i])q.push(i);
    int cnt=0,maxn=-1,id;
    while (!q.empty())
    {
        ++cnt;
        int u=q.front();q.pop();
        for(auto i:v[u])
        {
            earlist[i.to]=max(earlist[i.to],earlist[u]+i.val);
            if(!(--in[i.to]))q.push(i.to);
        }
    }
    if(cnt!=n){printf("0");return -1;}
    for(int i=1;i<=n;++i)
    if(!out[i]&&maxn<earlist[i])maxn=earlist[i],id=i;
    printf("%d\n",maxn);
    return id;
}
void las(int maxn)
{
    for(int i=1;i<=n;++i)if(!out[i])q.push(i);
    last[maxn]=earlist[maxn];
    while (!q.empty())
    {
        int u=q.front();q.pop();
        for(auto i:e[u])
        {
            if(last[i.to]&&last[u]-i.val<=last[i.to])last[i.to]=last[u]-i.val;
            else last[i.to]=last[u]-i.val;
            d[i.to][u]=last[u]-earlist[i.to]-i.val;
            if(!(--out[i.to]))q.push(i.to);
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&x,&y,&val);
        v[x].push_back(edge(y,val));
        e[y].push_back(edge(x,val));
        in[y]++,out[x]++;
    }
    memset(d,-1,sizeof(d));
    int maxn=ear();
    if(maxn==-1)return 0;
    las(maxn);
    for(int i=1;i<=n;++i)
    {
        for(int j=n;j;--j)
        if(!d[i][j])printf("%d->%d\n",i,j);
    }
}