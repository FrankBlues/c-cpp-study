#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 读取文件 写入vector
vector<string> open_file(const string& fn)
{
    // 读取的临时量
    string s;
    vector<string> temp;
    ifstream in(fn);
    // while (getline(in, s))  // 逐行写入vector
    while (in >> s)  // 以空格为间隔，把每一个词写出
    {
        temp.push_back(s);
    }
    // cout << strs.size() << endl;
    in.close();
    return temp;
}

int main(int argc, char const *argv[])
{
    // 注意是用的WSL 在linux下 文件路径
    string in_file("/mnt/d/temp/t.txt");
    vector<string> strs = open_file(in_file);
    

    string out_file("/mnt/d/temp/to.txt");
    ofstream of;
    // 默认out写入模式，文件内容会丢失 app 会在每次操作文件前 定位到文件末尾
    of.open(out_file, ofstream::out | ofstream::app);
    for(auto i: strs){
        cout << i << endl;  // 打印在控制台
        of << i << endl;  // 写出到文件
    }
    of.close();
    return 0;
}
