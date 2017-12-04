#include <iostream>
#include <string.h>
#include <stdio.h>//不包含printf和scanf函数 ，编译器也不提醒 
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
		printf("请输入要编码的字符串:\n"); 
		gets(str);//输入字符串 
																//getchar();
																//printf("%s\n",str);
		printf("字符串长度为：%d\n",strlen(str));
		
		tree tr[100];
		int effective=0;
		effective=initializeTree(tr,str,strlen(str));	//初始化哈夫曼树，1.扫描每一个字符得出频率，权值=频率 2.将其构造为哈夫曼树 
		printf("叶子节点个数：%d\n",effective);
		
		printf("经过频度整理得到的叶子节点：\n"); 
		for(int i=0;i<effective;i++)
		{
			printf("%c %d %d\n",tr[i].data,tr[i].mean,tr[i].weight);
		}
		
		
		
		int real=2*effective-1;
		getTree(tr,real,effective);
//		printf("---------\n");
//		printf("哈夫曼树构造完成后所有的节点：\n"); 
//		for(int i=0;i<real;i++)
//		{
//			printf("%c %d %d\n",tr[i].data,tr[i].mean,tr[i].weight);
//		}
		
		char ch[100];
		encode(&tr[real-1],ch);			//!!!存在的要解决的问题之一就是 怎么自动确定根节点的位置？ 根节点位置就在最后呀！！！ 
		
		printf("---------\n");
		printf("叶子节点个数为：%d\n",hfmCount);
		printf("各字符的哈夫曼编码为：\n"); 
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
		
		printf("请输入要解码的哈夫曼编码:\n"); 
		gets(input);
		decode(&tr[real-1],input);
		printf("---------\n");
		printf("---------\n");
		
	}
	
	
	return 0;
}
