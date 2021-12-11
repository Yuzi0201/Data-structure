#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

void Binary_Search(vector<char> data, int result[2])
{
    int mid, start = 0, end = data.size() - 1;
    char input;
    cin >> input;
    result[1] = 0; //数组第一个存是否找到，找到为1，没找到为0，第二个存比较次数
    while (start <= end)
    {
        mid = (start + end) / 2;
        result[1]++;
        if (data[mid] < input)
        {
            start = mid + 1;
        }
        else if (data[mid] > input)
        {
            end = mid - 1;
        }
        else
        {
            result[0] = 1;
            return;
        }
    }
    result[0] = 0;
    return;
}

int main()
{
    int length = 16;
    vector<char> data;
    for (size_t i = 97; i <= 122; i++) //将ASCII中a-z放入容器
    {
        data.push_back(i);
    }
    srand((unsigned)time(NULL));
    random_shuffle(data.begin(), data.end());      //将a-z随机打乱
    data.erase(data.begin() + length, data.end()); //删除第16-25项，只保留前16项（即0-15项）组成原始数据
    cout << "请输入一个字母： ";
    sort(data.begin(), data.end()); //进行排序
    int result[2];
    Binary_Search(data, result);
    if (result[0])
        cout << "找到该字母，比较次数为" << result[1] << endl;
    else
        cout << "该字母不在随机数列中！比较次数为" << result[1] << endl;
}