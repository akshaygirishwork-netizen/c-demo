#include<stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int data;
    struct stack *next;
}sll;

sll*top=NULL;

void push(int num){

    sll*new=(sll*) malloc(sizeof(sll));
    
    new->data=num;    
    new->next=top;
    top=new;

}

int pop(){

    if(top == NULL){
        printf("stack underflow\n");
        return -1;
    }

    sll*temp;

    temp=top;
    int val = top->data;
    top=top->next;
    free(temp);

    return val;

}

int peek(){

    if(top==NULL){
        printf("stack is empty\n");
        return -1;
    }
    return (top->data);
}

int main(){

    push(10);
    push(20);
    push(30);
    push(40);
    push(50);

    printf("peek=%d\n",peek());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("peek=%d\n",peek());
    
    return 0;
}