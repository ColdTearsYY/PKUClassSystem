//选课系统 2.0.0 基于1.0.0重写了近50%的代码，重点是改其他部分为普通文件读写，仅对密码部分保留二进制读写
//项目地址：https://github.com/ColdTearsYY/PKUClassSystem
//欢迎提交 issue

#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int sumClass;//有多少节课
char t[1000], t1[1000], name1[100], temp[100]; //通用临时变量

struct account {
	char name[100];
	char username[100];
	char academy[100];
	char password[100];
};//存在database.txt的账号元素结构体

struct ke {
	char name[100];
	char maxnum[100];
	char nownum[100];
	char tag[50] ;
};//课程库kecheng.txt的元素，存课程信息

struct keUnit {
	char name[100];
	char tag[50] ;
};//【学号】.txt里面的，每个人选的课的元素，存每个人选的课

struct userUnit {
	char name[100];
	char username[100];
	char academy[100];
	char tag[50] ;
};//【课程名】.txt里面的，人元素，属于课，记录所有选这个课的人

int checkClassNum() {//计数函数
	ke cshow;
	sumClass = 0;//计数器拨回0
	ifstream fcin("kecheng.txt");//检查文件是否存在

	if (!fcin) {
		cout << "暂时还没有课程" << endl;
		fcin.close();
		//exit(1);
		return 0;//不存在就是0课
	} else {
		while (!fcin.eof()) {
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) {
				if ((strcmp(cshow.tag, "1") == 0) && (atoi(cshow.maxnum) != 0)) { //课程状态正常+最大人数！=0
					sumClass++;//计数器+1
				}
			}
		}

		fcin.close();//关闭文件
		return sumClass;//返回有多少节课
	}
}

int checkUserNum(char s[]) {
	userUnit userunit;
	ifstream fcin;
	fcin.open(s);
	int usersum = 0;

	while (!fcin.eof()) {
		if (fcin >> userunit.name >> userunit.username >> userunit.academy >> userunit.tag) {
			if (strcmp(userunit.tag, "1") == 0)
				usersum++;
		}
	}

	return usersum;
}

void teacher();//教师一级
void teacherLogin();//教师登录
void student();//学生一级
void studentLogin();//学生登录
void studentReg();//学生注册
void studentMenu();//学生菜单
void mainMenu();//主菜单，同main，用于返回
void teacherMenu();//教师菜单

void addClass();//教师-加课
void delClass();//教师-删课
void modifyClass();//教师-设置课程
void checkAll();//教师-检查某某课的人选

void selectClass();//学生-选课
void quitClass();//学生-退课
void checkMe();//学生-自查

int main() {
	int n = 0;
	char s[1000];//输入栏

	ofstream KECHENG;//创建kecheng库
	KECHENG.open("kecheng.txt", ios::app);
	KECHENG.close();

	while (n != 3) {
		system("cls");
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 欢迎使用北京大学      ┃" << endl;
		cout << "┃ 选课系统师生统一端    ┃" << endl;
		cout << "┃                       ┃" << endl;
		cout << "┃ 1. 我是教务           ┃" << endl;
		cout << "┃ 2. 我是学生           ┃" << endl;
		cout << "┃ 3. 退出               ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━┛ \n" << endl;
		cout << "请输入数字选择功能 1/2/3: " ;
		cin >> s;//输入选择

		//getchar();
		if ((strlen(s) == 1) && isdigit(s[0])) //检查输入是否合法
			n = s[0] - '0';//合法则赋值

		switch (n) {
			case 1:
				teacher();//到教师一级
				break;

			case 2:
				student();//到学生一级
				break;

			case 3:
				exit(2);//退出

			default:
				break;//输入无意义，等待正确输入
		}
	}

	return 0;
}

void mainMenu() {//同上int main，不赘述
	int n = 0;
	char s[1000];

	while (n != 3) {
		system("cls");
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 欢迎使用北京大学      ┃" << endl;
		cout << "┃ 选课系统师生统一端    ┃" << endl;
		cout << "┃                       ┃" << endl;
		cout << "┃ 1. 我是教务           ┃" << endl;
		cout << "┃ 2. 我是学生           ┃" << endl;
		cout << "┃ 3. 退出               ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━┛ \n" << endl;
		cout << "请输入数字选择功能 1/2/3: " ;
		cin >> s;

		//getchar();
		if ((strlen(s) == 1) && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				teacher();
				break;

			case 2:
				student();
				break;

			case 3:
				exit(2);

			default:
				break;
		}
	}
}

void teacher() {//教师一级
	int n = 0;//选择器拨回0
	char s[1000];//用于储存输入

	while (true) {
		system("cls");//清屏
		cout << "┍━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 欢迎您，教务！┃" << endl;
		cout << "┃               ┃" << endl;
		cout << "┃ 1. 登录系统   ┃" << endl;
		cout << "┃ 2. 返回上级   ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━┛ \n" << endl;
		cout << "请输入数字选择功能 1/2: " ;
		cin >> s;
		getchar();//清理缓冲区

		if ((strlen(s) == 1) && isdigit(s[0])) //检查合法
			n = s[0] - '0';

		switch (n) {
			case 1:
				teacherLogin();//跳转教师登录
				break;

			case 2:
				mainMenu();//返回主菜单
				break;

			default:
				break;//输入无意义
		}
	}
}

void teacherLogin() {//教师-登录
	char key[] = "@2022";//密码
	char keyIn[10000];
	char back[] = "back";
	char exit0[] = "exit";

	while (true) {
		system("cls");
		cout << "┍━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 请输入密码    ┃" << endl;
		cout << "┃ 输入back返回  ┃" << endl;
		cout << "┃ 输入exit退出  ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━┛ \n" << endl;
		cout << "密码：";
		cin.getline(keyIn, 10000);//读入输入

		if (strcmp(keyIn, key) == 0) {//密码正确
			system("cls");
			cout << "┍━━━━━━━━━━━━━━━┓ \n";
			cout << "┃ 登陆成功！    ┃" << endl;
			cout << "┕━━━━━━━━━━━━━━━┛ \n" << endl;
			system("pause");
			teacherMenu();
			break;
		} else if (strcmp(keyIn, back) == 0) {
			break;//返回上级
		} else if (strcmp(keyIn, exit0) == 0) {
			exit(0);//退出程序
			break;
		} else {
			system("cls");//清屏
			cout << "┍━━━━━━━━━━━━━━━┓ \n";
			cout << "┃ 密码错误！    ┃" << endl;
			cout << "┃ 请再次尝试    ┃" << endl;
			cout << "┕━━━━━━━━━━━━━━━┛ \n" << endl;
			system("pause");
		}
	}
}

void teacherMenu() {//教师菜单
	int n = 0;
	char s[1000];

	while (true) {
		system("cls");
		cout << "┍━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 教务，您已登录┃" << endl;
		cout << "┃ 请选择功能    ┃" << endl;
		cout << "┃ 1. 添加课程   ┃" << endl;
		cout << "┃ 2. 删除课程   ┃" << endl;
		cout << "┃ 3. 修改课程   ┃" << endl;
		cout << "┃ 4. 查看结果   ┃ " << endl;
		cout << "┃ 5. 退出登录   ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━┛ \n" <<
		     endl;
		cout << "本学期开放选择的课程共 " << checkClassNum() << " 门，名称及剩余名额如下：" << endl;
		cout << endl;
		ifstream fcin;
		fcin.open("kecheng.txt");//检查kecheng库是否存在
		//附加功能：即刻查询实时人数
		int inthismax, inthisnow;//课程最大人数，课程当前人数
		ke cshow;

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "━━━━━━━━━━━";

		cout << endl;

		while (!fcin.eof()) {//读kecheng库
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //如果课程状态正常
				//cout << cshow.tag[0] << endl;
				if (strcmp(cshow.tag, "1") == 0)
					printf("%-10s ", cshow.name);
			}
		}

		cout << endl;
		fcin.close();
		fcin.open("kecheng.txt");

		while (!fcin.eof()) {//读kecheng库
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //如果课程状态正常
				//cout << cshow.tag[0] << endl;
				if (strcmp(cshow.tag, "1") == 0) {
					inthismax = atoi(cshow.maxnum);
					inthisnow = atoi(cshow.nownum);

					if (inthismax - inthisnow > 0)
						printf("%-10d ", inthismax - inthisnow);
					else {
						printf("已满/");
						printf("%-5d ", inthismax);
					}
				}

			}
		}

		fcin.close();
		cout << endl;

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "━━━━━━━━━━━";

		cout << endl;
		n = 0;
		cout << "请输入数字以选择功能 1/2/3/4/5: ";
		cin >> s;//输入功能选择

		if ((strlen(s) == 1) && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				addClass();//去加课
				break;

			case 2:
				delClass();//去删课
				break;

			case 3:
				modifyClass();//去调课
				break;

			case 4:
				checkAll();//查某某课谁选了
				break;

			case 5:
				cout << "┍━━━━━━━━━━━━━━━┓ \n";
				cout << "┃ 安全退出成功  ┃" << endl;
				cout << "┃ 欢迎下次使用  ┃" << endl;
				cout << "┕━━━━━━━━━━━━━━━┛ \n" << endl;
				system("pause");
				exit(9);//退出程序
				break;

			default:
				break;
		}
	}
}

char kename[100];//可多次使用的临时变量
void addClass() {
	ke c, c1;//声明变量
	system("cls");//清屏
	cout << "你选择了 1. 添加课程  " << endl;
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入课程名称                             ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "课程名称：";
	cin >> kename;//输入

	ofstream fcout;
	fcout.open("kecheng.txt", ios::app); //不存在则创建
	fcout.close();//结束FILE

	ifstream fcin("kecheng.txt", ios::in); //创建读流

	int op = 0;//判定变量，判重

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if (strcmp(c1.name, kename) == 0 && strcmp(c1.tag, "1") == 0) { //如果课程重复
				cout << endl;
				cout << "该课程已存在，无法重复添加" << endl;
				cout << endl;
				op = 1;
				system("pause");
				break;
			}
		}
	}

	fcin.close();//关闭

	if (op == 0) {//如果名字没重复
		strcpy(c.name, kename);
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 请输入课程计划人数，欲取消添加请输入-1     ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		cout << "输入计划人数：";
		cin >> c.maxnum;//输入计划人数

		if (!isdigit(c.maxnum[0])) {//粗略检查输入是否合法
			cout << "\n人数输入非法，添加课程取消" << endl;
			system("pause");
			return;
		}

		strcpy(c.nownum, "0") ;//新课，当前选择人数当然默认是0
		strcpy(c.tag, "1"); //状态为1，正常
		fcout.open("kecheng.txt", ios::app); //打开课程库在末尾写入这个课

		fcout << c.name << " " << c.maxnum << " " << c.nownum << " " << c.tag << endl; //写
		fcout.close();//关闭FILE
		cout << "\n课程 " << kename << " 已经成功添加" << endl;//返回信息
		system("pause");
	}
}

void delClass() {//教师-删课
	ke c, c1;
	int confirm = 0;//删除前需要确认
	system("cls");
	cout << "你选择了 2. 删除课程  " << endl;
	cout << endl;

	if (checkClassNum() == 0) {
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 当前暂无课程，不可删除课程                 ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		remove("kecheng.txt");
		ofstream fcout;
		fcout.open("kecheng.txt", ios::app);
		fcout.close();
		system("pause");
		return;
	}

	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入要删除的课程名称                     ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "课程名称：";
	cin >> kename;
	ofstream fcout;
	fcout.open("kecheng.txt", ios::app); //检查kecheng库是否存在


	fcout.close();//over
	ifstream fcin("kecheng.txt"); //创建读流

	int op = 0;//判断要删的课是否存在

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			//cout << c1.name << " " << c1.tag << endl;!!!
			if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0)) {
				op = 1;//存在
				break;
			}
		}
	}

	fcin.close();//over

	if (op == 0 ) {//不存在
		cout << endl;
		cout << "该课程不存在，请检查" << endl;
		cout << endl;
		system("pause");
	} else if (op == 1) {//存在
		confirm = 0;
		cout << endl;
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 确认要删除吗？输入1确认，其他数字返回      ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		cout << "确认：";
		cin >> confirm;//确认是否删

		//cout << confirm << endl;
		if (confirm == 1) {//想好要删
			fcout.open("kecheng.txt", ios::app); //检查kecheng库是否存在

			fcout.close();
			fstream f;
			f.open("kecheng.txt", ios::in | ios::out | ios::binary); //文件输入输出流

			while (!f.eof()) {
				if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
					if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0)) {
						f << "0\n";
						break;
					}
				}
			}


			f.close();//关闭文件
			cout << kename << " 删除完成" << endl;

			if (checkClassNum() == 0) {
				remove("kecheng.txt");
				ofstream TEMP1;
				TEMP1.open("kecheng.txt", ios::app);
				TEMP1.close();
				system("pause");
				return;
			}

			system("pause");
		}
	}
}


void modifyClass() {//教师-改课
	ke c, c1;
	system("cls");
	cout << "你选择了 3. 修改课程  " << endl;
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入要修改的课程名称                     ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "课程名称：";
	cin >> kename;
	getchar();
	ofstream fcout;
	fcout.open("kecheng.txt", ios::app); //若不存在则创建kecheng库
	fcout.close();
	ifstream fcin;
	fcin.open("kecheng.txt");

	int op = 0;//判断要修改的课程是否存在

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0)) {
				op = 1;//存在
				break;
			}
		}
	}

	fcin.close();//over

	if (op == 0 ) {//不存在
		cout << endl;
		cout << "该课程不存在…… " << endl;
		cout << endl;
		system("pause");


	} else if (op == 1) {//存在
		cout << endl;
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 您要修改课程名称为？                       ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		cout << "输入新名称：";
		cin >> c.name;//输入新名字
		getchar();//清理缓冲区

		fstream f;//检查课程库是否存在
		f.open("kecheng.txt", ios::in | ios::out | ios::binary);

		while (!f.eof()) {//读
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) { //一个一个找
				if ((strcmp(c1.name, c.name) == 0) && (strcmp(kename, c.name) != 0)
				        && (strcmp(c1.tag, "1") == 0))  { //保证可以修改自己人数的同时避免出现同名课程
					cout << "同名课程已存在，改名失败！" << endl;//返回提示
					system("pause");
					f.close();//关闭
					return;
					break;
				}
			}
		}

		f.close();//关闭

		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 您要修改课程最大人数为？（取消请输入-1）   ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		cout << "最大人数：";
		cin >> c.maxnum;//输入要改的人数，这里允许了最大人数超过已选人数，符合实际使用习惯；在最大人数不大于已选人数时，后续会保证课程可退不可再选
		getchar();//清理缓冲区

		if (!isdigit(c.maxnum[0])) {//粗略检测输入的是不是合法
			cout << "人数输入非法，添加课程取消" << endl;
			system("pause");
			return;
		}

		strcpy(c.nownum, c1.nownum);//继承课程已选人数
		strcpy(c.tag, "1"); //初始化状态

		f.open("kecheng.txt", ios::in | ios::out | ios::binary);

		while (!f.eof()) {
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
				if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0) ) { //状态正常
					f << "1\n";
					break;
				}
			}
		}

		f.close();

		fcout.open("kecheng.txt", ios::app); //写

		fcout << c.name << " " << c.maxnum << " " << c.nownum << " " << c.tag << endl; //文件末尾二进制写入
		fcout.close();

		if (strcmp(kename, c.name) == 0) {
			cout << "已将" << kename << " 修改为 " << c.name << "，课程上限人数为" << c.maxnum << "人。" << endl; //返回信息
			system("pause");
			return;
		}

		//fcin
		//fstream FILECHECK;
		//fcout
		strcpy(t, kename);
		strcat(t, ".txt");//继续重命名
		userUnit userunit;
		keUnit keunit;
		fcin.open(t);

		if (fcin) {
			while (!fcin.eof()) {
				if (fcin >> userunit.name >> userunit.username >> userunit.academy >> userunit.tag) { //在学生的列表中重命名
					if (strcmp(userunit.tag, "1") == 0) {
						strcpy(t, userunit.username);
						strcat(t, ".txt");
						f.open(t, ios::in | ios::out | ios::binary);

						while (!f.eof()) {
							if (f >> keunit.name >> keunit.tag) {
								if ((strcmp(keunit.tag, "1") == 0) && (strcmp(keunit.name, kename) == 0)) {
									f << "1\n";
									break;
								}
							}
						}

						f.close();
						strcpy(keunit.name, c.name);
						strcpy(keunit.tag, "1");
						fcout.open(t, ios::app);
						fcout << keunit.name << " " << keunit.tag << endl;
						fcout.close();
					}
				}
			}

			fcin.close();
			strcpy(t, kename);
			strcat(t, ".txt");
			strcpy(t1, c.name);
			strcat(t1, ".txt");
			fcout.open(t1, ios::app);
			fcout.close();
			CopyFile(t, t1, FALSE);
			remove(t);
		}

		fcin.close();

		cout << "已将" << kename << " 修改为 " << c.name << "，课程上限人数为" << c.maxnum << "人。" << endl; //返回信息
		system("pause");
	}

}


void checkAll() {//教师-检查某某课选择情况
	system("cls");
	char s[1000];
	ke c1;
	userUnit userunit1;
	cout << "你选择了 4. 查看结果  " << endl;
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入您要查的课程名称                     ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "课程名称：";
	cin >> s;
	//system("cls");
	cout << endl;
	char filename[1000];
	strcpy(filename, s);
	strcat(filename, ".txt");
	ofstream fcout;
	fcout.open(filename, ios::app); //如不存在则创建
	fcout.close();

	ifstream fcin;
	fcin.open("kecheng.txt");
	int op = 0;//判断要查的课是否存在

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			//cout << c1.name << " " << c1.tag << endl;
			if ((strcmp(c1.name, s) == 0) && (strcmp(c1.tag, "1") == 0)) {
				op = 1;//存在
				break;
			}
		}
	}

	fcin.close();//over

	if (op == 0 ) {//不存在
		cout << endl;
		cout << "该课程不存在，请检查" << endl;
		cout << endl;
		system("pause");


	} else if (op == 1) {//存在
		fcin.open(filename);
		int cnt = 1;
		printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		printf("序号  学号       姓名       学院      \n");//序号5 学号10 姓名10 学院10

		while (!fcin.eof()) {
			if (fcin >> userunit1.name >> userunit1.username >> userunit1.academy >> userunit1.tag) {
				if ((strcmp(userunit1.tag, "1") == 0)) {
					printf("%-5d %-10s %-10s %-10s\n", cnt, userunit1.username, userunit1.name, userunit1.academy);
					cnt++;
				}
			}
		}

		if (cnt == 1)
			cout << "\n#暂时无人选这门课呢#\n\n";

		printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		cout << endl;
		system("pause");
	}
}


void student() {//学生一级
	int n = 0;
	char s[1000];

	while (true) {
		system("cls");
		cout << "┍━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 欢迎您，同学！┃" << endl;
		cout << "┃               ┃" << endl;
		cout << "┃ 1. 账号登陆   ┃" << endl;
		cout << "┃ 2. 新生注册   ┃" << endl;
		cout << "┃ 3. 返回上级   ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━┛ \n" <<
		     endl;
		cout << "请输入数字选择功能 1/2/3/4: ";
		cin >> s;//输入选择
		getchar();

		if ((strlen(s) == 1) && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				system("cls");//提示用户保护隐私
				cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
				cout << "┃ 即将跳转至北大统一认证系统，请注意隐私安全 ┃" <<
				     endl;
				cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
				     << endl;
				system("pause");
				studentLogin();
				break;

			case 2:
				system("cls");//提示用户保护隐私
				cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
				cout << "┃ 即将跳转至北大统一认证系统，请注意隐私安全 ┃" <<
				     endl;
				cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
				     << endl;
				system("pause");
				studentReg();
				break;

			case 3:
				mainMenu();//返回
				break;

			default:
				break;//输入无意义
		}
	}
}

char username[100];//登录cookie，记录学号
char useracademy[100];//登录cookie，记录学院
char userRealname[100];//登录cookie，记录姓名

void studentLogin() {//学生-登录
	account st1;
	system("cls");
	cout << "你选择了 1. 账号登录  " << endl;
	char password[100];
	ofstream FILE;
	FILE.open("database.txt", ios::app); //如不存在则创建

	if (!FILE) {
		cout << "无法打开database.txt"
		     << endl;
		exit(1);
	}

	FILE.close();//over
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入您的学号，如：2100010101          ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "学号：";
	cin >> temp;

	ifstream FILE1("database.txt");//检查是否存在

	if (!FILE1) {
		cout << "无法打开database.txt"
		     << endl;
		FILE1.close();
		exit(1);
	}

	int op = 0;//判断账号是否存在

	while (!FILE1.eof()) {
		if (FILE1.read((char *)&st1, sizeof(account))) {
			if (strcmp(st1.username, temp) == 0) {
				op = 1;//存在
				break;
			}
		}
	}

	FILE1.close();

	if (op == 0) {//不存在
		cout << "该学号尚未注册，请先注册 " << endl;
		system("pause");


	} else if (op == 1) {//存在
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 请输入密码                              ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		cout << "密码：";
		cin >> password;
		getchar();

		if (strcmp(st1.password, password) == 0 ) {//密码正确
			strcpy(username, temp);
			system("cls");
			cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
			cout << "┃ 登陆成功！                              ┃" << endl;
			cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n";
			strcpy(userRealname, st1.name);//记录cookie
			strcpy(useracademy, st1.academy);//记录cookie
			system("pause");
			studentMenu();//跳转至学生菜单
		} else {//密码错误
			cout << "密码错误，请再次登录 " << endl;
			system("pause");
		}
	}
}


void studentReg() {//学生-注册
	account st, st1;
	system("cls");
	cout << "你选择了 2. 新生注册  " << endl;
	cout << endl;
	ofstream FILE;
	FILE.open("database.txt", ios::app); //如不存在则创建

	if (!FILE) {
		cout << "无法打开database.txt"
		     << endl;
		exit(1);
	}

	FILE.close();//over
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入您的姓名，例如：李华              ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "姓名：";
	cin.getline(name1, 100);
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入您的学号，例如：2000010101        ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "学号：";
	cin >> temp;
	getchar();
	ifstream FILE1("database.txt");//检查是否存在

	if (!FILE1) {
		cout << "无法打开database.txt"
		     << endl;
		exit(1);
	}

	int op = 0;//判断这个学号注册过没

	while (!FILE1.eof()) {
		if (FILE1.read((char *)&st1, sizeof(account))) {
			if (strcmp(st1.username, temp) == 0) {
				op = 1;//注册了
				cout << "这个学号已经注册了，请直接用密码登录。" << endl;
				system("pause");
				break;
			}
		}
	}

	FILE1.close();//over

	if (op == 0) {//没注册
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 请新建密码：密码不大于30位，不小于6位。 ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
		     << endl;
		cout << "新密码：";
		cin.getline(t, 1000);

		if (strlen(t) < 6 || strlen(t) > 30) {//基本保护，强制要求用户不使用随意的密码或容易遗忘的密码
			cout << "您设置的密码不安全，本次注册取消。" << endl;
			system("pause");

		} else {//密码合规
			cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
			cout << "┃ 请重复您刚才设置的密码。                ┃" << endl;
			cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
			     << endl;
			cout << "重复密码：";
			cin.getline(t1, 1000);//帮助用户记住自己的密码

			if (strcmp(t, t1) != 0) {
				cout << "两次密码不一致，注册取消……" << endl;
				system("pause");
			} else {//记住了
				strcpy(st.password, t);//存入st
				strcpy(st.name, name1);
				strcpy(st.username, temp);
				cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
				cout << "┃ 请输入您的学院名称，便于核查。          ┃" << endl;
				cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
				     << endl;
				cout << "学院：";
				cin >> st.academy;//记录学院
				system("cls");
				cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
				cout << "┃ 注册成功，已为您自动登录……            ┃" << endl;
				cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
				     << endl;//便利用户，注册后直接登录
				FILE.open("database.txt", ios::app); //在文件末尾二进制写入
				FILE.write((char *)&st, sizeof(account));
				FILE.close();//关闭
				strcpy(useracademy, st.academy);//cookie
				strcpy(userRealname, st.name);//cookie
				strcpy(username, st.username);//cookie
				system("pause");
				studentMenu();
			}
		}

	}
}

void studentMenu() {//学生菜单
	int n = 0;
	char s[1000];
	ke cshow;
	ifstream fcin;
	fcin.open("kecheng.txt");//检查课程库是否存在

	fcin.close();//关

	while (true) {
		system("cls");
		cout << "欢迎来自" << useracademy << "学院的" << userRealname << "，登录学号为" << username << endl;//必要的提示信息
		cout << endl;
		cout << "┍━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 欢迎您，同学！┃" << endl;
		cout << "┃ 1. 我要选课   ┃" << endl;
		cout << "┃ 2. 我要退课   ┃" << endl;
		cout << "┃ 3. 查看已选   ┃" << endl;
		cout << "┃ 4. 安全退出   ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━┛ \n" <<
		     endl;
		cout << endl;

		//直接看到现在有哪些课，还剩多少
		cout << "本学期开放选择的课程共 " << checkClassNum() << " 门，名称及剩余名额如下：" << endl;
		cout << endl;

		//功能：即刻查询实时人数
		int inthismax, inthisnow;//课程最大人数，课程当前人数
		ke cshow;
		fcin.open("kecheng.txt");

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "━━━━━━━━━━━";

		cout << endl;

		while (!fcin.eof()) {//读kecheng库
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //如果课程状态正常
				//cout << cshow.tag[0] << endl;
				if (strcmp(cshow.tag, "1") == 0)
					printf("%-10s ", cshow.name);
			}
		}

		cout << endl;
		fcin.close();
		fcin.open("kecheng.txt");

		while (!fcin.eof()) {//读kecheng库
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //如果课程状态正常
				if (strcmp(cshow.tag, "1") == 0) {
					//cout << cshow.tag[0] << endl;
					inthismax = atoi(cshow.maxnum);
					inthisnow = atoi(cshow.nownum);

					if (inthismax - inthisnow > 0)
						printf("%-10d ", inthismax - inthisnow);
					else {
						printf("已满/");
						printf("%-5d ", inthismax);
					}
				}

			}
		}

		fcin.close();
		cout << endl;

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "━━━━━━━━━━━";

		cout << endl;

		cout << "请输入数字选择功能 1/2/3/4: ";
		cin >> s;//输入功能选择
		getchar();
		n = 0;

		if (strlen(s) == 1 && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				selectClass();//学生-选课
				break;

			case 2:
				quitClass();//学生-退课
				break;

			case 3:
				checkMe();//学生-自查
				break;

			case 4:
				cout << "┍━━━━━━━━━━━━━━━┓ \n";
				cout << "┃ 安全退出成功  ┃" << endl;
				cout << "┃ 欢迎下次使用  ┃" << endl;
				cout << "┕━━━━━━━━━━━━━━━┛ \n" << endl;
				system("pause");
				exit(99);//退出程序
				break;

			default:
				break;
		}
	}
}

void selectClass() {
	char classname[1000];
	int status = 0;//0：初始/不存在
	char config[100];
	strcpy(config, username);
	strcat(config, ".txt");//形成【学号】.txt

	ofstream fcout;
	fcout.open(config, ios::app);  //按学生学号创建文件
	fcout.close();
	int count = 0;
	char cname[100];

	ke c, c1;//声明变量
	keUnit keunit, keunit1;
	userUnit userunit, userunit1;
	account st, st1;

	system("cls");
	cout << "你选择了 1. 我要选课 " << endl;
	cout << endl;
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入你想选择的课程名称                ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "课程名：";
	cin.getline(classname, 100);//输入选课的课程名
	//getchar();
	strcpy(cname, classname);
	strcat(cname, ".txt");//形成【课程名】.txt
	fcout.open(cname, ios::app);//按课程创建课程名单文件
	fcout.close();

	ifstream fcin;//检查课程库是否存在
	fcin.open("kecheng.txt");

	int inthismax, inthisnow;//判断课程的状态

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0 ) && (strcmp(c1.name, classname) == 0)) {
				//cout << c1.maxnum << " " << c1.nownum << endl;
				inthismax = atoi(c1.maxnum);
				inthisnow = atoi(c1.nownum);

				if (inthisnow < inthismax)
					status = 1;//1：可选
				else
					status = 2;//2：人满或超员

				break;
			}
		}
	}

	fcin.close();

	fcin.open(config);//读配置

	if (!fcin) {
		cout << "1154无法打开" << username << "的配置" << endl;
		exit(3);
	}

	while (!fcin.eof()) {
		if (fcin >> keunit1.name >> keunit1.tag) {
			//cout << "success:" << keunit.tag[0] << " " << keunit.name << endl;
			if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, classname) == 0)) {
				status = 3;//3：用户已经选了，不让用户再重复选
				break;
			}
		}
	}

	fcin.close();
	//cout << endl;
	//cout << status << endl;
	//system("pause");

	if (status == 0) {
		cout << endl;
		cout << "您输入的课程不存在……" << endl;
		remove(cname);
		system("pause");



	} else if (status == 1) {
		cout << endl;
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 选课成功！                              ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n" << endl;
		strcpy(keunit.name, classname);//传递
		strcpy(keunit.tag, "1");
		fcout.open(config, ios::app);

		if (!fcout) {
			cout << "无法写入" << username << "的配置" << endl;
			exit(3);
		}

		fcout << keunit.name << " " << keunit.tag << endl; //写入这个人的选课列表
		fcout.close();

		fstream f;
		f.open("kecheng.txt", ios::out | ios::in | ios::binary);

		while (!f.eof()) {
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
				//cout << c1.tag << " " << c1.name << endl;
				if ((strcmp(c1.name, classname) == 0) && (strcmp(c1.tag, "1") == 0)) {
					//原理同样是先删除后添加，形成按最后选的时间顺序排列课程
					//inthisnow = atoi(c1.nownum);
					//inthisnow = inthisnow + 1;
					//itoa(inthisnow, c1.nownum, 10);
					f << "0\n";
					break;
				}
			}
		}

		f.close();

		strcpy(c1.tag, "1");
		inthisnow = atoi(c1.nownum);//atoi，用于计算
		inthisnow = inthisnow + 1;//选择人数+1
		itoa(inthisnow, c1.nownum, 10);//转回去
		strcpy(c1.name, classname);

		//在课程文件末尾添加
		fcout.open("kecheng.txt", ios::app);
		fcout << c1.name << " " << c1.maxnum << " " << c1.nownum << " " << c1.tag << endl;
		fcout.close();//关闭

		fcout.open(cname, ios::app);//检查【课程名】.txt是否存在

		if (!fcout) {
			cout << "1231无法写入" << classname << "的配置。" << endl;
			exit(4);
		}

		strcpy(userunit.academy, useracademy);//cookie发挥作用
		strcpy(userunit.name, userRealname);
		strcpy(userunit.username, username);
		strcpy(userunit.tag, "1");
		fcout << userunit.name << " " << userunit.username << " " << userunit.academy << " " << userunit.tag << endl; //存入
		fcout.close();
		system("pause");

	} else if (status == 2) {
		cout << endl;
		cout << "课程人数已满，请选择其他课程" << endl;
		cout << endl;
		system("pause");



	} else if (status == 3) {
		cout << endl;
		cout << "你已经选过这门课了，请勿重复选择" << endl;
		cout << endl;
		system("pause");
	}
}

void quitClass() {//学生-退课
	char classname[1000];
	int status = 0;
	char config[100];
	strcpy(config, username);
	strcat(config, ".txt");

	ofstream fcout;
	fcout.open(config, ios::app);       //如果不存在则创建文件
	fcout.close();//关闭

	char cname[100];

	ke c, c1;
	keUnit keunit, keunit1;
	userUnit userunit, userunit1;
	account st, st1;

	system("cls");//清屏
	cout << "你选择了 2. 我要退课 " << endl;
	cout << endl;
	cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
	cout << "┃ 请输入你想退的课程名称                  ┃" << endl;
	cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n"
	     << endl;
	cout << "课程名：";
	cin.getline(classname, 100);
	getchar();
	strcpy(cname, classname);
	strcat(cname, ".txt");

	fcout.open(cname, ios::app);//同样是不存在则创建
	fcout.close();

	ifstream fcin;
	fcin.open("kecheng.txt");//检查课程库是否存在

	if (!fcin) {
		cout << "1297无法打开kecheng.txt"
		     << endl;
		exit(1);
	}

	int inthismax, inthisnow;

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0) && (strcmp(c1.name, classname) == 0)) {
				status = 1;//这个课在课程库存在 默认0
				break;
			}
		}
	}

	fcin.close();

	fcin.open(config);

	if (!fcin) {
		cout << "1318无法打开" << username << "的配置" << endl;
		exit(3);
	}

	while (!fcin.eof()) {
		//cout << "mudamudamudamuda";
		if (fcin >> keunit1.name >> keunit1.tag) {
			if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, classname) == 0)) {
				status = 3;//这个课存在并且确实被选了，这样才能退课
				break;
			}
		}
	}

	fcin.close();

	//cout << "status::" << status << endl;

	if (status == 0) {//课不存在
		cout << endl;
		cout << "您输入的课程不存在……" << endl;
		remove(cname);
		system("pause");



	} else if (status == 3) {
		cout << endl;
		cout << "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n";
		cout << "┃ 退课完成！                              ┃" << endl;
		cout << "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n" << endl;
		strcpy(keunit.name, classname);

		fstream f;
		f.open(config, ios::in | ios::out | ios::binary);

		if (!f) {
			cout << "1355无法写入" << username << "的配置" << endl;
			exit(3);
		}

		while (!f.eof()) {
			if (f >> keunit1.name >> keunit1.tag) {
				if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, classname) == 0)) {
					//删除
					f << "0\n";
					break;
				}
			}
		}

		f.close();//关闭

		f.open("kecheng.txt", ios::out | ios::in | ios::binary);

		if (!f) {
			cout << "1374没打开" << endl;
			exit(9);
		}

		while (!f.eof()) {
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
				if ((strcmp(c1.name, classname) == 0) && (strcmp(c1.tag, "1") == 0) ) {
					//cout << "yesyesyesyesyes";
					f << "0\n"; //删除
					break;
				}
			}
		}

		f.close();//关闭
		strcpy(c1.tag, "1");
		inthisnow = atoi(c1.nownum) - 1;//atoi便于计算，退课后选课人数-1
		//cout << endl << inthisnow << endl;
		itoa(inthisnow, c1.nownum, 10);//itoa便于储存

		fcout.open("kecheng.txt", ios::app);//在文件末尾写入
		fcout << c1.name << " " << c1.maxnum << " " << c1.nownum << " " << c1.tag << endl;
		fcout.close();



		//fstream FILECLASS;//对课程人数表
		f.open(cname, ios::in | ios::out | ios::binary);

		if (!f) {
			cout << "1405无法写入" << classname << "的配置。" << endl;
			exit(4);
		}

		while (!f.eof()) {
			if (f >> userunit1.name >> userunit1.username >> userunit1.academy >> userunit1.tag) {
				//cout << userunit1.name << " " << userunit1.tag << endl;
				if ((strcmp(userunit1.username, username) == 0) && (strcmp(userunit1.tag, "1") == 0)) {
					//删除
					f << "0\n";
					//cout << "改后：" << userunit1.name << " " << userunit1.tag << endl;
					break;
				}
			}
		}

		f.close();//关闭
		//cout << "选课人数:" << checkUserNum(cname) << endl;
		//if (checkUserNum(cname) == 0)
		//	remove(cname);
		system("pause");



	} else if (status == 1) {
		cout << endl;
		cout << "你还没选这门课程……" << endl;
		cout << endl;
		system("pause");
	}
}

void checkMe() {//学生-自查
	system("cls");
	int a[1000];
	char config[100];
	int cnt = 3, cnt1 = 3;//计数器
	ke c1;
	keUnit keunit1;
	strcpy(config, username);
	strcat(config, ".txt");

	ofstream fcout;
	fcout.open(config, ios::app);//不存在则创建
	fcout.close();

	a[0] = strlen(username);
	a[1] = strlen(userRealname);
	a[2] = strlen(useracademy);

	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

	for (int i = 1; i <= checkClassNum(); i++)
		cout << "━━━━━━━━━━━";

	cout << endl;
	printf("序号  %-10s ", "学号"); //序号5 学号10
	printf("%-10s %-10s ", "姓名", "学院");//姓名10 学院10

	ifstream fcin;//创建流
	fcin.open("kecheng.txt");//检查课程库是否存在

	if (!fcin) {
		cout << "1204无法读kecheng的配置" << endl;
		exit(1);
	}

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0) && (atoi(c1.maxnum) > 0)) {
				a[cnt] = strlen(c1.name);
				printf("%-10s ", c1.name);//表格第一排
				cnt++;
			}
		}
	}

	cout << endl;
	fcin.close();
	printf("1     %-10s %-10s %-10s ", username, userRealname, useracademy);//第二排

	fcin.open("kecheng.txt");
	int op(0);
	ifstream ffcin;

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0) && (atoi(c1.maxnum) > 0)) {//每一个正常状态的课程
				op = 0;
				ffcin.open(config);

				//cout << c1.name << endl;
				while (!ffcin.eof()) {
					if (ffcin >> keunit1.name >> keunit1.tag) {
						if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, c1.name) == 0)) {
							op = 1;
							break;
						}
					}
				}

				if (op == 0) {
					printf("%-10s ", "n");//表格第二排，没选
					cnt1++;
				} else if (op == 1) {
					printf("%-10s ", "y");//选了
					cnt1++;
				}

				op = 0;
				ffcin.close();
			}
		}
	}

	cout << endl;
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

	for (int i = 1; i <= checkClassNum(); i++)
		cout << "━━━━━━━━━━━";

	cout << endl;
	fcin.close();//关闭
	system("pause");
}

