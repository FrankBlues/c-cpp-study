#include <iostream>
#include <vector>
#include <list>
#include <string>

#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
using namespace std::placeholders;

using namespace std;

void printVec(vector<string> &);

// 可以将此函数作为“谓词”供sort函数调用
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}


// 去除重复单词
void elimDups(vector<string> &words)
{
    // so rt words alphabetically so we can find the duplicates
    sort(words.begin(), words.end());
    //printVec(words);
    // unique reorders the input range so that each word appears once in the
    // front portion of the range and returns an iterator one past the unique range
    auto end_unique = unique(words.begin(), words.end());
    // printVec(words);
    // 使用向量操作erase删除重复单词
    words.erase(end_unique, words.end());
    // printVec(words);
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
    stable_sort(words.begin(), words.end(), 
        [](const string &s1, const string &s2)
            {return s1.size() < s2.size();});
    // 获取迭代器 指向第一个满足size >=sz的元素
    auto wc = find_if(words.begin(), words.end(),
        [sz](const string &s)
            {return s.size() >= sz;});
    // 计算满足size >=sz的元素
    auto count = words.end() - wc;
    cout << count << endl;
    // 打印长度大于等于给定值的单词
    for_each(wc, words.end(),
        [](const string &w){cout << w << " ";});
    cout << endl;
}

void excise101()
{
    vector<int> ivec{2, 3, 4, 5, 9, 8, 9, 4, 5, 2};
    auto c = count(ivec.cbegin(), ivec.cend(), 5);
    cout << c << endl;
    int sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
    cout << sum << endl;
}

void excise105()
{
    vector<int> ivec(10);
    fill_n(ivec.begin(), ivec.size(), 0);

    fill_n(back_inserter(ivec), 10, 0);  //插入新
    //cout << sum << endl;
}

void excise106()
{
    vector<string> svec{"hello", "world", "!"};
    list<const char*> cvec{"hello", "world", "!", "!!"};
    bool b = equal(svec.begin(), svec.end(), cvec.begin());
    cout << b << endl;
    string sum = accumulate(cvec.cbegin(), cvec.cend(), string(""));
    cout << sum << endl;
}

bool have5more(const string &s)
{
    return s.size() >= 5;
}

/// Print the elements that have five or more characters.
void excese1013(vector<string> &words)
{
    auto iter = partition(words.begin(), words.end(), have5more);
    words.erase(iter, words.end());
}

void excese1018(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);  // 将words按字典序排序，删除重复单词
    // 按长度排序，长度相同的单词维持字典序
    stable_sort(words.begin(), words.end(), 
        [](const string &s1, const string &s2)
            {return s1.size() < s2.size();});
    // 获取迭代器 指向第一个满足size >=sz的元素
    auto wc = stable_partition(words.begin(), words.end(),
        [sz](const string &s)
            {return s.size() >= sz;});
    // 计算满足size >=sz的元素
    auto count = wc - words.begin();
    cout << count << endl;
    // 打印长度大于等于给定值的单词
    for_each(words.begin(), wc,
        [](const string &w){cout << w << " ";});
    cout << endl;
}

void excese1020(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);  // 将words按字典序排序，删除重复单词
    // 按长度排序，长度相同的单词维持字典序
    stable_sort(words.begin(), words.end(), 
        [](const string &s1, const string &s2)
            {return s1.size() < s2.size();});
    // 获取迭代器 指向第一个满足size >=sz的元素
    auto wc = stable_partition(words.begin(), words.end(),
        [sz](const string &s)
            {return s.size() >= sz;});
    // 计算满足size >=sz的元素
    auto count = wc - words.begin();
    auto ct = count_if(words.begin(), words.end(),
        [=](const string &s)
            {return s.size() >= sz;});
    cout << ct << endl;
    // 打印长度大于等于给定值的单词
    for_each(words.begin(), wc,
        [](const string &w){cout << w << " ";});
    cout << endl;
}

void excese1021()
{
    int i = 10;
    auto f = [&i]() -> bool
        {while (i > 0) --i;
         return true;};
    if (f())
        cout << i << endl;

}

bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

/// (bind) vector of ints that has a value greater than the length of a specified string value.
void excese1024()
{
    vector<int> ivec = {1, 3, 5, 7, 9};
    string s("hello");
    auto iter = find_if_not(ivec.begin(), ivec.end(), bind(check_size, ref(s), _1));
    cout << *iter << endl;
}


/// 1020 use bind
void excese1025(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);  // 将words按字典序排序，删除重复单词
    // 按长度排序，长度相同的单词维持字典序
    stable_sort(words.begin(), words.end(), isShorter);
    // 获取迭代器 指向第一个满足size >=sz的元素
    auto wc = stable_partition(words.begin(), words.end(),
        bind(check_size, _1, sz));
    // 计算满足size >=sz的元素
    auto count = wc - words.begin();
    auto ct = count_if(words.begin(), words.end(),
        bind(check_size, _1, sz));
    cout << ct << endl;
    // 打印长度大于等于给定值的单词
    for_each(words.begin(), wc,
        [](const string &w){cout << w << " ";});
    cout << endl;
}

/// uses unique_copy to copy the unique elements from a vector into an
/// initially empty list.
void excese1027()
{
    vector<string> svec = {"hello", "hello", "world"};
    list<string> slst;
    unique_copy(svec.begin(), svec.end(), back_inserter(slst));
    for_each(slst.begin(), slst.end(), [](const string &w){cout << w << " ";});
    cout << endl;
}

void excese1029()
{
    
    istream_iterator<string>  in_iter(cin), eof;
    // vector<string> svec;
    vector<string> svec(in_iter, eof);
    // while (in_iter != eof)
    // {
    //     svec.push_back(*in_iter++);
    // }
    printVec(svec);
    
}

void excese1030()
{
    
    istream_iterator<int>  in_iter(cin), eof;
    vector<int> ivec(in_iter, eof);
    sort(ivec.begin(), ivec.end());

    ostream_iterator<int> out_iter(cout, " ");
    // for (auto i: ivec)
    //     *out_iter++ = i;
    copy(ivec.cbegin(), ivec.cend(), out_iter);
    cout << endl;
}

void excese1034()
{
    vector<int> ivec{0, 1, 0, 2, 3, 4, 5, 6, 7, 8, 9};

    ostream_iterator<int> out_iter(cout, " ");
    // copy(ivec.crbegin(), ivec.crend(), out_iter);
    // cout << endl;

    auto end = ivec.cend() - 1;
    while(end >= ivec.cbegin())
        cout << *end-- << " ";
    cout << endl;

    auto it = find(ivec.crbegin(), ivec.crend(), 0);
    list<int> ilst;
    // copy(ivec.crbegin() + 3, ivec.crbegin() + 7, back_inserter(ilst));
    copy(ivec.cbegin() + 3, ivec.cbegin() + 7, front_inserter(ilst));
    
    copy(ilst.cbegin(), ilst.cend(), out_iter);
    cout << endl;
}

// 去除重复单词 list有单独的算法
void elimDupsList(list<string> &words)
{
    // so rt words alphabetically so we can find the duplicates
    words.sort();
    // unique reorders the input range so that each word appears once in the
    // front portion of the range and returns an iterator one past the unique range
    words.unique();
    ostream_iterator<string> os_iter(cout, " ");
    copy(words.begin(), words.end(), os_iter);
    cout << endl;
}

int main(int argc, char const *argv[])
{
    excise105();
    vector<string> words{"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    list<string> words1{"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    // sort(words.begin(), words.end());
    // elimDups(words);
    // printVec(words);
    // 重载默认vec 先按长度排序然后采用默认的字典排序
    // sort(words.begin(), words.end(), isShorter);
    // printVec(words);

    // stable 保持原来列表的顺序
    // stable_sort(words.begin(), words.end(), isShorter);
    // printVec(words);
    // stable_sort(words.begin(), words.end(), 
    //     [](const string &s1, const string &s2){return s1.size() < s2.size();});  // lambda
    // printVec(words);

    // biggies(words, 4);
    // excese1018(words, 4);
    // excese1020(words, 5);
    // excese1021();
    // excese1024();
    // excese1025(words, 5);
    // excese1027();
    // excese1029();
    // excese1030();
    // excese1034();
    // excese1013(words);
    // printVec(words);
    elimDupsList(words1);
    return 0;
}
