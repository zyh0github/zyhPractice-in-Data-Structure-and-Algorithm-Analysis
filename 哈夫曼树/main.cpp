#include <iostream>
#include <string.h>
#include <stdio.h>//������printf��scanf���� ��������Ҳ������ 
#include "head.h" 
using namespace std;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
														//	tree tr[9]={{'a',true,5,},{'b',true,2},{'c',true,9},{'d',true,3},{'e',true,6}};
														//	for(int i=0;i<9;i++)
														//	{
														//		printf("%c %d %d\n",tr[i].data,tr[i].mean,tr[i].weight);
														//	}
														
														
	char str[100];
		printf("������Ҫ������ַ���:\n"); 
		gets(str);//�����ַ��� 
																//getchar();
																//printf("%s\n",str);
		printf("�ַ�������Ϊ��%d\n",strlen(str));
		
		tree tr[100];
		int effective=0;
		effective=initializeTree(tr,str,strlen(str));	//��ʼ������������1.ɨ��ÿһ���ַ��ó�Ƶ�ʣ�Ȩֵ=Ƶ�� 2.���乹��Ϊ�������� 
		printf("Ҷ�ӽڵ������%d\n",effective);
		
		printf("����Ƶ������õ���Ҷ�ӽڵ㣺\n"); 
		for(int i=0;i<effective;i++)
		{
			printf("%c %d %d\n",tr[i].data,tr[i].mean,tr[i].weight);
		}
		
		
		
		int real=2*effective-1;
		getTree(tr,real,effective);
//		printf("---------\n");
//		printf("��������������ɺ����еĽڵ㣺\n"); 
//		for(int i=0;i<real;i++)
//		{
//			printf("%c %d %d\n",tr[i].data,tr[i].mean,tr[i].weight);
//		}
		
		char ch[100];
		encode(&tr[real-1],ch);			//!!!���ڵ�Ҫ���������֮һ���� ��ô�Զ�ȷ�����ڵ��λ�ã� ���ڵ�λ�þ������ѽ������ 
		
		printf("---------\n");
		printf("Ҷ�ӽڵ����Ϊ��%d\n",hfmCount);
		printf("���ַ��Ĺ���������Ϊ��\n"); 
		for(int i=0;i<hfmCount;i++)
		{
			printf("%c:",hfmTable[i].data);
			for(int j=0;j<hfmTable[i].num;j++)
			{
				printf("%c",hfmTable[i].code[j]);
			}
			printf("\n");
		}
		
		char input[100];
		for(int i=0;i<100;i++)
		{
			input[i]='\0';
		}
	while(1)
	{
		
		printf("������Ҫ����Ĺ���������:\n"); 
		gets(input);
		decode(&tr[real-1],input);
		printf("---------\n");
		printf("---------\n");
		
	}
	
	
	return 0;
}
