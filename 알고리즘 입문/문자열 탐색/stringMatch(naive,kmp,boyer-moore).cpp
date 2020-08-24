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
	//����.txt�� ������ i��  buffer�� �����ϱ� ���� ���� ���� ������ a�� ��ȯ�մϴ�.(module���� ���)  
	int a=i%m;
	//�� ���ڶ� ����ġ �� ��� flag�� false�� �ٲ��ݴϴ�.  
	bool isMatch=true;
	//���ʴ�� ��ġ�ϴ��� Ȯ�� 
	for(int j=0;j<m;j++){
		if(buffer[a] != pattern.at(j)){
			//�� ���ڶ� ����ġ �� ��� flag�� false�� �ٲ��ݴϴ�.  
			isMatch=false; 
		}
		a = (a+1)%m;//ȯ�� �����̹Ƿ� increment���� module ���� ����  
	}
	return isMatch;
	//��� ���ڰ� ��ġ�ϴ� ��쿡�� true����  
}
void stringMatch::naive(){
	ifstream read("sample1.txt");// ���� ���ڿ� ������ �Է� 
	int i=-1;//����.txt�� ������  
	int index=0;//����.txt�� ������ ȯ�� ���ۿ� �����ϱ� ���� ȯ�� ���� ������ 
	bool match=false;//�� ���̶� ���ڿ��� ��ġ�ϸ� match�� true�� �ٲ�ϴ�	
	char* buffer = new char[m];//����.txt�� �Ϻθ� �����ϴ� ȯ�� ���� 
	int count=0; 
	if(read.is_open()){
		char c;
		//���� ȯ������ ũ�⸸ŭ ����.txt�� ���ڿ��� ä���ֽ��ϴ� 
		for(;index<m;){
			read.get(c);
			buffer[index++]=c;
		}	
		while(!read.eof()){
			i++;
			// A[i...i+m-1] ���ڿ��� ���ϰ� ��ġ�ϸ� ��ġ�� ��ġ�� ����մϴ�. 
			if(this->match(buffer,i)){
				cout<<"match found!>> "<<i+m<<endl;
				match=true;
				count++;
			}
			//����.txt�� ������ Ž�� ����  
			if(read.eof()){break;}
			//����.txt�� ���ڿ��� ȯ�����ۿ� �� ���ھ� �߰��մϴ�. 
			read.get(c);
			buffer[(index%m)] = c;
			index = (index+1)%m;
		}
		//�ѹ��̶� ��Ī�� �ȵ� ��� ��� 
    	if(!match){cout<<"match not found ;("<<endl;}
	}
	cout<<count<<"���� ���� ���ڿ� Ž��!!"<<endl;
    read.close();
} 
void stringMatch::kmp(){
    //�ش� ���ϰ� ��ġ���� ���� �� �̵��ϴ� ���� ������ ��ġ�� ������ pi�迭�� �����մϴ� 
	ifstream read("sample1.txt");// ���� ���ڿ� ������ �Է�
	int* pi;
	pi = new int[m+1];
	preprocessing(pi);
	int i=0;//����.txt�� ������ 
	int j=0;//������ ������ 
	bool match=false;
	int count=0;

	if(read.is_open()){
		char c;
		read.get(c);
		i++;
		
		while(!read.eof()){
			if(j==m){
				//������ ������ ��ġ�� �߱� ������ ��Ī�� ��ġ�� ���
				cout<<"match found!>> "<<i-1<<endl;
				j=-1;//���� ��Ī��ġ�� ã�� ���� ���� �����͸� �ʱ�ȭ
				match=true;
				count++; 
			}
			if((j==-1)||(c==pattern.at(j))){
				//ù ���� ���� ���� ��쳪 ���� ���ڰ� ��ġ�� ��� ���������Ϳ� ����.txt�� �����͸� ���� 
				read.get(c);
				i++;
				j++;
			}
			else{
				//�ش� ���ϰ� ��ġ���� ���� ��� �̵��ؾ� �� ��ġ�� ���� �����͸� ���� 
				j = pi[j];
			}
		}
		//�ѹ��̶� ��Ī�� �ȵ� ��� ��� 
		if(!match){cout<<"match not found ;("<<endl;}
	}
	cout<<count<<"���� ���� ���ڿ� Ž��!!"<<endl;
}
void stringMatch::preprocessing(int* pi){
    //�ش� ���ϰ� ��ġ���� ���� �� �̵��ϴ� ���� ������ ��ġ�� ������ pi�迭�� �����մϴ� 
	//����� �ڱ� ���Ͽ� ���� kmp �˰����� �����մϴ�. 
	int j=0;//���� ������ 
	int k=-1;//���� ������ 
	pi[0]=-1; //ó�� ���ϰ� ��ġ���� ���� ���� �����͸� �ʱ�ȭ ������� �ϹǷ� -1�� ����  
	while(j<m){
        if((k==-1)||(pattern.at(j)==pattern.at(k))){
         	//k�� �ʱ�ȭ�ǰų� �ش� �����Ͱ� ����Ű�� ���ڳ��� ��ġ�ϴ� ��� ���������͵��� �����ϰ� pi�迭�� �� ����  
			j++;
         	k++;
         	pi[j]=k;
		}
		else{
			//�ش� �����Ͱ� ����Ű�� ���ڳ��� ��ġ���� �ʴ� ��� �������� ���� �迭�� ����� ��ġ��ŭ �մ�� 
		 	k=pi[k];
		}
	} 
}

void stringMatch::boyerMoore(){
	ifstream read("sample1.txt");// ���� ���ڿ� ������ �Է�
	vector<pair<int,int> > jump;
	
	//computeJump�κ�����  
	//�ش��ϴ� ���ڿ��� ��� �̵��ؾ� �Ǵ� Ƚ���� �����ϱ� ���� �迭�� ���� 
	//���Ϳ��� (������ ������,�̵��ϴ� Ƚ��)�� �迭�� ����� 
	int num;
	int count =0;
	//������ char���� ���ڷ� �ٲ㼭 �����մϴ�. 
	char* ch = new char[m+1];
	strcpy(ch,pattern.c_str());
	for(int i=0;i<m-1;i++){
		num =(int)ch[i];
		jump.push_back(pair<int,int>(num,m-1-i));//�ش� ���ڿ��� �̵�Ƚ�� ���Ϳ� ���� 
	}
	num = (int)pattern.at(m-1);
	jump.push_back(pair<int,int>(num,m));//������ ���ڴ� m�� �̵� 
	
	int i=0;//����.txt�� �ε��� 
	int j;//������ �ε��� 
	int skip;//������ Ƚ�� 
	int index=0;//ȯ�� ���ۿ� �����ϱ� ���� ������ 
	bool match=false;
	char* buffer = new char[m];//����.txt�� �Ϻθ� �����ϴ� ȯ������ 
		
	//��ġ �޸���ƽ�� �̵�Ƚ�� ����ϴ� ���� 
	int* goodSuffix = new int[m];
	int a;//������ �޺κ� ������ 
	int b=0;//������ �պκ� ������ 
	a=m-1;//�ڿ��� ���� ���ϱ� ���� ������ ������ ���� 
	for(int c=0;c<m;c++){
		goodSuffix[c]=m;	
	}//�⺻ �̵�Ƚ���� m���� �ʱ�ȭ 	
	//������ �պκа� ������ �޺κ��� ��ġ�ϴ��� ���ذ��� �̵��ؾߵǴ� Ƚ���� ��� 
	while(a>0){
		if((b>=0)&&(pattern.at(a+b)==pattern.at(b))){
			b--;//�����ʺ��� ������ �޺κ��� ������ �պκа� ��ġ�ϸ� �� ������ ������ �÷����鼭 ��� ��
		}
		else{
			if(b<0){//������ �պκ��� ������ �޺κа� ��ġ�Ͽ� ������ �պκ��� �� �ձ��� �÷��� �� ��� 
				for(;a+b>=0;--b){
					goodSuffix[a+b]=a;
					//�񱳰� ���� �κк��� �� �ձ����� ��ġ�ϴ� ������ �޺κ����� ������ �ֱ� ������ ��� �̵��� �� �ִ� Ƚ���� a�� ����  
				}
			}
			else{//�� �� ������ ����ġ�� �߰��� ���� ������ �պκ��� �Ϻΰ� ������ �޺κа� ��ġ�ϴ� ��� 
				goodSuffix[a+b]=a;
				//����ġ �� �κп����� �̵�Ƚ���� a�� ����
			}
			b=m-a;//������ �պκ� ������ ���������� ��ĭ �̵� 
			a--;//������ �޺κ� ������ �������� ��ĭ �̵�			
		}
	}
	
	//���ڿ��� ���ϰ� ���ϸ� �̵��ϴ� ���� 
	if(read.is_open()){
		char c;
		//ȯ�� ���ۿ� �ʱ� ���ڿ����� ���� �־��ݴϴ�. 
		for(;index<m;){
			read.get(c);
			buffer[index++]=c;
		}
		index %= m;
		int k; 
		while(!read.eof()){
			j=m-1;//���� ������ 
			k=i+m-1;//����.txt�� ������ ��ġ�� ���� �� ��ġ�� ���� �����ϱ� ���ؼ� ���� ���嵵�� buffer�ּ��� k%m�� ��ȯ   
			while((j>-1)&&(pattern.at(j)==buffer[k%m])){
				//�����ʺ��� ���ϰ� ��ġ�ϴ��� Ȯ�� 
				//��ġ���� ������ �ݺ��� Ż�� 
				j--;
				k--;		
			}
			//��ġ���� ���� ��� ������ ���ڿ� �ش��ϴ� �̵� Ƚ����ŭ ����.txt�̵� 
			
			num = (int)buffer[(k)%m];//����ġ�� �߻��� ���� ����  		
			skip = m;//��Ÿ ���ڴ� m�� ������ �ؿ� for������ �׳� ����� ��� m�� �̵�  
			
			pair<int,int> temp;
			for(int a=0;a<m;a++){
				temp = jump.at(a);
				if(temp.first == num){
					 if(temp.second<skip){
					 	skip = temp.second;
						 //���ڿ� �߿� ������ ��� �ش��ϴ� �̵�Ƚ�� ��� 
						 //���� ������ ��� ���� ���� �̵�Ƚ���� ���  
					 }
				}
			}
			//����ġ �޸���ƽ�� ��쳪 ��ġ �޸���ƽ�� ��쿡�� �̵�Ƚ�� ��
			skip = skip-(m-j);//����ġ �޸���ƽ�� �̵�Ƚ�� ����ġ�� ���� �����ʿ��� (m-j)��ŭ ������ �����Ƿ� �̵� Ƚ������ ���� 
			if(goodSuffix[j]>skip){//����ġ�� �Ͼ�� �� ���̻簡 ������ �պκп��� ��ġ�� �̵��ϴ� Ƚ���� ���(��ġ �޸���ƽ)�� �̵�Ƚ�� �� 
				skip=goodSuffix[j];
			}
			//�� �̵�Ƚ���� ū ��츦 ä���Ͽ� �̵�Ƚ�� ����  			
			
			if(j==-1){
				//��Ī�� �� ��ġ�� ���  
				cout<<"match found!>> "<<i+m<<endl;
				match=true;	
				count++;
				skip =m;//��Ī�� �Ϸ� �Ǿ����Ƿ� ���ο� ��Ī ��ġ�� ã�� ���� m�� ����			
			}	
			
			//�̵� ����ŭ buffer�� ����.txt�� ���ڿ��� ȯ�����ۿ� ���� ���� 
			for(int a=0;a<skip;a++){
				read.get(c);
				buffer[index]=c;
				index=(index+1)%m;//ȯ�� ���ۿ� �����ϱ� ������ �����͸� increment �� module���� 		 
			} 
			//����.txt�� ������ ���� �̵��� ��ŭ ����  
			i +=skip;		
		}
		//�ѹ��̶� ��Ī�� �ȵ� ��� ��� 
		if(!match){ 
			cout<<"match not found ;("<<endl;
		}
	}
	cout<<count<<"���� ���� ���ڿ� Ž��!!"<<endl;    
	read.close();
}
