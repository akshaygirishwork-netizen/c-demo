#include<stdio.h>

void printChar(char*p){

    if(*p){
        printf("%c ",*p);
        printChar(++p);
    }
    
}

void main(){

    char s[]= "akshay girish";

    printChar(s);
}
