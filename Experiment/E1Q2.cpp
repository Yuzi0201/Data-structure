#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

typedef struct node
{
    int data;
    node *next;
};

typedef struct stack
{
    node *top;
    node *bottom;
};

class E1Q2
{
public:
    stack s;
    E1Q2(/* args */);
    ~E1Q2();
};

E1Q2::E1Q2(/* args */)
{
    s.top = new node;
    s.bottom = new node;
    s.bottom->next = nullptr;
    s.top->next = s.bottom;
}

E1Q2::~E1Q2()
{
}

int main()
{
    E1Q2 e;
    srand((unsigned)time(NULL));
    node *p;
    for (size_t i = 0; i < 10; i++)
    {
        p = new node;
        p->data = (rand() % (1000 - 100)) + 100;
        p->next = e.s.top->next;
        e.s.top->next = p;
        cout << p->data << " ";
    }
    cout << endl;
    p = e.s.top->next;
    while (p->next)
    {
        cout << p->data << " ";
        e.s.top->next = p->next;
        node *q = p;
        delete q;
        p = e.s.top->next;
    }
}