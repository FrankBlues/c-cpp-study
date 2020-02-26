/*
几种顺序容器
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> vs{"Mil", "Jim", "Austin"};  // 优先选用 随机访问快 但是中间插入删除慢
    vs.push_back("Lucy");
    vs.insert(vs.begin(), "Lily");  // vector不支持push_front，但可以用insert
    vs.insert(vs.begin(), 10, "Lily");  // 插入10个

    deque<string> ds{"Mil", "Jim", "Austin"};  // 随机访问快 两端插入删除快
    ds.push_front("Lucy");  // 插入元素
    list<string> ls{"Mil", "Jim", "Austin"};  // 中间插入删除快 随机访问慢  可选择先用list最后拷贝到vector
    list<string> ls3(10); // 初始化 10个元素 默认空字符
    forward_list<string> fls{"Mil", "Jim", "Austin"};  // 单向list

    list<string> ls2(ls);  // 拷贝方式初始化 两个容器类型相同 内容类型相同
    deque<string> ds2(vs.begin(), vs.begin()+1);  // 拷贝内容 内容类型相同即可
    array<int, 10> ai = {1};  // array为固定大小 初始化时需指定大小  允许进行拷贝和对象赋值操作
    // ai = {0};  // 错误

    swap(ds, ds2);  // 交换两个相同容器的内容

    string s2 = "pi = 3.14";
    // 转换s2中以数字开始的第一个字串 转换成浮点数
    double d = stod(s2.substr(s2.find_first_of("+-.0123456789")));


    // 删除偶数元素，复制每个奇数元素
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = vi.begin();
    while (iter != vi.end())
    {
        if(*iter%2){
            iter = vi.insert(iter, *iter); // 复制当前元素 insert 指向插入后的新元素
            iter +=2;  // 向前移动
        }else{
            iter = vi.erase(iter);  // 删除偶数元素
            // 删除后 iter指向之后的元素 不需要 ++iter
        }
    }

    // capacity: 容器预先分配的内存 size: 容器实际大小
    vector<int> ivec;
    cout << "size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;  // 0
    // 添加24个元素
    for (vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);
    cout << "size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;  // size:24  c:32
    ivec.reserve(50);  // 让capacity 至少设定为50
    cout << "size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // 填满容器
    while (ivec.size() != ivec.capacity())
    {
        ivec.push_back(0);
    }
    cout << "size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    
    ivec.push_back(24);  // 添加元素 超出capacity , capacity 重新分配
    cout << "size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    
    ivec.shrink_to_fit();  // 要求归还内存 系统不保证退回
    cout << "size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // for(auto d: vi){
    //     cout << d << endl;
    // }
    return 0;
}
