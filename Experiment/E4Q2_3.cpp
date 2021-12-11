#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    char value;
    TreeNode *Lchild;
    TreeNode *Rchild;
};

class BSTree
{
public:
    TreeNode *root = nullptr;
    int frequency = 0;

public:
    BSTree(vector<char> data[10]);
    ~BSTree();
    bool BSTInsert(TreeNode *&root, char value);
    void PreOrder(TreeNode *root);
    void InOrder(TreeNode *root);
    bool BSTSearch(TreeNode *root, int val);
};

BSTree::BSTree(vector<char> data[10]) //构造函数，使用插入函数一步步的构建二叉树
{
    for (size_t i = 0; i < 10; i++)
    {
        BSTInsert(root, data->at(i));
    }
}

BSTree::~BSTree()
{
}

bool BSTree::BSTInsert(TreeNode *&root, char value) //递归插入
{
    TreeNode *node = new TreeNode; //初始化节点
    node->value = value;
    node->Lchild = nullptr;
    node->Rchild = nullptr;
    if (root == NULL)
    {
        root = node;
        return true;
    }
    if (value == root->value)
        return false;
    if (value < root->value)
        return BSTInsert(root->Lchild, value);
    return BSTInsert(root->Rchild, value);
}

void BSTree::PreOrder(TreeNode *root) //先序遍历
{
    if (!root)
    {
        return;
    }
    else
    {
        printf("%c ", root->value);
        PreOrder(root->Lchild);
        PreOrder(root->Rchild);
    }
}

void BSTree::InOrder(TreeNode *root) //中序遍历
{
    if (!root)
    {
        return;
    }
    else
    {
        InOrder(root->Lchild);
        printf("%c ", root->value);
        InOrder(root->Rchild);
    }
}

bool BSTree::BSTSearch(TreeNode *root, int value)
{
    frequency++;
    if (!root)
        return false;
    if (root->value == value)
        return true;
    if (value < root->value)
        return BSTSearch(root->Lchild, value);
    return BSTSearch(root->Rchild, value);
}

int main()
{
    vector<char> data[10];
    printf("请输入10个字母： ");
    for (size_t i = 0; i < 10; i++)
    {
        char temp;
        cin >> temp;
        data->push_back(temp);
    }
    BSTree *tree = new BSTree(data);
    printf("该二叉查找树的先序遍历为：\n");
    tree->PreOrder(tree->root);
    printf("\n该二叉查找树的中序遍历为：\n");
    tree->InOrder(tree->root);
    char character;
    printf("\n请输入要查找的字母： ");
    cin >> character;
    if (tree->BSTSearch(tree->root, character))
        cout << "在树中找到了此字母，一共找了" << tree->frequency << "次";
    else
        cout << "没有在树中找到此字母，一共找了" << tree->frequency << "次";
}