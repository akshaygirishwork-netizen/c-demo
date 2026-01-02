#include<stdio.h>

int fact(int num){

    if(num){
        return num*fact(num-1);
    }
    else{
        return 1;
    }

}

void main(){

    int num=5;
    int r;

    r=fact(num);

    printf("%d\n",r);
}