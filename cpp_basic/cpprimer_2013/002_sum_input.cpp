#include <iostream>
/*
 * 简单循环, 计算输入数据和
 */
int main()
{
    // 提示输入两个数
    std::cout << "Enter numbers: " << std::endl;
    int value = 0, sum = 0;
    // 文件结束符(win ctrl+z,  unix ctrl+d) 或遇到无效输入时结束(非int)
    while (std::cin >> value)
    {
        std::cout << "value: " << value << std::endl;
        sum += value;
    }
    std::cout << "Sum is " << sum << std::endl;
    return 0;
}