#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

struct node
{
    int data;
    node *back;
    node *next;
};

void swap(node *a, node *b)
{
    a->back->next = b;
    b->next->back = a;
    a->next = b->next;
    b->back = a->back;
    a->back = b;
    b->next = a;
}

int main()
{
    srand((unsigned)time(NULL));
    node *list = new node;
    node *p = new node;
    list->back = nullptr;
    list->next = p;
    p->back = list;
    for (size_t i = 0; i < 10; i++)
    {
        p->data = (rand() % (1000 - 100)) + 100;
        p->next = new node;
        p->next->back = p;
        cout << p->data << " ";
        p = p->next;
    }
    p->next = nullptr;
    cout << endl;
    // swap(list->next, list->next->next);

    p = list->next;
    /*————冒泡排序————*/
    int min;
    for (int i = 0; i < 10 - 1; i++)
    {
        for (int j = 0; j < 10 - 1 - i; j++)
        {
            if (p->data > p->next->data)
                swap(p, p->next);
            else
                p = p->next;
        }
        p = list->next;
    }

    /*——————插入数字——————*/
    cout << "请输入需要插入的数字： ";
    int num;
    cin >> num;
    p = list->next;
    while (p->data < num && p->next)
        p = p->next;
    p = p->back;
    node *q = new node;
    q->data = num;
    p->next->back = q;
    q->next = p->next;
    p->next = q;
    q->back = p;

    p = list->next;
    while (p->next)
    {
        cout << p->data << " ";
        p = p->next;
    }
}