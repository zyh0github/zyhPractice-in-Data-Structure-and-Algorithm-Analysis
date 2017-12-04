#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;



//�������ڵ�ṹ 
struct tree
{
	char data='\0';//����ַ���������  Ҫ��ʼ��Ϊ'\0' 
	bool mean=0;//����Ƿ���Ҷ�ӽڵ�   Ҫ��ʼ��Ϊ0 
	int weight=0;//Ȩֵ					Ҫ��ʼ��Ϊ0 
	struct tree *left,*right;//ָ��tree�ṹ�ڵ������ָ�� 
};

void getTree(tree tr[],int total,int effective)//����������� 
{
	if(2*effective-1 != total)//��Ϊ���������Ƕ�����ȫ�����������ܽ����=2*Ҷ�ӽڵ���-1�Ĺ��� 
	{
		printf("error\n");
		return ;
	 } 
	int loopStart=0; //ѭ����ʼ���±� 
	while(effective != total)//����Ч����==ʵ�ʸ���ʱ������ɣ� 
	{
		//�����������нڵ� 
		for(int i=loopStart;i<effective;i++)
		{
			//ÿ��ѭ��ȡ������Сֵ������������Сֵ������tr�����е�ǰѭ����ʼ��λ
			if(tr[i].weight<tr[loopStart].weight)//����if��ġ�;��!!! 
			{
				//����С��tr[i]����ѭ����ʼ�����ṹ����ڴ濽�����ƣ�����ָ����ǳ�㸴�� 
				tree temp;
				temp = tr[i];
				tr[i] = tr[loopStart];
				tr[loopStart] = temp;
			 } 
			 
//			 for(int i=0;i<9;i++)
//			{
//				printf("%c %d %d\n",tr[i].data,tr[i].mean,tr[i].weight);
//			}
		}

		for(int i=loopStart+1;i<effective;i++)
		{
			if(tr[i].weight<tr[loopStart+1].weight)
			{
				//�ѵڶ�С�ķ���ѭ����ʼ+1�����ṹ����ڴ濽�����ƣ�����ָ����ǳ�㸴�� 
				tree temp;
				temp = tr[i];
				tr[i] = tr[loopStart+1];
				tr[loopStart+1] = temp;
			 }  
		}

		//����Ϊͨ����Сֵ���������
		
		tr[effective].mean = false;
		tr[effective].weight = tr[loopStart].weight + tr[loopStart+1].weight;
		tr[effective].left = &tr[loopStart];
		tr[effective].right = &tr[loopStart+1];
//		//������������Ч������� 
		effective++;
		loopStart=loopStart+2;
	}
}


struct hfm
{
	char data;//һ��Ҷ�ӽڵ��Դ����ַ� 
	char code[11];//code�����������ַ���Ӧ�ı��� 
	int num=0;//����ַ���Ӧ����ĳ��� 
}hfmTable[100];//������һ����100�������ṹ��hfmTable����� 



int hfmCount=0;//����ȫ�ֱ���ʱ��ע�����ķ�Χ����ȫ������ 
int numcode=0;
void encode(tree *tr,char ch[])//tr�Ǹ��ڵ㣬�Ӹ��ڵ㿪ʼ���� 
{
	
	if(tr==NULL)
	{
		return ;
	 } 
	else
	{
		if(tr->mean==false)//����Ҷ�ӽڵ�
		{
			ch[numcode] = '0';
			numcode++;			//ÿһ��numcodeָ�����δ�������ַ��ĵط� 
			encode(tr->left,ch);//��ڵ����Ϊ��0��
			
			ch[numcode] = '1';
			numcode++;
			encode(tr->right,ch);//�ҽڵ����Ϊ��1��
		}
		
		if(tr->mean==true)//��Ҷ�ӽڵ�
		{
			hfmTable[hfmCount].data = tr->data;//�ڱ��һ���ṹ��data�Ƕ�Ӧ���ַ���num�Ǳ��볤�� 
			hfmTable[hfmCount].num = numcode;
			int j=0;
			while(j < numcode)//������д��ṹ��code���� 
			{
				hfmTable[hfmCount].code[j] = ch[j];
				j++;
			}//�������ӳ�����hfmTable�� 
			hfmCount++;//Ҳָ�����δ�������ĵط� 
		}
		numcode--;//������������ʱ������Ҫ-- 
	}
}

int  initializeTree(tree tr[],char str[],int length)
{
	//��ʼ���������������������������飬�������ַ����飬�ַ�������
	
	int weightArr[length];
	for(int i=0;i<length;i++)//ʹ������֮ǰ��ʼ���Ƿǳ���Ҫ�ģ��� 
	{
		weightArr[i]=0;
	}
	int nnew=0;//�µ��ַ�
	int  subscript=0;//�±� 
	while(subscript!=length)
	{
		int flag=0;
		for(int i=0;i<subscript;i++)
		{
			if(str[i]==str[subscript])
			{
				flag=1;
				subscript++;
				break;
			}
		}
		if(flag==0)
		{
			
			for(int i=subscript;i<length;i++)
			{
				if(str[i]==str[subscript])
				{
					weightArr[nnew]++;
				}
			}
			tr[nnew].data=str[subscript];
			tr[nnew].weight=weightArr[nnew];
			tr[nnew].mean=true;
			nnew++;
			subscript++;
		}
		
	}
	return nnew;//����Ҷ�ӽڵ���� 
	 
}




//void decode(tree tr[],char input[])
//{
//	
//}


void decode(tree *tr,char *hfm)
{
	tree *p=tr;//���ڵ㱣����p 
	printf("�������:\n"); 
	while(*hfm!=NULL)
	{
		if(*hfm=='0')
		{
			tr=tr->left;
			if(tr->mean==1)
			{
				printf("%c",tr->data);
				tr=p;
			}
			hfm++;
			continue;
		}
		if(*hfm=='1')
		{
			tr=tr->right;
			if(tr->mean==1)
			{
				printf("%c",tr->data);
				tr=p;
			}
			hfm++;
			continue;
		}
		printf("����ʶ��ñ��룺%c\n",*hfm);
		return ;
	}
	printf("\n");
	tr=p;
}
