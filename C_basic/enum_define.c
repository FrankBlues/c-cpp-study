#include <stdio.h>

int main(){
    enum Season  {Spring,Summer,Autumn,Winter};
    enum Season s;
    s=Spring;
    s = 3;//Winter
    for (s=Spring;s<=Winter;s++){
        printf("枚举元素：%d \n",s);
    }
    return 0;
}
