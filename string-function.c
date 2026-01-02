#include<stdio.h>

void main(){

    char s[100];

    printf("enter a string\n");
    scanf("%[^\n]s",s);

    char *start,*end;
    start=end=s;

    while(*start){
        while(*start == ' ')
            start++;
        
        end=start;
    
        while(*end != ' ' &&  *end)
            end++;

        char* left = start;
        char *right = end-1;

        while(left < right){
            char t=*left;
            *left=*right;
            *right=t;
            left++;
            right--;
        }
        start=end;
    }
    printf("%s\n",s);
}