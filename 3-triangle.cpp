#include <iostream>
using namespace std;

typedef struct triangle
{
    int data;
    struct triangle *next;
    struct triangle *back;
} triangle, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} Link;

class yanghui_tri
{
private:
    Link Yanghui;
    triangle *p, *q;

public:
    yanghui_tri(/* args */);
    ~yanghui_tri();
    void export_tri(int line);
};

yanghui_tri::yanghui_tri(/* args */)
{
    Yanghui.front = new triangle;
    Yanghui.rear = new triangle;
    Yanghui.front->data = 0;
    Yanghui.rear->data = 0;
    Yanghui.rear->next = NULL;
    Yanghui.front->back = NULL;
    p = new triangle;
    Yanghui.front->next = p;
    p->data = 1;
    p->back = Yanghui.front;
    q = new triangle;
    p->next = q;
    q->data = 0;
    q->back = p;
    q->next = Yanghui.rear;
    Yanghui.rear->back = q; //初始化了一个为“1 0”的双向链队
}

yanghui_tri::~yanghui_tri()
{
}

void yanghui_tri::export_tri(int line)
{
    if (line == 1) //只输出一行时不进行后续操作
    {
        p = Yanghui.front->next;
        while (p->next->next)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    else
    {
        p = Yanghui.front->next;
        while (p->next->next)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
        for (size_t i = 0; i < line; i++)
        {
            p = new triangle;
            p->data = 0;
            p->next = Yanghui.rear;
            p->back = Yanghui.rear->back;
            Yanghui.rear->back->next = p;
            Yanghui.rear->back = p; //给链队末尾添加“0”
            p = p->back;
            while (p->back)
            {
                p->data = p->data + p->back->data;

                p = p->back;
            }
            p = Yanghui.front->next;
            while (p->next->next)
            {
                cout << p->data << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
}

int main()
{
    yanghui_tri a;
    cout << "Please enter how many line(s) would you export the Yanhui triangle: ";
    a.export_tri((int)cin.get() - 49);
}