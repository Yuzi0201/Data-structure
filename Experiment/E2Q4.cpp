#include <iostream>
#include <string>
using namespace std;

typedef struct
{
    char c;
    int weight;
    int parent, Lchild, Rchild; //节点的双亲、左右孩子的下标
} * HuffmanTree, Treenode;

typedef char **HuffmanCode;

void select(HuffmanTree HT, int k, int &s1, int &s2);

void CreateHuffmanTree(HuffmanTree &HT, int Letter_freq[], int n)
{
    if (n <= 1)
        return;
    int m = 2 * n - 1;
    for (size_t i = 1; i < m; i++)
    {
        HT[i].parent = 0;
        HT[i].Lchild = 0;
        HT[i].Rchild = 0;
    }
    for (size_t i = 1; i <= n; i++) //1到n节点为叶子节点，将原始数据存入
    {
        for (int j = 0; 1; j++)
        {
            if (Letter_freq[j])
            {
                HT[i].c = j;
                HT[i].weight = Letter_freq[j];
                Letter_freq[j] = 0;
                break;
            }
        }
    }
    /*初始化结束，开始创建树*/
    int s1, s2;
    for (size_t i = n + 1; i <= m; i++)
    {
        select(HT, i - 1, s1, s2); //在HT[k](1<=k<=i-1)中选择两个双亲为0且权值最小的节点，并返回其序号s1,s2
        HT[s1].parent = i;
        HT[s2].parent = i; //新节点i，将s1和s2的双亲置为i，i的左右孩子置为s1，s2
        HT[i].Lchild = s1;
        HT[i].Rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight; //i权值为左右孩子权值之和
    }
    HT[m].parent = 0; //根节点的双亲置空
}

void writein_freq_to_array(string s, int Letter_freq[], int length, int &n)
{
    for (size_t i = 0; i < length; i++)
        Letter_freq[s[i]]++;         //char类型会自动转换为int类型，对应的是ASCII码表的位置
    Letter_freq[32] = 0;             //空格不算字符
    for (size_t i = 0; i < 128; i++) //统计字符种类数，即n
        if (Letter_freq[i])
            n++;
}

void select(HuffmanTree HT, int k, int &s1, int &s2)
{
    s1 = 0;
    s2 = 0;
    int i = 1;
    while (!s2) //初始化s1,s2(s1<s2)
    {
        if (HT[i].parent) //有双亲节点的（相当于已经脱离了森林的）跳过不计
        {
            i++;
            continue;
        }
        if (!s1)
        {
            s1 = i++;
            continue;
        }
        if (HT[i].weight < HT[s1].weight)
        {
            s2 = s1;
            s1 = i++;
        }
        else
        {
            s2 = i++;
        }
    }

    for (; i <= k; i++) //i继续沿用上面的i
    {
        if (HT[i].parent) //有双亲节点的（相当于已经脱离了森林的）跳过不计
            continue;
        if (HT[i].weight >= HT[s2].weight)
            continue;
        if (HT[i].weight <= HT[s1].weight)
        {
            s2 = s1;
            s1 = i;
        }
        else //大于s1的权值又小于s2的权值的
            s2 = i;
    }
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    char *cd = new char[n]; //临时存放每个字符编码的数组空间
    cd[n - 1] = '\0';
    int start, c, f;
    for (size_t i = 1; i <= n; i++)
    {
        start = n - 1; //开始时指向最后(结束符)
        c = i;
        f = HT[i].parent;
        while (f) //从叶子向上回溯直到根
        {
            start--;
            if (c == HT[f].Lchild) //若c为parent的左孩子，置编码0
                cd[start] = '0';
            else //若c为parent的右孩子，置编码1
                cd[start] = '1';
            c = f;
            f = HT[f].parent; //继续向上
        }
        HC[i] = new char[n - start]; //为第i节点编码分配空间
        int j;
        for (j = 0; start <= n - 1; start++, j++)
            HC[i][j] = cd[start]; //将临时空间中的内容复制到HC[i]中
    }
    delete cd;
}

int main()
{
    string s = "The Chinese official said he viewed the Trump Presidency not as an aberration but as the product of a failing political system. This jibes with other accounts. The Chinese leadership believes that the United States, and Western democracies in general, haven't risen to the challenge of a globalized economy, which necessitates big changes in production patterns, as well as major upgrades in education and public infrastructure. In Trump and Trumpism, the Chinese see an inevitable backlash to this failure.";
    int length = s.length();
    int Letter_freq[128] = {}; //对应ASCII码表的128位
    int n = 0;
    writein_freq_to_array(s, Letter_freq, length, n);
    int m = 2 * n - 1;
    HuffmanTree HT = new Treenode[m + 1]; //0号未用，分配m+1个，HT[m]为根节点
    CreateHuffmanTree(HT, Letter_freq, n);
    printf("出现的字符及频率为：\n");
    for (size_t i = 1; i <= n; i++)
    {
        cout << HT[i].c << " " << HT[i].weight << endl;
    }
    printf("哈夫曼树为：\n节点序号 权值(频率) 左孩子 右孩子 双亲 字符\n");
    for (size_t i = 1; i <= n; i++)
        cout << i << " " << HT[i].weight << " " << HT[i].Lchild << " " << HT[i].Rchild << " " << HT[i].parent << " " << HT[i].c << endl;
    for (size_t i = n + 1; i <= m; i++)
    {
        cout << i << " " << HT[i].weight << " " << HT[i].Lchild << " " << HT[i].Rchild << " " << HT[i].parent << endl;
    }
    HuffmanCode HC = new char *[n + 1];
    CreateHuffmanCode(HT, HC, n);
    printf("哈夫曼编码为：\n");
    for (size_t i = 1; i <= n; i++)
    {
        cout << HT[i].c << ": " << HC[i] << endl;
    }
}