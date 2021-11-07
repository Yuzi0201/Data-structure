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
        break;
    case ',':
    case ')':
    case NULL:
        return;
        break;
    default:
        root->data = s[i];
        create(root, s, ++i);
        return;
        break;
    }
    // if (s[i] != '(') //如果不是为终止符号
    // {
    //     root->data = data; //设置数据
    //     cout << "请输入" << data << "的左子树:\n";
    //     create(root->Lchild); //建立该结点左子树
    //     cout << "请输入" << data << "的右子树:\n";
    //     create(root->Rchild); //建立该结点右子树
    // }
    // else
    //     root = NULL;
}

int main()
{
    string s = "A(B(D,E(H(J,K(L,M(,N)))))C(F,G(,I)))";
    BinTree *b = new BinTree;
    int i = 0;
    create(b, s, i);
    cout << 1;
}