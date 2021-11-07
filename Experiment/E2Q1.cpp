#include <iostream>
#include <string>
using namespace std;

struct BinTree
{
    char data;
    BinTree *Lchild;
    BinTree *Rchild;
};

void create(BinTree *&root, string s, int &i) //创建二叉树
{

    switch (s[i])
    {
    case '(':
        root->Lchild = new BinTree;
        create(root->Lchild, s, ++i);
        root->Rchild = new BinTree;
        create(root->Rchild, s, ++i);
        if (root->Rchild->data != '\r') //判断右节点是否为空，若非空，不需要读“）”就可以返回，导致跳回出错，故要在计数器上手动+1
            ++i;
        break;
    case ',':
    case ')':
        root->Lchild = nullptr;
        root->Rchild = nullptr;
        break;
    case NULL:
        break;
    default:
        root->data = s[i];
        create(root, s, ++i);
        break;
    }
}

void outputTree(BinTree *root)
{
    if ((!root) || (root->data == '\r'))
    {
        printf("NULL ");
        return;
    }
    else
    {
        printf("%c ", root->data);
        outputTree(root->Lchild);
        outputTree(root->Rchild);
    }
}

int main()
{
    string s = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    BinTree *b = new BinTree;
    int i = 0;
    create(b, s, i);
    outputTree(b);
    cin >> i;
}