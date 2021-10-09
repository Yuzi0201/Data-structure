#include <iostream>
using namespace std;

typedef struct QNode
{
    int data;
    struct QNode *next;
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} Link;

class Quene
{
private:
    Link Q;
    int n;
    int a[100];
    int length;

public:
    Quene(int a[], int length, int n);
    Quene();
    ~Quene();
    void makequeue()
    {
        int min = 0;
        for (int i = 0; i < n; i++)
        {
            QueuePtr p = new QNode; //入队元素开辟空间
            p->data = a[i];         //置数1
            p->next = NULL;
            Q.rear->next = p; //新节点插入队尾
            Q.rear = p;       //修改新节点指针
            if (!i)
            {
                min = p->data;
            }
            else if (p->data < min)
            {
                min = p->data;
            }
        }
        cout << min << " ";
        for (size_t i = n; i < length; i++)
        {
            /*——————入队——————*/
            QueuePtr p = new QNode; //入队元素开辟空间
            p->data = a[i];         //置数1
            p->next = NULL;
            Q.rear->next = p; //新节点插入队尾
            Q.rear = p;       //修改新节点指针
            /*——————出队——————*/
            //Q.front->next = Q.front->next->next;   更新头指针（过于粗暴，没有删掉这个值）
            p = Q.front->next;
            Q.front->next = p->next; //更新头指针
            p = Q.front->next;       //为下面的比较大小而重置p
            min = p->data;           //重置最小值
            while (p->next)
            {
                if (p->next->data < min)
                {
                    min = p->next->data;
                }
                p = p->next;
            }
            cout << min << " ";
            min = 0x7fffffff; //最小值置最大；
        }
    }
};

Quene::Quene(int a[], int length, int n)
{
    Q.front = Q.rear = new QNode;
    Q.front->next = NULL;
    this->length = length;
    this->n = n;
    for (size_t i = 0; i < length; i++)
    {
        this->a[i] = a[i];
    }
}

Quene::Quene()
{
    length = 0;
    cout << "\nPlease enter the array:" << endl;
    while (cin >> a[length])
    {
        length++;
        if (cin.get() == '\n')
            break;
    }
    cout << "Please enter n: ";
    cin >> n;
    Q.front = Q.rear = new QNode;
    Q.front->next = NULL;
}

Quene::~Quene()
{
}

int main()
{
    int a[100] = {2, 3, 4, 5, 6, 114514, 9, 4, 5, 7, 1919810, 655, 66, 4500, 37, 19, 23, 298, 13, 2};
    int length = 20;
    int n = 4;
    Quene q(a, length, n);
    q.makequeue();
    /*————手动输入数据————*/
    Quene manual;
    manual.makequeue();
}