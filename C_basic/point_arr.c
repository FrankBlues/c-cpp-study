#include <stdio.h>
//指针遍历数组
int main(){
    int a[4] = {1,3,5,8};
    int *p = a;
    int i;
    for (i = 0;i<4;i++){
        printf("a[%d] = %d\n",i,*(p + i));

    };
    return 0;
}
