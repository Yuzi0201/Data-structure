#include<iostream>
using namespace std;

typedef struct Node
{
    int value;
    struct Node *next;
} Node, *List;

void initlist(List &L)
{
    L = new Node;
    L->next = NULL;
}

void array2node(Node &node,int array[],int length)
{
    Node *s = new Node;
    *s = {array[0], NULL};
    node.next = s;              //单独处理第一个

    for (size_t i = 1; i < length; i++)
    {
        Node *r = new Node;
        *r = {array[i], NULL};      //为后面的赋值
        s->next = r;
        s = r;
    }
}

int main()
{
    int A[] = {3, 5, 8, 11};
    int B[] = {2, 6, 8, 9, 11, 15, 20};
    List ListA;
    initlist(ListA);
    array2node(*ListA, A, sizeof(A) / sizeof(A[0]));
    List ListB;
    initlist(ListB);
    array2node(*ListB, B, sizeof(B) / sizeof(B[0]));
    List C;
    initlist(C);
    array2node(*C, A, sizeof(A) / sizeof(A[0]));
    List p = C->next;
    for (size_t i = 0; i < sizeof(A) / sizeof(A[0]) - 1; i++)
    {
        p = p->next;
    }
    for (size_t i = 0; i < (sizeof(B) / sizeof(B[0]) - sizeof(A) / sizeof(A[0]))-1; i++)
    {
        List k = new Node;
        p->next = k;
        p = p->next;
    }
    p = C->next;
    List q = ListB->next;
    List ppre = C;
    while (q)
    {
        while (p)
        {
            if(q->value!=p->value)
            {
                if(p->value == 0)
                {
                    p->value = q->value;
                }
                else if (q->value > p->value)
                {
                    ppre = p;
                    p = p->next;
                }
                else
                {
                    List temp = new Node;
                    temp->value = q->value;
                    temp->next = ppre->next;
                    ppre->next = temp;
                    break;
                }
            }
            else
                break;
        }
        q = q->next;
        p = C->next;
        ppre = C;
    }
    p = C->next;
    while (p)
    {
        cout << p->value << " ";
        p = p->next;
    }
}