//ѡ��ϵͳ 2.0.0 ����1.0.0��д�˽�50%�Ĵ��룬�ص��Ǹ���������Ϊ��ͨ�ļ���д���������벿�ֱ��������ƶ�д
//��Ŀ��ַ��https://github.com/ColdTearsYY/PKUClassSystem
//��ӭ�ύ issue

#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int sumClass;//�ж��ٽڿ�
char t[1000], t1[1000], name1[100], temp[100]; //ͨ����ʱ����

struct account {
	char name[100];
	char username[100];
	char academy[100];
	char password[100];
};//����database.txt���˺�Ԫ�ؽṹ��

struct ke {
	char name[100];
	char maxnum[100];
	char nownum[100];
	char tag[50] ;
};//�γ̿�kecheng.txt��Ԫ�أ���γ���Ϣ

struct keUnit {
	char name[100];
	char tag[50] ;
};//��ѧ�š�.txt����ģ�ÿ����ѡ�Ŀε�Ԫ�أ���ÿ����ѡ�Ŀ�

struct userUnit {
	char name[100];
	char username[100];
	char academy[100];
	char tag[50] ;
};//���γ�����.txt����ģ���Ԫ�أ����ڿΣ���¼����ѡ����ε���

int checkClassNum() {//��������
	ke cshow;
	sumClass = 0;//����������0
	ifstream fcin("kecheng.txt");//����ļ��Ƿ����

	if (!fcin) {
		cout << "��ʱ��û�пγ�" << endl;
		fcin.close();
		//exit(1);
		return 0;//�����ھ���0��
	} else {
		while (!fcin.eof()) {
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) {
				if ((strcmp(cshow.tag, "1") == 0) && (atoi(cshow.maxnum) != 0)) { //�γ�״̬����+���������=0
					sumClass++;//������+1
				}
			}
		}

		fcin.close();//�ر��ļ�
		return sumClass;//�����ж��ٽڿ�
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

void teacher();//��ʦһ��
void teacherLogin();//��ʦ��¼
void student();//ѧ��һ��
void studentLogin();//ѧ����¼
void studentReg();//ѧ��ע��
void studentMenu();//ѧ���˵�
void mainMenu();//���˵���ͬmain�����ڷ���
void teacherMenu();//��ʦ�˵�

void addClass();//��ʦ-�ӿ�
void delClass();//��ʦ-ɾ��
void modifyClass();//��ʦ-���ÿγ�
void checkAll();//��ʦ-���ĳĳ�ε���ѡ

void selectClass();//ѧ��-ѡ��
void quitClass();//ѧ��-�˿�
void checkMe();//ѧ��-�Բ�

int main() {
	int n = 0;
	char s[1000];//������

	ofstream KECHENG;//����kecheng��
	KECHENG.open("kecheng.txt", ios::app);
	KECHENG.close();

	while (n != 3) {
		system("cls");
		cout << "�������������������������������������������������� \n";
		cout << "�� ��ӭʹ�ñ�����ѧ      ��" << endl;
		cout << "�� ѡ��ϵͳʦ��ͳһ��    ��" << endl;
		cout << "��                       ��" << endl;
		cout << "�� 1. ���ǽ���           ��" << endl;
		cout << "�� 2. ����ѧ��           ��" << endl;
		cout << "�� 3. �˳�               ��" << endl;
		cout << "�������������������������������������������������� \n" << endl;
		cout << "����������ѡ���� 1/2/3: " ;
		cin >> s;//����ѡ��

		//getchar();
		if ((strlen(s) == 1) && isdigit(s[0])) //��������Ƿ�Ϸ�
			n = s[0] - '0';//�Ϸ���ֵ

		switch (n) {
			case 1:
				teacher();//����ʦһ��
				break;

			case 2:
				student();//��ѧ��һ��
				break;

			case 3:
				exit(2);//�˳�

			default:
				break;//���������壬�ȴ���ȷ����
		}
	}

	return 0;
}

void mainMenu() {//ͬ��int main����׸��
	int n = 0;
	char s[1000];

	while (n != 3) {
		system("cls");
		cout << "�������������������������������������������������� \n";
		cout << "�� ��ӭʹ�ñ�����ѧ      ��" << endl;
		cout << "�� ѡ��ϵͳʦ��ͳһ��    ��" << endl;
		cout << "��                       ��" << endl;
		cout << "�� 1. ���ǽ���           ��" << endl;
		cout << "�� 2. ����ѧ��           ��" << endl;
		cout << "�� 3. �˳�               ��" << endl;
		cout << "�������������������������������������������������� \n" << endl;
		cout << "����������ѡ���� 1/2/3: " ;
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

void teacher() {//��ʦһ��
	int n = 0;//ѡ��������0
	char s[1000];//���ڴ�������

	while (true) {
		system("cls");//����
		cout << "���������������������������������� \n";
		cout << "�� ��ӭ�������񣡩�" << endl;
		cout << "��               ��" << endl;
		cout << "�� 1. ��¼ϵͳ   ��" << endl;
		cout << "�� 2. �����ϼ�   ��" << endl;
		cout << "���������������������������������� \n" << endl;
		cout << "����������ѡ���� 1/2: " ;
		cin >> s;
		getchar();//��������

		if ((strlen(s) == 1) && isdigit(s[0])) //���Ϸ�
			n = s[0] - '0';

		switch (n) {
			case 1:
				teacherLogin();//��ת��ʦ��¼
				break;

			case 2:
				mainMenu();//�������˵�
				break;

			default:
				break;//����������
		}
	}
}

void teacherLogin() {//��ʦ-��¼
	char key[] = "@2022";//����
	char keyIn[10000];
	char back[] = "back";
	char exit0[] = "exit";

	while (true) {
		system("cls");
		cout << "���������������������������������� \n";
		cout << "�� ����������    ��" << endl;
		cout << "�� ����back����  ��" << endl;
		cout << "�� ����exit�˳�  ��" << endl;
		cout << "���������������������������������� \n" << endl;
		cout << "���룺";
		cin.getline(keyIn, 10000);//��������

		if (strcmp(keyIn, key) == 0) {//������ȷ
			system("cls");
			cout << "���������������������������������� \n";
			cout << "�� ��½�ɹ���    ��" << endl;
			cout << "���������������������������������� \n" << endl;
			system("pause");
			teacherMenu();
			break;
		} else if (strcmp(keyIn, back) == 0) {
			break;//�����ϼ�
		} else if (strcmp(keyIn, exit0) == 0) {
			exit(0);//�˳�����
			break;
		} else {
			system("cls");//����
			cout << "���������������������������������� \n";
			cout << "�� �������    ��" << endl;
			cout << "�� ���ٴγ���    ��" << endl;
			cout << "���������������������������������� \n" << endl;
			system("pause");
		}
	}
}

void teacherMenu() {//��ʦ�˵�
	int n = 0;
	char s[1000];

	while (true) {
		system("cls");
		cout << "���������������������������������� \n";
		cout << "�� �������ѵ�¼��" << endl;
		cout << "�� ��ѡ����    ��" << endl;
		cout << "�� 1. ��ӿγ�   ��" << endl;
		cout << "�� 2. ɾ���γ�   ��" << endl;
		cout << "�� 3. �޸Ŀγ�   ��" << endl;
		cout << "�� 4. �鿴���   �� " << endl;
		cout << "�� 5. �˳���¼   ��" << endl;
		cout << "���������������������������������� \n" <<
		     endl;
		cout << "��ѧ�ڿ���ѡ��Ŀγ̹� " << checkClassNum() << " �ţ����Ƽ�ʣ���������£�" << endl;
		cout << endl;
		ifstream fcin;
		fcin.open("kecheng.txt");//���kecheng���Ƿ����
		//���ӹ��ܣ����̲�ѯʵʱ����
		int inthismax, inthisnow;//�γ�����������γ̵�ǰ����
		ke cshow;

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "����������������������";

		cout << endl;

		while (!fcin.eof()) {//��kecheng��
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //����γ�״̬����
				//cout << cshow.tag[0] << endl;
				if (strcmp(cshow.tag, "1") == 0)
					printf("%-10s ", cshow.name);
			}
		}

		cout << endl;
		fcin.close();
		fcin.open("kecheng.txt");

		while (!fcin.eof()) {//��kecheng��
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //����γ�״̬����
				//cout << cshow.tag[0] << endl;
				if (strcmp(cshow.tag, "1") == 0) {
					inthismax = atoi(cshow.maxnum);
					inthisnow = atoi(cshow.nownum);

					if (inthismax - inthisnow > 0)
						printf("%-10d ", inthismax - inthisnow);
					else {
						printf("����/");
						printf("%-5d ", inthismax);
					}
				}

			}
		}

		fcin.close();
		cout << endl;

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "����������������������";

		cout << endl;
		n = 0;
		cout << "������������ѡ���� 1/2/3/4/5: ";
		cin >> s;//���빦��ѡ��

		if ((strlen(s) == 1) && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				addClass();//ȥ�ӿ�
				break;

			case 2:
				delClass();//ȥɾ��
				break;

			case 3:
				modifyClass();//ȥ����
				break;

			case 4:
				checkAll();//��ĳĳ��˭ѡ��
				break;

			case 5:
				cout << "���������������������������������� \n";
				cout << "�� ��ȫ�˳��ɹ�  ��" << endl;
				cout << "�� ��ӭ�´�ʹ��  ��" << endl;
				cout << "���������������������������������� \n" << endl;
				system("pause");
				exit(9);//�˳�����
				break;

			default:
				break;
		}
	}
}

char kename[100];//�ɶ��ʹ�õ���ʱ����
void addClass() {
	ke c, c1;//��������
	system("cls");//����
	cout << "��ѡ���� 1. ��ӿγ�  " << endl;
	cout << "�������������������������������������������������������������������������������������������� \n";
	cout << "�� ������γ�����                             ��" << endl;
	cout << "�������������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "�γ����ƣ�";
	cin >> kename;//����

	ofstream fcout;
	fcout.open("kecheng.txt", ios::app); //�������򴴽�
	fcout.close();//����FILE

	ifstream fcin("kecheng.txt", ios::in); //��������

	int op = 0;//�ж�����������

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if (strcmp(c1.name, kename) == 0 && strcmp(c1.tag, "1") == 0) { //����γ��ظ�
				cout << endl;
				cout << "�ÿγ��Ѵ��ڣ��޷��ظ����" << endl;
				cout << endl;
				op = 1;
				system("pause");
				break;
			}
		}
	}

	fcin.close();//�ر�

	if (op == 0) {//�������û�ظ�
		strcpy(c.name, kename);
		cout << "�������������������������������������������������������������������������������������������� \n";
		cout << "�� ������γ̼ƻ���������ȡ�����������-1     ��" << endl;
		cout << "�������������������������������������������������������������������������������������������� \n"
		     << endl;
		cout << "����ƻ�������";
		cin >> c.maxnum;//����ƻ�����

		if (!isdigit(c.maxnum[0])) {//���Լ�������Ƿ�Ϸ�
			cout << "\n��������Ƿ�����ӿγ�ȡ��" << endl;
			system("pause");
			return;
		}

		strcpy(c.nownum, "0") ;//�¿Σ���ǰѡ��������ȻĬ����0
		strcpy(c.tag, "1"); //״̬Ϊ1������
		fcout.open("kecheng.txt", ios::app); //�򿪿γ̿���ĩβд�������

		fcout << c.name << " " << c.maxnum << " " << c.nownum << " " << c.tag << endl; //д
		fcout.close();//�ر�FILE
		cout << "\n�γ� " << kename << " �Ѿ��ɹ����" << endl;//������Ϣ
		system("pause");
	}
}

void delClass() {//��ʦ-ɾ��
	ke c, c1;
	int confirm = 0;//ɾ��ǰ��Ҫȷ��
	system("cls");
	cout << "��ѡ���� 2. ɾ���γ�  " << endl;
	cout << endl;

	if (checkClassNum() == 0) {
		cout << "�������������������������������������������������������������������������������������������� \n";
		cout << "�� ��ǰ���޿γ̣�����ɾ���γ�                 ��" << endl;
		cout << "�������������������������������������������������������������������������������������������� \n"
		     << endl;
		remove("kecheng.txt");
		ofstream fcout;
		fcout.open("kecheng.txt", ios::app);
		fcout.close();
		system("pause");
		return;
	}

	cout << "�������������������������������������������������������������������������������������������� \n";
	cout << "�� ������Ҫɾ���Ŀγ�����                     ��" << endl;
	cout << "�������������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "�γ����ƣ�";
	cin >> kename;
	ofstream fcout;
	fcout.open("kecheng.txt", ios::app); //���kecheng���Ƿ����


	fcout.close();//over
	ifstream fcin("kecheng.txt"); //��������

	int op = 0;//�ж�Ҫɾ�Ŀ��Ƿ����

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			//cout << c1.name << " " << c1.tag << endl;!!!
			if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0)) {
				op = 1;//����
				break;
			}
		}
	}

	fcin.close();//over

	if (op == 0 ) {//������
		cout << endl;
		cout << "�ÿγ̲����ڣ�����" << endl;
		cout << endl;
		system("pause");
	} else if (op == 1) {//����
		confirm = 0;
		cout << endl;
		cout << "�������������������������������������������������������������������������������������������� \n";
		cout << "�� ȷ��Ҫɾ��������1ȷ�ϣ��������ַ���      ��" << endl;
		cout << "�������������������������������������������������������������������������������������������� \n"
		     << endl;
		cout << "ȷ�ϣ�";
		cin >> confirm;//ȷ���Ƿ�ɾ

		//cout << confirm << endl;
		if (confirm == 1) {//���Ҫɾ
			fcout.open("kecheng.txt", ios::app); //���kecheng���Ƿ����

			fcout.close();
			fstream f;
			f.open("kecheng.txt", ios::in | ios::out | ios::binary); //�ļ����������

			while (!f.eof()) {
				if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
					if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0)) {
						f << "0\n";
						break;
					}
				}
			}


			f.close();//�ر��ļ�
			cout << kename << " ɾ�����" << endl;

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


void modifyClass() {//��ʦ-�Ŀ�
	ke c, c1;
	system("cls");
	cout << "��ѡ���� 3. �޸Ŀγ�  " << endl;
	cout << "�������������������������������������������������������������������������������������������� \n";
	cout << "�� ������Ҫ�޸ĵĿγ�����                     ��" << endl;
	cout << "�������������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "�γ����ƣ�";
	cin >> kename;
	getchar();
	ofstream fcout;
	fcout.open("kecheng.txt", ios::app); //���������򴴽�kecheng��
	fcout.close();
	ifstream fcin;
	fcin.open("kecheng.txt");

	int op = 0;//�ж�Ҫ�޸ĵĿγ��Ƿ����

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0)) {
				op = 1;//����
				break;
			}
		}
	}

	fcin.close();//over

	if (op == 0 ) {//������
		cout << endl;
		cout << "�ÿγ̲����ڡ��� " << endl;
		cout << endl;
		system("pause");


	} else if (op == 1) {//����
		cout << endl;
		cout << "�������������������������������������������������������������������������������������������� \n";
		cout << "�� ��Ҫ�޸Ŀγ�����Ϊ��                       ��" << endl;
		cout << "�������������������������������������������������������������������������������������������� \n"
		     << endl;
		cout << "���������ƣ�";
		cin >> c.name;//����������
		getchar();//��������

		fstream f;//���γ̿��Ƿ����
		f.open("kecheng.txt", ios::in | ios::out | ios::binary);

		while (!f.eof()) {//��
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) { //һ��һ����
				if ((strcmp(c1.name, c.name) == 0) && (strcmp(kename, c.name) != 0)
				        && (strcmp(c1.tag, "1") == 0))  { //��֤�����޸��Լ�������ͬʱ�������ͬ���γ�
					cout << "ͬ���γ��Ѵ��ڣ�����ʧ�ܣ�" << endl;//������ʾ
					system("pause");
					f.close();//�ر�
					return;
					break;
				}
			}
		}

		f.close();//�ر�

		cout << "�������������������������������������������������������������������������������������������� \n";
		cout << "�� ��Ҫ�޸Ŀγ��������Ϊ����ȡ��������-1��   ��" << endl;
		cout << "�������������������������������������������������������������������������������������������� \n"
		     << endl;
		cout << "���������";
		cin >> c.maxnum;//����Ҫ�ĵ������������������������������ѡ����������ʵ��ʹ��ϰ�ߣ������������������ѡ����ʱ�������ᱣ֤�γ̿��˲�����ѡ
		getchar();//��������

		if (!isdigit(c.maxnum[0])) {//���Լ��������ǲ��ǺϷ�
			cout << "��������Ƿ�����ӿγ�ȡ��" << endl;
			system("pause");
			return;
		}

		strcpy(c.nownum, c1.nownum);//�̳пγ���ѡ����
		strcpy(c.tag, "1"); //��ʼ��״̬

		f.open("kecheng.txt", ios::in | ios::out | ios::binary);

		while (!f.eof()) {
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
				if ((strcmp(c1.name, kename) == 0) && (strcmp(c1.tag, "1") == 0) ) { //״̬����
					f << "1\n";
					break;
				}
			}
		}

		f.close();

		fcout.open("kecheng.txt", ios::app); //д

		fcout << c.name << " " << c.maxnum << " " << c.nownum << " " << c.tag << endl; //�ļ�ĩβ������д��
		fcout.close();

		if (strcmp(kename, c.name) == 0) {
			cout << "�ѽ�" << kename << " �޸�Ϊ " << c.name << "���γ���������Ϊ" << c.maxnum << "�ˡ�" << endl; //������Ϣ
			system("pause");
			return;
		}

		//fcin
		//fstream FILECHECK;
		//fcout
		strcpy(t, kename);
		strcat(t, ".txt");//����������
		userUnit userunit;
		keUnit keunit;
		fcin.open(t);

		if (fcin) {
			while (!fcin.eof()) {
				if (fcin >> userunit.name >> userunit.username >> userunit.academy >> userunit.tag) { //��ѧ�����б���������
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

		cout << "�ѽ�" << kename << " �޸�Ϊ " << c.name << "���γ���������Ϊ" << c.maxnum << "�ˡ�" << endl; //������Ϣ
		system("pause");
	}

}


void checkAll() {//��ʦ-���ĳĳ��ѡ�����
	system("cls");
	char s[1000];
	ke c1;
	userUnit userunit1;
	cout << "��ѡ���� 4. �鿴���  " << endl;
	cout << "�������������������������������������������������������������������������������������������� \n";
	cout << "�� ��������Ҫ��Ŀγ�����                     ��" << endl;
	cout << "�������������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "�γ����ƣ�";
	cin >> s;
	//system("cls");
	cout << endl;
	char filename[1000];
	strcpy(filename, s);
	strcat(filename, ".txt");
	ofstream fcout;
	fcout.open(filename, ios::app); //�粻�����򴴽�
	fcout.close();

	ifstream fcin;
	fcin.open("kecheng.txt");
	int op = 0;//�ж�Ҫ��Ŀ��Ƿ����

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			//cout << c1.name << " " << c1.tag << endl;
			if ((strcmp(c1.name, s) == 0) && (strcmp(c1.tag, "1") == 0)) {
				op = 1;//����
				break;
			}
		}
	}

	fcin.close();//over

	if (op == 0 ) {//������
		cout << endl;
		cout << "�ÿγ̲����ڣ�����" << endl;
		cout << endl;
		system("pause");


	} else if (op == 1) {//����
		fcin.open(filename);
		int cnt = 1;
		printf("��������������������������������������������������������������������������������\n");
		printf("���  ѧ��       ����       ѧԺ      \n");//���5 ѧ��10 ����10 ѧԺ10

		while (!fcin.eof()) {
			if (fcin >> userunit1.name >> userunit1.username >> userunit1.academy >> userunit1.tag) {
				if ((strcmp(userunit1.tag, "1") == 0)) {
					printf("%-5d %-10s %-10s %-10s\n", cnt, userunit1.username, userunit1.name, userunit1.academy);
					cnt++;
				}
			}
		}

		if (cnt == 1)
			cout << "\n#��ʱ����ѡ���ſ���#\n\n";

		printf("��������������������������������������������������������������������������������\n");
		cout << endl;
		system("pause");
	}
}


void student() {//ѧ��һ��
	int n = 0;
	char s[1000];

	while (true) {
		system("cls");
		cout << "���������������������������������� \n";
		cout << "�� ��ӭ����ͬѧ����" << endl;
		cout << "��               ��" << endl;
		cout << "�� 1. �˺ŵ�½   ��" << endl;
		cout << "�� 2. ����ע��   ��" << endl;
		cout << "�� 3. �����ϼ�   ��" << endl;
		cout << "���������������������������������� \n" <<
		     endl;
		cout << "����������ѡ���� 1/2/3/4: ";
		cin >> s;//����ѡ��
		getchar();

		if ((strlen(s) == 1) && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				system("cls");//��ʾ�û�������˽
				cout << "�������������������������������������������������������������������������������������������� \n";
				cout << "�� ������ת������ͳһ��֤ϵͳ����ע����˽��ȫ ��" <<
				     endl;
				cout << "�������������������������������������������������������������������������������������������� \n"
				     << endl;
				system("pause");
				studentLogin();
				break;

			case 2:
				system("cls");//��ʾ�û�������˽
				cout << "�������������������������������������������������������������������������������������������� \n";
				cout << "�� ������ת������ͳһ��֤ϵͳ����ע����˽��ȫ ��" <<
				     endl;
				cout << "�������������������������������������������������������������������������������������������� \n"
				     << endl;
				system("pause");
				studentReg();
				break;

			case 3:
				mainMenu();//����
				break;

			default:
				break;//����������
		}
	}
}

char username[100];//��¼cookie����¼ѧ��
char useracademy[100];//��¼cookie����¼ѧԺ
char userRealname[100];//��¼cookie����¼����

void studentLogin() {//ѧ��-��¼
	account st1;
	system("cls");
	cout << "��ѡ���� 1. �˺ŵ�¼  " << endl;
	char password[100];
	ofstream FILE;
	FILE.open("database.txt", ios::app); //�粻�����򴴽�

	if (!FILE) {
		cout << "�޷���database.txt"
		     << endl;
		exit(1);
	}

	FILE.close();//over
	cout << "�������������������������������������������������������������������������������������� \n";
	cout << "�� ����������ѧ�ţ��磺2100010101          ��" << endl;
	cout << "�������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "ѧ�ţ�";
	cin >> temp;

	ifstream FILE1("database.txt");//����Ƿ����

	if (!FILE1) {
		cout << "�޷���database.txt"
		     << endl;
		FILE1.close();
		exit(1);
	}

	int op = 0;//�ж��˺��Ƿ����

	while (!FILE1.eof()) {
		if (FILE1.read((char *)&st1, sizeof(account))) {
			if (strcmp(st1.username, temp) == 0) {
				op = 1;//����
				break;
			}
		}
	}

	FILE1.close();

	if (op == 0) {//������
		cout << "��ѧ����δע�ᣬ����ע�� " << endl;
		system("pause");


	} else if (op == 1) {//����
		cout << "�������������������������������������������������������������������������������������� \n";
		cout << "�� ����������                              ��" << endl;
		cout << "�������������������������������������������������������������������������������������� \n"
		     << endl;
		cout << "���룺";
		cin >> password;
		getchar();

		if (strcmp(st1.password, password) == 0 ) {//������ȷ
			strcpy(username, temp);
			system("cls");
			cout << "�������������������������������������������������������������������������������������� \n";
			cout << "�� ��½�ɹ���                              ��" << endl;
			cout << "�������������������������������������������������������������������������������������� \n";
			strcpy(userRealname, st1.name);//��¼cookie
			strcpy(useracademy, st1.academy);//��¼cookie
			system("pause");
			studentMenu();//��ת��ѧ���˵�
		} else {//�������
			cout << "����������ٴε�¼ " << endl;
			system("pause");
		}
	}
}


void studentReg() {//ѧ��-ע��
	account st, st1;
	system("cls");
	cout << "��ѡ���� 2. ����ע��  " << endl;
	cout << endl;
	ofstream FILE;
	FILE.open("database.txt", ios::app); //�粻�����򴴽�

	if (!FILE) {
		cout << "�޷���database.txt"
		     << endl;
		exit(1);
	}

	FILE.close();//over
	cout << "�������������������������������������������������������������������������������������� \n";
	cout << "�� �������������������磺�              ��" << endl;
	cout << "�������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "������";
	cin.getline(name1, 100);
	cout << "�������������������������������������������������������������������������������������� \n";
	cout << "�� ����������ѧ�ţ����磺2000010101        ��" << endl;
	cout << "�������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "ѧ�ţ�";
	cin >> temp;
	getchar();
	ifstream FILE1("database.txt");//����Ƿ����

	if (!FILE1) {
		cout << "�޷���database.txt"
		     << endl;
		exit(1);
	}

	int op = 0;//�ж����ѧ��ע���û

	while (!FILE1.eof()) {
		if (FILE1.read((char *)&st1, sizeof(account))) {
			if (strcmp(st1.username, temp) == 0) {
				op = 1;//ע����
				cout << "���ѧ���Ѿ�ע���ˣ���ֱ���������¼��" << endl;
				system("pause");
				break;
			}
		}
	}

	FILE1.close();//over

	if (op == 0) {//ûע��
		cout << "�������������������������������������������������������������������������������������� \n";
		cout << "�� ���½����룺���벻����30λ����С��6λ�� ��" << endl;
		cout << "�������������������������������������������������������������������������������������� \n"
		     << endl;
		cout << "�����룺";
		cin.getline(t, 1000);

		if (strlen(t) < 6 || strlen(t) > 30) {//����������ǿ��Ҫ���û���ʹ��������������������������
			cout << "�����õ����벻��ȫ������ע��ȡ����" << endl;
			system("pause");

		} else {//����Ϲ�
			cout << "�������������������������������������������������������������������������������������� \n";
			cout << "�� ���ظ����ղ����õ����롣                ��" << endl;
			cout << "�������������������������������������������������������������������������������������� \n"
			     << endl;
			cout << "�ظ����룺";
			cin.getline(t1, 1000);//�����û���ס�Լ�������

			if (strcmp(t, t1) != 0) {
				cout << "�������벻һ�£�ע��ȡ������" << endl;
				system("pause");
			} else {//��ס��
				strcpy(st.password, t);//����st
				strcpy(st.name, name1);
				strcpy(st.username, temp);
				cout << "�������������������������������������������������������������������������������������� \n";
				cout << "�� ����������ѧԺ���ƣ����ں˲顣          ��" << endl;
				cout << "�������������������������������������������������������������������������������������� \n"
				     << endl;
				cout << "ѧԺ��";
				cin >> st.academy;//��¼ѧԺ
				system("cls");
				cout << "�������������������������������������������������������������������������������������� \n";
				cout << "�� ע��ɹ�����Ϊ���Զ���¼����            ��" << endl;
				cout << "�������������������������������������������������������������������������������������� \n"
				     << endl;//�����û���ע���ֱ�ӵ�¼
				FILE.open("database.txt", ios::app); //���ļ�ĩβ������д��
				FILE.write((char *)&st, sizeof(account));
				FILE.close();//�ر�
				strcpy(useracademy, st.academy);//cookie
				strcpy(userRealname, st.name);//cookie
				strcpy(username, st.username);//cookie
				system("pause");
				studentMenu();
			}
		}

	}
}

void studentMenu() {//ѧ���˵�
	int n = 0;
	char s[1000];
	ke cshow;
	ifstream fcin;
	fcin.open("kecheng.txt");//���γ̿��Ƿ����

	fcin.close();//��

	while (true) {
		system("cls");
		cout << "��ӭ����" << useracademy << "ѧԺ��" << userRealname << "����¼ѧ��Ϊ" << username << endl;//��Ҫ����ʾ��Ϣ
		cout << endl;
		cout << "���������������������������������� \n";
		cout << "�� ��ӭ����ͬѧ����" << endl;
		cout << "�� 1. ��Ҫѡ��   ��" << endl;
		cout << "�� 2. ��Ҫ�˿�   ��" << endl;
		cout << "�� 3. �鿴��ѡ   ��" << endl;
		cout << "�� 4. ��ȫ�˳�   ��" << endl;
		cout << "���������������������������������� \n" <<
		     endl;
		cout << endl;

		//ֱ�ӿ�����������Щ�Σ���ʣ����
		cout << "��ѧ�ڿ���ѡ��Ŀγ̹� " << checkClassNum() << " �ţ����Ƽ�ʣ���������£�" << endl;
		cout << endl;

		//���ܣ����̲�ѯʵʱ����
		int inthismax, inthisnow;//�γ�����������γ̵�ǰ����
		ke cshow;
		fcin.open("kecheng.txt");

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "����������������������";

		cout << endl;

		while (!fcin.eof()) {//��kecheng��
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //����γ�״̬����
				//cout << cshow.tag[0] << endl;
				if (strcmp(cshow.tag, "1") == 0)
					printf("%-10s ", cshow.name);
			}
		}

		cout << endl;
		fcin.close();
		fcin.open("kecheng.txt");

		while (!fcin.eof()) {//��kecheng��
			if (fcin >> cshow.name >> cshow.maxnum >> cshow.nownum >> cshow.tag) { //����γ�״̬����
				if (strcmp(cshow.tag, "1") == 0) {
					//cout << cshow.tag[0] << endl;
					inthismax = atoi(cshow.maxnum);
					inthisnow = atoi(cshow.nownum);

					if (inthismax - inthisnow > 0)
						printf("%-10d ", inthismax - inthisnow);
					else {
						printf("����/");
						printf("%-5d ", inthismax);
					}
				}

			}
		}

		fcin.close();
		cout << endl;

		for (int i = 1; i <= checkClassNum(); i++)
			cout << "����������������������";

		cout << endl;

		cout << "����������ѡ���� 1/2/3/4: ";
		cin >> s;//���빦��ѡ��
		getchar();
		n = 0;

		if (strlen(s) == 1 && isdigit(s[0]))
			n = s[0] - '0';

		switch (n) {
			case 1:
				selectClass();//ѧ��-ѡ��
				break;

			case 2:
				quitClass();//ѧ��-�˿�
				break;

			case 3:
				checkMe();//ѧ��-�Բ�
				break;

			case 4:
				cout << "���������������������������������� \n";
				cout << "�� ��ȫ�˳��ɹ�  ��" << endl;
				cout << "�� ��ӭ�´�ʹ��  ��" << endl;
				cout << "���������������������������������� \n" << endl;
				system("pause");
				exit(99);//�˳�����
				break;

			default:
				break;
		}
	}
}

void selectClass() {
	char classname[1000];
	int status = 0;//0����ʼ/������
	char config[100];
	strcpy(config, username);
	strcat(config, ".txt");//�γɡ�ѧ�š�.txt

	ofstream fcout;
	fcout.open(config, ios::app);  //��ѧ��ѧ�Ŵ����ļ�
	fcout.close();
	int count = 0;
	char cname[100];

	ke c, c1;//��������
	keUnit keunit, keunit1;
	userUnit userunit, userunit1;
	account st, st1;

	system("cls");
	cout << "��ѡ���� 1. ��Ҫѡ�� " << endl;
	cout << endl;
	cout << "�������������������������������������������������������������������������������������� \n";
	cout << "�� ����������ѡ��Ŀγ�����                ��" << endl;
	cout << "�������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "�γ�����";
	cin.getline(classname, 100);//����ѡ�εĿγ���
	//getchar();
	strcpy(cname, classname);
	strcat(cname, ".txt");//�γɡ��γ�����.txt
	fcout.open(cname, ios::app);//���γ̴����γ������ļ�
	fcout.close();

	ifstream fcin;//���γ̿��Ƿ����
	fcin.open("kecheng.txt");

	int inthismax, inthisnow;//�жϿγ̵�״̬

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0 ) && (strcmp(c1.name, classname) == 0)) {
				//cout << c1.maxnum << " " << c1.nownum << endl;
				inthismax = atoi(c1.maxnum);
				inthisnow = atoi(c1.nownum);

				if (inthisnow < inthismax)
					status = 1;//1����ѡ
				else
					status = 2;//2��������Ա

				break;
			}
		}
	}

	fcin.close();

	fcin.open(config);//������

	if (!fcin) {
		cout << "1154�޷���" << username << "������" << endl;
		exit(3);
	}

	while (!fcin.eof()) {
		if (fcin >> keunit1.name >> keunit1.tag) {
			//cout << "success:" << keunit.tag[0] << " " << keunit.name << endl;
			if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, classname) == 0)) {
				status = 3;//3���û��Ѿ�ѡ�ˣ������û����ظ�ѡ
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
		cout << "������Ŀγ̲����ڡ���" << endl;
		remove(cname);
		system("pause");



	} else if (status == 1) {
		cout << endl;
		cout << "�������������������������������������������������������������������������������������� \n";
		cout << "�� ѡ�γɹ���                              ��" << endl;
		cout << "�������������������������������������������������������������������������������������� \n" << endl;
		strcpy(keunit.name, classname);//����
		strcpy(keunit.tag, "1");
		fcout.open(config, ios::app);

		if (!fcout) {
			cout << "�޷�д��" << username << "������" << endl;
			exit(3);
		}

		fcout << keunit.name << " " << keunit.tag << endl; //д������˵�ѡ���б�
		fcout.close();

		fstream f;
		f.open("kecheng.txt", ios::out | ios::in | ios::binary);

		while (!f.eof()) {
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
				//cout << c1.tag << " " << c1.name << endl;
				if ((strcmp(c1.name, classname) == 0) && (strcmp(c1.tag, "1") == 0)) {
					//ԭ��ͬ������ɾ������ӣ��γɰ����ѡ��ʱ��˳�����пγ�
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
		inthisnow = atoi(c1.nownum);//atoi�����ڼ���
		inthisnow = inthisnow + 1;//ѡ������+1
		itoa(inthisnow, c1.nownum, 10);//ת��ȥ
		strcpy(c1.name, classname);

		//�ڿγ��ļ�ĩβ���
		fcout.open("kecheng.txt", ios::app);
		fcout << c1.name << " " << c1.maxnum << " " << c1.nownum << " " << c1.tag << endl;
		fcout.close();//�ر�

		fcout.open(cname, ios::app);//��顾�γ�����.txt�Ƿ����

		if (!fcout) {
			cout << "1231�޷�д��" << classname << "�����á�" << endl;
			exit(4);
		}

		strcpy(userunit.academy, useracademy);//cookie��������
		strcpy(userunit.name, userRealname);
		strcpy(userunit.username, username);
		strcpy(userunit.tag, "1");
		fcout << userunit.name << " " << userunit.username << " " << userunit.academy << " " << userunit.tag << endl; //����
		fcout.close();
		system("pause");

	} else if (status == 2) {
		cout << endl;
		cout << "�γ�������������ѡ�������γ�" << endl;
		cout << endl;
		system("pause");



	} else if (status == 3) {
		cout << endl;
		cout << "���Ѿ�ѡ�����ſ��ˣ������ظ�ѡ��" << endl;
		cout << endl;
		system("pause");
	}
}

void quitClass() {//ѧ��-�˿�
	char classname[1000];
	int status = 0;
	char config[100];
	strcpy(config, username);
	strcat(config, ".txt");

	ofstream fcout;
	fcout.open(config, ios::app);       //����������򴴽��ļ�
	fcout.close();//�ر�

	char cname[100];

	ke c, c1;
	keUnit keunit, keunit1;
	userUnit userunit, userunit1;
	account st, st1;

	system("cls");//����
	cout << "��ѡ���� 2. ��Ҫ�˿� " << endl;
	cout << endl;
	cout << "�������������������������������������������������������������������������������������� \n";
	cout << "�� �����������˵Ŀγ�����                  ��" << endl;
	cout << "�������������������������������������������������������������������������������������� \n"
	     << endl;
	cout << "�γ�����";
	cin.getline(classname, 100);
	getchar();
	strcpy(cname, classname);
	strcat(cname, ".txt");

	fcout.open(cname, ios::app);//ͬ���ǲ������򴴽�
	fcout.close();

	ifstream fcin;
	fcin.open("kecheng.txt");//���γ̿��Ƿ����

	if (!fcin) {
		cout << "1297�޷���kecheng.txt"
		     << endl;
		exit(1);
	}

	int inthismax, inthisnow;

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0) && (strcmp(c1.name, classname) == 0)) {
				status = 1;//������ڿγ̿���� Ĭ��0
				break;
			}
		}
	}

	fcin.close();

	fcin.open(config);

	if (!fcin) {
		cout << "1318�޷���" << username << "������" << endl;
		exit(3);
	}

	while (!fcin.eof()) {
		//cout << "mudamudamudamuda";
		if (fcin >> keunit1.name >> keunit1.tag) {
			if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, classname) == 0)) {
				status = 3;//����δ��ڲ���ȷʵ��ѡ�ˣ����������˿�
				break;
			}
		}
	}

	fcin.close();

	//cout << "status::" << status << endl;

	if (status == 0) {//�β�����
		cout << endl;
		cout << "������Ŀγ̲����ڡ���" << endl;
		remove(cname);
		system("pause");



	} else if (status == 3) {
		cout << endl;
		cout << "�������������������������������������������������������������������������������������� \n";
		cout << "�� �˿���ɣ�                              ��" << endl;
		cout << "�������������������������������������������������������������������������������������� \n" << endl;
		strcpy(keunit.name, classname);

		fstream f;
		f.open(config, ios::in | ios::out | ios::binary);

		if (!f) {
			cout << "1355�޷�д��" << username << "������" << endl;
			exit(3);
		}

		while (!f.eof()) {
			if (f >> keunit1.name >> keunit1.tag) {
				if ((strcmp(keunit1.tag, "1") == 0) && (strcmp(keunit1.name, classname) == 0)) {
					//ɾ��
					f << "0\n";
					break;
				}
			}
		}

		f.close();//�ر�

		f.open("kecheng.txt", ios::out | ios::in | ios::binary);

		if (!f) {
			cout << "1374û��" << endl;
			exit(9);
		}

		while (!f.eof()) {
			if (f >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
				if ((strcmp(c1.name, classname) == 0) && (strcmp(c1.tag, "1") == 0) ) {
					//cout << "yesyesyesyesyes";
					f << "0\n"; //ɾ��
					break;
				}
			}
		}

		f.close();//�ر�
		strcpy(c1.tag, "1");
		inthisnow = atoi(c1.nownum) - 1;//atoi���ڼ��㣬�˿κ�ѡ������-1
		//cout << endl << inthisnow << endl;
		itoa(inthisnow, c1.nownum, 10);//itoa���ڴ���

		fcout.open("kecheng.txt", ios::app);//���ļ�ĩβд��
		fcout << c1.name << " " << c1.maxnum << " " << c1.nownum << " " << c1.tag << endl;
		fcout.close();



		//fstream FILECLASS;//�Կγ�������
		f.open(cname, ios::in | ios::out | ios::binary);

		if (!f) {
			cout << "1405�޷�д��" << classname << "�����á�" << endl;
			exit(4);
		}

		while (!f.eof()) {
			if (f >> userunit1.name >> userunit1.username >> userunit1.academy >> userunit1.tag) {
				//cout << userunit1.name << " " << userunit1.tag << endl;
				if ((strcmp(userunit1.username, username) == 0) && (strcmp(userunit1.tag, "1") == 0)) {
					//ɾ��
					f << "0\n";
					//cout << "�ĺ�" << userunit1.name << " " << userunit1.tag << endl;
					break;
				}
			}
		}

		f.close();//�ر�
		//cout << "ѡ������:" << checkUserNum(cname) << endl;
		//if (checkUserNum(cname) == 0)
		//	remove(cname);
		system("pause");



	} else if (status == 1) {
		cout << endl;
		cout << "�㻹ûѡ���ſγ̡���" << endl;
		cout << endl;
		system("pause");
	}
}

void checkMe() {//ѧ��-�Բ�
	system("cls");
	int a[1000];
	char config[100];
	int cnt = 3, cnt1 = 3;//������
	ke c1;
	keUnit keunit1;
	strcpy(config, username);
	strcat(config, ".txt");

	ofstream fcout;
	fcout.open(config, ios::app);//�������򴴽�
	fcout.close();

	a[0] = strlen(username);
	a[1] = strlen(userRealname);
	a[2] = strlen(useracademy);

	cout << "������������������������������������������������������������������������������";

	for (int i = 1; i <= checkClassNum(); i++)
		cout << "����������������������";

	cout << endl;
	printf("���  %-10s ", "ѧ��"); //���5 ѧ��10
	printf("%-10s %-10s ", "����", "ѧԺ");//����10 ѧԺ10

	ifstream fcin;//������
	fcin.open("kecheng.txt");//���γ̿��Ƿ����

	if (!fcin) {
		cout << "1204�޷���kecheng������" << endl;
		exit(1);
	}

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0) && (atoi(c1.maxnum) > 0)) {
				a[cnt] = strlen(c1.name);
				printf("%-10s ", c1.name);//����һ��
				cnt++;
			}
		}
	}

	cout << endl;
	fcin.close();
	printf("1     %-10s %-10s %-10s ", username, userRealname, useracademy);//�ڶ���

	fcin.open("kecheng.txt");
	int op(0);
	ifstream ffcin;

	while (!fcin.eof()) {
		if (fcin >> c1.name >> c1.maxnum >> c1.nownum >> c1.tag) {
			if ((strcmp(c1.tag, "1") == 0) && (atoi(c1.maxnum) > 0)) {//ÿһ������״̬�Ŀγ�
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
					printf("%-10s ", "n");//���ڶ��ţ�ûѡ
					cnt1++;
				} else if (op == 1) {
					printf("%-10s ", "y");//ѡ��
					cnt1++;
				}

				op = 0;
				ffcin.close();
			}
		}
	}

	cout << endl;
	cout << "������������������������������������������������������������������������������";

	for (int i = 1; i <= checkClassNum(); i++)
		cout << "����������������������";

	cout << endl;
	fcin.close();//�ر�
	system("pause");
}

