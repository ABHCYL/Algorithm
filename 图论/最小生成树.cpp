//kruskal
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAXN 5010//MAXN是节点数
using namespace std;
struct edge
{
    int x,y,val;
    edge(int xx,int yy,int vv){x=xx,y=yy,val=vv;}
    bool operator<(const edge&c){return val<c.val;}
};
vector<edge>v;
int n,m,x,y,val,ans,sum;
int father[MAXN];
int find(int x){return x==father[x]?x:father[x]=find(father[x]);}
void kruskal()
{
    sort(v.begin(),v.end());
    for(int i=0;i<m;++i)
    {
        int a=find(v[i].x),b=find(v[i].y);
        if(a!=b)++sum,father[a]=b,ans+=v[i].val;
    }
    sum==n-1 ? printf("%d",ans): printf("不连通");
}
int main()
{
    for(int i=0;i<=n;++i)father[i]=i;//初始化
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)//建边
    {
        scanf("%d%d%d",&x,&y,&val);
        v.push_back(edge(x,y,val));
    }
    kruskal();
}
//prim
