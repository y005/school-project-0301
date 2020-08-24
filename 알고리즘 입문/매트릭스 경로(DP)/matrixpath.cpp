#include "matrixpath.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//행렬에서의 좌표값을 저장하기 위한 Point클래스  
//기본생성자 (0,0)좌표 
Point::Point(){
	x=0;
	y=0;
}
//생성자 (x,y)좌표 
Point::Point(int xx,int yy){
    x=xx;
    y=yy;
}
//복사대입 연산자 
Point& Point::operator=(Point& p){
    this->x= p.getX();
    this->y= p.getY();
    return *this;
}
//좌표값을 (x,y) 형태로 출력 
void Point::printPoint(){
    cout<<"("<<this->getX()<<", "<<this->getY()<<")";
}
int Point::getX(){
    return this->x;
}
int Point::getY(){
    return this->y;
}
//행렬을 동적할당하고 행렬의 가중치를 랜덤으로 설정
//이외 재귀 및 DP 를 하기 위해 필요한 배열 할당 및 초기화  
matrixPath::matrixPath(int n){
    //matirx[i][j] == 행렬[i][j]에서의 가중치를 저장한 배열 	
	matrix = new int*[n];
	
	//fcount[i][j] == 행렬[i][j]에서의 함수 호출 횟수를 기록하기 위한 배열 
	fcount = new int*[n];
	
	//최대값의 경로를 저장하는 배열입니다
    //path[i][j] == [1][1]에서 [i][j]까지 경로 중 최대값을 갖는 
	//경로에서 현재 위치 직전의 행렬 위치를 Point(x좌표,y좌표)로 저장한 객체들의 배열  
	path = new Point*[n];
    
	//재귀버전에서 중복된 값을 하기위해 메모이제이션을 쓰기 위한 배열 
	//c[i][j] == [1][1]에서 [i][j]까지 경로 중 최대값을 저장하는 배열 
	c = new int*[n];
	
	//행렬의 크기를 저장 N*N의 행렬로 동적할당됨 
    size = n;
    
    //다중배열의 형태(N*N)로 각 배열들을 동적 할당합니다. 
    for(int i=0;i<=n;i++){
       matrix[i] = new int[n];
       fcount[i] = new int[n];
       path[i] = new Point[n];
       c[i] =  new int[n];
	}
   	//행렬의 범위가 아닌 곳의 가중치를 0으로 초기화 
    for(int a=0;a<=n;a++){
       matrix[0][a] = 0;
    }
    for(int b=0;b<=n;b++){
       matrix[b][0] = 0;
    }
    
   	srand((unsigned int)time(NULL));
    //행렬 초기값으로 -9~+9까지의 랜덤한 값으로 초기화  
	cout<<"\n\t\t\t<대각선의 허용과 음수값 여부의 관계...?>"<<endl; 
	cout<<">>행렬의 초기값에 음수를 포함시키는 것은 행렬의 이동에 있어서 대각선의 움직임을 경로에 포함할 수 있습니다. 행렬의 초기값에 양수만을 포함하게 되는 경우 경로에 이동에서 대각선의 이동을 허락한다해도 최대한 경로를 길게 해야 경로의 최댓값이 커지기 때문에 대각선의 이동경로를 항상 행렬의 이동 경로에 포함하지 않기 때문입니다."<<endl<<endl; 
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            matrix[i][j] = rand()%19-9;
        }
    }
   
   //탐색을 위한 배열들 초기화 
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            fcount[i][j] = 0;
        }
    }
    //Point(0,0)으로 초기화 
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            Point p = Point(0,0);
			path[i][j] = p;
        }
    }
    cout<<"\t\t\t\t<<생성된 행렬의 모습>>\n"<<endl; 
	for(int i=1;i<=n;i++){
        cout<<"\t\t\t\t[";
		for(int j=1;j<=n;j++){
            cout<<" "<<matrix[i][j];
        }
        cout<<"]"<<endl;
    }
}

//recursive(i,j) 설명 

//[1][1]에서 현재 위치까지의 경로에서 갖는 최대값은 직전 위치까지의 경로에서 갖는 최대값에 현재 위치가 가지는 값을 더한 것입니다. 
//행렬에서 움직일 수 있는 방향은 오른쪽, 아래, 대각선 아래로 제한되어 있기 때문에 직전 위치는 3가지의 경우가 있습니다.	
//1. ( 현재 가로 인덱스 - 1, 현재 세로 인덱스 )
//2. ( 현재 가로 인덱스, 현재 세로 인덱스 - 1 )
//3. ( 현재 가로 인덱스 - 1, 현재 세로 인덱스 - 1 )
//따라서 세 경우 중 최대값을 갖는 경로에서 현재 위치가 갖는 값을 더해주면 최대값을 구할 수 있습니다.
//([1][1]에서 현재 [i][j]까지 경로의 최대값) = 현재 [i][j]가 가지는 가중치 + MAX([1][1]에서 직전 위치까지 경로 가중치합들)
//추가적으로 위의 세 경우 중 최대값을 갖는 직전 위치값을 path[i][j]에 저장하면 나중에 [N][N]부터 시작하여 역으로 지나온 경로를 알 수 있습니다.
//이렇게 구해낸 현재 위치까지의 경로에서 갖는 최대값을 리턴	 
int matrixPath::recursive(int i,int j){
	int maxPrev;
	Point p;
	//함수의 중복호출횟수를 세기 위해 함수(recursive(i,j))의 호출횟수를 추가 
	fcount[i][j]++;
	
	
	//경로에 포함되지 않는 구간이기 때문에 해당 가중치를 최소값으로 설정하여 자동으로 경로에 포함되지 않도록 최소값으로 설정
	//값을 구하기 위해선 [0][0]은 0으로 설정필수 
	if((i==0)||(j==0)){
		if((i==0)&&(j==0)){return 0;}  
		return INT_MIN;
	} 
	
	int a = this->recursive(i-1,j);
	int b = this->recursive(i,j-1);
	int c = this->recursive(i-1,j-1);
	
	//각 직전 위치들까지의 경로 중 최댓값을 가진 값
	maxPrev = max(a,max(b,c)); 
	
	//각 직전 위치들까지의 경로 중 최댓값을 가진 직전위치의 좌표값을 Point형태로 path[i][j]에 저장 
	if(maxPrev == a){Point p1 = Point(i-1,j);p=p1;}
	if(maxPrev == b){Point p1 = Point(i,j-1);p=p1;}
	if(maxPrev == c){Point p1 = Point(i-1,j-1);p=p1;}
	path[i][j] = p;
	
	//현재위치까지의 최대값을 리턴 
	return matrix[i][j] + maxPrev;
}

//dynammic(n) 설명 

//동적프로그래밍의 설계는 재귀버전에서 추가적으로 메모이제이션을 위한 행렬의 형태와 같은 배열을 할당
//c[i][j]는 [1][1]에서 [i][j]까지 경로 중 최대값을 저장
//재귀버전과 다르게 loop문 안에서 크기가 작은 문제의 값을 풀어가면서 크기가 큰 문제의 값을 구함 
//[1][1]에서 [n][n]까지의 경로 중 최대값을 리턴	

int matrixPath::dynamic(int n){
    int maxPrev;
    Point p;
	
	//경로에 포함되지 않는 배열의 구간은 최소값으로 설정 
	for(int a=1;a<=n;a++){
        c[0][a] = INT_MIN;
    }
    for(int b=1;b<=n;b++){
        c[b][0] = INT_MIN;
    }
    //값을 구하기 위해선 [0][0] 0으로 초기화 필수 
	c[0][0] = 0;
    
    
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){		
     		//각 직전 위치들까지의 경로 중 최댓값을 가진 값   
            maxPrev = max(c[i][j-1],max(c[i-1][j],c[i-1][j-1]));
			//현재위치까지의 최대값을 c[i][j]에 저장 
			c[i][j] = matrix[i][j] + maxPrev;           
			//각 직전 위치들까지의 경로 중 최댓값을 가진 직전위치의 좌표값을 Point p형태로 path[i][j]에 저장 
			if(maxPrev == c[i][j-1]){Point p1 = Point(i,j-1);p=p1;}
			if(maxPrev == c[i-1][j]){Point p1 = Point(i-1,j);p=p1;}
			if(maxPrev == c[i-1][j-1]){Point p1 = Point(i-1,j-1);p=p1;}
			path[i][j] = p;
		} 
    }
	//최종적으로 구하려는 [N][N]까지의 최대값 c[i][j] 리턴 
    return c[n][n];
}

void matrixPath::printPath(){
	//역순으로 출력되기 때문에 스택형태로 버퍼에 모아둔 뒤 FILO으로 출력하면 경로를 출력할 수 있다. 
	Point* printBuffer = new Point[size*size];
	//스택 구현을 위한 인덱스 포인터로 가르키는 부분부터 먼저 출력할 수 있게 합니다. 
	int index=0; 
	Point p = Point(size,size);
	
	//[N][N]을 먼저 스택에 넣어줍니다.	
	printBuffer[index++] = p; 
	
	//경로를 거슬러가기 위해 [N][N]에서 path[N][N]을 따라 탐색을 시작 
	p = path[size][size];
	
	//시작점인 [1][1]에 도달하기 전까지 최대값 경로로 거슬러 가면서 지나친 좌표값을 Point객체 형태로 프린트버퍼에 저장 
   	while((p.getX() !=1)||(p.getY() !=1)){
        //스택에 저장합니다. 
		printBuffer[index++] = p; 
		p = path[p.getX()][p.getY()];
	}
	//시작점[1][1] 스택에 삽입 
	printBuffer[index] = p; 
	
	//버퍼에 역순으로 저장된 경로점들을 원래 순서대로 꺼내며 출력 
	cout<<"\n\t\t\t<<최대값을 가진 경로를 출력합니다.>>"<<endl<<endl;
	while(index!=0){
		printBuffer[index--].printPoint();
		cout<<" -> ";
	}
	//마지막 경로점 출력 
	printBuffer[index].printPoint();
	cout<<endl;
}
void matrixPath::printFcount(){
	cout<<"\n\t\t<recursive()의 중복된 함수 횟수를 출력합니다.>"<<endl<<endl;
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			cout<<"\t\t- recursive("<<i<<","<<j<<")는 "<<fcount[i][j]<<"번 호출되었습니다."<<endl;
		}
	}
}
