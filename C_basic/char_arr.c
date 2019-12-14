#include <stdio.h>
//字符串在c中表示为字符数组，以\0结束
int main(){
    char a[3] = {'m','j','\0'};
    char b[3] = "mj";
    char d[] = "mj";
    char e[20] = "mj";
    printf("a = %s 内存地址：%x\n",a,a);
    return 0;
}
