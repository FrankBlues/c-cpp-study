#include <stdio.h>
//数组名字代表内存地址
//数组作为变量
void test(int b[]){
    b[0] = 9;
}

int main()
{
    int a[3];
    a[0] = 10;
    printf("a[0] = %d \n",a[0]);
    test(a);
    printf("a[0] = %d \n",a[0]);
    return 0;
}
