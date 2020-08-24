#include "matrixpath.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

int main(){
	int num;
	cout<<"\t\t\t<<9장 프로젝트 문정현 1815060>>"<<endl<<endl;
	cout<<"이번 프로젝트는 최대값을 갖는 경로를 구하는 재귀적 방법과 동적프로그래밍의 분석과 비교 레포트입니다."<<endl;
	
	cout<<"\n행렬의 사이즈를 입력하세요\n>> ";
	cin>>num;	
	
	matrixPath p = matrixPath(num);
	cout<<"\n\t\t\t\t<재귀버전 문제해결법>"<<endl<<endl;
	
	cout<<"[1][1]에서 현재 위치까지의 경로에서 갖는 최대값은 직전 위치까지의 경로에서 갖는 최대값에 현재 위치가 가지는 값을 더한 것입니다. 행렬에서 움직일 수 있는 방향은 오른쪽, 아래, 대각선 아래로 제한되어 있기 때문에 직전 위치는 3가지의 경우가 있습니다."<<endl;
	
	cout<<"\n\t1. ( 현재 가로 인덱스 - 1, 현재 세로 인덱스 )"<<endl;
	cout<<"\t2. ( 현재 가로 인덱스, 현재 세로 인덱스 - 1 )"<<endl;
	cout<<"\t3. ( 현재 가로 인덱스 - 1, 현재 세로 인덱스 - 1 )"<<endl;
	
	cout<<"\n따라서 세 경우 중 최대값을 갖는 경로에서 현재 위치가 갖는 값을 더해주면 최대값을 구할 수 있습니다.\n"<<endl;
	cout<<"([1][1]에서 현재 [i][j]까지 경로의 최대값) "<<endl;
	cout<<"= 현재 [i][j]가 가지는 가중치 + MAX([1][1]에서 직전 위치까지 경로 가중치합들)"<<endl;
	cout<<"\n#추가적으로 위의 세 경우 중 최대값을 갖는 직전 위치값을 path[i][j]에 저장하면 나중에 [N][N]부터 시작하여 역으로 지나온 경로를 알 수 있습니다."<<endl;
	//대각선과 음수 가중치의 허가의 상관관계 출력 
	 
	//시간 시작 
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// 시간 측정에 사용하기 위한 변수
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	//재귀버전 실행 
	cout<< "\n - [1][1]에서 ["<<num<<"]["<<num<<"]까지 가는 경로중 가질 수 있는 최대값의 합은 <<"<<p.recursive(num,num)<<">>입니다."<<endl;		
	//시간 종료 
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	//걸린 시간 출력 
	fprintf(stderr, " - %d * %d 개의 행렬에 대한 최대값 경로를 재귀버전으로 찾는데 걸린 시간(초): %7.2f\n", num, num,(double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
	
	//경로 출력	
	p.printPath();
	//프로그래밍 호출 횟수 출력 
	p.printFcount();
	cout<<"\n\n\t\t\t<동적 프로그래밍 버전 문제해결법>"<<endl<<endl;
	
	cout<<"동적프로그래밍의 설계는 재귀버전에서 추가적으로 메모이제이션을 위한 행렬의 형태와 같은 배열을 할당합니다. c[i][j]는 [1][1]에서 [i][j]까지 경로 중 최대값을 저장하였습니다. 재귀버전과 다르게 loop문 안에서 크기가 작은 문제의 값을 풀어가면서 크기가 큰 문제의 값을 구해나갈 수 있습니다. "<<endl;
	
	//시간 시작 
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	
	cout<< "\n - [1][1]에서 ["<<num<<"]["<<num<<"]까지 가는 경로중 가질 수 있는 최대값의 합은 <<"<<p.dynamic(num)<<">>입니다."<<endl;		
	
	//시간 종료 
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	//걸린 시간 출력 
	fprintf(stderr, " - %d * %d 개의 행렬에 대한 최대값 경로를 DP로 찾는데 걸린 시간(초): %7.2f\n", num, num,(double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
	
	//경로 출력 
	p.printPath();
}
