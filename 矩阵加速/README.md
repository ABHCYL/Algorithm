# 矩阵加速与斐波那契数列
> ## 背景：斐波那契数列
> 在引入矩阵加速之前，先介绍斐波那契数列问题。
> 斐波那契数列是一个加法形式的递推式。即 F (n) = F (n-1) + F (n-2) 。

![avatar](https://github.com/ABHCYL/pitcure/blob/main/%E7%9F%A9%E9%98%B5%E5%8A%A0%E9%80%9F1.png)

![avatar](https://github.com/ABHCYL/pitcure/blob/main/%E7%9F%A9%E9%98%B5%E5%8A%A0%E9%80%9F2.png)

## 代码实现
>定义 matrix 类 和 matrix乘法

    struct matrix
    {
        int a,b;
        int c,d;
        matrix operator*(const matrix &x)
        {
            int newa = x.a*a+x.b*c;
            int newb = x.a*b+x.b*d;
            int newc = x.c*a+x.d*c;
            int newd = x.c*b+x.d*d;
            return { newa,newb,newc,newd };
        }
    };

>矩阵快速幂

    int fibonacci(int n)
    {
        if(n == 0)return 0;
        matrix ans={1,0,0,1};
        matrix m={1,1,1,0};
        while(n)
        {
            if(n&1)
                ans = ans*m;
            m = m*m;
            n >>= 1;
        }
        return ans.b;
    }
