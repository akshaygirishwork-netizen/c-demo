#include<stdio.h>
#include<stdlib.h>

typedef struct student {
    int mark;
    char name;
    struct student* next;
}sll;


void addbegin(sll**head,int data){
    sll* newNode;

    newNode=(sll*)malloc(sizeof(sll));
    newNode->next=0;
    newNode->mark=data;

    if(*head==NULL){
        *head=newNode;
        return;
    }
    else{
        newNode->next=*head;
        *head=newNode;
    }
}

void findMiddle(sll*head){
    if(head==NULL){
        printf("No data\n");
    }
    else{
        sll* slow,*fast;
        slow=fast=head;

        while(fast!=NULL && fast->next!=0){
            slow=slow->next;
            fast=fast->next->next;
        }
        printf("Middle is %d\n",slow->mark);
    }
}

void deleteData(sll**head,int num){
    sll*temp=*head;

    if(temp==NULL){
        printf("NO data\n");
    }
    else{
        sll* prev,*current;
        current=prev=*head;

        current=current->next;

        while(current){
            if(current->mark == num){
                prev->next=current->next;
                free(current);
                current=prev->next;
                continue;
            }
            prev=current;
            current=current->next;
        }

        current=*head;
        if(current->mark == num){
            *head=current->next;
            free(current);
        }
    }

}

void printdata(sll*head){
    if(head==NULL){
        printf("No data available");
    }
    else{
        sll*temp=head;
        while(temp){
            printf("%d  ",temp->mark);
            temp=temp->next;
        }
    }
}

void main(){
    sll* head=NULL;
    int num,option=1;

    // while(option){
    //     printf("enter a number\n");
    //     scanf("%d",&num);
    //     addbegin(&head,num);

    //     printf("Do u want to add node again? Enter 1 to add 0 to stop\n");
    //     scanf("%d",&option);
    // }
    addbegin(&head,10);
    addbegin(&head,10);
    addbegin(&head,30);
    addbegin(&head,40);
    addbegin(&head,10);
    addbegin(&head,60);
    addbegin(&head,70);
    addbegin(&head,10);
    addbegin(&head,10);


    printdata(head);

    printf("\n");

    //findMiddle(head);
    deleteData(&head,10);

    printdata(head);
}