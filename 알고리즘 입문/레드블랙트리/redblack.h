#ifndef REDBLACK_H
#define REDBLACK_H

const int black = 0;
const int red = 1;

#define	MAX_STRKEY_LEN	20

class Node {
	public:
		Node(int bb, int k, int i, Node *ll, Node *rr){ 
			b = bb, key = k; index = i, l = ll, r = rr; 
		};	    
		int b;			// color
		int key;		// data
		int index;
		Node *l, *r; 	//���� �ڽİ� ������ �ڽ��� ������  
};

class Point{
	//��带 ȭ�鿡 ����ϱ� ���� Ŭ����  
    public: 
        Point(Node* nn,int xx,int yy){
			n = nn;
			x = xx;
			y = yy;
		};
		Node* n;//����� ��� ������ 
        int x,y;//����� ��ǥ x,y(����,����)	
};

class IntRBTree {
	public:
		IntRBTree();  
    	Node *search(int search_key);
    	void insert(int v, int index);
		void split(int v);
		Node *rotate(int v, Node *y);
		void print();
	private:
		Node *head, *z, *gg, *g, *p, *x;
		//��� ������,NIL������,������ �����ϱ� ���� ������  
};

#endif
