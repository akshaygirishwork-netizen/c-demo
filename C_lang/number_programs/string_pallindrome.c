#include<stdio.h>
#include <string.h>


int checkPall(char *s1){
    char *p=s1;
    char*q=s1+strlen(s1)-1;

    while(p<q){
        if(*p++ != *q--){
            return 0;
        }
    }
    return 1;
}

void main(){
    char s1[100];
    int i,j;

    printf("Enter a string\n");
    scanf("%s",s1);

    int l = strlen(s1);

    for(i=0,j=l-1;i<j;i++,j--){
        if(s1[i]!=s1[j]){
            break;
        }
    }

    // if(i>=j){
    //     printf("string is pallindrome\n");
    // }
    // else{
    //     printf("string is not pallindrome\n");
    // }

    if(checkPall(s1)){
        printf("string is pallindrome\n");
    }
    else{
        printf("string is not pallindrome\n");
    }
    
}