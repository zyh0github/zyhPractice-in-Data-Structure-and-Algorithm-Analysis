#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;



//二叉树节点结构 
struct tree
{
	char data='\0';//存放字符的数据域  要初始化为'\0' 
	bool mean=0;//标记是否是叶子节点   要初始化为0 
	int weight=0;//权值					要初始化为0 
	struct tree *left,*right;//指向tree结构节点的两个指针 
};

void getTree(tree tr[],int total,int effective)//构造哈夫曼树 
{
	if(2*effective-1 != total)//因为哈夫曼树是二叉完全数，所以有总结点数=2*叶子节点数-1的规律 
	{
		printf("error\n");
		return ;
	 } 
	int loopStart=0; //循环开始的下标 
	while(effective != total)//当有效个数==实际个数时构造完成！ 
	{
		//来按升序排列节点 
		for(int i=loopStart;i<effective;i++)
		{
			//每次循环取两个最小值，并将两个最小值放置在tr数组中当前循环起始两位
			if(tr[i].weight<tr[loopStart].weight)//警惕if后的“;”!!! 
			{
				//把最小的tr[i]放在循环开始处，结构体的内存拷贝复制，但是指针是浅层复制 
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
				//把第二小的放在循环开始+1处，结构体的内存拷贝复制，但是指针是浅层复制 
				tree temp;
				temp = tr[i];
				tr[i] = tr[loopStart+1];
				tr[loopStart+1] = temp;
			 }  
		}

		//以下为通过最小值构造的新树
		
		tr[effective].mean = false;
		tr[effective].weight = tr[loopStart].weight + tr[loopStart+1].weight;
		tr[effective].left = &tr[loopStart];
		tr[effective].right = &tr[loopStart+1];
//		//新树插入在有效数据最后 
		effective++;
		loopStart=loopStart+2;
	}
}


struct hfm
{
	char data;//一个叶子节点自带的字符 
	char code[11];//code数组里放这个字符对应的编码 
	int num=0;//这个字符对应编码的长度 
}hfmTable[100];//先生成一个有100个这样结构的hfmTable来存放 



int hfmCount=0;//定义全局变量时，注意它的范围会是全部程序！ 
int numcode=0;
void encode(tree *tr,char ch[])//tr是根节点，从根节点开始往下 
{
	
	if(tr==NULL)
	{
		return ;
	 } 
	else
	{
		if(tr->mean==false)//不是叶子节点
		{
			ch[numcode] = '0';
			numcode++;			//每一次numcode指向的是未被决定字符的地方 
			encode(tr->left,ch);//左节点编码为‘0’
			
			ch[numcode] = '1';
			numcode++;
			encode(tr->right,ch);//右节点编码为‘1’
		}
		
		if(tr->mean==true)//是叶子节点
		{
			hfmTable[hfmCount].data = tr->data;//在表里，一个结构的data是对应的字符，num是编码长度 
			hfmTable[hfmCount].num = numcode;
			int j=0;
			while(j < numcode)//将编码写入结构的code数组 
			{
				hfmTable[hfmCount].code[j] = ch[j];
				j++;
			}//保存编码映射表在hfmTable中 
			hfmCount++;//也指向的是未被决定的地方 
		}
		numcode--;//函数结束调用时返回来要-- 
	}
}

int  initializeTree(tree tr[],char str[],int length)
{
	//初始化哈夫曼树。参数：哈夫曼树组，待编码字符串组，字符串长度
	
	int weightArr[length];
	for(int i=0;i<length;i++)//使用数组之前初始化是非常重要的！！ 
	{
		weightArr[i]=0;
	}
	int nnew=0;//新的字符
	int  subscript=0;//下标 
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
	return nnew;//返回叶子节点个数 
	 
}




//void decode(tree tr[],char input[])
//{
//	
//}


void decode(tree *tr,char *hfm)
{
	tree *p=tr;//根节点保存在p 
	printf("解码完成:\n"); 
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
		printf("不能识别该编码：%c\n",*hfm);
		return ;
	}
	printf("\n");
	tr=p;
}
