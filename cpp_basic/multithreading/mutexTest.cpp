#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m;  // 实例化m对象，不要理解为定义变量

void proc1(int a)
{
    m.lock();  // 调用线程将该互斥量锁住
    cout << "proc1函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 2 << endl;
    m.unlock();  // 解锁供其它线程使用
}

void proc2(int a)
{
    m.lock();
    cout << "proc2函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 1 << endl;
    m.unlock();
}

void proc3(int a)
{
    lock_guard<mutex> g1(m);//用此语句替换了m.lock()；lock_guard传入一个参数时，该参数为互斥量，此时调用了lock_guard的构造函数，申请锁定m
    cout << "proc3函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 2 << endl;
}//此时不需要写m.unlock(),g1出了作用域被释放，自动调用析构函数，于是m被解锁

void proc4(int a)
{
    {
        lock_guard<mutex> g2(m);
        cout << "proc4函数正在改写a" << endl;
        cout << "原始a为" << a << endl;
        cout << "现在a为" << a + 1 << endl;
    }//通过使用{}来调整作用域范围，可使得m在合适的地方被解锁
    cout << "作用域外的内容3" << endl;
    cout << "作用域外的内容4" << endl;
    cout << "作用域外的内容5" << endl;
}

void proc5(int a)
{
    m.lock();//手动锁定
    lock_guard<mutex> g1(m, adopt_lock);
    cout << "proc5函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 2 << endl;
}//自动解锁

void proc6(int a)
{
    lock_guard<mutex> g2(m);//自动锁定
    cout << "proc6函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 1 << endl;
}//自动解锁

void proc7(int a)
{
    unique_lock<mutex> g1(m, defer_lock);//始化了一个没有加锁的mutex
    cout << "不拉不拉不拉" << endl;
    g1.lock();//手动加锁，注意，不是m.lock();注意，不是m.lock();注意，不是m.lock()
    cout << "proc7函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 2 << endl;
    g1.unlock();//临时解锁
    cout << "不拉不拉不拉"  << endl;
    g1.lock();
    cout << "不拉不拉不拉" << endl;
}//自动解锁

void proc8(int a)
{
    unique_lock<mutex> g2(m,try_to_lock);//尝试加锁，但如果没有锁定成功，会立即返回，不会阻塞在那里；
    cout << "proc8函数正在改写a" << endl;
    cout << "原始a为" << a << endl;
    cout << "现在a为" << a + 1 << endl;
}//自动解锁

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  m.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  m.unlock();
}

int main(int argc, char const *argv[])
{
    int a = 0;
    // lock unlock
    // thread p1(proc1, a);
    // thread p2(proc2, a);
    // p1.join();
    // p2.join();
    std::thread th1 (print_block,20,'*');//线程1：打印*
    std::thread th2 (print_block,20,'$');//线程2：打印$

    th1.join();
    th2.join();

    // lock guard  作用域内自动加锁解锁
    // thread p3(proc3, a);
    // thread p4(proc4, a);
    // p3.join();
    // p4.join();

    // lock grard adopt_lock 需提前手动锁定
    // thread p5(proc5, a);
    // thread p6(proc6, a);
    // p5.join();
    // p6.join();

    // unique_lock 用法更加丰富 可以手动lock()与手动unlock() 支持adopt_lock/try_to_lock/defer_lock参数
    // thread p7(proc7, a);
    // thread p8(proc8, a);
    // p7.join();
    // p8.join();


    return 0;
}
