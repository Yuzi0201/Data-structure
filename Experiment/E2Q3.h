#include <iostream>

struct BinTree
{
    char data;
    BinTree *Lchild;
    BinTree *Rchild;
};

struct Sequential_ordered_Tree
{
    char data;
    Sequential_ordered_Tree *Lchild;
    int Ltag;
    Sequential_ordered_Tree *Rchild;
    int Rtag;
};

void Seq_Order(BinTree *b)
{
}