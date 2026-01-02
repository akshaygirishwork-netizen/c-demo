#include<stdio.h>

void printBinary(int num){
    static int pos=31;

    if(pos>=0){
        printf("%d",num>>pos&1);
        pos--;
        printBinary(num);
    }
    else{
        pos=31;
    }

}

void main(){

    int num1=10,num2=20;

    printBinary(num1);
    printf("\n");
    printBinary(num2);

}