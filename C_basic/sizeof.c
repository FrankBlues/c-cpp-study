#include <stdio.h>
int main(){
    int a = 21;
    printf("内存字节数a：%d\n",sizeof a);
    printf("内存字节数a：%d\n",sizeof(a));
    printf("内存字节数double：%d\n",sizeof(double));
}
