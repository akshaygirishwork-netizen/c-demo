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
	printf("\n");
}

sll *mergeList(sll *l1, sll *l2)
{

	sll new_list = {0};

	sll *tail = &new_list;

	while (l1 && l2)
	{
		if (l1->data > l2->data)
		{
			tail->next = l1;
			l1 = l1->next;
		}
		else
		{
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}

	if (l1)
	{
		tail->next = l1;
	}
	else
	{
		tail->next = l2;
	}
	return new_list.next;
}

void deleteNode(sll ** head){

	if(*head == NULL){
		printf("No data\n");
		return;
	}

	int num;
	printData(*head);
	printf("Eneter a node to delete\n");
	scanf("%d",&num);

	sll * cur;
	sll * prev;

	cur=prev=*head;
	cur=cur->next;

	while(cur){
		if(cur->data == num){
			sll * temp=cur;
			prev->next=cur->next;
			free(temp);
			cur=prev->next;
			continue;
		}
		prev=cur;
		cur=cur->next;
	}
	cur=*head;

	if(cur->data == num){
		*head=cur->next;
		free(cur);
	}
	printData(*head);
}

void main(){
	sll* head=0;
	sll* head1=0;

	createNode(10,&head);
	createNode(10,&head);
	// createNode(30,&head);
	// createNode(40,&head);
	// createNode(50,&head);
	// createNode(60,&head);
	// createNode(10,&head);
	// createNode(10,&head);

	createNode(5,&head1);
	createNode(15,&head1);
	createNode(25,&head1);
	createNode(35,&head1);
	createNode(45,&head1);
	createNode(55,&head1);
	createNode(65,&head1);
	createNode(75,&head1);
	createNode(85,&head1);


	deleteNode(&head);

	// printData(mergeList(head,head1));
	// printData(head);
}
