#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

typedef struct node
{
    int data;
    node *next;
    node *back;
};

typedef struct queue
{
    node *top;
    node *bottom;
};

int main()
{
    queue *Q = new queue;
    srand((unsigned)time(NULL));
    node *p = new node;
    Q->top = new node;
    Q->top->next = p;
    Q->top->back = nullptr;
    Q->bottom = new node;
    Q->bottom->next = nullptr;
    p->back = Q->top;
    for (size_t i = 0; i < 10; i++)
    {
        p->data = (rand() % (1000 - 100)) + 100;
        if (i != 9)
        {
            p->next = new node;
            p->next->next = Q->bottom;
            p->next->back = p;
            Q->bottom->back = p->next;
        }
        else
        {
            p->next = Q->bottom;
        }

        p = p->next;
    }

    p = Q->top->next;
    while (p->next)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;

    queue *Q_bilateral = new queue;
    node *q = new node;
    Q_bilateral->top = new node;
    Q_bilateral->top->next = q;
    Q_bilateral->top->back = nullptr;
    Q_bilateral->bottom = new node;
    Q_bilateral->bottom->next = nullptr;
    q->back = Q_bilateral->top;
    p = Q->bottom->back;
    while (p->back)
    {
        q->data = p->data;
        q->next = new node;
        q->next->next = Q_bilateral->bottom;
        q = q->next;
        p = p->back;
    }

    while (Q_bilateral->top->next->next->next)
    {
        cout << Q_bilateral->top->next->data << " ";
        Q_bilateral->top->next = Q_bilateral->top->next->next;
    }
}