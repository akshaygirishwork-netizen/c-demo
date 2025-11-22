#include<stdio.h>
#include<stdlib.h>

typedef struct mark {
	int data;
	struct mark* next;
}sll;

void createNode( int num,sll **head){
	sll * newNode;

	newNode=(sll*) malloc(sizeof(sll));
	newNode->next=NULL;

	newNode->data=num;

	if(*head==NULL) {
		*head=newNode;
	}
	else{
		newNode->next=*head;
		*head=newNode;
	}

}

void printData(sll* head){
	if(head == NULL){
		printf("No data");
	}
	else{
		sll*temp=head;

		while(temp){
			printf("%d	",temp->data);
			temp=temp->next;
		}
	}
}

void main(){
	sll* head=0;
	createNode(10,&head);
	createNode(20,&head);
	createNode(30,&head);
	createNode(40,&head);
	createNode(50,&head);
	createNode(60,&head);
	createNode(70,&head);
	createNode(80,&head);

	printData(head);
	

}
