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

void find(char c, BinTree *root)
{
    if ((!root) || (root->data == '\r'))
    {
        return;
    }
    else
    {
        if (root->data == c)
        {
            printf("%c %c\n", root->Lchild->data, root->Rchild->data);
            return;
        }
        find(c, root->Lchild);
        find(c, root->Rchild);
    }
}

void outputnode(BinTree *root, int &i)
{
    if ((!root) || (root->data == '\r'))
    {
        return;
    }
    else
    {
        i++;
        outputnode(root->Lchild, i);
        outputnode(root->Rchild, i);
    }
}

void outputleafnode(BinTree *root, int &i)
{
    if ((!root) || (root->data == '\r'))
    {
        return;
    }
    else
    {
        if (root->data != '\r' && (!root->Lchild) && (!root->Rchild))
        {
            i++;
        }

        outputleafnode(root->Lchild, i);
        outputleafnode(root->Rchild, i);
    }
}

void degree(BinTree *root, int &i) //计算二叉树的度
{
    if (i == 2)
        return;
    else if (root != NULL && root->Lchild && root->Rchild)
    {
        i = 2;
        return;
    }
    else if (root->Lchild || root->Rchild)
    {
        i = i > 1 ? i : 1; //如果该结点只有左右子树之一，取较大值
        if (root->Lchild && root->Rchild)
            degree(root->Lchild, i);
        if (root->Lchild && root->Rchild)
            degree(root->Lchild, i);
    }
    else
    {
        i = 0;
        return;
    }
}

int depth(BinTree *root) //计算二叉树深度
{
    if ((!root) || (root->data == '\r'))
        return 0;
    else
    {
        int m = depth(root->Lchild) + 1; //计算左子树到该点的最大深度
        int n = depth(root->Rchild) + 1; //计算右子树到该点的最大深度
        if (m >= n)
            return m; //比较两深度大小，取较大
        else
            return n;
    }
}

int main()
{
    string s = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    BinTree *b = new BinTree;
    int i = 0;
    create(b, s, i);
    printf("该树为：");
    outputTree(b);
    printf("\nH的左孩子和右孩子分别是： ");
    find('H', b);
    i = 0;
    outputnode(b, i);
    cout << "节点总数为： " << i << endl;
    i = 0;
    outputleafnode(b, i);
    cout << "叶子节点总数为： " << i << endl;
    i = 0;
    degree(b, i);
    cout << "树的度为： " << i << endl;
    cout << "树的高度为： " << depth(b) << endl;
    //Q1结束
}