/*学生成绩管理系统，分为教师界面和学生界面，教师界面需要密码进入可以输入学生的信息，
修改学生的成绩，删除学生信息，查询学生的成绩,给成绩排序，查看所有学生信息，读取和保存学
生信息，读取学生的建议功能。学生需要提供学号和密码，成功进入后可以查看个人信息，修改密码，
给老师留言（这里老师添加完信息需要保存，然后学生才能根据老师的录入来登录）,进入系统可以读取
上次存放在文件中的数据，这样能够更好的实现交互性。教师可以查看学生的建议，可以显示留下建议
的同学的学号。总体而言功能较为全面，可能有些许ｂｕｇ可以修改*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getch.h>
#include<ctype.h>

void main_menu();          //主页面的显示
void teacher_menu();       //教师登录页面的显示
void student_menu();       //学生登录页面的显示
void advice_menu();        //对该程序的建议
void teacher_operation();  //教师的页面操作处理
void student_operation();  //学生的页面操作处理
void studentgrade_scanf();      //学生成绩录入
void inputallstudent();    //输出所有学生信息
void studentgrade_modify();//修改学生成绩
void student_information_p();//学生自我查询成绩输出
void quert_student();      //教师查询学生成绩
void studentgrade_sort(); //学生成绩排序
void save_studentinformation(); //保存学生信息到文件
void read_studentinformation(); //从文件读取学生信息
void delete_student();      //删除学生信息
void student_advice();       //学生建议查看
void student_advice_p();  //学生意见写入
void modify_grade();    //学生修改密码

typedef struct     //学生信息
{
	char s_name[10];    //名字
	unsigned int age;   //年龄
	char s_studentnumber[17]; //学号
	char sex[4];         //性别
	char major[10];       //专业
	unsigned int grade;//分数
	char s_password[18];//密码
}Student;

typedef struct _Node   //结点定义
{
	Student stu;     //结点信息
	struct _Node* next;   //下一个结点地址
}Node;

Node* g_pHead=NULL;//头结点
char s_number[17];

int main()
{
	char command;           //定义最开始页面的输入指令
	while(1)
	{
		system("clear");
		main_menu();         //显示页面
		command=getch();       //获取用户的指令
		switch(command)          //对指令进行分析
		{
			case '1':teacher_menu();break;  //跳转到教师的登录界面
			case '2':student_menu();break;    //跳转到学生的登录界面
			case '3':advice_menu();break;     //跳转到建议界面
			case '0':exit(0);                //退出
			case 'r':read_studentinformation();break;//读取数据
			default:printf("输入数据非法请重新输入!\n");
		}
	}
}

void main_menu()//主页面
{
	printf("\t\t\t----------------------------------\n");
	printf("\t\t\t|         学生管理系统1.0v       |\n");
	printf("\t\t\t----------------------------------\n");
	printf("\t\t\t|1.教师登录            2.学生登录|\n");
	printf("\t\t\t|0.退出系统            3.提出建议|\n");
	printf("\t\t\t|r.读入库中数据------------------|\n");
	printf("\t\t\t----------------------------------\n");
	printf("请输入指令：\n");
}

void teacher_menu()  //教师登录页面
{
	//存放教师的登录账号和密码
	char c_teacher_number[10]="xiong",c_teacher_mm[10]="250";
	char c_print_number[10],c_print_mm[10];//定义输入的账号和密码
	printf("请输入教师账号:");
	gets(c_print_number);
	//如果输入账号的长度过大或者不匹配提示重新输入
	if(strlen(c_print_number)>strlen(c_teacher_number)||\
		strcmp(c_print_number,c_teacher_number))  
	{
		printf("账号输入有误,请重新输入!\n");
		teacher_menu();
	}
	printf("请输入密码:");
	gets(c_print_mm);
	//如果输入密码的长度过大或者不匹配提示重新输入
	if(strlen(c_print_mm)>strlen(c_teacher_mm)||\
		strcmp(c_print_mm,c_teacher_mm))
	{
		printf("密码输入有误,请重新输入!\n");
		teacher_menu();
	}
	printf("登录成功，欢迎熊老师！\n");
	teacher_operation();//跳转到教师操作界面
}

void student_menu()  //学生登录页面
{
	char number[17],s_password[18];
	int sign=0;  //如果没找到学生的学号
	printf("请输入你的学号:");
	gets(number);
	Node *p=g_pHead;
	while(p!=NULL)
	{
		if(strcmp(p->stu.s_studentnumber,number)==0)
		{
			printf("请输入密码:");
			gets(s_password);
			if(strcmp(p->stu.s_password,s_password)!=0)
			{
				printf("密码错误!!!\n");
				student_menu();
			}
			else
			{
			    strcpy(s_number,number);
			    sign=1;
			    printf("欢迎登录！！\n");
			    student_operation();
			}
		}
		p=p->next;
	}
	if(sign==0)
	{
		printf("学号未找到!!!\n");
	}
	getch();
	system("clear");
	return;
}

void teacher_operation()//教师操作界面
{
	system("clear");
	printf("\t\t\t----------------------------------\n");
	printf("\t\t\t|           教师管理界面         |\n");
	printf("\t\t\t----------------------------------\n");
    printf("\t\t\t|1.录入学生信息    2.修改学生成绩|\n");
    printf("\t\t\t|3.显示所有学生信息4.学生成绩排名|\n");
    printf("\t\t\t|5.查询学生成绩    6.查看学生留言|\n");
	printf("\t\t\t|7.保存学生信息　　8.读取学生信息|\n");
    printf("\t\t\t|9.删除学生信息    0.退出登录    |\n");
	printf("\t\t\t----------------------------------\n");
	char command;
	printf("请老师输入指令:\n");
	command=getch();
	switch(command)     //命令跳转
	{
		case '1':studentgrade_scanf();break;
		case '2':studentgrade_modify();break;
		case '3':inputallstudent();break;
		case '4':studentgrade_sort();break;
		case '5':quert_student();break;
		case '6':student_advice();break;
		case '7':save_studentinformation();break;
		case '8':read_studentinformation();break;
		case '9':delete_student();break;
		case '0':return;
	}
	system("clear");
	teacher_operation();
}

void studentgrade_scanf()//学生信息输入
{
	Node* p=(Node *)malloc(sizeof(Node)); //请求存储空间
	p->next=NULL;
	printf("请输入学生的姓名:\n");
	scanf("%s",p->stu.s_name);
	printf("请输入学生的年龄:\n");
	scanf("%d",&p->stu.age);
	printf("请输入学生的学号:\n");
	scanf("%s",p->stu.s_studentnumber);
	printf("请输入学生的性别:\n");
	scanf("%s",p->stu.sex);
	printf("请输入学生的专业:\n");
	scanf("%s",p->stu.major);
	printf("请输入学生的分数:\n");
	scanf("%d",&p->stu.grade);
	printf("请输入学生的登录密码\n");
	scanf("%s",p->stu.s_password);

	if(g_pHead==NULL)     //给第一个结点赋值
	{
		g_pHead=p;
	}
	else                   //将结点从已有结点的头部插入
	{
		p->next=g_pHead;
		g_pHead=p;
	}

	printf("成绩录入成功!\n");
	getch();
	getch();
	teacher_operation();
}

void studentgrade_modify()            //学生成绩修改
{
	char name[10];
	int grade;
	printf("请输入要修改的学生名字:");
	scanf("%s",name);
	Node* p=g_pHead;

    while(p!=NULL)                    //遍历链表
	{
		if(strcmp(name,p->stu.s_name)==0)       
		{
			printf("此学生的成绩为：%d\n",p->stu.grade);
			printf("要将此学生的成绩改为：");
			scanf("%d",&grade);
			if(grade>=0&&grade<=100)         //如果成绩合法可以修改
			{
				p->stu.grade=grade;
				printf("\n修改成功！\n");
			}
			else                               //不合法重新输入
			{
				printf("\n输入不合法,请重新输入!\n");
				system("clear");
				studentgrade_modify();
			}
		}
		p=p->next;
    }

	getchar();
}

void quert_student()   //教师查询学生成绩
{
	char studentnumber[17];
	int sign=0;//是否找到

	system("clear");
	printf("请输入你要查询的学生学号:\n");
	scanf("%s",studentnumber);

	Node* p=g_pHead;

	while(p!=NULL)
	{
		if(strcmp(p->stu.s_studentnumber,studentnumber)==0)
		{
			printf("\t\t\t----------------------------------\n");
			printf("\t\t\t姓名  年龄  学号  性别  专业  分数\n");
			printf("\t\t\t----------------------------------\n");
			printf("\t\t\t%5s  %2d  %5s  %4s  %5s  %3d\n",p->stu.s_name,p->stu.age,p->stu.s_studentnumber,p->stu.sex\
			,p->stu.major,p->stu.grade);
			sign=1;
		}
		p=p->next;
	}

	if(sign==0)
	{
		printf("未找到该学生信息!!!\n");
	}

	getch();
	getch();
}

void inputallstudent()    //输出所有的学生信息
{
	//system("clear");
	printf("\t\t\t----------------------------------\n");
	printf("\t\t\t姓名  年龄  学号  性别  专业  分数\n");
	printf("\t\t\t----------------------------------\n");

	Node* p=g_pHead;

	while(p!=NULL)       //遍历链表输出学生信息
	{
		printf("\t\t\t%5s  %2d  %5s  %4s  %5s  %3d\n",p->stu.s_name,p->stu.age,p->stu.s_studentnumber,p->stu.sex\
		,p->stu.major,p->stu.grade);
		p=p->next;
	}

	getchar();
}

void studentgrade_sort()    //学生成绩排序
{
	Node* p=g_pHead;
	Node* q=p+1;
	Student temp;

	for(p=g_pHead;p!=NULL;p=p->next)    //双循环来排序
	{
		for(q=p->next;q!=NULL;q=q->next)
		{
			if(p->stu.grade<q->stu.grade)
			{
				temp=p->stu;
				p->stu=q->stu;
				q->stu=temp;
			}
		}
	}

	inputallstudent();
}

void save_studentinformation()//保存学生信息
{
	FILE* p_file=fopen("student.txt","w+");

	if(p_file==NULL)    //打开失败
	{
		printf("打开文件失败！！");
		return;
	}

	Node* p=g_pHead;
	while(p!=NULL)    //遍历把数据读入
	{
		fprintf(p_file,"%s %d %s %s %s %d %s\n",p->stu.s_name,p->stu.age,p->stu.s_studentnumber,p->stu.sex\
		,p->stu.major,p->stu.grade,p->stu.s_password);
		p=p->next;
	}
	printf("数据保存成功!\n");
	getch();
	fclose(p_file);
}

void read_studentinformation()    //读取文件中信息
{
	Node* p,*p2;
	p=p2=g_pHead;

	while(p2!=NULL)     //先将结点中已有的信息释放
	{
		p=p->next;
		free(p2);

		p2=p;
	}
	g_pHead=NULL;

	FILE* s_file=fopen("student.txt","r");

	if(s_file==NULL)
	{
		printf("读取文件失败！！");
		return;
	}

	while(!feof(s_file))//读取文件的信息
	{
		Node* ptemp = (Node *)malloc(sizeof(Node));//申请内存因为前面释放了
		fscanf(s_file,"%s %d %s %s %s %d %s\n",ptemp->stu.s_name,&ptemp->stu.age,ptemp->stu.s_studentnumber,ptemp->stu.sex\
		,ptemp->stu.major,&ptemp->stu.grade,ptemp->stu.s_password);//按格式读取文件中的信息

		if(g_pHead==NULL)//如果头结点为空则讲数据给头结点
		{
			g_pHead=ptemp;
			p=g_pHead;
		}
		else//不是头结点就把信息给ｐ的下一个结点
		{
			p->next=ptemp;
			p=p->next;
			p->next=NULL;
		}
	}
	printf("读取成功\n");
	getch();
	fclose(s_file);
}

void delete_student()   //删除某个学生的信息
{
	char s_studentnumber[17];
	printf("请输入要删除的学生学号：\n");
	scanf("%s",s_studentnumber);
	Node* p = g_pHead;
	Node* p2;
	if(strcmp(g_pHead->stu.s_studentnumber,s_studentnumber)==0)
	//如果输入的学号跟头结点一样就保存头结点的地址，然后把头结点赋值为下一个结点的地址，然后把头结点的地址释放
	{
		p2=g_pHead;
		g_pHead=g_pHead->next;
		free(p2);
		printf("删除成功!!\n");
		getch();
		return;
	}
	//如果不是头结点就遍历，如果一个结点的下一个结点是要找的就保存他的地址，然后把该节点的地址赋值为下一个地址，然后将他的地址释放
	while(p->next!=NULL)
	{
		if(strcmp(p->next->stu.s_studentnumber,s_studentnumber)==0)
		{
			p2=p->next;
			p->next=p->next->next;
			free(p2);
			printf("删除成功!!\n");
			getch();
			return;
		}
		p=p->next;

		if(p->next==NULL)
		{
			break;
		}
	}
	if(p==NULL)
	{
		printf("没有找到该学员的信息！！");
	}
	getch();

}

void student_advice()//读取学生建议
{
	FILE* p_file = fopen("studentadvice.txt","r");
	fseek( p_file , 0 , SEEK_END );
	int file_size;
    file_size = ftell(p_file);
	char *tmp;
	fseek( p_file , 0 , SEEK_SET);
	tmp =  (char *)malloc( file_size * sizeof( char ) );
	fread( tmp , file_size , sizeof(char) , p_file);
	printf("%s" , tmp );
	getch();
	fclose(p_file);
}

void student_operation()   //学生操作页面
{
	system("clear");
	char temp;
	printf("\t\t\t----------------------------------\n");
    printf("\t\t\t|           学生管理界面         |\n");
	printf("\t\t\t----------------------------------\n");
	printf("\t\t\t|1.显示我的信息      2.给老师留言|\n");
    printf("\t\t\t|3.返回主页          4.退出系统  |\n");
	printf("\t\t\t|5.修改密码                      |\n");
	printf("\t\t\t----------------------------------\n");
	printf("请继续你的操作：\n");
	temp=getchar();
	switch(temp)
	{
		case '1':student_information_p();break;
		case '2':student_advice_p();break;
		case '4':exit(0);
		case '3':return;
		case '5':modify_grade();break;
		default:printf("输入有误!!\n");student_operation();
	}
}

void student_information_p()   //学生信息显示
{
	Node* p=g_pHead;


	while(p!=NULL)                    //遍历链表
    {
		if(strcmp(s_number,p->stu.s_studentnumber)==0)
		{
			printf("\t\t\t姓名%s  年龄%d  学号%s  性别%s  专业%s  分数%d\n",p->stu.s_name,p->stu.age,p->stu.s_studentnumber,p->stu.sex\
			,p->stu.major,p->stu.grade);
		}
		p=p->next;
	}
	getch();
	getch();
	student_operation();
}

void student_advice_p()     //学生建议写入保存
{
	char studentadvice[200];
	printf("请输入你对老师的建议：\n");
	FILE* p_file = fopen("studentadvice.txt","a");
	scanf("%s",studentadvice);
	fprintf(p_file,"%s %s\n",s_number,studentadvice);
	fclose(p_file);
	p_file=NULL;
	printf("写入成功!!!\n");
	getch();
	getch();
	student_operation();
}

void modify_grade()
{
	char password[18],newpassword[18];
	Node* p = g_pHead;
	while(p!=NULL)
	{
		if(strcmp(p->stu.s_studentnumber,s_number)==0)
		{
			printf("请输入原密码:\n");
			getchar();
			gets(password);
			if(strcmp(p->stu.s_password,password)==0)
			{
				printf("请输入新的密码:\n");
				gets(newpassword);
				if(strcmp(p->stu.s_password,newpassword)==0)
				{
				    printf("密码相同，修改失败!!!");
					break;
				}
				else
				{
				    strcpy(p->stu.s_password,newpassword);
					printf("修改成功!!!");
					break;
				}
			}
		}
		p=p->next;
	}

	getch();
	student_operation();
}

void advice_menu() //对系统的建议
{
	char advice[200];
	FILE* p_file = fopen("advice.txt","a");
	system("clear");
	printf("您的建议是(最多可输入２００字):\n");
	scanf("%s",advice);
	getchar();
	fprintf(p_file,"%s\n",advice);
	fclose(p_file);
	p_file=NULL;
	printf("\n感谢您的建议，我们将会做的更好!\n");
	getch();
}
