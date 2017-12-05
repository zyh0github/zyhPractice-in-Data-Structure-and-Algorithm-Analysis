#include <iostream>
#include "Head.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

LinkStack<char> operatorStack;//运算符栈 
LinkStack<double> calculateStack;//操作数栈

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
		cout<<"like this：2+3*(3+5)-6/4=    "<<endl;
		cout<<"only integers!"<<endl;
		cout<<"Please input your Computation Expression:  "<<endl;
		cout<<endl;
		while(cin>>x&&x!='=')//以等号结束 输入 
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
		
		
		//得到中缀表达式在input数组里，得到后缀表达式放在get数组里
		for(int i=0;i<last;i++)
		{
			if(judge(input[i])==10)//如果是数字 
			{
				//printf("%d",last);
				get[lastget]=input[i];
				lastget++;
				//printf("%c",calculateStack.GetTop());
			}
			else if((judge(input[i])!=10&&judge(input[i])>0)||input[i]==')')//是运算符 
			{
				if(operatorStack.GetTop()==NULL)//运算符栈空 
				{
					operatorStack.Push(input[i]);
				}
				else//把运算符和栈顶比较 
				{
					if(input[i]==')')
					{
						//printf("1\n");
						while(operatorStack.GetTop()!='(')
						{
							
							char ch;
							operatorStack.Pop(ch);
							//printf("%c\n",ch);
							// 用ch计算 
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
					//若栈顶运算符优先级低于当前运算符，则当前运算符进栈
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
		
		
		//扫描完之后，把操作符栈剩余的元素全部放进get 
		//printf("%s\n",get);
		while(operatorStack.GetTop()!=NULL)
		{
		 	char ch;
		 	operatorStack.Pop(ch);
		 	//用ch运算 
		 	get[lastget]=ch;
		 	lastget++;
		} 
		
		 //printf("%s\n",get);
		
		for(int i=0;i<lastget;i++)//从左到右扫描
		{
			if(judge(get[i])==10)//如果是数字 
			{
				//printf("%d",last);
				calculateStack.Push(get[i]-48);
				//printf("%c",calculateStack.GetTop());
			}
			else if(judge(get[i])!=10&&judge(get[i])>0)//是运算符 
			{
				
					//printf("1\n");
					compute(get[i]); 
				
			}
			
		 } 
		 
		 
		 //扫描完之后，如果运算栈不为空则弹出并运算，直到为空
//		while(operatorStack.GetTop()!=NULL)
//		 {
//		 	char ch;
//		 	operatorStack.Pop(ch);
//		 	//用ch运算 
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
