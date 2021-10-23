### 扩展欧几里得
```cpp
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b){x=1;y=0;return;}
    exgcd(b,a%b,x,y);
    int tmp =x;
    x=y;
    y=tmp-a/b*y;
}
```
### 逆元
```cpp
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b){x=1;y=0;return;}
    exgcd(b,a%b,x,y);
    int tmp =x;
    x=y;
    y=tmp-a/b*y;
}
ll modinreverse(ll a,ll b)
{
    ll x,y;
    exgcd(a,b,x,y);
    x=(x%b+b)%b;
    return x;
}
```
