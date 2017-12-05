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






template<class ElemType>//����� 
struct Node
{
	ElemType data;
	Node *next;
};

template<class ElemType>//��ջ�� 
class LinkStack
{
	protected:
		Node<ElemType> * top;	//ջ��ָ��
		void Init();	//��ʼ��ջ����
		
	public:
		LinkStack();	//�޲ι��캯��
		virtual ~LinkStack();	//�����麯��
		int Length() const;		//��ջ����
		bool Empty() const;		//�ж�ջ�Ƿ�Ϊ��
		void Clear();			//��ջ���
		void Show();
		
		int Push(const ElemType &e);//��ջ
		int Pop(ElemType &e);	//��ջ
		ElemType GetTop() const;//����ջ��Ԫ��
		 
};

template <class ElemType>
void LinkStack<ElemType>::Init()//��ʼ��ջ 
{
	top=NULL;
 } 
 
template <class ElemType>
LinkStack<ElemType>::LinkStack()//���� ������ 
{
	Init();
}

template <class ElemType>
LinkStack<ElemType>::~LinkStack()
{
	Clear();//����ջ 
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
{//����ջ�ĳ��� 
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
{//��eԪ��׷�ӵ�ջ�����ɹ��򷵻�SUCCESS�����������̬�ڴ��Ѻľ�����OVER_FLOW
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
{//���ջ�ǿգ���e���շ��ص�ջ��Ԫ�أ���ɾ��ջ��Ԫ��,�ɹ��򷵻�SUCCESS������ջΪ�գ�����UNDER_FLOW 
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
//{//���ջ�ǿգ���e���շ��ص�ջ��Ԫ�أ���ɾ��ջ��Ԫ��,�ɹ��򷵻�SUCCESS������ջΪ�գ�����UNDER_FLOW 
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
{//���ջ�ǿգ���e���շ��ص�ջ��Ԫ�أ��ɹ��򷵻�SUCCESS������ջΪ�գ�����UNDER_FLOW 
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
