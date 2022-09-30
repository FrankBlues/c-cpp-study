#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;


void print(int n, const std::string &str)
{
    std::cout << "Printing integer: " << n << std::endl;  
    std::cout << "Printing string: " << str << std::endl;  
}


void thread_1()
{
    while(1)
    {
        cout<<"子线程1111"<<endl;
    }
}
void thread_2(int x)
{
    while(1)
    {
        cout<<"子线程2222"<<endl;
    }
}


int main(int argc, char const *argv[])
{
    // single thread example 
    // std::thread t1(print, 10, "hello");
    // t1.join();  // pausing the main function’s thread

    // multithread example
    // std::vector<std::string> svec = {"aa", "bb", "cc", "dd"};
    // std::vector<std::thread> threads;

    // for(decltype(svec.size()) i = 0; i < svec.size(); ++i)
    //     threads.push_back(std::thread(print, i, svec[i]));

    // for(auto &th : threads)
    //     th.join();
    

    // detach 不会等待子线程结束。如果主线程运行结束，程序则结束。
    // join 等待启动的线程完成，才会继续往下执行
    thread first ( thread_1);     // 开启线程，调用：thread_1()
    thread second (thread_2, 100);  // 开启线程，调用：thread_2(100)

    first.detach();                
    second.detach();            
    for(int i = 0; i < 10; i++)
    {
        std::cout << "主线程\n";
    }

    return 0;
}
