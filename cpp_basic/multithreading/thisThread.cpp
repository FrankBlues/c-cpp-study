#include <iostream>
#include <chrono>
#include <thread>

using std::chrono::system_clock;

int main(int argc, char const *argv[])
{
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    struct std::tm *ptm = std::localtime(&tt);
    std::cout << ptm->tm_min << ":" << ptm->tm_sec << std::endl;
    std::cout << "Waiting for the next minute to begin...\n";
    ++ptm->tm_min;  // 加一分钟
    ptm->tm_sec = 0;  // 秒数设置为0

    //暂停执行，到下一整分执行
    std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
    
    std::cout << ptm->tm_min << ":" << ptm->tm_sec << std::endl;
    return 0;
}



