#include <stdio.h>
#include <string.h>

int main(){
    //定义字符串，用指针指向，这里s是常量
    char *s = "mj";
    int len = strlen(s);
    printf("String length:%d\n",len);
    return 0;
}
