class Point{
    int x,y;
    public:
        Point(int xx,int yy);
        Point(); 
		Point& operator=(Point& p);
		void printPoint();
      	int getX();
      	int getY();
};

class matrixPath{
  	Point** path;
  	int** matrix;
  	int** fcount;
 	int** c;
  	int size;
  
  public:
      matrixPath(int n);
      int recursive(int i,int j);
      int dynamic(int n);
      void printPath();
      void printFcount();
      Point maxPath(int a, int b, int c);
};
