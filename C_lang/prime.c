#include<stdio.h>

void main(){
    int num,i;

    printf("enter a number to check prime\n");
    scanf("%d",&num);   

    for( i=2;i<num;i++){
        if(num%i==0){
            break;
        }
    }
    if(num==i){
        printf("NO is prime\n");
    }
    else{
        printf("NO is not prime\n");
    }
}