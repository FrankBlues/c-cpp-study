#include <iostream>
#include <vector>
#include <string>

#include <algorithm>

using namespace std;

// 可以将此函数作为“谓词”供sort函数调用
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

// 去除重复单词
void elimDups(vector<string> &words)
{
    // 按字典顺序排序words
    sort(words.begin(), words.end());
    // unique 重排输入范围 使得每个单词只出现一次
    auto end_unique = unique(words.begin(), words.end());
    // 使用向量操作erase删除重复单词
    words.erase(end_unique, words.end());
}

void printVec(vector<string> &words)
{
    for (const auto &w : words)
    {
        cout << w << " ";
    }
    cout << endl;
}

// 只打印大于等于给定长度的词
void biggies(vector<string> &words,
              vector<string>::size_type sz)
{
    elimDups(words);  // 将words按字典序排序，删除重复单词
    // 按长度排序，长度相同的单词维持字典序
    stable_sort(words.begin(), words.end(), isShorter);
    // 获取迭代器 指向第一个满足size >=sz的元素
    // 计算满足size >=sz的元素数码
    // 打印长度大于等于给定值的单词
}


int main(int argc, char const *argv[])
{
    vector<string> words{"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    // sort(words.begin(), words.end());
    // elimDups(words);
    // printVec(words);
    // 重载默认vec 先按长度排序然后采用默认的字典排序
    // sort(words.begin(), words.end(), isShorter);
    // printVec(words);

    // stable 保持原来列表的顺序
    stable_sort(words.begin(), words.end(), isShorter);
    printVec(words);
    return 0;
}
