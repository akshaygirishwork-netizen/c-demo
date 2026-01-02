#include<stdio.h>
void main(){

    unsigned short int y1;

    unsigned short int x=0xABCD; // 0xDCAB

    printf("%x\n",x);

    y1 = (x&(0x000F))<< 12 | (x&(0x00F0))<< 4 | (x&(0x0F00))>> 8 |(x&(0xF000))>> 8;

    printf("%x\n",y1);

}