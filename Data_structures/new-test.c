#include <stdio.h>
#include <stdlib.h>

typedef struct student 
{
    
    int mark;
    struct student * next;

}sll;

void createNode(sll**head,int num){
    
    sll * newnode= (sll*) malloc(sizeof(sll));

    newnode->mark=num;
    newnode->next=0;

    if(*head==NULL){
        *head=newnode;
        return;
    }
    newnode->next=*head;
    *head=newnode;
}

void printData(sll*head){

    if(head == NULL){
        printf("NO data\n");
        return;
    }

    sll * temp = head;

    while(temp){
        printf("%d  ",temp->mark);
        temp=temp->next;
    }
    printf("\n");
}

void delateData(sll **head,int num){
    
    sll dummy = {0};

    sll * prev = &dummy;

    sll * curr = dummy.next = *head;

    while(curr != NULL){

        if(curr->mark == num ){
            prev->next = curr ->next;
            free(curr);
            curr=prev->next;
        }
        else{
            prev=curr;
            curr=curr->next;
        }

    }

    *head = dummy.next;

    printData(*head);

}

void deletePos(sll **head, int num)
{

    sll dummy = {0};
    sll *prev = &dummy;
    sll *curr = dummy.next = *head;
    int c = 0;

    while (curr)
    {
        if (c == num)
        {
            prev ->next = curr->next;
            free(curr);
            break;
        }
        else
        {
            prev = curr;
            curr = curr->next;
            c++;
        }
    }
    *head=dummy.next;

    printData(*head);
}

void main(){
    sll *head=NULL;

    createNode(&head,10);
    createNode(&head,20);
    createNode(&head,30);
    createNode(&head,40);
    createNode(&head,50);

    printData(head);
    // delateData(&head,10);

    deletePos(&head,0);
}