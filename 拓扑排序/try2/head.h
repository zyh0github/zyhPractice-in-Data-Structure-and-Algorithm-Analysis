#include<iostream>
#include<fstream>
#include<cstdlib>//dev c++太坑了，exit没有包含也不提示
#include<string.h>
#include <queue>
using namespace std;

struct CourseNode{
    char courseNo[4];
    CourseNode* next=NULL;
};

//课程节点
struct Course{
	char courseNo[4];//课程编号
	char courseName[100];//课程名
	int period=0;//学时数
	int term=0;//开课学期
	CourseNode* next=NULL;
	CourseNode* last=NULL;
};


//课程表类模版
class Schedule{
	private:
		int inDu[38];//一共38个课程的入度
		int semester[8];//储存每个学期的课程总数
		Course cou[38];//38个课程节点
		queue<int>  que1;//有个队列存储当前入度为0的编号，不断维护

	public:
	    void initializeIndu();//初始化入度数组
		void amendinDu();//修改入度数组
		void getSemester(char* s);//得到学期课程行
		Course getOneCourse(int courseNumber,char* s);//得到各个课程节点
		void getAllCourse();//用得到的课程节点建立图
		void getGragh(int courseNumber,int i,char *s,Course course);//建立图
		queue<int> getqueue();//得到最初队列
		void amendqueue();//修改队列
		void Topprint();//打印拓扑结果
};

void Schedule::initializeIndu()
{
    for(int k=0;k<38;k++)
    {
        inDu[k]=0;
    }
    for(int k=0;k<38;k++)
    {
        cou[k].next=NULL;
        cou[k].last=NULL;
    }
}


void Schedule::getSemester(char* s)
{
    int i=0;
    int sem=0;
    while(i<strlen(s))
    {
        if('0'<=s[i]&&s[i]<='9')
        {
            //cout<<s[i]<<endl;
            semester[sem]=s[i]-'0';
            sem++;
        }
            i++;
    }
}

Course Schedule::getOneCourse(int courseNumber,char* s)
{
    Course course;
    for(int i=0;i<100;i++)
    {
        course.courseName[i]='\0';
    }
    for(int i=0;i<5;i++)
    {
        course.courseNo[i]='\0';
    }
    int i=0;
    int flag=1;//1-5分别是课程编号、课程名称、学时数、指定开课学期、先决条件
    if(flag==1)
    {

        for(i=0;i<3;i++)
        {
            course.courseNo[i]=s[i];
        }
    }
    while(s[i]=='\t'||s[i]==' ')
    {
        i++;
    }
    flag=2;
    if(flag==2)
    {
        int j=0;
        while(s[i]!=' '&&s[i]!='\t')
        {
            course.courseName[j]=s[i];
            j++;
            i++;
        }
    }
    while(s[i]=='\t'||s[i]==' ')
    {
        i++;
    }
    flag=3;
    if(flag==3)
    {
        course.period=s[i]-'0';
        i++;
    }
    while(s[i]=='\t'||s[i]==' ')
    {
        i++;
    }
    flag=4;
    if(flag==4)
    {
        course.term=s[i]-'0';
        i++;
    }
    while(s[i]=='\t'||s[i]==' ')
    {
        i++;
    }
    flag=5;
    if(flag==5)
    {
        getGragh(courseNumber,i,s,course);
    }

    return course;
}
int courseNumber=0;

void Schedule::getAllCourse()
{
	char s[318];
	//打开文件
	ifstream f;
	f.open("course_inf.txt");
	if(f.fail())
	{
		cout<<"fail!"<<endl;
		exit(1);
	}
	initializeIndu();//初始化入度数组
	//逐行读取并处理;
	courseNumber=0;//(全局变量)当前正在读取的课程编号
	while(!f.eof())
	{
		f.getline(s,318);
		if((s[0]=='/'&&s[1]=='/')||(strlen(s)==0))//getline()读到空行时返回,使字符串长度为0
        {
            continue;
        }
        if(s[0]!='c')//是学期课程行,给学期数组赋值
        {
            getSemester(s);
        }
        else//是课程行
        {
            cou[courseNumber]=getOneCourse(courseNumber,s);
            courseNumber++;
        }
	}
	cout<<"读取完成后每个点的入度："<<endl;
	for(int i=0;i<38;i++)
    {
        cout<<inDu[i]<<endl;
    }

	/*for(int i=0;i<38;i++)
    {
        cout<<cou[i].courseName<<endl;
    }*/
	f.close();
}

void Schedule::getGragh(int courseNumber,int i,char* s,Course course)//逐行建图
{
        int j=0;
        char courseArr[4];

        while(i<strlen(s))//逐个获取前驱编号
        {
            int x=0;
            if(s[i]==' '||s[i]=='\t'||s[i]=='\n')
            {
                i++;
                if(i>=strlen(s))
                {
                    continue;
                }
            }
            for(int k=0;k<4;k++)
            {
                courseArr[k]='\0';
            }
            for(int k=0;k<3;k++)
            {
                courseArr[k]=s[i];
                i++;
                x=1;
            }
            if(x==1)
            {
                cout<<"头："<<courseArr<<endl;

                for(int k=0;k<38;k++)
                {
                    if(strcmp(cou[k].courseNo,courseArr)==0)//找到射出点，建立出度图
                    {
                        //CourseNode couN;//新建节点每次建都是同一个地址，只会覆盖!!!!!!
                        CourseNode *couN;
                        couN=(struct CourseNode*) malloc(sizeof(CourseNode));
                        for(int m=0;m<4;m++)//任何东西使用之前初始化太重要了，不要全部预设最初都是\0，不然会吃亏的。
                        {
                            couN->courseNo[m]='\0';
                            couN->next=NULL;
                        }
                        for(int m=0;m<3;m++)
                        {
                            couN->courseNo[m]=course.courseNo[m];//把当前节点赋给新建节点
                        }
                        if(cou[k].next==NULL)
                        {
                            cou[k].next=couN;
                            cou[k].last=couN;
                            cou[k].last->next=NULL;
                            inDu[courseNumber]++;
                            cout<<"头的第一个节点，尾的入度为："<<inDu[courseNumber]<<endl;
                        }
                        else
                        {
                            cou[k].last->next=couN;
                            cou[k].last=couN;
                            cou[k].last->next=NULL;
                            inDu[courseNumber]++;
                            cout<<"这不是头的第一个节点，尾的入度为："<<inDu[courseNumber]<<endl;
                        }


                        cout<<"当前行节点："<<couN->courseNo<<endl<<endl;
                        //cout<<"yes!"<<endl;

                    }
                }
            }
            x=0;

        }
}

queue<int> Schedule::getqueue()
{
    for(int k=0;k<38;k++)
    {
        if(cou[k].term==0)
        {
            if(inDu[k]==0)
            {
                que1.push(k);
            }
        }

    }

    return que1;
}

void Schedule::Topprint()
{
    queue<int> que;
    que=getqueue();//得到最初队列

    int nowSemester=1;
    int nowCourseNum=0;
    for(int k=0;k<8;k++)
    {
        nowCourseNum=0;
        cout<<"第"<<nowSemester<<"学期:"<<endl;
        for(int j=0;j<38;j++)
        {
            if(nowSemester==cou[j].term)
            {
                cout<<cou[j].courseName<<' ';
                nowCourseNum++;
            }
        }
        //cout<<nowSemester<<endl;
        //if(cou[0].next==cou[0].last)
        //{
        //    cout<<cou[0].courseName<<endl;
        //}
        for(int j=1;j<=semester[k]-nowCourseNum;j++)//每个学期的课程总数
        {
            int x;
            x=que.front();
            que.pop();
            cout<<cou[x].courseName<<' ';
            //每出队一个就修改indu数组并维护队列
            CourseNode* now=NULL;
            /*if(cou[x].next==cou[x].last)
            {
                cout<<"Null"<<endl;
            }*/
            while(cou[x].next!=NULL)
            {
                //cout<<'!'<<endl;
                now=cou[x].next;
                //cout<<'!'<<endl;
                for(int v=0;v<29;v++)
                {
                    //cout<<now->courseNo<<endl;
                    if(strcmp((cou[v].courseNo),(now->courseNo))==0)//后面的节点入度--
                    {
                        inDu[v]--;
                        if(inDu[v]==0)
                        {
                            que.push(v);
                        }
                        //cout<<'?'<<endl;
                        //amendqueue();
                        if(now!=cou[x].last)
                        {
                            cou[x].next=now->next;
                        //delete *now;
                            now=cou[x].next;
                        }
                        else
                        {
                            cou[x].next=NULL;
                            //cout<<'!'<<endl;
                            break;
                        }
                    }
                }
                //cout<<'!'<<endl;
                //inDu[x]--
            }
            //cout<<'!'<<endl;
            if(cou[x].next==cou[x].last)
            {
                cou[x].last=NULL;
            }


        }

         //cout<<nowSemester<<endl;
         nowSemester++;
         cout<<endl;
    }
}
