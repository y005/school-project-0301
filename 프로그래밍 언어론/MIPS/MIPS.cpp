#include <stdio.h>
//MIPS�� ������ c�� ������ ������Ʈ�Դϴ�. 

int M[1000] = {0};//��ɾ� ���� �迭 
int R[10] = {0};//�������� ���� �迭 


//��ɾ �����մϴ�. 
void input(){
	int num=-1;
    int i=0;
    while((num !=100)&&(num !=0)){
      scanf("%d\n",&num);
      M[i++] = num;
    }
}

//decode+execute�� ������ �Լ��Դϴ�. 
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
//��ɾ ����� �� ���������� ������ ������ݴϴ�. 
void print(){
  for(int i=0;i<10;i++){
    printf("R[%d] = %d\n",i,R[i]);
  }
}

int main(void) {
  input();
  //����� ��ɾ��� ���� ����մϴ�. 
  printf("%d\n",interpreter());
  print();
  return 0;
}
