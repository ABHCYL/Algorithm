# 中缀表达式求值问题

## 方法一 : 正统的中缀表达式转换为逆波兰表达式，再用栈求值
#### 头文件
    #include <vector>
    #include <string>
    #include <unordered_map>
    using std::unordered_map;
    using std::vector;
    using std::string;
### 转换为逆波兰表达式
    void postfix(string& s,vector<string>&res)
    {
        unordered_map<string, int> priority; // 哈希表
        priority["+"] = 1; // 设定优先级，乘除高于加减，左括号优先级最低
        priority["-"] = 1;
        priority["*"] = 2;
        priority["/"] = 2;
        priority["("] = 0;
        stack<string> ops;
        if (!s.length()) return; // 表达式为空直接返回

        s.insert(0, 1, '(');  // 表达式字符串开头结尾加入括号 保证全部符号可以出栈
        s.push_back(')');
        int n = s.length();

        for (int i = 0; i < n; i++) 
        {
            if (s[i] == ' ') continue; // 表达式字符串有空格直接跳过
            // 处理数字
            if (s[i] >= '0') 
            {
                string cur = "";
                while (i < n && s[i] >= '0') 
                {
                    cur += s[i];
                    i++;
                }
                res.push_back(cur); // 将数字存放在res中
                i--;  //循环时，i指向的下一个符号
            }
            // 处理括号的不同情况
            if (s[i] == '(') ops.push("("); // 左括号直接入栈
            else if (s[i] == ')') // 右括号到左括号符号全部出栈
            { 
                while (ops.top() != "(") 
                {
                    res.push_back(ops.top()); // 将括号中的符号出栈且存放在res中
                    ops.pop();
                }
                ops.pop(); // 把"(" pop
            }
            // 处理+-*/四种情况，当前优先级最高时
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') 
            {
                if (ops.empty() || priority[string(1, s[i])] > priority[ops.top()]) ops.push(string(1, s[i]));//栈空或优先级比栈顶元素优先级高，直接入栈
                else 
                { // 当前优先级比较低，栈中符号出栈，直到满足上面入栈要求
                    while (!ops.empty()) 
                    {
                        string op = ops.top(); 
                        if (priority[op] >= priority[string(1, s[i])]) 
                        {
                            res.push_back(op);
                            ops.pop();
                        }
                        else break;
                    }
                    ops.push(string(1, s[i])); // 栈为空 返回
                }
            }
        }
    }
>遍历vector< string >res就是所求中缀表达式
### 栈求逆波兰表达式值
    int evalRPN(vector<string>& tokens) 
    {
        stack<int> nums;
        int n = tokens.size();
        for (int i = 0; i < n; i++) 
        {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") 
            {
                int num2 = nums.top();
                nums.pop();
                int num1 = nums.top();
                nums.pop();
                if (tokens[i] == "+") nums.push(num1 + num2);
                if (tokens[i] == "-") nums.push(num1 - num2);
                if (tokens[i] == "*") nums.push(num1 * num2);
                if (tokens[i] == "/") nums.push(num1 / num2);
            }
            else nums.push(std::stoi(tokens[i])); // 字符串转化为int
        }
        return nums.top();
    }

### 调用
    int solve(string s) 
    {
        vector<string> tokens ;
        toRPN(s,tokens);
        return evalRPN(tokens);
    }
## 方法二 : 更简洁但晦涩的递归解法
    int caulcate(string s) 
    {
        int res = 0; //用于返回当前字符串的计算结果
        stack<int> sum; //用于求和
        char sign = '+'; //记录前一个符号，初始化为+，因为可以看成当前字符串前先加0
        int num = 0; //用于将连续数字字符串转化成数字或者记录递归结果
        for(int i = 0; i < s.size(); i++) 
        { //遍历每一个字符
            if(s[i] >= '0' && s[i] <= '9') //先处理数字字符
                num = 10 * num + s[i] - '0'; //进位后加个位数
            if(s[i] == '(') 
            { //对于括号
                int left = i++, count = 1; //用left记录最左括号位置，count记录左括号数，i当成右指针右移一格
                while(count > 0) 
                { //最终目的是找到与最左括号匹配的右括号，类似于栈操作
                    if(s[i] == '(') count++;
                    else if(s[i] == ')') count--;
                    i++;
                }
                num = caulcate(s.substr(left + 1, i - left - 2)); //迭代计算括号内数值，注意不要包含最左最右括号，不然会死循环
                i--; //此时i是最右括号下一位，需要左移一位防止最右括号在字符串尾时发生越界从而使下面的判定失效
            }
            if(i == s.size() - 1 || s[i] == '+' || s[i] == '-' || s[i] == '*' ||s[i] == '/') 
            { //对于字符串尾，或者加减乘，此时我们用的符号是上一次的，结算当前数字
                if(sign == '+') sum.push(num); //加法入栈
                else if(sign == '-') sum.push(-num); //减法相当于加负数
                else if(sign == '*') sum.top() *= num; //乘法与栈顶相乘
                else if(sign == '/') sum.top() /= num;
                sign = s[i]; //更新符号，若为末尾的右括号也无妨，因为马上就退出循环了
                num = 0; //重置当前数
            }
        }
        while(!sum.empty()) 
        { //将栈内所有数字相加
            res += sum.top();
            sum.pop();
        }
        return res; //返回当前字符串计算结果
    }
