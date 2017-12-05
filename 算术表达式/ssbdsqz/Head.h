#include<iostream>

#define SUCCESS 1
#define UNDER_FLOW -1
#define OVER_FLOW -2

using namespace std;

int judge(char x)
{
	switch(x)
		{
			case'+':case'-':
			return 1;
			break;
			
			case'*':case'/':
			return 3;
			break;
			
			case'(':
			return 2;
			break;
			
			case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':
			return 10;
			break;
			
			default: return -1;
		}
		
}






template<class ElemType>//结点类 
struct Node
{
	ElemType data;
	Node *next;
};

template<class ElemType>//链栈类 
class LinkStack
{
	protected:
		Node<ElemType> * top;	//栈顶指针
		void Init();	//初始化栈函数
		
	public:
		LinkStack();	//无参构造函数
		virtual ~LinkStack();	//析构虚函数
		int Length() const;		//求栈长度
		bool Empty() const;		//判断栈是否为空
		void Clear();			//将栈清空
		void Show();
		
		int Push(const ElemType &e);//入栈
		int Pop(ElemType &e);	//出栈
		ElemType GetTop() const;//返回栈顶元素
		 
};

template <class ElemType>
void LinkStack<ElemType>::Init()//初始化栈 
{
	top=NULL;
 } 
 
template <class ElemType>
LinkStack<ElemType>::LinkStack()//构造 空链表 
{
	Init();
}

template <class ElemType>
LinkStack<ElemType>::~LinkStack()
{
	Clear();//销毁栈 
}

template <class ElemType>
void LinkStack<ElemType>::Clear()
{
	ElemType tmpElem;
	while(!Empty())
	{
		Pop(tmpElem);
	}
}

template <class ElemType>
void LinkStack<ElemType>::Show()
{
	for(Node<ElemType> * tmpPtr=top;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{
		//count++;
		printf("%c ",tmpPtr->data);
	}
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
{//返回栈的长度 
	int count=0;
	for(Node<ElemType> * tmpPtr=top;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{
		count++;
	}
	return count;
}

template <class ElemType>
bool LinkStack<ElemType>::Empty() const
{
	return top==NULL;
}

template <class ElemType>
int LinkStack<ElemType>::Push(const ElemType &e)
{//将e元素追加到栈顶，成功则返回SUCCESS，否则机器动态内存已耗尽返回OVER_FLOW
	Node<ElemType> * new_top=new Node<ElemType>{e,top};
	if(new_top==NULL)
	{
		return OVER_FLOW;
	}
	else
	{
		new_top->next=top;//!!!!
		top=new_top;
		
		return SUCCESS;
	}
}

template <class ElemType>
int LinkStack<ElemType>::Pop(ElemType &e)
{//如果栈非空，用e接收返回的栈顶元素，并删除栈顶元素,成功则返回SUCCESS；否则栈为空，返回UNDER_FLOW 
	if(Empty())
	{
		return UNDER_FLOW;
	}
	else
	{
		Node<ElemType> * old_top=top;
		e=old_top->data;
		top=old_top->next;
		delete old_top;
		
		return SUCCESS;
	}
}
//template <class ElemType>
//int LinkStack<ElemType>::Pop()
//{//如果栈非空，用e接收返回的栈顶元素，并删除栈顶元素,成功则返回SUCCESS；否则栈为空，返回UNDER_FLOW 
//	if(Empty())
//	{
//		return UNDER_FLOW;
//	}
//	else
//	{
//		Node<ElemType> * old_top=top;
//		top=old_top->next;
//		delete old_top;
//		
//		return SUCCESS;
//	}
//}

template <class ElemType>
ElemType LinkStack<ElemType>::GetTop() const
{//如果栈非空，用e接收返回的栈顶元素，成功则返回SUCCESS；否则栈为空，返回UNDER_FLOW 
	if(Empty())
	{
		return NULL;
	}
	else
	{
		ElemType e;
		e=top->data;
		return e;
	}
}
