#include<stdio.h>

void main(){
	int num,sum=0,r=0;

	printf("enter a number\n");
	scanf("%d",&num);

	for (int temp=num;temp;temp=temp/10){
		r=temp%10;
		sum=sum*10+r;
	}
	if(sum==num){
		printf("NO is pallindrome\n");
	}
	else{
		printf("No is not pallindrome\n");
	}
}
