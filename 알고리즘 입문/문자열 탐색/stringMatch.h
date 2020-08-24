#include<iostream>
#include<string>
class stringMatch{
  private:
	  std::string pattern;//비교한 패턴을 저장 
	  int m;//size of pattern
  public:
           stringMatch();
           bool match(char* buffer,int i);//문자열 i...i+m-1이 패턴과 일치하는지 여부 리턴 
           void naive();//원시매칭 알고리즘 
           
		   void kmp();//kmp 알고리즘 
           void preprocessing(int* pi);//kmp
           
		   void boyerMoore();//보이어 무어 알고리즘 
};
