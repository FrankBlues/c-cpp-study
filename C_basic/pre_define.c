#include <stdio.h>

#define PI 3.14
//参数名和结果最好用括号括住
#define average(a,b) (((a) + (b))/2)
int main(){
    printf("average=%d\n",average(10,4));
    printf("%f\n",PI);
    return 0;
}
//取消定义的宏
#undef PI
