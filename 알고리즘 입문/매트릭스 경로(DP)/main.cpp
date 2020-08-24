#include "matrixpath.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

int main(){
	int num;
	cout<<"\t\t\t<<9�� ������Ʈ ������ 1815060>>"<<endl<<endl;
	cout<<"�̹� ������Ʈ�� �ִ밪�� ���� ��θ� ���ϴ� ����� ����� �������α׷����� �м��� �� ����Ʈ�Դϴ�."<<endl;
	
	cout<<"\n����� ����� �Է��ϼ���\n>> ";
	cin>>num;	
	
	matrixPath p = matrixPath(num);
	cout<<"\n\t\t\t\t<��͹��� �����ذ��>"<<endl<<endl;
	
	cout<<"[1][1]���� ���� ��ġ������ ��ο��� ���� �ִ밪�� ���� ��ġ������ ��ο��� ���� �ִ밪�� ���� ��ġ�� ������ ���� ���� ���Դϴ�. ��Ŀ��� ������ �� �ִ� ������ ������, �Ʒ�, �밢�� �Ʒ��� ���ѵǾ� �ֱ� ������ ���� ��ġ�� 3������ ��찡 �ֽ��ϴ�."<<endl;
	
	cout<<"\n\t1. ( ���� ���� �ε��� - 1, ���� ���� �ε��� )"<<endl;
	cout<<"\t2. ( ���� ���� �ε���, ���� ���� �ε��� - 1 )"<<endl;
	cout<<"\t3. ( ���� ���� �ε��� - 1, ���� ���� �ε��� - 1 )"<<endl;
	
	cout<<"\n���� �� ��� �� �ִ밪�� ���� ��ο��� ���� ��ġ�� ���� ���� �����ָ� �ִ밪�� ���� �� �ֽ��ϴ�.\n"<<endl;
	cout<<"([1][1]���� ���� [i][j]���� ����� �ִ밪) "<<endl;
	cout<<"= ���� [i][j]�� ������ ����ġ + MAX([1][1]���� ���� ��ġ���� ��� ����ġ�յ�)"<<endl;
	cout<<"\n#�߰������� ���� �� ��� �� �ִ밪�� ���� ���� ��ġ���� path[i][j]�� �����ϸ� ���߿� [N][N]���� �����Ͽ� ������ ������ ��θ� �� �� �ֽ��ϴ�."<<endl;
	//�밢���� ���� ����ġ�� �㰡�� ������� ��� 
	 
	//�ð� ���� 
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// �ð� ������ ����ϱ� ���� ����
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	//��͹��� ���� 
	cout<< "\n - [1][1]���� ["<<num<<"]["<<num<<"]���� ���� ����� ���� �� �ִ� �ִ밪�� ���� <<"<<p.recursive(num,num)<<">>�Դϴ�."<<endl;		
	//�ð� ���� 
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	//�ɸ� �ð� ��� 
	fprintf(stderr, " - %d * %d ���� ��Ŀ� ���� �ִ밪 ��θ� ��͹������� ã�µ� �ɸ� �ð�(��): %7.2f\n", num, num,(double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
	
	//��� ���	
	p.printPath();
	//���α׷��� ȣ�� Ƚ�� ��� 
	p.printFcount();
	cout<<"\n\n\t\t\t<���� ���α׷��� ���� �����ذ��>"<<endl<<endl;
	
	cout<<"�������α׷����� ����� ��͹������� �߰������� �޸������̼��� ���� ����� ���¿� ���� �迭�� �Ҵ��մϴ�. c[i][j]�� [1][1]���� [i][j]���� ��� �� �ִ밪�� �����Ͽ����ϴ�. ��͹����� �ٸ��� loop�� �ȿ��� ũ�Ⱑ ���� ������ ���� Ǯ��鼭 ũ�Ⱑ ū ������ ���� ���س��� �� �ֽ��ϴ�. "<<endl;
	
	//�ð� ���� 
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	
	cout<< "\n - [1][1]���� ["<<num<<"]["<<num<<"]���� ���� ����� ���� �� �ִ� �ִ밪�� ���� <<"<<p.dynamic(num)<<">>�Դϴ�."<<endl;		
	
	//�ð� ���� 
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	//�ɸ� �ð� ��� 
	fprintf(stderr, " - %d * %d ���� ��Ŀ� ���� �ִ밪 ��θ� DP�� ã�µ� �ɸ� �ð�(��): %7.2f\n", num, num,(double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
	
	//��� ��� 
	p.printPath();
}
