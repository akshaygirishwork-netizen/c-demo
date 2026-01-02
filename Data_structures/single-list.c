#include<stdio.h>
#include<stdlib.h>

typedef struct student
{
    char name[10];
    int mark;
    struct student * next;
} sll;

void add_begin(sll** head,int num){

    sll*newNode=(sll*)malloc(sizeof(sll));

    newNode->next=0;
    newNode->mark=num;

    if(*head==0){
        *head=newNode;
        return;
    }
    newNode->next=*head;
    *head=newNode;
}

void printData(sll*head){
    if(head==NULL){
        printf("No data\n");
        return;
    }
    
    sll*temp=head;
    while(temp){
        printf("%d\n",temp->mark);
        temp=temp->next;
    }

    printf("\n");
}

void sortBoth(sll *l1, sll *l2)
{

    sll dummy={0};
    sll *tail = &dummy;

    while (l1 && l2)
    {
        if (l1->mark < l2->mark)
        {
            tail->next = l1;
            l1 = l1->next;
        }
        else
        {
            tail->next = l2;
            l2 = l2->next;
        }
        tail=tail->next;
    }
    if (l1)
    {
        tail->next = l1;
    }
    else
    {
        tail->next = l2;
    }

    printData(dummy.next);
}

void deleteData(sll**head,int num){
    if (*head == NULL) return;

    sll dummy;
    dummy.next = *head;

    sll *prev = &dummy;
    sll *curr = *head;

    while (curr != NULL) {
        if (curr->mark == num) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    *head = dummy.next;  // update real head
}

void reverseList(sll**head){

    if(*head == NULL){
        printf("No data to reverse\n");
        return;
    }

    sll*prev,*next;

    prev=next=NULL;

    sll*curr=*head;

    while(curr != NULL){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }

*head=prev;

}

void main(){
    sll *head1 =NULL;

    sll *head2=NULL;

    add_begin(&head1,50);    
    add_begin(&head1,40);    
    add_begin(&head1,30);    
    add_begin(&head1,20);    
    add_begin(&head1,10);
    
    // add_begin(&head2,45);    
    // add_begin(&head2,35);    
    // add_begin(&head2,25);    
    // add_begin(&head2,15);    
    // add_begin(&head2,5);

    // sortBoth(head1,head2);

    // deleteData(&head1,10);
    printData(head1);
    reverseList(&head1);
    printData(head1);
}