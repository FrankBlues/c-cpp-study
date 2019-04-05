#include <stdio.h>

int main(){
    struct Student{
        char *name;
        int age;
    };    
    //初始化
    struct Student stu0 = {"mj",27};
    printf("stu0'age is %d.\n",stu0.age);

    return 0;
}
