#include<stdio.h>

void printBinary(int num){

  for (int pos=31;pos>=0;pos--){
    printf("%d",num>>pos&1);
  }

}

void reversePrint(int num){

  for (int pos=0;pos<=31;pos++){
    printf("%d",num>>pos&1);
  }

}

void reverseAllbit(int *num){

  for(int pos=31;pos>=0;pos--){
    *num=*num^(1<<pos);
  }

}

void checkbitSetclear(int num){

  int pos;
  printf("Enter position to check\n");
  scanf("%d",&pos);

  if((num>>pos&1)){
    printf("%dth bit is set\n",pos);
  }
  else{
    printf("%dth bit is clear\n",pos);
  }

}

void add(){

  int a,b;
  printf("Enter two numbers\n");
  scanf("%d%d",&a,&b);

  while(b){
    int carry = a&b;
    a=a^b;
    b=carry<<1;
  }
  printf("sum= %d\n",a);

}

void multiBy4(){

  int num;
  printf("Enter a number\n");
  scanf("%d",&num);

  num=num<<2;

  printf("%d\n",num);

}

void checkPowerOf2(){

  int num;
  printf("Enter a number\n");
  scanf("%d",&num);

  if(num&(num-1)){
    printf("Not power of 2\n");
  }
  else{
    printf("Power of 2\n");
  }

}

void chechpowerWithoutBtwise(){

  int num;
  printf("Enter a number\n");
  scanf("%d",&num);

  while(num%2 == 0)
    num=num/2;

  if(num==1){
    printf("Power of 2\n");
  }
  else{
    printf("Not power of 2\n");
  }

}

void findTrailingZeros(){

  int num;
  printf("Enter a number\n");
  scanf("%d",&num);
  int count=0;

  for(int i=0;i<=31;i++){
    if((num>>i&1) ==0 ){
      count++;
    }
    else{
      break;
    }
  }

  printf("%d\n",count);
}

void highestSetBit(){

  int num,i;
  printf("Enter a number\n");
  scanf("%d",&num);

  for( i=31;i>=0;i--){
    if((num>>i&1) ==1){
      break;
    }
  }
  printf("Highest set bit=%d\n",i);

}

void swapBit(int p,int q){
  int num=15;

  int bit_p = num>>p&1;
  int bit_q = num>>q&1;

  if(bit_p!=bit_q){
    num=num^(1<<p);
    num=num^(1<<q);
  }
  printBinary(num);
}

void replaceBite(){

  int x=0,y=15;
  int pos=5,n=3;

  int mask=((1<<n) - 1) << pos;

  x=x&~(mask);

  y=(y<<pos)&mask;

  x=x|y;

  printBinary(x);

}

void checkBitpall(){
  
  int num,i,flag=0;
  printf("Enter a number\n");
  scanf("%x",&num);
  

  for(int start=0,end=31;start<=end;start++,end-- ){

    if((num>>start&1)!= (num>>end&1)){
      flag=1;
      break;
    }
  }
  if(!flag){
    printf("Pallindrome bits\n");
  }
  else{
    printf("Not pallindrome bits\n");
  }
  
printBinary(num);
}

void main(int argc,char**argv[]){
    
  int num=10;

  // printBinary(num);
  // reversePrint(num);
  // reverseAllbit(&num);

  // checkbitSetclear(num);

  // add();
  // multiBy4();
  // checkPowerOf2();
  // printBinary(num);
  // chechpowerWithoutBtwise();
  // findTrailingZeros();
  // highestSetBit();
  // swapBit(1,2);
  checkBitpall();

  // replaceBite();

}
