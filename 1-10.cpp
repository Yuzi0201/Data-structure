#include<iostream>
#define Max 10

typedef struct
{
    int a[Max] = {1, 1, 4, 2, 5, 1, 4, 2, 3, 3};
} test;

typedef struct list
{
    test *elem;
    int length;
} SqList;

void InitList(SqList &L)
{
    L.elem = new test[Max];
    L.length = Max;
}

void delete2(list &L)
{
    for (size_t i = 0, j = 0; i < Max; i++)
    {
        L.elem->a[i - j] = L.elem->a[i];
        if (L.elem->a[i] == 2)
        {
            j++;
            L.length--;
        }
    }
}

void show(list L)
{
    for (size_t i = 0; i < L.length; i++)
    {
        std::cout << L.elem->a[i] << " ";
    }
}

int main()
{
    list L;
    InitList(L);
    delete2(L);
    show(L);
}