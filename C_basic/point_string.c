#include <stdio.h>

int main(){
    char *p;
    char s[] = {'m','j','\0'};
    p = s;
    for(; *p != '\0';p++){
        printf("%c",*p);
    }
    return 0;
}
