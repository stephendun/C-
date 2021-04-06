#include<iostream>
#include<stdio.h>
#include <math.h>
#include<algorithm>
#include<cstring>
using namespace std;
#define Max 1000
void showmenu() {
	cout << "*************************" << endl;
	cout << "****** 1.�����ϵ�� *****" << endl;
	cout << "****** 2.��ʾ��ϵ�� *****" << endl;
	cout << "****** 3.ɾ����ϵ�� *****" << endl;
	cout << "****** 4.������ϵ�� *****" << endl;
	cout << "****** 5.�޸���ϵ�� *****" << endl;
	cout << "****** 6.�����ϵ�� *****" << endl;
	cout << "****** 0.�˳�ͨѶ¼ *****" << endl;
	cout << "*************************" << endl;
};
struct person {
	string name;
	int m_sex;
	int m_age;
	string m_phone;
	string m_addr;
};
struct addressbooks {
	struct person personarray[Max];
	int m_size;
};
//�����ϵ��
void addperson(addressbooks* abs) {
	if (abs->m_size == Max)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else
	{
		string name;
		cout << "������������ " << endl;
		cin >> name;
		abs->personarray[abs->m_size].name = name;
		cout << "�������Ա� " << endl;
		cout << "1----��" << endl;
		cout << "2----Ů" << endl;
		int sex = 0;
		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personarray[abs->m_size].m_sex = sex;
				break;
			}
			cout << "������������������" << endl;
		}
		cout << "���������䣺 " << endl;
		int age = 0;
		while (true) {
			cin >> age;
			if (age > 17 && age < 61) {
				abs->personarray[abs->m_size].m_age = age;
				break;
			}
			cout << "�����������������" << endl;
		}
		cout << "��������ϵ�˵绰: " << endl;
		string phone;
		while (true) {
			cin >> phone;
			if (phone.length() == 11)
			{
				abs->personarray[abs->m_size].m_phone = phone;
				break;
			}
			cout << "�����������������" << endl;
		}
		cout << "�������ͥסַ�� " << endl;
		string addr;
		cin >> addr;
		abs->personarray[abs->m_size].m_addr = addr;
		abs->m_size++;
		cout << "��ӳɹ�" << endl;
		system("pause");
		system("cls");   //��������
	}
}
//��ʾ������ϵ��
void showperson(addressbooks* abs)
{//�ж�ͨѶ¼�������Ƿ�Ϊ��
	if (abs->m_size == 0) {
		cout << "��ǰ�ļ�¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_size; i++)
		{
			cout << "��" << i + 1 << "λ��Ա��Ϣ��" << endl;
			cout << "������ " << abs->personarray[i].name << "\t";
			cout << "�Ա� " << (abs->personarray[i].m_sex == 1 ? "��" : "Ů") << "\t";
			cout << "���䣺 " << abs->personarray[i].m_age << "\t";
			cout << "�绰�� " << abs->personarray[i].m_phone << "\t";
			cout << "��ַ�� " << abs->personarray[i].m_addr << "\n";
		}
	}
	system("pause");
	system("cls");
}
//�����ϵ���Ƿ���ڣ�������ڣ�������ϵ�����������еľ���λ�ã������ڷ���ֵΪ-1
int isexist(addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_size; i++)
	{
		if (abs->personarray[i].name == name) {
			return i;
		}
	}return -1;
}
//ɾ��ָ����ϵ��
void deleteperson(addressbooks* abs) 
{
	cout << "��������Ҫɾ������ϵ��\n";
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		for (int i = ret; i < abs->m_size; i++)
		{
			abs->personarray[i] = abs->personarray[i + 1];
		}
		abs->m_size--;
		cout << "ɾ���ɹ�\n";
	}
	else
	{
		cout << "���޴���\n";
	}
	system("pause");
	system("cls");
}
//����ָ����ϵ����Ϣ
void findperson(addressbooks* abs)
{
	cout << "��������Ҫ���ҵ���ϵ��\n";
	string name;
	cin >> name;
	if (isexist(abs, name) == -1)cout << "����ϵ�˲�����\n";
	else
	{
		int ret = isexist(abs, name);
		cout << "������ " << abs->personarray[ret].name << "\t";
		cout << "�Ա� " << (abs->personarray[ret].m_sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺 " << abs->personarray[ret].m_age << "\t";
		cout << "�绰�� " << abs->personarray[ret].m_phone << "\t";
		cout << "��ַ�� " << abs->personarray[ret].m_addr << "\n";
	}
	system("pause");
	system("cls");
}
//�޸�ָ����ϵ����Ϣ
void modifyperson(addressbooks* abs)
{
	cout << "��������Ҫ�޸ĵ���ϵ��\n";
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		string name;
		cout << "������������\n";
		cin >> name;
		abs->personarray[ret].name = name;
		cout << "�������Ա�\n";
		cout << "1---��\n";
		cout << "2---Ů\n";
		int sex = 0;
		while(true)
		{	
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
			abs->personarray[ret].m_sex = sex;
			break;
		}
			cout << "������������������\n";
		}
		cout << "���������䣺 \n";
		int age = 0;
		cin >> age;
		abs->personarray[ret].m_age = age;
		cout << "��������ϵ�绰�� \n";
		string phone;
		cin >> phone;
		abs->personarray[ret].m_phone = phone;
		cout << "�������ͥסַ�� \n";
		string address;
		cin >> address;
		abs->personarray[ret].m_addr = address;
		cout << "�޸ĳɹ���\n";
	}
	else
	{
		cout << "���޴���\n";
	}
	system("pause");
	system("cls");
}
//���������ϵ��
void cleanperson(addressbooks* abs)
{
	abs->m_size = 0;
	cout << "ͨѶ¼�����\n";
	system("pause");
	system("cls");
}
int main()
{
	addressbooks abs;
	abs.m_size = 0;
	int select = 0;
	while (true)
	{
		showmenu();
		cin >> select;
		switch (select) {
		case 1://1.�����ϵ��
			addperson(&abs);//��ַ����
			break;
		case 2://2.��ʾ��ϵ��
			showperson(&abs);
			break;
		case 3://3.ɾ����ϵ��
			deleteperson(&abs);
		break; 
		case 4://4.������ϵ��
			findperson(&abs);
			break;
		case 5://5.�޸���ϵ��
			modifyperson(&abs);
			break;
		case 6://6.�����ϵ��
			cleanperson(&abs);
			break;
		case 0://0.�˳�ͨѶ¼ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}
