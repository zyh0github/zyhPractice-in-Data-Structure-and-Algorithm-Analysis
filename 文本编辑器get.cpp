echo "# Practice-in-Data-Structure-and-Algorithm-Analysis" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/zyh0github/Practice-in-Data-Structure-and-Algorithm-Analysis.git
git push -u origin master



#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/*
//#include"Struct.h"
1、具有图形菜单界面；
2、 查找、替换（等长、不等长）、插入（插串、文本块的插入）、
块移动（行块、列块的移动）、删除 
3、可正确存盘、取盘
4、正确显示总行数
*/
 
//字符节点
struct Node
{
	char ch;
	Node *next;//定义一个指针，指向另一个是Node类型的结构体对象
 };
 
//行节点
struct Row
{
	Node *line;
	Row *next;
 };
 
//创建一个Node对象
Node* createNode(char ch)
{
	Node *p=new Node;//Node类型的指针 
	p->ch=ch;
	p->next=NULL;
	
	return p;
 } 
 
 //创建一个Row对象
 Row* createRow(Node *line)
 {
 	Row *p=new Row;
 	p->line=line;
 	p->next=NULL;
 	
 	return p;
  } 
  
  //定位到某一行的第index号指针处
Node* locate(Node *line,int index)
{
  	Node *p=line;
  	int i=-1;
  	while(p!=NULL&&i<index)
  	{
  		p=p->next;
  		i++;
	  }
	  
	  return p;
} 
   
Row* locate(Row *list,int index)
{
	Row *p=list;
	int i=-1;
	while(p!=NULL&&i<index)
	{
		p=p->next;
		i++;
	}
	
	return p;
 } 
 
 //插入节点
 bool insert(Node *list,int index,char c)
 {
 	Node *p=locate(list,index-1);
 	if(p)
 	{
 		Node *node=createNode(c);
 		node->next=p->next;
 		p->next=node;
 		
 		return true;
	 }
	 return false;
  } 
bool insert(Row *list,int index,Node *line)
{
	Row *p=locate(list,index-1);
	if(p)
	{
		Row *row=createRow(line);
		row->next=p->next;
		p->next=row;
		
		return true;
	}
	return false;
}

//删除节点
bool remove(Node *list,int index)
{
	Node *p=locate(list,index-1);
	Node *q=NULL;
	if(p&&q->next)
	{
		q=p->next;
		p->next=q->next;
		delete q;
		
		return true;
	}
	return false;
 } 
 
//清空链表
void clear(Node *line)
{
	Node *p=line->next;
	Node *q;
	while(p)
	{
		q=p->next;
		delete p;
		p=q;
	}
 } 
 
bool remove(Row *list,int index)
{
	Row *p=locate(list,index-1);
	Row *q=NULL;
	if(p&&p->next)
	{
		q=p->next;
		p->next=q->next;
		
		clear(q->line);//清空字符链表
		delete q->line;//删除字符链表表头
		delete q;
		
		return true; 
	}
	return false;
}

void clear(Row *text)
{
	Row *p=text->next;
	Row *q;
	while(p)
	{
		q=p->next;
		clear(p->line);
		
		delete p->line;//删除字符链表表头
		
		delete p;
		p=q; 
	}
}

void Line(int i)
{
	if(i==1)
	{
		return;//"--------------------------------" 
	}
	else if(i==2)
	{
		cout<<"==============================="<<endl;
	}
}

int YesOrNo()
{
	char c;
	cin>>c;
	if(c=='Y'||c=='y')
	{
		return 1;
	}
	else if(c=='N'||c=='n')
	{
		return 0;
	}
	return -1;
}

//主菜单
void Menu()
{
	cout<<"***********************************"<<endl;
	cout<<"**         简易文本编辑器        **"<<endl;
	cout<<"***********************************"<<endl;
	cout<<"\tr.读取文件到缓冲区"<<endl;
	cout<<"\tn.新建文件"<<endl;
	cout<<"\tw.内容写入文件并保存"<<endl;
	cout<<"\ti.插入字符串"<<endl;
	cout<<"\td.删除字符串"<<endl;
	cout<<"\tf.查找字符串，并返回行号列号，可选择是否替换"<<endl;
	cout<<"\tg.当前行移到用户指定行号"<<endl;
	cout<<"\tc.当前列移到用户指定列号"<<endl;
	cout<<"\tv.显示缓冲区全部内容"<<endl;
	cout<<"\tq.退出编辑器，立即结束"<<endl;
	cout<<"\th.帮助"<<endl;
	Line(1);
 } 
 
//输出当前文本
void PrintText(Row *text)
{
	//cout<<endl;
	Line(2);
	cout<<"当前文本为："<<endl;
	Line(1);
	
	Row *p=text->next;
	Node *q;
	int i=0;
	while(p!=NULL)
	{
		i++;
		cout<<"行"<<i<<" ";
		q=p->line->next;
		while(q!=NULL)
		{
			cout<<q->ch;
			q=q->next;
		}
		cout<<endl;
		p=p->next;
	}
	Line(1);
	cout<<"总共 "<<i<<" 行"<<endl;
	Line(2);
 }
  
//打开文件
bool OpenFile(char *fileName,Row *text)
{
	ifstream file(fileName,ios::in);
	if(!file)
	{
		cout<<"文件读取失败！"<<endl;
		
		return false;
	}
	char c;
	Row *rp;
	rp=text;
	while(!file.eof())
	{
		Node *line=new Node;
		line->next=NULL;
		Node *p=line;
		file.get(c);
		while(c!=10&&!file.eof())
		{
			Node *q=createNode(c);
			q->next=NULL;
			p->next=q;
			p=p->next;
			file.get(c);
		}
		if(!file.eof())
		{
			Row *rq=createRow(line);
			rp->next=rq;
			rp=rp->next;
		}
	}
	file.close();
	cout<<"文件读取完成！"<<endl;
	return true;
 } 
 
//创建文件
bool CreateFile(const char *fileName,Row *text)
{
	ofstream file(fileName);
	if(!file)
	{
		cout<<"文件创建失败！"<<endl;
		
		return false;
	}
	file.close();
	cout<<"文件创建成功！"<<endl;
	return true;
 } 
 
//保存
bool SaveFile(const char *fileName,Row *text)
{
	ofstream file(fileName);
	if(!file)
	{
		cout<<"文件保存失败"<<endl;
		
		return false;
	}
	
	Row *p=text->next;
	Node *q=NULL;
	while(p!=NULL)
	{
		q=p->line->next;
		while(q!=NULL)
		{
			file<<q->ch;
			q=q->next;
		}
		file<<endl;
		p=p->next;
	}
	file.close();
	
	cout<<"文件保存成功！"<<endl;
	return true;
 } 
 
//插入字符串
void InsertStr(Row *text,int row,int col)
{
	int i=-1,j=-1;
	Row *rp,*rq;
	Node *np,*nq;
	rp=text;
	while(rp->next&&i<row)
	{
		rp=rp->next;
		i++; 
	}
	while(i<row)
	{
		nq=createNode(' ');//定义一个新行链表
		rq=createRow(nq);
		rp->next=rq;
		rp=rp->next;
		i++; 
	}
	np=rp->line;
	while(np->next&&j<col-1)
	{
		np=np->next;
		j++;
	}
	while(j<col-1)
	{
		nq=createNode(' ');
		np->next=nq;
		np=np->next;
		j++;
	}
	cin.get();
	string s;
	getline(cin,s);
	for(int k=0;k<s.length();k++)
	{
		nq=createNode(s[k]);
		nq->next=np->next;
		np->next=nq;
		np=np->next;
	}
 } 
//行移动
bool MoveRow(Row *text,int row,int poz)
{
	if(row==poz)
	{
		return true;
	}
	Row *p=locate(text,row-1);
	Row *t=locate(text,poz-1);
	Row *q;
	if(p&&p->next&&t)
	{
		q=p->next;
		p->next=q->next;
		
		q->next=t->next;
		t->next=q;
		return true;
	}
	return false;
 } 

//列移动
void MoveCol(Row *text,int col,int poz)
{
	if(col==poz)
		return ;
	Row *rp=text->next;
	while(rp)
	{
		Node *np=locate(rp->line,col-1);
		Node *nt=locate(rp->line,poz-1);
		Node *nq;
		if(np&&np->next&&nt)
		{
			nq=np->next;
			np->next=nq->next;
			
			nq->next=nt->next;
			nt->next=nq;
		}
		rp=rp->next;
	}
 } 
 
//查找替换
void FindStr(Row *text)
{
	string str,rep;
	int pos,k=0,row=1,col=0;
	cout<<"请输入你要查找的字符串："<<endl;
	cin>>str;
	Row *p=text->next;
	while(p)
	{
		string line;
		Node *nq=p->line->next;
		while(nq)
		{
			line.append(1,nq->ch);
			nq=nq->next;
		}
		pos=line.find(str.c_str(),0);
		while(pos!=string::npos)
		{
			col=pos;
			k++;
			cout<<str<<"第"<<k<<"次出现的位置是:第"<<row<<"行，第"<<col<<"列"<<endl;
			cout<<"是否替换？（Y/N）";
			int yon=YesOrNo();
			while(yon==-1)
			{
				cout<<"是否替换？（Y/N）";
				yon=YesOrNo();
			 } 
			if(yon==1)
			{
				cout<<"将"<<str<<" 替换为：";
				cin>>rep;
				int j;
				for(j=0;j<str.length();j++)
				{
					remove(p->line,col);
				}
				for(j=0;j<rep.length();j++)
				{
					insert(p->line,col+j,rep[j]);
				}
				cout<<"替换成功！"<<endl;
			}
			pos=line.find(str.c_str(),col+str.length());
		}
		row++;
		p=p->next;
	}
	if(k==0)
	{
		cout<<"当前文本中找不到该字符串！"<<endl;
	}
 } 
 
 void DelStr(Row *text,int row,int col,int len)
 {
 	Row *rp=locate(text,row);
 	if(rp==NULL)
 	{
 		cout<<"无法删除，因为该位置没有字符串！"<<endl;
		 return; 
	 }
	 Node *np=locate(rp->line,col-1);
	 if(np==NULL)
	 {
	 	cout<<"无法删除，因为该位置没有字符串！"<<endl;
	 	return; 
	 }
	 Node *nq=np->next;
	 string s;
	 int k=0;
	 
	 while(nq&&k<len)
	 {
	 	s.append(1,nq->ch);
	 	np->next=nq->next;
	 	delete nq;
	 	nq=np->next;
	 	k++;
	  } 
	cout<<"成功删除字符串 "<<s<<endl;
 }
 
 class Help{
	public:
		Help()
		{
			b = 1;
		};
		void view()
		{
			cout<<"h：显示帮助"<<endl;
			cout<<"n：新建文件"<<endl;
			cout<<"r：读取文件到缓冲区"<<endl;
			cout<<"v：打印缓冲区全部内容"<<endl;
			cout<<"w：将缓冲区的内容写入文件"<<endl;
			cout<<"q：退出编辑器，立即结束"<<endl;
			cout<<endl;
//			cout<<"n：当前行移到下一行"<<endl;
//			cout<<"p：当前行移到上一行"<<endl;
//			cout<<"b：当前行移到第一行"<<endl;
//			cout<<"e：当前行移到最末行"<<endl;
			cout<<"g：当前行移到用户指定行号"<<endl;
			cout<<"c：当前列移到用户指定列号"<<endl;
			cout<<endl;
			cout<<"i：插入字符串在某一行某一列的后面"<<endl;
			cout<<"d：删除某一行，并将指针移到下一行"<<endl;
			cout<<"f：从第一行开始查找包含用户请求的字符串的第一行，并返回行号"<<endl;
			
		//	cout<<"return：返回到上一步"<<endl;
		}
	private:
		int b = 0;	
};
 
 int main()
 {
 	bool flag=false;
 	int row,col,poz;
 	char sel;
 	Row *text=new Row;
 	text->next=NULL;
 	string fileName;
 	
 	Menu();
 	
 	cout<<"请选择操作：";
 	cin>>sel;
 	Help object_h = Help();
 	while(sel!='q')//退出 
 	{
 		switch(sel)
 		{
 			case 'r'://打开文件
				cout<<"请输入要打开的文件路径（例如 E:\\1.txt）：";
				cin>>fileName;
				flag=OpenFile((char *)fileName.c_str(),text);
				if(flag)
				{
					PrintText(text);
				} 
				break;
			case 'n'://新建文件 
				if(flag)
				{
					cout<<"要保存前一个文件吗？（Y/N）";
					int yon=YesOrNo();
					while(yon==-1)
					{
						cout<<"要保存前一个文件吗？(Y/N)";
						yon=YesOrNo(); 
					}
					if(yon==1)
					{
						SaveFile((char *)fileName.c_str(),text);
					}
					flag=false;
				}
				clear(text);
				cout<<"请输入要新建的文件路径（例如 E:\\1.txt）：";
				cin>>fileName;
				flag=CreateFile((char *)fileName.c_str(),text);
				if(flag)
				{
					PrintText(text);
				}
				break;
			case 'w'://保存文件
				 if(flag)
				 {
				 	SaveFile((char *)fileName.c_str(),text);
				 	flag=false;
				 }
				 else
				 {
				 	cout<<"请输入文件路径：";
				 	cin>>fileName;
				 	flag=SaveFile((char *)fileName.c_str(),text);
				 }
				 break;
			case 'i'://插入字符串
				cout<<"请选择要插入的位置（第x行第y个字符）之后:"<<endl;
				cout<<"行：";
				cin>>row;
				cout<<"列：";
				cin>>col;
				cout<<"请输入要插入的字符串：";
				row--;
				col--;
				InsertStr(text,row,col);
				cout<<"插入成功！"<<endl;
				PrintText(text);
				break; 
			case 'd'://删除字符串
				int len;
				cout<<"请选择要删除的字符串的开始位置（第x行第y个字符）:"<<endl;
				cout<<"行：";
				cin>>row;
				cout<<"列：";
				cin>>col;
				cout<<"请输入要删除的字符串的长度：";
				cin>>len;
				row--;
				col--;
				DelStr(text,row,col,len);
				PrintText(text);
				break;
			case 'f'://查找替换字符串
				FindStr(text);
				PrintText(text);
				break;
			case 'g'://行移动
				cout<<"请选择你要移动的行：";
				cin>>row;
				cout<<"你想要将第"<<row<<"行移动到第几行之前？>:";
				cin>>poz;
				row--;
				poz--;
				if(MoveRow(text,row,poz))
				{
					cout<<"移动完成！"<<endl;
				}
				else
				{
					cout<<"无法移动！"<<endl;
				}
				PrintText(text);
				break;
			case 'c'://列移动
				cout<<"请选择你要移动的列：";
				cin>>col;
				cout<<"你想要将第"<<col<<"列移动到第几列之前？>:";
				cin>>poz;
				col--;
				poz--;
				MoveCol(text,col,poz);
				cout<<"移动完成！"<<endl;
				PrintText(text);
				break;
			case 'v'://显示文本
				PrintText(text);
				break;
			case 'h':
				
				object_h.view();
				break; 
			default:
				break; 
		 }
		 cout<<"请选择操作：";
		 cin>>sel;
	 }
	 if(flag)
	 {
	 	cout<<"要保存前一个文件吗？（Y/N）";
		 int yon=YesOrNo();
		 while(yon==-1)
		 {
		 	cout<<"要保存前一个文件吗？(Y/N)";
		 	yon=YesOrNo();
		  } 
		if(yon==1)
		{
			SaveFile((char *)fileName.c_str(),text);
		}
		flag=false;
	 }
	 clear(text);
	 delete text;
	 return 0;
 }
