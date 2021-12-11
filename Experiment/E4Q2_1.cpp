#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

int Sequential_search(vector<char> data)
{
    char input;
    cin >> input;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i] == input)
            return i + 1;
    }
    return 114514;
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
    int result = Sequential_search(data);
    if (result != 114514)
        cout << "找到该字母位于随机数列的第" << result << "位，比较次数为" << result << endl;
    else
        cout << "该字母不在随机数列中！" << endl;
    cout << endl;
}