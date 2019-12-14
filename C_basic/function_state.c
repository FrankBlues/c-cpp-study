#include <stdio.h>
//必须声明在main函数前
int sum(int a,int b);

int main(){
    int c = sum(1,4);
    printf("%d",c);
    return 0;
}

//定义
int sum(int a,int b)
{
    return a + b;
}
