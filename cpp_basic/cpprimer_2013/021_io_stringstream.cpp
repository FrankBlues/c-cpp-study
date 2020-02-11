#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
#include <sstream> //使用stringstream

struct PersonInfo
{
    string name;
    vector<string> phones;
};


int main(int argc, char const *argv[])
{

    string line, word;  // 保存输入的一行和单词
    vector<PersonInfo> people;  // 保存所有记录
    while (getline(std::cin, line))  // 逐行从输入读取数据
    {
        PersonInfo info;
        std::istringstream record(line);  // 将数据记录绑定到刚读入的行
        // 解析输入的一行字符串
        record >> info.name;  // 读取名字
        while (record >> word)  // 读取电话
        {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }

    for(const auto &entry:people){
        std::ostringstream formatted, badNums;
        for(const auto &nums : entry.phones){  // 将所有phones输出到ostringstream
            formatted << " " << nums;
        }
        std::cout << entry.name << " "
                  << formatted.str() << std::endl;  // 统一打印ostringstream
    }
    
    return 0;
}
