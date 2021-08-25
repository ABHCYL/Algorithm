//spfa主要是判负环
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#define MAXN 2010
using namespace std;
struct edge
{
    int from,to,val;
    edge(int f,int t,int v){from=f,to=t,val=v;}
};
vector<edge>v[MAXN];
int zu,n,m,val,x,y;
int dis[MAXN],neg[MAXN];
bool inqueue[MAXN];
bool spfa()
{
    for(int i=1;i<=n;++i){dis[i]=(1<<30);neg[i]=inqueue[i]=0;}
    queue<int>q;
    q.push(1);
    neg[1]=inqueue[1]=1;
    dis[1]=0;
    while (!q.empty())
    {
        int u=q.front();q.pop();
        inqueue[u]=0;
        for(auto i:v[u])
        {
            int to=i.to,vval=i.val;
            if(dis[to]>dis[u]+vval)
            {
                dis[to]=dis[u]+vval;
                neg[to]=neg[u]+1;
                if(neg[to]>n)return 0;//某个节点走过了n遍，说明有负环
                if(!inqueue[to])
                {
                    inqueue[to]=1;
                    q.push(to);
                }
            }
        }
    }
    return 1;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    scanf("%d",&zu);
    while (zu--)
    {
        scanf("%d%d",&n,&m);
        for(int j=1;j<=n;j++)v[j].clear();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&x,&y,&val);
            v[x].push_back(edge(x,y,val));
            v[y].push_back(edge(y,x,val));
        }
        if(spfa()) printf("NO\n");
        else printf("YES\n");
    }
}