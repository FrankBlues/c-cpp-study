#include <stdio.h>

void swap(char a,char b){
    char temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_p(char *a,char *b){
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    char a = 8;
    char b = 10;
    printf("befor swap: a = %d,b = %d\n",a,b);

    swap_p(&a,&b);
    printf("after swap: a = %d,b = %d\n",a,b);

}
