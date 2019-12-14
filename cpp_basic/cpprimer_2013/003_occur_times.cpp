#include <iostream>
/*
 * 判断语句, 统计输入数值连续出现次数
 */
int main()
{
    //
    int currVal = 0, val = 0;
    // 读取第一个数,并确保确实有数据可以处理
    if (std::cin >> currVal)
    {
        int cnt = 1;
        while (std::cin >> val)
        {
            if (val == currVal)
            {
                ++cnt;
            }
            else
            {
                std::cout << currVal << " occurs " << cnt << " times." << std::endl;
                currVal = val;
                cnt = 1;
            }
        }
        // 最后一个值连续出现的次数
        std::cout << currVal << " occurs " << cnt << " times." << std::endl;
    }
    return 0;
}