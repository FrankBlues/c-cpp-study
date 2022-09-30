#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;  // 与unique_lock配合使用

int cargo = 0;
bool shipment_available() {return cargo != 0;}

void consume (int n)
{
    for (int i = 0; i < n; ++i)
    {
        mtx.lock();
        std::cout << "cargo = " << cargo << std::endl;
        std::cout << "ii = " << i << std::endl;
        std::cout << "子进程" << std::endl;
        mtx.unlock();
        std::unique_lock<std::mutex> lck(mtx);  // 自动上锁
        // 第二个参数为false才阻塞(wait),阻塞完即解锁
        cv.wait(lck, shipment_available);
        // std::cout << "iii = " << i << std::endl;
        // consume
        std::cout << cargo << std::endl;
        cargo = 0;  // cargo置0才能回到主线程
    }
}

int value;
void read_value()
{
    std::cin >> value;
    cv.notify_one();
}

int main(int argc, char const *argv[])  // 主进程
{
    int nn = 5;
    // wait test
    // std::thread consumer_thread(consume, nn);  // 子进程
    // for (int i = 0; i < nn; ++i)
    // {
    //     // 每次cargo为0才运行
    //     while (shipment_available()) std::this_thread::yield();
    //     mtx.lock();
    //     std::cout << "i = " << i << std::endl;
    //     std::cout << "主进程" << std::endl;
    //     mtx.unlock();
    //     std::unique_lock<std::mutex> lck(mtx);
    //     cargo = i + 1;
    //     // 每次cargo被置为0，会通知子线程unblock(非阻塞)，也就是子线程可以继续往下执行
    //     // 子线程中cargo被置为0后，wait又一次启动等待
    //     cv.notify_one();
    // }
    // consumer_thread.join();

    // wait for
    std::cout << "Please, enter an integer (I'll be printing dots): \n";
    std::thread th (read_value);

    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    // 通知或者超时都会解锁，所以主线程会一直打印
    while (cv.wait_for(lck,std::chrono::seconds(2))==std::cv_status::timeout) {
        std::cout << '.' << std::endl;
    }
    std::cout << "You entered: " << value << '\n';

    th.join();

    return 0;
}
