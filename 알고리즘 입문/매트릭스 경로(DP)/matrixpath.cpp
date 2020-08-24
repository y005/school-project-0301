#include "matrixpath.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//��Ŀ����� ��ǥ���� �����ϱ� ���� PointŬ����  
//�⺻������ (0,0)��ǥ 
Point::Point(){
	x=0;
	y=0;
}
//������ (x,y)��ǥ 
Point::Point(int xx,int yy){
    x=xx;
    y=yy;
}
//������� ������ 
Point& Point::operator=(Point& p){
    this->x= p.getX();
    this->y= p.getY();
    return *this;
}
//��ǥ���� (x,y) ���·� ��� 
void Point::printPoint(){
    cout<<"("<<this->getX()<<", "<<this->getY()<<")";
}
int Point::getX(){
    return this->x;
}
int Point::getY(){
    return this->y;
}
//����� �����Ҵ��ϰ� ����� ����ġ�� �������� ����
//�̿� ��� �� DP �� �ϱ� ���� �ʿ��� �迭 �Ҵ� �� �ʱ�ȭ  
matrixPath::matrixPath(int n){
    //matirx[i][j] == ���[i][j]������ ����ġ�� ������ �迭 	
	matrix = new int*[n];
	
	//fcount[i][j] == ���[i][j]������ �Լ� ȣ�� Ƚ���� ����ϱ� ���� �迭 
	fcount = new int*[n];
	
	//�ִ밪�� ��θ� �����ϴ� �迭�Դϴ�
    //path[i][j] == [1][1]���� [i][j]���� ��� �� �ִ밪�� ���� 
	//��ο��� ���� ��ġ ������ ��� ��ġ�� Point(x��ǥ,y��ǥ)�� ������ ��ü���� �迭  
	path = new Point*[n];
    
	//��͹������� �ߺ��� ���� �ϱ����� �޸������̼��� ���� ���� �迭 
	//c[i][j] == [1][1]���� [i][j]���� ��� �� �ִ밪�� �����ϴ� �迭 
	c = new int*[n];
	
	//����� ũ�⸦ ���� N*N�� ��ķ� �����Ҵ�� 
    size = n;
    
    //���߹迭�� ����(N*N)�� �� �迭���� ���� �Ҵ��մϴ�. 
    for(int i=0;i<=n;i++){
       matrix[i] = new int[n];
       fcount[i] = new int[n];
       path[i] = new Point[n];
       c[i] =  new int[n];
	}
   	//����� ������ �ƴ� ���� ����ġ�� 0���� �ʱ�ȭ 
    for(int a=0;a<=n;a++){
       matrix[0][a] = 0;
    }
    for(int b=0;b<=n;b++){
       matrix[b][0] = 0;
    }
    
   	srand((unsigned int)time(NULL));
    //��� �ʱⰪ���� -9~+9������ ������ ������ �ʱ�ȭ  
	cout<<"\n\t\t\t<�밢���� ���� ������ ������ ����...?>"<<endl; 
	cout<<">>����� �ʱⰪ�� ������ ���Խ�Ű�� ���� ����� �̵��� �־ �밢���� �������� ��ο� ������ �� �ֽ��ϴ�. ����� �ʱⰪ�� ������� �����ϰ� �Ǵ� ��� ��ο� �̵����� �밢���� �̵��� ����Ѵ��ص� �ִ��� ��θ� ��� �ؾ� ����� �ִ��� Ŀ���� ������ �밢���� �̵���θ� �׻� ����� �̵� ��ο� �������� �ʱ� �����Դϴ�."<<endl<<endl; 
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            matrix[i][j] = rand()%19-9;
        }
    }
   
   //Ž���� ���� �迭�� �ʱ�ȭ 
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            fcount[i][j] = 0;
        }
    }
    //Point(0,0)���� �ʱ�ȭ 
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            Point p = Point(0,0);
			path[i][j] = p;
        }
    }
    cout<<"\t\t\t\t<<������ ����� ���>>\n"<<endl; 
	for(int i=1;i<=n;i++){
        cout<<"\t\t\t\t[";
		for(int j=1;j<=n;j++){
            cout<<" "<<matrix[i][j];
        }
        cout<<"]"<<endl;
    }
}

//recursive(i,j) ���� 

//[1][1]���� ���� ��ġ������ ��ο��� ���� �ִ밪�� ���� ��ġ������ ��ο��� ���� �ִ밪�� ���� ��ġ�� ������ ���� ���� ���Դϴ�. 
//��Ŀ��� ������ �� �ִ� ������ ������, �Ʒ�, �밢�� �Ʒ��� ���ѵǾ� �ֱ� ������ ���� ��ġ�� 3������ ��찡 �ֽ��ϴ�.	
//1. ( ���� ���� �ε��� - 1, ���� ���� �ε��� )
//2. ( ���� ���� �ε���, ���� ���� �ε��� - 1 )
//3. ( ���� ���� �ε��� - 1, ���� ���� �ε��� - 1 )
//���� �� ��� �� �ִ밪�� ���� ��ο��� ���� ��ġ�� ���� ���� �����ָ� �ִ밪�� ���� �� �ֽ��ϴ�.
//([1][1]���� ���� [i][j]���� ����� �ִ밪) = ���� [i][j]�� ������ ����ġ + MAX([1][1]���� ���� ��ġ���� ��� ����ġ�յ�)
//�߰������� ���� �� ��� �� �ִ밪�� ���� ���� ��ġ���� path[i][j]�� �����ϸ� ���߿� [N][N]���� �����Ͽ� ������ ������ ��θ� �� �� �ֽ��ϴ�.
//�̷��� ���س� ���� ��ġ������ ��ο��� ���� �ִ밪�� ����	 
int matrixPath::recursive(int i,int j){
	int maxPrev;
	Point p;
	//�Լ��� �ߺ�ȣ��Ƚ���� ���� ���� �Լ�(recursive(i,j))�� ȣ��Ƚ���� �߰� 
	fcount[i][j]++;
	
	
	//��ο� ���Ե��� �ʴ� �����̱� ������ �ش� ����ġ�� �ּҰ����� �����Ͽ� �ڵ����� ��ο� ���Ե��� �ʵ��� �ּҰ����� ����
	//���� ���ϱ� ���ؼ� [0][0]�� 0���� �����ʼ� 
	if((i==0)||(j==0)){
		if((i==0)&&(j==0)){return 0;}  
		return INT_MIN;
	} 
	
	int a = this->recursive(i-1,j);
	int b = this->recursive(i,j-1);
	int c = this->recursive(i-1,j-1);
	
	//�� ���� ��ġ������� ��� �� �ִ��� ���� ��
	maxPrev = max(a,max(b,c)); 
	
	//�� ���� ��ġ������� ��� �� �ִ��� ���� ������ġ�� ��ǥ���� Point���·� path[i][j]�� ���� 
	if(maxPrev == a){Point p1 = Point(i-1,j);p=p1;}
	if(maxPrev == b){Point p1 = Point(i,j-1);p=p1;}
	if(maxPrev == c){Point p1 = Point(i-1,j-1);p=p1;}
	path[i][j] = p;
	
	//������ġ������ �ִ밪�� ���� 
	return matrix[i][j] + maxPrev;
}

//dynammic(n) ���� 

//�������α׷����� ����� ��͹������� �߰������� �޸������̼��� ���� ����� ���¿� ���� �迭�� �Ҵ�
//c[i][j]�� [1][1]���� [i][j]���� ��� �� �ִ밪�� ����
//��͹����� �ٸ��� loop�� �ȿ��� ũ�Ⱑ ���� ������ ���� Ǯ��鼭 ũ�Ⱑ ū ������ ���� ���� 
//[1][1]���� [n][n]������ ��� �� �ִ밪�� ����	

int matrixPath::dynamic(int n){
    int maxPrev;
    Point p;
	
	//��ο� ���Ե��� �ʴ� �迭�� ������ �ּҰ����� ���� 
	for(int a=1;a<=n;a++){
        c[0][a] = INT_MIN;
    }
    for(int b=1;b<=n;b++){
        c[b][0] = INT_MIN;
    }
    //���� ���ϱ� ���ؼ� [0][0] 0���� �ʱ�ȭ �ʼ� 
	c[0][0] = 0;
    
    
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){		
     		//�� ���� ��ġ������� ��� �� �ִ��� ���� ��   
            maxPrev = max(c[i][j-1],max(c[i-1][j],c[i-1][j-1]));
			//������ġ������ �ִ밪�� c[i][j]�� ���� 
			c[i][j] = matrix[i][j] + maxPrev;           
			//�� ���� ��ġ������� ��� �� �ִ��� ���� ������ġ�� ��ǥ���� Point p���·� path[i][j]�� ���� 
			if(maxPrev == c[i][j-1]){Point p1 = Point(i,j-1);p=p1;}
			if(maxPrev == c[i-1][j]){Point p1 = Point(i-1,j);p=p1;}
			if(maxPrev == c[i-1][j-1]){Point p1 = Point(i-1,j-1);p=p1;}
			path[i][j] = p;
		} 
    }
	//���������� ���Ϸ��� [N][N]������ �ִ밪 c[i][j] ���� 
    return c[n][n];
}

void matrixPath::printPath(){
	//�������� ��µǱ� ������ �������·� ���ۿ� ��Ƶ� �� FILO���� ����ϸ� ��θ� ����� �� �ִ�. 
	Point* printBuffer = new Point[size*size];
	//���� ������ ���� �ε��� �����ͷ� ����Ű�� �κк��� ���� ����� �� �ְ� �մϴ�. 
	int index=0; 
	Point p = Point(size,size);
	
	//[N][N]�� ���� ���ÿ� �־��ݴϴ�.	
	printBuffer[index++] = p; 
	
	//��θ� �Ž������� ���� [N][N]���� path[N][N]�� ���� Ž���� ���� 
	p = path[size][size];
	
	//�������� [1][1]�� �����ϱ� ������ �ִ밪 ��η� �Ž��� ���鼭 ����ģ ��ǥ���� Point��ü ���·� ����Ʈ���ۿ� ���� 
   	while((p.getX() !=1)||(p.getY() !=1)){
        //���ÿ� �����մϴ�. 
		printBuffer[index++] = p; 
		p = path[p.getX()][p.getY()];
	}
	//������[1][1] ���ÿ� ���� 
	printBuffer[index] = p; 
	
	//���ۿ� �������� ����� ��������� ���� ������� ������ ��� 
	cout<<"\n\t\t\t<<�ִ밪�� ���� ��θ� ����մϴ�.>>"<<endl<<endl;
	while(index!=0){
		printBuffer[index--].printPoint();
		cout<<" -> ";
	}
	//������ ����� ��� 
	printBuffer[index].printPoint();
	cout<<endl;
}
void matrixPath::printFcount(){
	cout<<"\n\t\t<recursive()�� �ߺ��� �Լ� Ƚ���� ����մϴ�.>"<<endl<<endl;
	for(int i=1;i<=size;i++){
		for(int j=1;j<=size;j++){
			cout<<"\t\t- recursive("<<i<<","<<j<<")�� "<<fcount[i][j]<<"�� ȣ��Ǿ����ϴ�."<<endl;
		}
	}
}
