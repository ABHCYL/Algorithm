#include <vector>
#include <string>
#include <unordered_map>
using std::unordered_map;
using std::vector;
using std::string;
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
// 转化为逆波兰表达式
vector<string> toRPN(string& s) 
{
    unordered_map<string, int> priority; // 哈希表
    priority["+"] = 1; // 设定优先级，乘除高于加减，左括号优先级最低
    priority["-"] = 1;
    priority["*"] = 2;
    priority["/"] = 2;
    priority["("] = 0;
 
    vector<string> res;
    stack<string> ops;
    if (!s.length()) return res; // 表达式为空直接返回
 
    s.insert(0, 1, '(');  // 表达式字符串开头结尾加入括号 保证全部符号可以出栈
    s.push_back(')');
    int n = s.length();
 
    for (int i = 0; i < n; i++) 
    {
        if (s[i] == ' ') continue; // 表达式字符串有空格直接跳出循环
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
        else if (s[i] == ')') 
        { // 右括号到左括号符号全部出栈
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
                    string op = ops.top(); //
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
    return res;
}
int solve(string s) 
{
    vector<string> tokens = toRPN(s);
    return evalRPN(tokens);
}
