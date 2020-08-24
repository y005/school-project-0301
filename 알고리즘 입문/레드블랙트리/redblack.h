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
		Node *l, *r; 	//왼쪽 자식과 오른쪽 자식의 포인터  
};

class Point{
	//노드를 화면에 출력하기 위한 클래스  
    public: 
        Point(Node* nn,int xx,int yy){
			n = nn;
			x = xx;
			y = yy;
		};
		Node* n;//출력할 노드 포인터 
        int x,y;//출력할 좌표 x,y(가로,세로)	
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
		//헤드 포인터,NIL포인터,노드들을 저장하기 위한 포인터  
};

#endif
