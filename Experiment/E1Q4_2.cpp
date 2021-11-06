#include <iostream>
#include <string>

struct node
{
    char data;
    node *next;
};

struct stuck
{
    node *top;
    node *bottom;
};

class E1Q4_2
{
public:
    stuck *parentheses;
    stuck *brackets;
    stuck *braces;
    E1Q4_2(/* args */);
    ~E1Q4_2();
    void pop(char c) //出栈
    {
        stuck *s;
        switch (c)
        {
        case '(':
            s = parentheses;
            break;
        case '[':
            s = brackets;
            break;
        case '{':
            s = braces;
            break;
        default:
            break;
        }
        node *p = new node;
        p = s->top->next;
        s->top->next = p->next;
        delete p;
    }
    void push(char c) //入栈
    {
        node *p = new node;
        switch (c)
        {
        case '(':
            p->data = '(';
            p->next = parentheses->top->next;
            parentheses->top->next = p;
            break;
        case '[':
            p->data = '[';
            p->next = brackets->top->next;
            brackets->top->next = p;
            break;
        case '{':
            p->data = '{';
            p->next = braces->top->next;
            braces->top->next = p;
            break;
        default:
            break;
        }
        p = nullptr;
        delete p;
    }
    bool IsNull(char c)
    {
        stuck *s;
        switch (c)
        {
        case '(':
        case ')':
            s = parentheses;
            break;
        case '[':
        case ']':
            s = brackets;
            break;
        case '{':
        case '}':
            s = braces;
            break;
        default:
            break;
        }
        if (s->top->next == s->bottom)
            return true;
        else
            return false;
    }
};

E1Q4_2::E1Q4_2(/* args */)
{
    parentheses = new stuck;
    parentheses->top = new node;
    parentheses->bottom = new node;
    brackets = new stuck;
    brackets->top = new node;
    brackets->bottom = new node;
    braces = new stuck;
    braces->top = new node;
    braces->bottom = new node;
    parentheses->top->next = parentheses->bottom;
    brackets->top->next = brackets->bottom;
    braces->top->next = braces->bottom;
}

E1Q4_2::~E1Q4_2()
{
}

int main()
{
    E1Q4_2 e;
    std::string s;
    std::printf("请输入一串带括号的字符串： ");
    std::cin >> s;
    for (size_t i = 0; s[i]; i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            e.push(s[i]);
        }
        if (s[i] == ')' || s[i] == ']' || s[i] == '}')
        {
            if (e.IsNull(s[i]))
            {
                std::printf("错误！为不合法嵌套！\n");
                return 0;
            }
            else
            {
                e.pop(s[i]);
            }
        }
    }
    if (e.IsNull('(') && e.IsNull('[') && e.IsNull('{'))
    {
        std::printf("正确！为合法嵌套！\n");
        return 0;
    }
    else
    {
        std::printf("错误！为不合法嵌套！\n");
        return 0;
    }
}