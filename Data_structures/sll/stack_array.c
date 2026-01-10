 #include<stdio.h>
 
 #define MAX 10

 int stack[10];
 int top =-1;
 
void push(int data){

    if(top== (MAX-1)){
        printf("stack overflow\n");
        return;
    }
    stack[++top] = data;

}

int pop(){

    if(top == -1){
        printf("stack underflow\n");
        return;
    }
    return stack[top--];

}

int peak(){
    if(top == -1){
        printf("stack is empty\n");
        return;
    }
    return stack[top];
}

 void main(){
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60);
    push(70);
    push(80);
    push(90);
    push(100);
    push(100);

    printf("peak=%d\n",peak());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("pop=%d\n",pop());
    printf("peak=%d\n",peak());

    push(100);

 }