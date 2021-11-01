#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

typedef struct E1Q1
{
    int data;
    E1Q1 *next;
};

typedef struct E1Q1_bilateral
{
    int data;
    E1Q1_bilateral *next;
    E1Q1_bilateral *back;
};

int main()
{
    srand((unsigned)time(NULL));
    E1Q1 *queue = new E1Q1;
    queue->data = 0;
    E1Q1 *p = queue;
    for (size_t i = 0; i < 10; i++)
    {
        p->next = new E1Q1;
        p->next->data = (rand() % (1000 - 100)) + 100;
        p = p->next;
    }
    p->next = new E1Q1;
    p->next->data = 0;
    p->next->next = NULL;

    p = queue->next;
    while (p->next)
    {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
    cout << "请输入一个整数： ";
    int a;
    int place = 1;
    cin >> a;
    p = queue->next;
    while (p->next)
    {
        if (p->data == a)
        {
            cout << "该数在表中，是第" << place << "位" << endl;
            break;
        }
        place++;
        p = p->next;
    }
    if (!p->next)
    {
        cout << "该数不在表中！！" << endl;
    }

    while (1)
    {
        cout << "请输入一个数字和要插入的位置： ";
        cin >> a >> place;
        if (place < 1 || place > 11)
        {
            cout << "输入位置非法！请重试！" << endl;
            continue;
        }
        p = queue;
        for (size_t i = 1; i < place; i++)
        {
            p = p->next;
        }
        E1Q1 *q = new E1Q1;
        q->next = p->next;
        q->data = a;
        p->next = q;

        p = queue->next;
        while (p->next)
        {
            cout << p->data << " ";
            p = p->next;
        }
        break;
    }
    cout << endl;

    cout << "请输入需要删除的数字： ";
    cin >> a;
    p = queue;
    while (p->next)
    {
        if (p->next->data == a)
        {
            p->next = p->next->next;
            cout << "删除后的结果为： " << endl;
            p = queue->next;
            while (p->next)
            {
                cout << p->data << " ";
                p = p->next;
            }
            cout << endl;
            p = queue->next;
            break;
        }
        p = p->next;
    }
    if (!p->next)
    {
        cout << "没有这个数字！" << endl;
    }

    E1Q1_bilateral *b = new E1Q1_bilateral;
    E1Q1_bilateral *q = new E1Q1_bilateral;
    b->next = q;
    q->back = b;
    b->back = NULL;
    p = queue->next;
    while (p->next)
    {
        q->data = p->data;
        q->next = new E1Q1_bilateral;
        q->next->back = q;
        q = q->next;
        p = p->next;
    }
    q = q->back;
    cout << "倒序输出是：" << endl;
    while (q->back)
    {
        cout << q->data << " ";
        q = q->back;
    }
    cout << endl;
}
