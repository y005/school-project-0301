#include <stdio.h>
//MIPS이 구조를 c로 구현한 프로젝트입니다. 

int M[1000] = {0};//명령어 저장 배열 
int R[10] = {0};//레지스터 저장 배열 


//명령어를 저장합니다. 
void input(){
	int num=-1;
    int i=0;
    while((num !=100)&&(num !=0)){
      scanf("%d\n",&num);
      M[i++] = num;
    }
}

//decode+execute를 구현한 함수입니다. 
int interpreter(){
   int c=0;
   int PC=0;//program counter 
   int op,op1,op2,a;
   while((op = M[PC++])!=0){
       switch(op/100){
       	   case 1:
               if(op!=100){return c;}
               return ++c;
           case 2:
               op1 = (op/10)%10;
               op2 = op%10;
               R[op1] = op2;
               c++;
               break;
           case 3:
               op1 = (op/10)%10;
               op2 = op%10;
               R[op1] = (R[op1]+op2)%1000;
               c++;
               break;
           case 4:
               op1 = (op/10)%10;
               op2 = op%10;
               R[op1] = (R[op1]*op2)%1000;
               c++;
               break;
           case 5:
               op1 = (op/10)%10;
               op2 = op%10;
               R[op1] = R[op2];
               c++;
               break;
           case 6:
               op1 = (op/10)%10;
               op2 = op%10;
               R[op1] = (R[op1]+R[op2])%1000;
               c++;
               break;
           case 7:
               op1 = (op/10)%10;
               op2 = op%10;
               R[op1] = (R[op1]*R[op2])%1000;
               c++;
               break;
           case 8:
               op1 = (op/10)%10;
               op2 = op%10;
               a = R[op2];
               R[op1] = M[a];
               c++;
               break;
           case 9:
               op1 = (op/10)%10;
               op2 = op%10;
               a = R[op2];
               M[a] = R[op1];
               c++;
               break;
           case 0:
               op1 = (op/10)%10;
               op2 = op%10;
               if(R[op2]!=0){PC = R[op1];}
               c++;
               break;
        }
    } 
}
//명령어가 실행된 후 레지스터의 값들을 출력해줍니다. 
void print(){
  for(int i=0;i<10;i++){
    printf("R[%d] = %d\n",i,R[i]);
  }
}

int main(void) {
  input();
  //실행된 명령어의 수를 출력합니다. 
  printf("%d\n",interpreter());
  print();
  return 0;
}
