#include <iostream>
#include <thread>
#include <future>
#include <unistd.h>

using namespace std;

double t1(const double a, const double b)
{
    double c = a + b;
    sleep(3);  // 假设t1函数是个复杂的计算过程，需要消耗3秒
    return c;
}

int main(int argc, char const *argv[])
{
    double a = 2.3;
	double b = 6.7;
	future<double> fu = async(t1, a, b);//创建异步线程线程，并将线程的执行结果用fu占位；
	cout << "正在进行计算" << endl;
	cout << "计算结果马上就准备好，请您耐心等待" << endl;
	cout << "计算结果：" << fu.get() << endl;//阻塞主线程，直至异步线程return
    return 0;
}
