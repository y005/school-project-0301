#include<iostream>
#include<string>
class stringMatch{
  private:
	  std::string pattern;//���� ������ ���� 
	  int m;//size of pattern
  public:
           stringMatch();
           bool match(char* buffer,int i);//���ڿ� i...i+m-1�� ���ϰ� ��ġ�ϴ��� ���� ���� 
           void naive();//���ø�Ī �˰��� 
           
		   void kmp();//kmp �˰��� 
           void preprocessing(int* pi);//kmp
           
		   void boyerMoore();//���̾� ���� �˰��� 
};
