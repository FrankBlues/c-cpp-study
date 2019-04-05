#include <stdio.h>

int sumAndMinus(int a,int b,int *minus){
    *minus = a - b;
    return a + b;
}


int main(){
    int a = 15 , b = 8;
    int sum,minus;
    sum = sumAndMinus(a,b,&minus);
    printf("a + b = %d,a - b = %d\n",sum,minus);   
    return 0;
}
