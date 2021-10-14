# 矩阵加速与斐波那契数列
> ## 背景：斐波那契数列
> 在引入矩阵加速之前，先介绍斐波那契数列问题。
> 斐波那契数列是一个加法形式的递推式。即 F (n) = F (n-1) + F (n-2) 。

### 方法1：通项公式
斐波那契数列在数学上有通项公式
<img src="https://latex.codecogs.com/svg.image?F(n)=\frac{1}{\sqrt&space;5}&space;[(\frac{1&plus;\sqrt&space;5}{2})^n&space;-(\frac{1-\sqrt&space;5}{2})^n]" title="F(n)=\frac{1}{\sqrt 5} [(\frac{1+\sqrt 5}{2})^n -(\frac{1-\sqrt 5}{2})^n]" />

时间复杂度则和计算n次方的算法有关.如果用for循环递推求<img src="https://latex.codecogs.com/svg.image?(\frac{1&plus;\sqrt5}{2})" title="(\frac{1+\sqrt5}{2})" />和<img src="https://latex.codecogs.com/svg.image?(\frac{1-\sqrt5}{2})" title="(\frac{1-\sqrt5}{2})" />的n次方，那我们可以认为时间复杂度是<img src="https://latex.codecogs.com/svg.image?O(n)" title="O(n)" />的。如果采用快速幂的方式，那我们可以认为时间复杂度是<img src="https://latex.codecogs.com/svg.image?O(\log{n)}" title="O(\log{n)}" />.

显然，空间复杂度是<img src="https://latex.codecogs.com/svg.image?O(1)" title="O(1)" />，不论是for循环递推还是快速幂（注：快速幂如果是迭代实现才是空间<img src="https://latex.codecogs.com/svg.image?O(1)" title="O(1)" /> ，若是用递归方法实现的快速幂，递归这一过程是需要开辟新的栈帧的就不是空间<img src="https://latex.codecogs.com/svg.image?O(1)" title="O(1)" />了）都只需用到常数个变量 。

理论上讲，用通项公式计算是可行的。但是，让计算机算<img src="https://latex.codecogs.com/svg.image?\sqrt&space;5" title="\sqrt 5" />和分数形式的数字很麻烦会有非整数数字精度丢失的问题。

### 方法2：矩阵加速 
### 首先有一个结论：对于一些加法形式的递推式（比如斐波那契），一般都可以使用矩阵乘法加速递推
于是可以用矩阵乘法加速斐波那契递推，公式如下

<img src="https://latex.codecogs.com/svg.image?\left[\begin{matrix}F_{n&plus;1}&space;&&space;F_n&space;\\F_n&space;&&space;F_{n-1}\end{matrix}\right]={\left[\begin{matrix}1&space;&&space;1&space;\\1&space;&&space;0\end{matrix}\right]}^n=\underbrace{\left[\begin{matrix}1&space;&&space;1&space;\\1&space;&&space;0\end{matrix}\right]\left[\begin{matrix}1&space;&&space;1&space;\\1&space;&&space;0\end{matrix}\right]\left[\begin{matrix}1&space;&&space;1&space;\\1&space;&&space;0\end{matrix}\right]}_{\text{n&space;times}}" title="\left[\begin{matrix}F_{n+1} & F_n \\F_n & F_{n-1}\end{matrix}\right]={\left[\begin{matrix}1 & 1 \\1 & 0\end{matrix}\right]}^n=\underbrace{\left[\begin{matrix}1 & 1 \\1 & 0\end{matrix}\right]\left[\begin{matrix}1 & 1 \\1 & 0\end{matrix}\right]\left[\begin{matrix}1 & 1 \\1 & 0\end{matrix}\right]}_{\text{n times}}" />

所以问题就变成了实现一个矩阵<img src="https://latex.codecogs.com/svg.image?\left[\begin{matrix}1&space;&&space;1\\1&space;&&space;0\end{matrix}\right]" title="\left[\begin{matrix}1 & 1\\1 & 0\end{matrix}\right]" />的n次方乘法问题 .
方法1提到过，朴素的for循环计算n次方问题是时间<img src="https://latex.codecogs.com/svg.image?O(n)" title="O(n)" />的，如果采用快速幂则是<img src="https://latex.codecogs.com/svg.image?O(\log{n)}" title="O(\log{n)}" /> 的。



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
