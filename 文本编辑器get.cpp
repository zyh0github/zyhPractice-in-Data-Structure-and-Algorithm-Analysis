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
1������ͼ�β˵����棻
2�� ���ҡ��滻���ȳ������ȳ��������루�崮���ı���Ĳ��룩��
���ƶ����п顢�п���ƶ�����ɾ�� 
3������ȷ���̡�ȡ��
4����ȷ��ʾ������
*/
 
//�ַ��ڵ�
struct Node
{
	char ch;
	Node *next;//����һ��ָ�룬ָ����һ����Node���͵Ľṹ�����
 };
 
//�нڵ�
struct Row
{
	Node *line;
	Row *next;
 };
 
//����һ��Node����
Node* createNode(char ch)
{
	Node *p=new Node;//Node���͵�ָ�� 
	p->ch=ch;
	p->next=NULL;
	
	return p;
 } 
 
 //����һ��Row����
 Row* createRow(Node *line)
 {
 	Row *p=new Row;
 	p->line=line;
 	p->next=NULL;
 	
 	return p;
  } 
  
  //��λ��ĳһ�еĵ�index��ָ�봦
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
 
 //����ڵ�
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

//ɾ���ڵ�
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
 
//�������
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
		
		clear(q->line);//����ַ�����
		delete q->line;//ɾ���ַ������ͷ
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
		
		delete p->line;//ɾ���ַ������ͷ
		
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

//���˵�
void Menu()
{
	cout<<"***********************************"<<endl;
	cout<<"**         �����ı��༭��        **"<<endl;
	cout<<"***********************************"<<endl;
	cout<<"\tr.��ȡ�ļ���������"<<endl;
	cout<<"\tn.�½��ļ�"<<endl;
	cout<<"\tw.����д���ļ�������"<<endl;
	cout<<"\ti.�����ַ���"<<endl;
	cout<<"\td.ɾ���ַ���"<<endl;
	cout<<"\tf.�����ַ������������к��кţ���ѡ���Ƿ��滻"<<endl;
	cout<<"\tg.��ǰ���Ƶ��û�ָ���к�"<<endl;
	cout<<"\tc.��ǰ���Ƶ��û�ָ���к�"<<endl;
	cout<<"\tv.��ʾ������ȫ������"<<endl;
	cout<<"\tq.�˳��༭������������"<<endl;
	cout<<"\th.����"<<endl;
	Line(1);
 } 
 
//�����ǰ�ı�
void PrintText(Row *text)
{
	//cout<<endl;
	Line(2);
	cout<<"��ǰ�ı�Ϊ��"<<endl;
	Line(1);
	
	Row *p=text->next;
	Node *q;
	int i=0;
	while(p!=NULL)
	{
		i++;
		cout<<"��"<<i<<" ";
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
	cout<<"�ܹ� "<<i<<" ��"<<endl;
	Line(2);
 }
  
//���ļ�
bool OpenFile(char *fileName,Row *text)
{
	ifstream file(fileName,ios::in);
	if(!file)
	{
		cout<<"�ļ���ȡʧ�ܣ�"<<endl;
		
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
	cout<<"�ļ���ȡ��ɣ�"<<endl;
	return true;
 } 
 
//�����ļ�
bool CreateFile(const char *fileName,Row *text)
{
	ofstream file(fileName);
	if(!file)
	{
		cout<<"�ļ�����ʧ�ܣ�"<<endl;
		
		return false;
	}
	file.close();
	cout<<"�ļ������ɹ���"<<endl;
	return true;
 } 
 
//����
bool SaveFile(const char *fileName,Row *text)
{
	ofstream file(fileName);
	if(!file)
	{
		cout<<"�ļ�����ʧ��"<<endl;
		
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
	
	cout<<"�ļ�����ɹ���"<<endl;
	return true;
 } 
 
//�����ַ���
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
		nq=createNode(' ');//����һ����������
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
//���ƶ�
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

//���ƶ�
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
 
//�����滻
void FindStr(Row *text)
{
	string str,rep;
	int pos,k=0,row=1,col=0;
	cout<<"��������Ҫ���ҵ��ַ�����"<<endl;
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
			cout<<str<<"��"<<k<<"�γ��ֵ�λ����:��"<<row<<"�У���"<<col<<"��"<<endl;
			cout<<"�Ƿ��滻����Y/N��";
			int yon=YesOrNo();
			while(yon==-1)
			{
				cout<<"�Ƿ��滻����Y/N��";
				yon=YesOrNo();
			 } 
			if(yon==1)
			{
				cout<<"��"<<str<<" �滻Ϊ��";
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
				cout<<"�滻�ɹ���"<<endl;
			}
			pos=line.find(str.c_str(),col+str.length());
		}
		row++;
		p=p->next;
	}
	if(k==0)
	{
		cout<<"��ǰ�ı����Ҳ������ַ�����"<<endl;
	}
 } 
 
 void DelStr(Row *text,int row,int col,int len)
 {
 	Row *rp=locate(text,row);
 	if(rp==NULL)
 	{
 		cout<<"�޷�ɾ������Ϊ��λ��û���ַ�����"<<endl;
		 return; 
	 }
	 Node *np=locate(rp->line,col-1);
	 if(np==NULL)
	 {
	 	cout<<"�޷�ɾ������Ϊ��λ��û���ַ�����"<<endl;
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
	cout<<"�ɹ�ɾ���ַ��� "<<s<<endl;
 }
 
 class Help{
	public:
		Help()
		{
			b = 1;
		};
		void view()
		{
			cout<<"h����ʾ����"<<endl;
			cout<<"n���½��ļ�"<<endl;
			cout<<"r����ȡ�ļ���������"<<endl;
			cout<<"v����ӡ������ȫ������"<<endl;
			cout<<"w����������������д���ļ�"<<endl;
			cout<<"q���˳��༭������������"<<endl;
			cout<<endl;
//			cout<<"n����ǰ���Ƶ���һ��"<<endl;
//			cout<<"p����ǰ���Ƶ���һ��"<<endl;
//			cout<<"b����ǰ���Ƶ���һ��"<<endl;
//			cout<<"e����ǰ���Ƶ���ĩ��"<<endl;
			cout<<"g����ǰ���Ƶ��û�ָ���к�"<<endl;
			cout<<"c����ǰ���Ƶ��û�ָ���к�"<<endl;
			cout<<endl;
			cout<<"i�������ַ�����ĳһ��ĳһ�еĺ���"<<endl;
			cout<<"d��ɾ��ĳһ�У�����ָ���Ƶ���һ��"<<endl;
			cout<<"f���ӵ�һ�п�ʼ���Ұ����û�������ַ����ĵ�һ�У��������к�"<<endl;
			
		//	cout<<"return�����ص���һ��"<<endl;
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
 	
 	cout<<"��ѡ�������";
 	cin>>sel;
 	Help object_h = Help();
 	while(sel!='q')//�˳� 
 	{
 		switch(sel)
 		{
 			case 'r'://���ļ�
				cout<<"������Ҫ�򿪵��ļ�·�������� E:\\1.txt����";
				cin>>fileName;
				flag=OpenFile((char *)fileName.c_str(),text);
				if(flag)
				{
					PrintText(text);
				} 
				break;
			case 'n'://�½��ļ� 
				if(flag)
				{
					cout<<"Ҫ����ǰһ���ļ��𣿣�Y/N��";
					int yon=YesOrNo();
					while(yon==-1)
					{
						cout<<"Ҫ����ǰһ���ļ���(Y/N)";
						yon=YesOrNo(); 
					}
					if(yon==1)
					{
						SaveFile((char *)fileName.c_str(),text);
					}
					flag=false;
				}
				clear(text);
				cout<<"������Ҫ�½����ļ�·�������� E:\\1.txt����";
				cin>>fileName;
				flag=CreateFile((char *)fileName.c_str(),text);
				if(flag)
				{
					PrintText(text);
				}
				break;
			case 'w'://�����ļ�
				 if(flag)
				 {
				 	SaveFile((char *)fileName.c_str(),text);
				 	flag=false;
				 }
				 else
				 {
				 	cout<<"�������ļ�·����";
				 	cin>>fileName;
				 	flag=SaveFile((char *)fileName.c_str(),text);
				 }
				 break;
			case 'i'://�����ַ���
				cout<<"��ѡ��Ҫ�����λ�ã���x�е�y���ַ���֮��:"<<endl;
				cout<<"�У�";
				cin>>row;
				cout<<"�У�";
				cin>>col;
				cout<<"������Ҫ������ַ�����";
				row--;
				col--;
				InsertStr(text,row,col);
				cout<<"����ɹ���"<<endl;
				PrintText(text);
				break; 
			case 'd'://ɾ���ַ���
				int len;
				cout<<"��ѡ��Ҫɾ�����ַ����Ŀ�ʼλ�ã���x�е�y���ַ���:"<<endl;
				cout<<"�У�";
				cin>>row;
				cout<<"�У�";
				cin>>col;
				cout<<"������Ҫɾ�����ַ����ĳ��ȣ�";
				cin>>len;
				row--;
				col--;
				DelStr(text,row,col,len);
				PrintText(text);
				break;
			case 'f'://�����滻�ַ���
				FindStr(text);
				PrintText(text);
				break;
			case 'g'://���ƶ�
				cout<<"��ѡ����Ҫ�ƶ����У�";
				cin>>row;
				cout<<"����Ҫ����"<<row<<"���ƶ����ڼ���֮ǰ��>:";
				cin>>poz;
				row--;
				poz--;
				if(MoveRow(text,row,poz))
				{
					cout<<"�ƶ���ɣ�"<<endl;
				}
				else
				{
					cout<<"�޷��ƶ���"<<endl;
				}
				PrintText(text);
				break;
			case 'c'://���ƶ�
				cout<<"��ѡ����Ҫ�ƶ����У�";
				cin>>col;
				cout<<"����Ҫ����"<<col<<"���ƶ����ڼ���֮ǰ��>:";
				cin>>poz;
				col--;
				poz--;
				MoveCol(text,col,poz);
				cout<<"�ƶ���ɣ�"<<endl;
				PrintText(text);
				break;
			case 'v'://��ʾ�ı�
				PrintText(text);
				break;
			case 'h':
				
				object_h.view();
				break; 
			default:
				break; 
		 }
		 cout<<"��ѡ�������";
		 cin>>sel;
	 }
	 if(flag)
	 {
	 	cout<<"Ҫ����ǰһ���ļ��𣿣�Y/N��";
		 int yon=YesOrNo();
		 while(yon==-1)
		 {
		 	cout<<"Ҫ����ǰһ���ļ���(Y/N)";
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
