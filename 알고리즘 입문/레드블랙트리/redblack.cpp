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
	//root��忡�� ���� ���� 
	while (x != z) {
		if (x->key == search_key) return x;
		//ã���� �ش� ��� ������ ���� 
		x = (x->key > search_key) ? x->l : x->r;
		//ũ�⸦ ���Ͽ� �����̳� 
		//������ Ʈ���� ���� Ž�� 
	}
	return NULL;
	//Ž���� �ȵ��� ��� �� ������ ���� 
}

void IntRBTree::insert(int v, int index){
	x = head; p = head; g = head;
	//root�������� ���� 
	cout<<"[��� "<<v<<" ���� ���� ����]"<<endl<<endl;
	cout<<"���� �� Ʈ���� ����"<<endl;
	this->print(); 
	while (x != z) {//x�� �� ����� �� ���� ���� 
		gg = g; g = p; p = x;
		//gg�� x�� �θ��� �θ��� �θ� ���
		//g�� x�� �θ��� �θ� ���
		//p�� x�� �θ� ���  
		if (x->key == v){return;}
		//���� ���ڰ� �ִ� ��� ������ �̷������ �ʴ´� 
		x = (x->key > v) ? x->l : x->r;
		//v�� ���� x��庸�� ũ�� x�� ������ Ʈ����
		//������ x�� ���� Ʈ���� ���� 
		if (x->l->b && x->r->b){this->split(v);}
		//�������� �� x�� �ڽĳ�尡 ��� �����̸� split�� �����Ѵ� 
	}
	x = new Node(red, v, index, z, z);
	//���γ��� ��带 ���� 
	if (p->key > v){p->l = x;}
	else{p->r = x;} 
	//����� Ű���� ���Ͽ� �˸��� ��ġ�� ���� 
	cout<<x->key<<" ��带 ���� �� �����մϴ�."<<endl;
	this->print(); 
	
	this->split(v); 
	//split ���� 
	
	head->r->b = black;
	//��Ʈ�� ������ �ٲ۴� 
	cout<<"��Ʈ ��带 ������ �ٲ۴�.\n"; 
	this->print();
	
	cout<<"["<<x->key<<" ��� ���� ���� �Ϸ�]"<<endl;
	this->print();
	cout<<endl<<endl;
}

void IntRBTree::split(int v){
	x->b = red; x->l->b = black; x->r->b = black;
	//x��带 ����,���� �ڽ��� ������ �ٲ۴� 
	cout<<x->key<<" ��带 ����, �ڽ� ����� "<<x->l->key<<", "<<x->r->key<<" ��带 ������ �ٲ۴�"<<endl; 
	this->print();
	 
	if (p->b) {//p��尡 �����̸�  
		g->b = red;//p�� �θ� ��带 ����� �ٲ۴�  
		cout<<p->key<<" ����� �θ� ����� "<<g->key<<" ��带 ����� �ٲ۴� "<<endl; 
		this->print();
		
		if (g->key > v != p->key > v){p = this->rotate(v, g);}
		//rotate 	
		
		x = this->rotate(v, gg);
		//rotate 
		
		x->b = black;
		cout<<x->key<<" ��带 ������ �ٲ۴� "<<endl;
		this->print();
		//x��带 ������ �ٲ۴� 
	}
}

Node* IntRBTree::rotate(int v, Node *y){
	Node *gc, *c;
	c = (y->key > v) ? y->l : y->r;
	//y����� �ڽ� ��� c 
	cout<<c->key<<" ��带 �߽����� rotate ����"<<endl; 
	if (c->key > v) {
		gc = c->l; c->l = gc->r; gc->r = c;
	}
	else {
		gc = c->r; c->r = gc->l; gc->l = c;
	}
	//c����� �ڽĳ�� gc 
	//c��� �ؿ� gc����� �ڽ� ���� ���� 
	//c��带 gc��� �ؿ� ����  
	if (y->key > v) y->l = gc; 
	else y->r = gc;
	//y��� �ؿ� gc��带 �����Ѵ� 
	//y->c->gc���� Ʈ���� ������
	//y->gc->c�� �ٲ����. 
	this->print();
	return gc;
}
 
void IntRBTree::print(){
    Point* queue[50];
    int front = 0;
    int end = 0;
	//bfs�� �����ϱ� ����
	//��� �����͸� ��� ť
	//FIFO�� ���� �ε��� 
    
	Point* printQ[50];
    int printFront = 0;
    int printEnd = 0;
    //���� ���̿� �ִ� ��带  
    //�� ���� ���� �ٿ� ����ϱ� ���� 
	//������ ���� ť�� �ε��� 
	 
    int level=0;
    //���� ��ġ ���� ���̸� �˱� ���� ���� 
	int center = 25;
	//����ϱ� ���� ���ʷ� ���� x��ǥ �ʱ���ġ 
	
	int X;//���� x��ǥ 
	int prevX;//���� x��ǥ 
			
    Point *p,*temp,*lc, *rc;
	
	queue[end++] = new Point(head->r,center,level+1);  
    //����� ���� ��Ʈ��带 ó������ ť�� ����  
	//��Ʈ �ּҰ��� �� ��尡 ǥ���ؾߵǴ� ���� ���� ���� ���� 
	
	while(front != end){//ť�� ����ִ� ��� �ݺ��� ���� 
        p = queue[front++];
		//ť �ȿ� �ִ� ���� ���� 
		printQ[printEnd++] = p;
		//����Ʈ ť�� ����
		 
		//���� ����� ���̰� ���� ��ϵ� ���̿� �ٸ� ��� 
		//���� ���̿� �ִ� ������ ��� ������ ��� 
		if(level != p->y){
			prevX = 0; 
			while(printFront !=printEnd-1){
				temp = printQ[printFront++];
				//����Ʈ ť�� ����� ��带 ������ 
				X = (temp->x)-prevX;
				prevX = temp->x;
				//���� ������ ������ 
				//�յ� ������ ���� ���̸� ���Ѵ� 
				for(int i=0;i<X-3;i++){cout<<" ";}
				//�� ���̸�ŭ ������ �����ش�	
				if((temp->n->b)){cout<<temp->n->key<<"(R)";}
				if(!(temp->n->b)){cout<<temp->n->key<<"(B)";}
				//����� Ű�� ���		
			}
			//���� ������ �ִ� ������ ��� ��µ� 
			cout<<endl; 
			for(int i=0;i<50;i++){cout<<"-";}
			cout<<endl; 
			level = p->y;
			//���̸� ���� ���� ���� �缳�� 
		}
		//�ڽĳ�尡 �ִٸ� ť���� �����Ѵ� 
		//�ڽĳ���� ���� ��ǥ = �θ��� ���� ��ǥ(+|-)k ���� 
		if(p->n->l->key){
			//if p node has left child push it into the queue
			lc = new Point(p->n->l,(p->x)-(10-level*2),(p->y)+1);
			//�ڽ��� �θ� ��� ���� ��ǥ(p->x)����   
			//���̰� ����� ���� 
			//�¿� ��ǥ ������ ������ 
			//���� ������ �����Ͽ����ϴ� 
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
	//����Ʈ ť�� �����ִ� ���� �� ������ ������ ��� ���
	//����� ���� ��İ� �����մϴ� 
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
