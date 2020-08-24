#include "stringMatch.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;
//sample1_Further Reading about Standards.txt
//sample2_17650    20000818.txt

int main(){
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// �ð� ������ ����ϱ� ���� ����

	cout<<"\t\t\t<<���ڿ� �˰��� ���� �� ����Ʈ>>"<< endl;
	cout<<"\t\t\t\t\t\t\t1815060 ������"<< endl;
	stringMatch match1;
	cout<<"���� ���ڿ� ������ stringMatch�� ���ǵ� �˰��� �Լ��� �Է��ؾ� �մϴ�."<<endl; 
	cout<<"\t\t\t\tnaive�˰���"<<endl; 
	cout<<"naive�˰����� ���ڿ��� ��ĭ�� �̵��ذ��鼭 ���ϰ� ���ϴ� ����Դϴ�."<<endl; 
	cout<<"naive�˰����� ������ ���ڿ� �迭�� ���� �迭�� ���ϴ� ��������� ��"<<endl;
	cout<<"��.txt ���ڿ��� char �迭�� ��ȯ�ϴ� ���� ���� �޸𸮿� ����ð��� ��ȿ"<<endl;
	cout<<"���� �ֱ� ������ ���� ���̸�ŭ�� ȯ�� ���۸� �Ҵ��ϰ� ���ڿ��� �� ĭ��"<<endl; 
	cout<<"�̵��� �� ���� ���ڿ� �� ���ھ� �о�ͼ� ȯ�� ���ۿ� ���� �� ���ϰ� ��"<<endl; 
	cout<<"���ϴ� ����� �̿��Ͽ����ϴ�. ���� �Է� ���ڿ��� �����Ϳ� �ش��ϴ� ���� "<<endl; 
	cout<<"�б� ���ؼ��� ���� ���� ����� ȯ�� ���ۿ� �����ͷ� ��ȯ�ϴ� module����"<<endl; 
	cout<<"�� �ʿ��մϴ�."<<endl; 
	
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	match1.naive();
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	printf("naive ����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout<<"\t\t\t\tKMP�˰���"<<endl; 
  	cout<<"kmp�˰����� ���ڿ��� �� ĭ�� �̵��ذ��鼭 ������ ���ϴ� ����Դϴ�."<<endl; 
	cout<<"���� naive�˰���� �ٸ� ���� ���ϰ� ��ġ���� ���� ��� ������ ����Ű��"<<endl; 
	cout<<"�����͸� ��ġ���� �ʴ� ��ġ���� ������ ��ܼ� ���س����� ����Դϴ�.��"<<endl; 
	cout<<"���ؾ� �ϴ� ��ġ�� ������ kmp������� ������ pi�迭�� Ȱ���մϴ�. �� ��� "<<endl; 
	cout<<"�� ���� �����ϱ� ���ؼ� �Է� ���� ���ڿ� ������ �� char�� �о�� ���ϰ�  "<<endl; 
	cout<<"��ġ�ϴ� ��� ������ �����Ϳ� ���ڿ� ������ ���ڸ� �÷����� ��� ���ذ�"<<endl; 
	cout<<"�� ��ġ���� �ʴ� ��� ���� �����͸� ���� ��ġ���� �̵��ؾ� �Ǵ� ����ŭ ��"<<endl; 
	cout<<"���մϴ�. ���� ����� �� �� �񱳸� ���� ���ڿ� ������ ���ڴ� �ٽ� ���ϰ� "<<endl; 
	cout<<"���ϴ� ������ ���� ������ naive, ���̾�� ��İ� �ٸ��� �Է¹��� ����"<<endl;
	cout<<"�� ������ ���ۿ� �����ϴ� ������ ���� �̷а� �ٸ��� ���� ����ð��� ���� "<<endl; 
	cout<<"������ �����˴ϴ�."<<endl; 
	 
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	match1.kmp();
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	printf("KMP ����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout<<"\t\t\t���̾� ���� �˰���"<<endl; 
	cout<<"���̾� ���� ȣ��Ǯ �˰��򿡼� �߰������� ������ �����Դϴ�. ������ �ڿ���"<<endl; 
	cout<<"���� ���ϴ� ���� ������ �������� ���ϰ� �� �� ��ġ�� ���� �ʴ� ���� ���"<<endl; 
	cout<<"�Ͽ� ���ڿ� ������ �����͸� ������Ű�� ����ġ �޸���ƽ�� �� ������ ��ġ�� ��"<<endl; 
	cout<<"������ �޺κ��� ������ �պκа� ��ġ�ϴ� ��� ���ڿ��� �̵����� ������ �պκ�"<<endl; 
	cout<<"���� ���ڿ��� ���ߴ� ��ġ �޸���ƽ �� ���ڿ��� �̵� Ƚ���� �� ū ����� ���� "<<endl; 
	cout<<"�Ͽ� ���ڿ��� �̵���Ű�� �����Դϴ�. ���� ������ ���ڿ� �� �˰���� �ٸ���"<<endl; 
	cout<<"���ڿ��� �����͸� �ϳ��� �̵��ϴ� ���� �ƴ� ���� �� �̵��ؼ� �ǳʶٱ� ������  "<<endl; 
	cout<<"�ֻ��� ��� m���� ���ڿ��� �̵��ϱ� ������ ȿ������ ���ڿ� �� �˰����Դϴ�."<<endl; 
	cout<<"�Է� ���ڿ��� naive�˰���� ���� ȯ�� ���۷� �����ϵ� ���ڿ��� �̵� Ƚ����ŭ"<<endl; 
	cout<<"ȯ�� ���ۿ� ���� �� �����ϴ� ������ ���ϴ�. ����ġ �޸���ƽ�� ���� ���̾�"<<endl; 
	cout<<"���� ȣ��Ǯ �˰��򿡼� �� �����迭�� ���Ͽ��� �� ��°���� ����ġ�� �Ͼ����"<<endl; 
	cout<<"����Ͽ� �����ϴ� Ƚ���� ���ϰ� ��ġ �޸���ƽ�� ���� �迭�� ����ġ�� ���� ������";
	cout<<"��ġ�� ������ �޺κ��� ������ �պκа� ��ġ�ϴ� �κ��� �ִٸ� �̵���Ű�� Ƚ����"<<endl; 
	cout<<"����� �迭�Դϴ�."<<endl; 
	
	QueryPerformanceFrequency(&liFrequency); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter); // �ڵ� ���� �� ī��Ʈ ����
	match1.boyerMoore();	
	QueryPerformanceCounter(&EndCounter); // �ڵ� ���� �� ī��Ʈ ����
	printf("Boyer Moore ����ð� = %f ��\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
}
