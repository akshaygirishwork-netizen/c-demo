#include<stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node*next;
}sll;

sll*head=NULL;

void createNode(int num){

    sll*newNode;

    newNode = (sll*) malloc(sizeof(sll));
    newNode->next=NULL;
    newNode->data=num;

    if(head==NULL){
        head=newNode;\
        return;
    }
    sll*temp=head;

    while(temp->next){
        temp=temp->next;
    }
    temp->next=newNode;

}

void removeNode(){

    sll*next;

    while(head){
        next=head->next;
        free(head);
        head=next;
    }

}

void printData(){

    sll*temp=head;

    while(temp){
        printf("%d\n",temp->data);
        temp=temp->next;
    }
    // printf("%d\n",temp->data);

}

void reverseList(){

    if(head==NULL){
        printf("No data\n");
        return;
    }

    sll *prev,*next;
    prev=next=NULL;
    sll*curr=head;

    while(curr){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }

    head=prev;
    printData();
}

int main(){

    createNode(10);
    createNode(20);
    createNode(30);
    createNode(40);
    printData();
    reverseList();


    removeNode();
    return(0);
}