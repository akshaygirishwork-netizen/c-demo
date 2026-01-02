#include<stdio.h>

void swap(int *a,int*b){

    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;

}

void swap1(int *a,int*b){

    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;

}

void swap2(int *a,int*b){
    
    *a=*a * *b;
    *b=*a / *b;
    *a=*a / *b;


}

void main(){

    int a =13,b=31;
    printf("Before swap\n");
    printf("a=%d,b=%d\n",a,b);
    // swap(&a,&b);
    // swap1(&a,&b);

    swap2(&a,&b);

    printf("After swap\n");
    printf("a=%d,b=%d",a,b);

}