#include "stringMatch.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;
//sample1_Further Reading about Standards.txt
//sample2_17650    20000818.txt

int main(){
	LARGE_INTEGER StartCounter, EndCounter, liFrequency;// 시간 측정에 사용하기 위한 변수

	cout<<"\t\t\t<<문자열 알고리즘 성능 비교 레포트>>"<< endl;
	cout<<"\t\t\t\t\t\t\t1815060 문정현"<< endl;
	stringMatch match1;
	cout<<"비교한 문자열 파일은 stringMatch에 정의된 알고리즘 함수에 입력해야 합니다."<<endl; 
	cout<<"\t\t\t\tnaive알고리즘"<<endl; 
	cout<<"naive알고리즘은 문자열을 한칸씩 이동해가면서 패턴과 비교하는 방법입니다."<<endl; 
	cout<<"naive알고리즘의 구현은 문자열 배열과 패턴 배열을 비교하는 방법이지만 입"<<endl;
	cout<<"력.txt 문자열을 char 배열로 변환하는 것은 많은 메모리와 실행시간의 저효"<<endl;
	cout<<"율을 주기 때문에 패턴 길이만큼의 환형 버퍼를 할당하고 문자열을 한 칸씩"<<endl; 
	cout<<"이동할 때 마다 문자열 한 글자씩 읽어와서 환형 버퍼에 저장 후 패턴과 비"<<endl; 
	cout<<"교하는 방법을 이용하였습니다. 따로 입력 문자열의 포인터에 해당하는 값을 "<<endl; 
	cout<<"읽기 위해서는 실제 값이 저장된 환형 버퍼에 포인터로 변환하는 module연산"<<endl; 
	cout<<"이 필요합니다."<<endl; 
	
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	match1.naive();
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	printf("naive 수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout<<"\t\t\t\tKMP알고리즘"<<endl; 
  	cout<<"kmp알고리즘은 문자열을 한 칸씩 이동해가면서 패턴을 비교하는 방법입니다."<<endl; 
	cout<<"기존 naive알고리즘과 다른 점은 패턴과 일치하지 않을 경우 패턴을 가르키는"<<endl; 
	cout<<"포인터를 일치하지 않는 위치보다 앞으로 당겨서 비교해나가는 방법입니다.이"<<endl; 
	cout<<"동해야 하는 위치는 패턴의 kmp방식으로 구해진 pi배열를 활용합니다. 이 방식 "<<endl; 
	cout<<"을 실제 구현하기 위해서 입력 받은 문자열 파일을 한 char씩 읽어가며 패턴과  "<<endl; 
	cout<<"일치하는 경우 패턴의 포인터와 문자열 파일의 문자를 늘려가며 계속 비교해가"<<endl; 
	cout<<"고 일치하지 않는 경우 패턴 포인터를 현재 위치에서 이동해야 되는 수만큼 이"<<endl; 
	cout<<"동합니다. 위의 방식은 한 번 비교를 끝낸 문자열 파일의 문자는 다시 패턴과 "<<endl; 
	cout<<"비교하는 과정이 없기 때문에 naive, 보이어무어 방식과 다르게 입력받은 문자"<<endl;
	cout<<"열 파일을 버퍼에 저장하는 과정이 없어 이론과 다르게 실제 실행시간이 제일 "<<endl; 
	cout<<"빠르게 측정됩니다."<<endl; 
	 
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	match1.kmp();
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	printf("KMP 수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);

	cout<<"\t\t\t보이어 무어 알고리즘"<<endl; 
	cout<<"보이어 무어 호스풀 알고리즘에서 추가적으로 발전된 형식입니다. 패턴의 뒤에서"<<endl; 
	cout<<"부터 비교하는 점이 같지만 차이점은 패턴과 비교 중 일치가 나지 않는 곳을 고려"<<endl; 
	cout<<"하여 문자열 파일의 포인터를 증가시키는 불일치 휴리스틱과 그 전까지 일치가 된"<<endl; 
	cout<<"패턴의 뒷부분이 패턴의 앞부분과 일치하는 경우 문자열을 이동시켜 패턴의 앞부분"<<endl; 
	cout<<"으로 문자열을 맞추는 일치 휴리스틱 중 문자열의 이동 횟수가 더 큰 방법을 선택 "<<endl; 
	cout<<"하여 문자열을 이동시키는 과정입니다. 위의 설명한 문자열 비교 알고리즘과 다르게"<<endl; 
	cout<<"문자열의 포인터를 하나씩 이동하는 것이 아닌 여러 번 이동해서 건너뛰기 때문에  "<<endl; 
	cout<<"최상의 경우 m번씩 문자열을 이동하기 때문에 효과적인 문자열 비교 알고리즘입니다."<<endl; 
	cout<<"입력 문자열은 naive알고리즘과 같은 환형 버퍼로 저장하되 문자열의 이동 횟수만큼"<<endl; 
	cout<<"환형 버퍼에 여러 번 저장하는 과정이 들어갑니다. 불일치 휴리스틱은 기존 보이어"<<endl; 
	cout<<"무어 호스풀 알고리즘에서 쓴 점프배열과 패턴에서 몇 번째에서 불일치가 일어났는지"<<endl; 
	cout<<"고려하여 점프하는 횟수를 구하고 일치 휴리스틱을 위한 배열은 불일치가 나기 전까지";
	cout<<"일치한 패턴의 뒷부분이 패턴의 앞부분과 일치하는 부분이 있다면 이동시키는 횟수를"<<endl; 
	cout<<"기록한 배열입니다."<<endl; 
	
	QueryPerformanceFrequency(&liFrequency); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter); // 코드 수행 전 카운트 저장
	match1.boyerMoore();	
	QueryPerformanceCounter(&EndCounter); // 코드 수행 후 카운트 저장
	printf("Boyer Moore 수행시간 = %f 초\n", (double)(EndCounter.QuadPart - StartCounter.QuadPart) / (double)liFrequency.QuadPart);
}
