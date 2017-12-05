#include <iostream>
#include "Head.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

LinkStack<char> operatorStack;//�����ջ 
LinkStack<double> calculateStack;//������ջ

void compute(char ch)
{
	if(ch=='+')
	{
		double a,b;
		calculateStack.Pop(b);
		calculateStack.Pop(a);
				
		a=a+b;
		calculateStack.Push(a);
		//printf("%lf\n",a);
	}
	else if(ch=='-')
	{
		double a,b;
		calculateStack.Pop(b);
		calculateStack.Pop(a);
				
		a=a-b;
		calculateStack.Push(a);
		//printf("%lf\n",a);
	}
	else if(ch=='*')
	{
		double a,b;
		calculateStack.Pop(b);
		calculateStack.Pop(a);
				
		a=a*b;
		calculateStack.Push(a);
		//printf("%lf\n",a);
	}
	else if(ch=='/')
	{
		double a,b;
		calculateStack.Pop(b);
		calculateStack.Pop(a);
				
		a=a/b;
		calculateStack.Push(a);
		//printf("%lf\n",a);
	}
}

int main(int argc, char** argv) {
	
	while(1)
	{
		
		char get[100];
		char input[100];
		char x=NULL;
		int last=0;
		int lastget=0;
		int correct=0;
		cout<<"like this��2+3*(3+5)-6/4=    "<<endl;
		cout<<"only integers!"<<endl;
		cout<<"Please input your Computation Expression:  "<<endl;
		cout<<endl;
		while(cin>>x&&x!='=')//�ԵȺŽ��� ���� 
		{
			
			input[last]=x;
			last++;
			//printf("%d",last);
		}
		
		
		for(int i=0;i<last;i++)
		{
			if(judge(input[i])==2)
			{
				correct=-1;
			}
			if(judge(input[i])==-1)
			{
				
				correct=0;
				break;
			} 
			
		}
		if(correct==-1)
		{
			printf("please input correct equation!\n");
			printf("\n");
			continue;
		 }
		
		
		//�õ���׺���ʽ��input������õ���׺���ʽ����get������
		for(int i=0;i<last;i++)
		{
			if(judge(input[i])==10)//��������� 
			{
				//printf("%d",last);
				get[lastget]=input[i];
				lastget++;
				//printf("%c",calculateStack.GetTop());
			}
			else if((judge(input[i])!=10&&judge(input[i])>0)||input[i]==')')//������� 
			{
				if(operatorStack.GetTop()==NULL)//�����ջ�� 
				{
					operatorStack.Push(input[i]);
				}
				else//���������ջ���Ƚ� 
				{
					if(input[i]==')')
					{
						//printf("1\n");
						while(operatorStack.GetTop()!='(')
						{
							
							char ch;
							operatorStack.Pop(ch);
							//printf("%c\n",ch);
							// ��ch���� 
							get[lastget]=ch;
							lastget++;
						 } 
						 char a;
						 operatorStack.Pop(a);
					 } 
					 
					else if(input[i]=='('||operatorStack.GetTop()=='(')
					{
						operatorStack.Push(input[i]);
					}
					 
					else if(judge(operatorStack.GetTop())<judge(input[i]))
					//��ջ����������ȼ����ڵ�ǰ���������ǰ�������ջ
					{
						operatorStack.Push(input[i]);
					 }
					
					 else
					{
					 	while(judge(operatorStack.GetTop())>=judge(input[i]))
					 	{
					 		char ch;
							operatorStack.Pop(ch);
							get[lastget]=ch;
							lastget++;
							
						 }
						 operatorStack.Push(input[i]);
					 	
					}
					
				}
			}
		}
		
		
		//ɨ����֮�󣬰Ѳ�����ջʣ���Ԫ��ȫ���Ž�get 
		//printf("%s\n",get);
		while(operatorStack.GetTop()!=NULL)
		{
		 	char ch;
		 	operatorStack.Pop(ch);
		 	//��ch���� 
		 	get[lastget]=ch;
		 	lastget++;
		} 
		
		 //printf("%s\n",get);
		
		for(int i=0;i<lastget;i++)//������ɨ��
		{
			if(judge(get[i])==10)//��������� 
			{
				//printf("%d",last);
				calculateStack.Push(get[i]-48);
				//printf("%c",calculateStack.GetTop());
			}
			else if(judge(get[i])!=10&&judge(get[i])>0)//������� 
			{
				
					//printf("1\n");
					compute(get[i]); 
				
			}
			
		 } 
		 
		 
		 //ɨ����֮���������ջ��Ϊ���򵯳������㣬ֱ��Ϊ��
//		while(operatorStack.GetTop()!=NULL)
//		 {
//		 	char ch;
//		 	operatorStack.Pop(ch);
//		 	//��ch���� 
//		 	//printf("2\n");
//		 	compute(ch);
//		} 
		  
		if(calculateStack.Length()==1)
		{
			printf("%lf\n",calculateStack.GetTop());
			printf("\n");
			double x;
			calculateStack.Pop(x); 
		}
		
		
		
	}
	
	
	
	return 0;
}
