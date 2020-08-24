#include "stringMatch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <vector> 
#include <fstream>
#include <algorithm>
#include <utility>
using namespace std;

stringMatch::stringMatch(){
	cout<<"insert pattern>>";
	getline(cin,pattern);
    m = pattern.length();
}
bool stringMatch::match(char* buffer,int i){
	//샘플.txt의 포인터 i를  buffer에 접근하기 위해 실제 접근 포인터 a로 변환합니다.(module연산 사용)  
	int a=i%m;
	//한 글자라도 불일치 할 경우 flag를 false로 바꿔줍니다.  
	bool isMatch=true;
	//차례대로 일치하는지 확인 
	for(int j=0;j<m;j++){
		if(buffer[a] != pattern.at(j)){
			//한 글자라도 불일치 할 경우 flag를 false로 바꿔줍니다.  
			isMatch=false; 
		}
		a = (a+1)%m;//환형 버퍼이므로 increment이후 module 연산 수행  
	}
	return isMatch;
	//모든 글자가 일치하는 경우에만 true리턴  
}
void stringMatch::naive(){
	ifstream read("sample1.txt");// 비교한 문자열 파일을 입력 
	int i=-1;//샘플.txt의 포인터  
	int index=0;//샘플.txt의 값들을 환형 버퍼에 저장하기 위한 환형 버퍼 포인터 
	bool match=false;//한 번이라도 문자열이 일치하면 match를 true로 바뀝니다	
	char* buffer = new char[m];//샘플.txt의 일부를 저장하는 환형 버퍼 
	int count=0; 
	if(read.is_open()){
		char c;
		//먼저 환형버퍼 크기만큼 샘플.txt의 문자열을 채워넣습니다 
		for(;index<m;){
			read.get(c);
			buffer[index++]=c;
		}	
		while(!read.eof()){
			i++;
			// A[i...i+m-1] 문자열이 패턴과 일치하면 일치한 위치를 출력합니다. 
			if(this->match(buffer,i)){
				cout<<"match found!>> "<<i+m<<endl;
				match=true;
				count++;
			}
			//샘플.txt가 끝나면 탐색 종료  
			if(read.eof()){break;}
			//샘플.txt의 문자열을 환형버퍼에 한 글자씩 추가합니다. 
			read.get(c);
			buffer[(index%m)] = c;
			index = (index+1)%m;
		}
		//한번이라도 매칭이 안된 경우 출력 
    	if(!match){cout<<"match not found ;("<<endl;}
	}
	cout<<count<<"개의 동일 문자열 탐지!!"<<endl;
    read.close();
} 
void stringMatch::kmp(){
    //해당 패턴과 일치하지 않을 때 이동하는 패턴 포인터 위치를 저장한 pi배열을 생성합니다 
	ifstream read("sample1.txt");// 비교한 문자열 파일을 입력
	int* pi;
	pi = new int[m+1];
	preprocessing(pi);
	int i=0;//샘플.txt의 포인터 
	int j=0;//패턴의 포인터 
	bool match=false;
	int count=0;

	if(read.is_open()){
		char c;
		read.get(c);
		i++;
		
		while(!read.eof()){
			if(j==m){
				//패턴의 끝까지 일치를 했기 때문에 매칭된 위치를 출력
				cout<<"match found!>> "<<i-1<<endl;
				j=-1;//다음 매칭위치를 찾기 위해 패턴 포인터를 초기화
				match=true;
				count++; 
			}
			if((j==-1)||(c==pattern.at(j))){
				//첫 패턴 문자 비교일 경우나 패턴 문자가 일치할 경우 패턴포인터와 샘플.txt의 포인터를 증가 
				read.get(c);
				i++;
				j++;
			}
			else{
				//해당 패턴과 일치하지 않은 경우 이동해야 할 위치로 패턴 포인터를 변경 
				j = pi[j];
			}
		}
		//한번이라도 매칭이 안된 경우 출력 
		if(!match){cout<<"match not found ;("<<endl;}
	}
	cout<<count<<"개의 동일 문자열 탐지!!"<<endl;
}
void stringMatch::preprocessing(int* pi){
    //해당 패턴과 일치하지 않을 때 이동하는 패턴 포인터 위치를 저장한 pi배열을 생성합니다 
	//방식은 자기 패턴에 대한 kmp 알고리즘을 실행합니다. 
	int j=0;//패턴 포인터 
	int k=-1;//패턴 포인터 
	pi[0]=-1; //처음 패턴과 일치하지 않을 때는 포인터를 초기화 시켜줘야 하므로 -1을 저장  
	while(j<m){
        if((k==-1)||(pattern.at(j)==pattern.at(k))){
         	//k가 초기화되거나 해당 포인터가 가르키는 문자끼리 일치하는 경우 패턴포인터들을 증가하고 pi배열의 값 저장  
			j++;
         	k++;
         	pi[j]=k;
		}
		else{
			//해당 포인터가 가르키는 문자끼리 일치하지 않는 경우 포인터의 값을 배열의 저장된 위치만큼 앞당김 
		 	k=pi[k];
		}
	} 
}

void stringMatch::boyerMoore(){
	ifstream read("sample1.txt");// 비교한 문자열 파일을 입력
	vector<pair<int,int> > jump;
	
	//computeJump부분으로  
	//해당하는 문자열인 경우 이동해야 되는 횟수를 저장하기 위한 배열을 생성 
	//벡터에는 (문자의 정수값,이동하는 횟수)가 배열로 저장됨 
	int num;
	int count =0;
	//패턴의 char값을 숫자로 바꿔서 저장합니다. 
	char* ch = new char[m+1];
	strcpy(ch,pattern.c_str());
	for(int i=0;i<m-1;i++){
		num =(int)ch[i];
		jump.push_back(pair<int,int>(num,m-1-i));//해당 문자열의 이동횟수 벡터에 저장 
	}
	num = (int)pattern.at(m-1);
	jump.push_back(pair<int,int>(num,m));//마지막 문자는 m번 이동 
	
	int i=0;//샘플.txt의 인덱스 
	int j;//패턴의 인덱스 
	int skip;//점프할 횟수 
	int index=0;//환형 버퍼에 저장하기 위한 포인터 
	bool match=false;
	char* buffer = new char[m];//샘플.txt의 일부를 저장하는 환형버퍼 
		
	//일치 휴리스틱의 이동횟수 계산하는 구간 
	int* goodSuffix = new int[m];
	int a;//패턴의 뒷부분 포인터 
	int b=0;//패턴의 앞부분 포인터 
	a=m-1;//뒤에서 부터 비교하기 위해 패턴의 끝으로 변경 
	for(int c=0;c<m;c++){
		goodSuffix[c]=m;	
	}//기본 이동횟수를 m으로 초기화 	
	//패턴의 앞부분과 패턴의 뒷부분이 일치하는지 비교해가며 이동해야되는 횟수를 기록 
	while(a>0){
		if((b>=0)&&(pattern.at(a+b)==pattern.at(b))){
			b--;//오른쪽부터 패턴의 뒷부분이 패턴의 앞부분과 일치하면 두 패턴을 앞으로 늘려가면서 계속 비교
		}
		else{
			if(b<0){//패턴의 앞부분이 패턴의 뒷부분과 일치하여 패턴의 앞부분이 맨 앞까지 늘려진 된 경우 
				for(;a+b>=0;--b){
					goodSuffix[a+b]=a;
					//비교가 끝난 부분부터 맨 앞까지는 일치하는 패턴을 뒷부분으로 가지고 있기 때문에 모두 이동할 수 있는 횟수를 a로 변경  
				}
			}
			else{//비교 중 패턴의 불일치가 발견한 경우로 패턴의 앞부분의 일부가 패턴의 뒷부분과 일치하는 경우 
				goodSuffix[a+b]=a;
				//불일치 된 부분에서만 이동횟수를 a로 변경
			}
			b=m-a;//패턴의 앞부분 기준을 오른쪽으로 한칸 이동 
			a--;//패턴의 뒷부분 기준을 왼쪽으로 한칸 이동			
		}
	}
	
	//문자열을 패턴과 비교하며 이동하는 구간 
	if(read.is_open()){
		char c;
		//환형 버퍼에 초기 문자열값을 먼저 넣어줍니다. 
		for(;index<m;){
			read.get(c);
			buffer[index++]=c;
		}
		index %= m;
		int k; 
		while(!read.eof()){
			j=m-1;//패턴 포인터 
			k=i+m-1;//샘플.txt의 포인터 위치로 실제 이 위치의 값에 접근하기 위해선 실제 저장도니 buffer주소인 k%m로 변환   
			while((j>-1)&&(pattern.at(j)==buffer[k%m])){
				//오른쪽부터 패턴과 일치하는지 확인 
				//일치하지 않으면 반복문 탈출 
				j--;
				k--;		
			}
			//일치하지 않은 경우 오른쪽 문자에 해당하는 이동 횟수만큼 샘플.txt이동 
			
			num = (int)buffer[(k)%m];//불일치가 발생한 문자 기준  		
			skip = m;//기타 문자는 m번 점프로 밑에 for문에서 그냥 통과한 경우 m번 이동  
			
			pair<int,int> temp;
			for(int a=0;a<m;a++){
				temp = jump.at(a);
				if(temp.first == num){
					 if(temp.second<skip){
					 	skip = temp.second;
						 //문자열 중에 문자인 경우 해당하는 이동횟수 기록 
						 //같은 문자인 경우 작은 수의 이동횟수로 기록  
					 }
				}
			}
			//불일치 휴리스틱의 경우나 일치 휴리스틱의 경우에서 이동횟수 비교
			skip = skip-(m-j);//불일치 휴리스틱의 이동횟수 불일치는 가장 오른쪽에서 (m-j)만큼 떨어져 있으므로 이동 횟수에서 빼줌 
			if(goodSuffix[j]>skip){//불일치가 일어나기 전 접미사가 패턴의 앞부분에서 일치해 이동하는 횟수의 경우(일치 휴리스틱)와 이동횟수 비교 
				skip=goodSuffix[j];
			}
			//더 이동횟수가 큰 경우를 채택하여 이동횟수 결정  			
			
			if(j==-1){
				//매칭이 된 위치를 출력  
				cout<<"match found!>> "<<i+m<<endl;
				match=true;	
				count++;
				skip =m;//매칭이 완료 되었으므로 새로운 매칭 위치를 찾기 위해 m번 점프			
			}	
			
			//이동 수만큼 buffer에 샘플.txt의 문자열을 환형버퍼에 새로 삽입 
			for(int a=0;a<skip;a++){
				read.get(c);
				buffer[index]=c;
				index=(index+1)%m;//환형 버퍼에 저장하기 때문에 포인터를 increment 후 module연산 		 
			} 
			//샘플.txt의 포인터 역시 이동한 만큼 증가  
			i +=skip;		
		}
		//한번이라도 매칭이 안된 경우 출력 
		if(!match){ 
			cout<<"match not found ;("<<endl;
		}
	}
	cout<<count<<"개의 동일 문자열 탐지!!"<<endl;    
	read.close();
}
