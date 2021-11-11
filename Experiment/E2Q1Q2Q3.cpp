#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct BinTree
{
    char data;
    BinTree *Lchild;
    int Ltag;
    BinTree *Rchild;
    int Rtag;
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

bool IsNullNode(BinTree *node)
{
    if (node && node->data != '\r')
    {
        return false;
    }
    else
        return true;
}

void outputTree(BinTree *root)
{
    if (IsNullNode(root))
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

BinTree *find(char c, BinTree *root)
{
    static BinTree *p;
    if (IsNullNode(root))
    {
        return p;
    }
    else
    {
        if (root->data == c)
        {
            p = root;
            return p;
        }
        find(c, root->Lchild);
        find(c, root->Rchild);
    }
}

void outputnode(BinTree *root, int &i)
{
    if (IsNullNode(root))
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
    if (IsNullNode(root))
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
    else if (!IsNullNode(root) && root->Lchild && root->Rchild)
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
    if (IsNullNode(root))
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

//Q2↓
void outputTree_preorder(BinTree *root)
{
    if (IsNullNode(root))
    {
        return;
    }
    else
    {
        printf("%c ", root->data);
        outputTree_preorder(root->Lchild);
        outputTree_preorder(root->Rchild);
    }
}

void outputTree_middle(BinTree *root)
{
    if (IsNullNode(root))
    {
        return;
    }
    else
    {
        outputTree_middle(root->Lchild);
        printf("%c ", root->data);
        outputTree_middle(root->Rchild);
    }
}

void outputTree_postorder(BinTree *root)
{
    if (IsNullNode(root))
    {
        return;
    }
    else
    {
        outputTree_postorder(root->Lchild);
        outputTree_postorder(root->Rchild);
        printf("%c ", root->data);
    }
}

void outputTree_preorder_without_recursion(BinTree *root)
{
    stack<BinTree *> s;
    BinTree *p = root;
    while ((!IsNullNode(p)) || !s.empty())
    {
        while (!IsNullNode(p))
        {
            cout << p->data << " ";
            s.push(p);
            p = p->Lchild;
        }
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->Rchild;
        }
    }
}

void outputTree_middle_without_recursion(BinTree *root) //非递归中序遍历
{
    stack<BinTree *> s;
    BinTree *p = root;
    while (!IsNullNode(p) || !s.empty())
    {
        while (!IsNullNode(p))
        {
            s.push(p);
            p = p->Lchild;
        }
        if (!s.empty())
        {
            p = s.top();
            cout << p->data << " ";
            s.pop();
            p = p->Rchild;
        }
    }
}

void outputTree_postorder_without_recursion(BinTree *root) //非递归后序遍历
{
    stack<BinTree *> s;
    BinTree *cur;        //当前结点
    BinTree *pre = NULL; //前一次访问的结点
    s.push(root);
    while (!s.empty())
    {
        cur = s.top();
        if ((IsNullNode(cur->Lchild) && IsNullNode(cur->Rchild)) ||
            (!IsNullNode(pre) && (pre == cur->Lchild || pre == cur->Rchild)))
        {
            cout << cur->data << " "; //如果当前结点没有孩子结点或者孩子节点都已被访问过
            s.pop();
            pre = cur;
        }
        else
        {
            if (!IsNullNode(cur->Rchild))
                s.push(cur->Rchild);
            if (!IsNullNode(cur->Lchild))
                s.push(cur->Lchild);
        }
    }
}

//Q3↓

void Seq_Order(BinTree *cur) //中序线索化二叉树
{
    static BinTree *pre = nullptr; //用静态变量，使得在递归时pre的值仍然正确，出递归后pre的值应该改变而不是入递归时的值
    if (IsNullNode(cur))
    {
        return;
    }
    else
    {
        Seq_Order(cur->Lchild);
        if (IsNullNode(cur->Lchild))
        { //建立前驱线索
            cur->Ltag = 1;
            cur->Lchild = pre;
        }

        //建立后继线索
        if ((!IsNullNode(pre)) && (IsNullNode(pre->Rchild)))
        {
            pre->Rtag = 1;
            pre->Rchild = cur;
        }
        pre = cur; //在此处更改静态变量的值
        Seq_Order(cur->Rchild);
    }
}

BinTree *return_Precursor(BinTree *root) //寻找节点的前驱
{
    BinTree *p = root->Lchild;
    if (root->Ltag != 1)     //若Ltag为1，则前驱就为左孩子，若不为1，说明有左子树，前驱即为左子树最右边的那一个叶子
        while (p->Rtag != 1) //若Rtag不为1，则还有右子树，继续向右查，若为1，则已到最右尽头，这个就是要找的前驱
            p = p->Rchild;
    return p;
}

BinTree *return_Successor(BinTree *root) //寻找节点的后继
{
    BinTree *p = root->Rchild;
    if (root->Rtag != 1)     //同理，若Rtag为1，则后继就为右孩子，若不为1，说明有右子树，后继即为右子树最左边的那一个叶子
        while (p->Ltag != 1) //同理，若Ltag不为1，则还有左子树，继续向左查，若为1，则已到最左尽头，这个就是要找的后继
            p = p->Lchild;
    return p;
}

int main()
{
    string s = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    BinTree *b = new BinTree;
    int i = 0;
    create(b, s, i);
    printf("该树为：");
    outputTree(b);
    BinTree *p = find('H', b);
    printf("\nH的左孩子和右孩子分别是： %c %c\n", p->Lchild->data, p->Rchild->data);
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
    //Q1结束↑
    printf("树的递归先序遍历为  : ");
    outputTree_preorder(b); //前序
    printf("\n树的非递归先序遍历为: ");
    outputTree_preorder_without_recursion(b);
    printf("\n树的递归中序遍历为  : ");
    outputTree_middle(b); //中序
    printf("\n树的非递归中序遍历为: ");
    outputTree_middle_without_recursion(b);
    printf("\n树的递归后序遍历为:   ");
    outputTree_postorder(b); //后序
    printf("\n树的非递归后序遍历为: ");
    outputTree_postorder_without_recursion(b);
    printf("\n");
    //Q2结束↑
    Seq_Order(b);
    cout << "根节点A在中序线索化树中的前驱是： " << return_Precursor(find('A', b))->data << endl;
    cout << "根节点A在中序线索化树中的后继是： " << return_Successor(find('A', b))->data << endl;
}