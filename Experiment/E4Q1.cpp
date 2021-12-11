#include <iostream>
#include <time.h>
using namespace std;

void PrintCurruntArray(int arr[], int length) //输出当前数组
{
    for (size_t i = 0; i < length; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void Insertion_Sort(int arr[], int len) //插入排序
{
    for (int i = 1; i < len; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while ((j >= 0) && (key < arr[j])) //直到比key小的值之前，不断地与前值交换，向前靠拢
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; //将key置到有序区末尾
        PrintCurruntArray(arr, len);
    }
}

void Selection_Sort(int arr[], int len) //选择排序
{
    for (size_t i = 0; i < len - 1; i++)
    {
        int min = i;
        for (size_t j = i + 1; j < len; j++)
            if (arr[j] < arr[min]) //找寻无序区内最小值
                min = j;
        swap(arr[min], arr[i]); //将最小值置于有序区末尾
        PrintCurruntArray(arr, len);
    }
}

void Bubble_Sort(int arr[], int len) //冒泡排序
{
    for (size_t i = 0; i < len - 1; i++)
    {
        for (size_t j = 0; j < len - 1 - i; j++)
            if (arr[j] > arr[j + 1]) //若j比j+1项大，就将其交换
                swap(arr[j], arr[j + 1]);
        PrintCurruntArray(arr, len);
    }
}

void Cocktail_Sort(int arr[], int len) //鸡尾酒（双向冒泡）排序
{
    int tail = len - 1;
    for (int i = 0; i < tail;)
    {
        for (int j = tail; j > i; --j) //第一轮，先将最小的数据排到前面
        {
            if (arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
        }
        i++; //原来i处数据已排好序，加1
        PrintCurruntArray(arr, len);
        for (int j = i; j < tail; ++j) //第二轮，将最大的数据排到后面
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        tail--; //原tail处数据也已排好序，将其减1
        PrintCurruntArray(arr, len);
    }
}

int Paritition(int arr[], int low, int high)
{
    int pivot = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] >= pivot)
        {
            --high;
        }
        arr[low] = arr[high]; //把右边小于pivot的扔到位于左边的pivot所在位置（第一次）//把右边小于pivot的扔到（左边刚刚扔到右边的数）位置（第二次及后续）
        while (low < high && arr[low] <= pivot)
        {
            ++low;
        }
        arr[high] = arr[low]; //把左边大于pivot的扔到（右边刚刚扔到左边的数）的位置
    }
    arr[low] = pivot; //把pivot扔到（最后一次左边扔到右边的数）的位置
    //此时，小于pivot的数全在其左边，大于pivot的数，全在其右边
    return low; //将pivot所在位置返回
}

void Quick_Sort(int arr[], int low, int high, int len) //快排母函数
{
    if (low < high) //递归，若此分区已排好（low=high）则返回，否则继续排
    {
        int pivot = Paritition(arr, low, high);
        Quick_Sort(arr, low, pivot - 1, len);
        Quick_Sort(arr, pivot + 1, high, len);
        PrintCurruntArray(arr, len);
    }
}

void Merge_Sort_Recursive(int arr[], int reg[], int start, int end, int total_len)
{
    if (start >= end) //各分区分完了，就开始返回
        return;
    int len = end - start, mid = (len / 2) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    Merge_Sort_Recursive(arr, reg, start1, end1, total_len); //递归分区，分左边
    Merge_Sort_Recursive(arr, reg, start2, end2, total_len); //递归分区，分右边
    int k = start;
    while (start1 <= end1 && start2 <= end2) //开始合并，先左右分区一起排
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1) //若左分区有剩余，则继续排完左分区
        reg[k++] = arr[start1++];
    while (start2 <= end2) //若右分区有剩余，则继续排完右分区
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++) //将排好的临时数组放回原数组中
        arr[k] = reg[k];
    PrintCurruntArray(arr, total_len);
}

void Merge_Sort(int arr[], int len) //二路归并排序
{
    int reg[len];
    Merge_Sort_Recursive(arr, reg, 0, len - 1, len);
}

int main()
{
    srand((unsigned)time(NULL));
    int data[6][16];
    int length = end(data[0]) - begin(data[0]);
    printf("原始数据为：\n");
    for (size_t i = 0; i < length; i++)
    {
        data[0][i] = (rand() % 90) + 10;
        cout << data[0][i] << " ";
    }
    for (size_t i = 1; i < 6; i++) //有6个算法，创造6个一样的数组供其使用
        for (size_t j = 0; j < length; j++)
            data[i][j] = data[0][j];
    printf("\n插入排序及其过程为：\n");
    Insertion_Sort(data[0], length);
    printf("\n选择排序及其过程为：\n");
    Selection_Sort(data[1], length);
    printf("\n冒泡排序及其过程为：\n");
    Bubble_Sort(data[2], length);
    printf("\n双向冒泡排序及其过程为：\n");
    Cocktail_Sort(data[3], length);
    printf("\n快速排序及其过程为：\n");
    Quick_Sort(data[4], 0, length - 1, length);
    printf("\n二路归并排序及其过程为：\n");
    Merge_Sort(data[5], length);
}