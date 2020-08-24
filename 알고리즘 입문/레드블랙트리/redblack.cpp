#include "redblack.h"
#include <iostream>

using namespace std;

IntRBTree::IntRBTree() { 
    z = new Node(black, 0, 0, 0, 0);
	z->l = z; 
	z->r = z;
	head =   new Node(black, 0, 0, 0, z); 
}

Node *IntRBTree::search(int search_key){
	Node *x = head->r;
	//root노드에서 부터 시작 
	while (x != z) {
		if (x->key == search_key) return x;
		//찾으면 해당 노드 포인터 리턴 
		x = (x->key > search_key) ? x->l : x->r;
		//크기를 비교하여 왼쪽이나 
		//오른쪽 트리로 들어가며 탐색 
	}
	return NULL;
	//탐색이 안됐을 경우 널 포인터 리턴 
}

void IntRBTree::insert(int v, int index){
	x = head; p = head; g = head;
	//root에서부터 진행 
	cout<<"[노드 "<<v<<" 삽입 과정 시작]"<<endl<<endl;
	cout<<"삽입 전 트리의 상태"<<endl;
	this->print(); 
	while (x != z) {//x가 빈 노드일 때 까지 진행 
		gg = g; g = p; p = x;
		//gg는 x의 부모의 부모의 부모 노드
		//g는 x의 부모의 부모 노드
		//p는 x의 부모 노드  
		if (x->key == v){return;}
		//같은 숫자가 있는 경우 삽입은 이루어지지 않는다 
		x = (x->key > v) ? x->l : x->r;
		//v의 값이 x노드보다 크면 x의 오른쪽 트리로
		//작으면 x의 왼쪽 트리로 들어간다 
		if (x->l->b && x->r->b){this->split(v);}
		//내려가는 중 x의 자식노드가 모두 레드이면 split을 수행한다 
	}
	x = new Node(red, v, index, z, z);
	//새로넣은 노드를 생성 
	if (p->key > v){p->l = x;}
	else{p->r = x;} 
	//노드의 키값을 비교하여 알맞은 위치에 삽입 
	cout<<x->key<<" 노드를 생성 후 삽입합니다."<<endl;
	this->print(); 
	
	this->split(v); 
	//split 실행 
	
	head->r->b = black;
	//루트를 블랙으로 바꾼다 
	cout<<"루트 노드를 블랙으로 바꾼다.\n"; 
	this->print();
	
	cout<<"["<<x->key<<" 노드 삽입 정렬 완료]"<<endl;
	this->print();
	cout<<endl<<endl;
}

void IntRBTree::split(int v){
	x->b = red; x->l->b = black; x->r->b = black;
	//x노드를 레드,양쪽 자식을 블랙으로 바꾼다 
	cout<<x->key<<" 노드를 레드, 자식 노드인 "<<x->l->key<<", "<<x->r->key<<" 노드를 블랙으로 바꾼다"<<endl; 
	this->print();
	 
	if (p->b) {//p노드가 레드이면  
		g->b = red;//p의 부모 노드를 레드로 바꾼다  
		cout<<p->key<<" 노드의 부모 노드인 "<<g->key<<" 노드를 레드로 바꾼다 "<<endl; 
		this->print();
		
		if (g->key > v != p->key > v){p = this->rotate(v, g);}
		//rotate 	
		
		x = this->rotate(v, gg);
		//rotate 
		
		x->b = black;
		cout<<x->key<<" 노드를 블랙으로 바꾼다 "<<endl;
		this->print();
		//x노드를 블랙으로 바꾼다 
	}
}

Node* IntRBTree::rotate(int v, Node *y){
	Node *gc, *c;
	c = (y->key > v) ? y->l : y->r;
	//y노드의 자식 노드 c 
	cout<<c->key<<" 노드를 중심으로 rotate 실행"<<endl; 
	if (c->key > v) {
		gc = c->l; c->l = gc->r; gc->r = c;
	}
	else {
		gc = c->r; c->r = gc->l; gc->l = c;
	}
	//c노드의 자식노드 gc 
	//c노드 밑에 gc노드의 자식 노드와 연결 
	//c노드를 gc노드 밑에 연결  
	if (y->key > v) y->l = gc; 
	else y->r = gc;
	//y노드 밑에 gc노드를 연결한다 
	//y->c->gc였던 트리의 구조가
	//y->gc->c로 바뀌었다. 
	this->print();
	return gc;
}
 
void IntRBTree::print(){
    Point* queue[50];
    int front = 0;
    int end = 0;
	//bfs를 실행하기 위해
	//노드 포인터를 담는 큐
	//FIFO을 위한 인덱스 
    
	Point* printQ[50];
    int printFront = 0;
    int printEnd = 0;
    //같은 깊이에 있는 노드를  
    //한 번에 같은 줄에 출력하기 위한 
	//프린터 버퍼 큐와 인덱스 
	 
    int level=0;
    //현재 위치 중인 깊이를 알기 위한 변수 
	int center = 25;
	//출력하기 위해 최초로 정한 x좌표 초기위치 
	
	int X;//현재 x좌표 
	int prevX;//이전 x좌표 
			
    Point *p,*temp,*lc, *rc;
	
	queue[end++] = new Point(head->r,center,level+1);  
    //출력을 위해 루트노드를 처음으로 큐에 삽입  
	//루트 주소값과 이 노드가 표시해야되는 가로 세로 값이 저장 
	
	while(front != end){//큐가 비어있는 경우 반복문 종료 
        p = queue[front++];
		//큐 안에 있는 원소 꺼냄 
		printQ[printEnd++] = p;
		//프린트 큐에 삽입
		 
		//꺼낸 노드의 깊이가 현재 기록된 깊이와 다른 경우 
		//이전 깊이에 있는 노드들을 모두 꺼내서 출력 
		if(level != p->y){
			prevX = 0; 
			while(printFront !=printEnd-1){
				temp = printQ[printFront++];
				//프린트 큐에 출력할 노드를 꺼낸다 
				X = (temp->x)-prevX;
				prevX = temp->x;
				//같은 깊이의 노드들은 
				//앞뒤 간격의 가로 차이를 구한다 
				for(int i=0;i<X-3;i++){cout<<" ";}
				//그 차이만큼 간격을 넓혀준다	
				if((temp->n->b)){cout<<temp->n->key<<"(R)";}
				if(!(temp->n->b)){cout<<temp->n->key<<"(B)";}
				//색깔과 키값 출력		
			}
			//같은 레벨에 있는 노드들이 모든 출력됨 
			cout<<endl; 
			for(int i=0;i<50;i++){cout<<"-";}
			cout<<endl; 
			level = p->y;
			//깊이를 현재 꺼낸 노드로 재설정 
		}
		//자식노드가 있다면 큐에다 삽입한다 
		//자식노드의 가로 좌표 = 부모노드 가로 좌표(+|-)k 형태 
		if(p->n->l->key){
			//if p node has left child push it into the queue
			lc = new Point(p->n->l,(p->x)-(10-level*2),(p->y)+1);
			//자식은 부모 노드 가로 좌표(p->x)에서   
			//깊이가 깊어질 수록 
			//좌우 좌표 간격을 좁혀서 
			//보기 쉽도록 설정하였습니다 
			queue[end++] = lc;
	        //push();
		}
		if(p->n->r->key){
			//if p node has right child push into the queue
	        rc = new Point(p->n->r,(p->x)+(10-level*2),(p->y)+1);
            queue[end++] = rc;
			//push();
		}
	} 
	//프린트 큐에 남아있는 제일 끝 깊이의 노드들을 모두 출력
	//방식은 위의 방식과 동일합니다 
	prevX = 0;
	while(printFront != printEnd){
		temp = printQ[printFront++];
		X = (temp->x)- prevX;
		prevX = temp->x;
		for(int i=0;i<X-3;i++){cout<<" ";}	
		if((temp->n->b)){cout<<temp->n->key<<"(R)";}
		if(!(temp->n->b)){cout<<temp->n->key<<"(B)";}		
	}
	cout<<endl; 
	for(int i=0;i<50;i++){cout<<"-";}
	cout<<endl;
	cout<<endl;		
}
