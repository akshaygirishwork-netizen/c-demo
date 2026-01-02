#include <stdio.h>

int main()
{
    char *a[] = {"akshay","girish", "hello", "world"};

    char**p =a;


    printf("%ld",sizeof(a));
    printf("%s",*a);
    printf("%s",*(a+1));
}