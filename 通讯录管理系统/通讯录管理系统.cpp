#include<iostream>
#include<stdio.h>
#include <math.h>
#include<algorithm>
#include<cstring>
using namespace std;
#define Max 1000
void showmenu() {
	cout << "*************************" << endl;
	cout << "****** 1.添加联系人 *****" << endl;
	cout << "****** 2.显示联系人 *****" << endl;
	cout << "****** 3.删除联系人 *****" << endl;
	cout << "****** 4.查找联系人 *****" << endl;
	cout << "****** 5.修改联系人 *****" << endl;
	cout << "****** 6.清空联系人 *****" << endl;
	cout << "****** 0.退出通讯录 *****" << endl;
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
//添加联系人
void addperson(addressbooks* abs) {
	if (abs->m_size == Max)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else
	{
		string name;
		cout << "请输入姓名： " << endl;
		cin >> name;
		abs->personarray[abs->m_size].name = name;
		cout << "请输入性别： " << endl;
		cout << "1----男" << endl;
		cout << "2----女" << endl;
		int sex = 0;
		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personarray[abs->m_size].m_sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}
		cout << "请输入年龄： " << endl;
		int age = 0;
		while (true) {
			cin >> age;
			if (age > 17 && age < 61) {
				abs->personarray[abs->m_size].m_age = age;
				break;
			}
			cout << "输入错误，请重新输入" << endl;
		}
		cout << "请输入联系人电话: " << endl;
		string phone;
		while (true) {
			cin >> phone;
			if (phone.length() == 11)
			{
				abs->personarray[abs->m_size].m_phone = phone;
				break;
			}
			cout << "输入错误，请重新输入" << endl;
		}
		cout << "请输入家庭住址： " << endl;
		string addr;
		cin >> addr;
		abs->personarray[abs->m_size].m_addr = addr;
		abs->m_size++;
		cout << "添加成功" << endl;
		system("pause");
		system("cls");   //清屏操作
	}
}
//显示所有联系人
void showperson(addressbooks* abs)
{//判断通讯录中人数是否为零
	if (abs->m_size == 0) {
		cout << "当前的记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_size; i++)
		{
			cout << "第" << i + 1 << "位成员信息：" << endl;
			cout << "姓名： " << abs->personarray[i].name << "\t";
			cout << "性别： " << (abs->personarray[i].m_sex == 1 ? "男" : "女") << "\t";
			cout << "年龄： " << abs->personarray[i].m_age << "\t";
			cout << "电话： " << abs->personarray[i].m_phone << "\t";
			cout << "地址： " << abs->personarray[i].m_addr << "\n";
		}
	}
	system("pause");
	system("cls");
}
//检测联系人是否存在，如果存在，返回联系人所在数组中的具体位置，不存在返回值为-1
int isexist(addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_size; i++)
	{
		if (abs->personarray[i].name == name) {
			return i;
		}
	}return -1;
}
//删除指定联系人
void deleteperson(addressbooks* abs) 
{
	cout << "请输入您要删除的联系人\n";
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
		cout << "删除成功\n";
	}
	else
	{
		cout << "查无此人\n";
	}
	system("pause");
	system("cls");
}
//查找指定联系人信息
void findperson(addressbooks* abs)
{
	cout << "请输入您要查找的联系人\n";
	string name;
	cin >> name;
	if (isexist(abs, name) == -1)cout << "该联系人不存在\n";
	else
	{
		int ret = isexist(abs, name);
		cout << "姓名： " << abs->personarray[ret].name << "\t";
		cout << "性别： " << (abs->personarray[ret].m_sex == 1 ? "男" : "女") << "\t";
		cout << "年龄： " << abs->personarray[ret].m_age << "\t";
		cout << "电话： " << abs->personarray[ret].m_phone << "\t";
		cout << "地址： " << abs->personarray[ret].m_addr << "\n";
	}
	system("pause");
	system("cls");
}
//修改指定联系人信息
void modifyperson(addressbooks* abs)
{
	cout << "请输入您要修改的联系人\n";
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		string name;
		cout << "请输入姓名：\n";
		cin >> name;
		abs->personarray[ret].name = name;
		cout << "请输入性别：\n";
		cout << "1---男\n";
		cout << "2---女\n";
		int sex = 0;
		while(true)
		{	
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
			abs->personarray[ret].m_sex = sex;
			break;
		}
			cout << "输入有误，请重新输入\n";
		}
		cout << "请输入年龄： \n";
		int age = 0;
		cin >> age;
		abs->personarray[ret].m_age = age;
		cout << "请输入联系电话： \n";
		string phone;
		cin >> phone;
		abs->personarray[ret].m_phone = phone;
		cout << "请输入家庭住址： \n";
		string address;
		cin >> address;
		abs->personarray[ret].m_addr = address;
		cout << "修改成功！\n";
	}
	else
	{
		cout << "查无此人\n";
	}
	system("pause");
	system("cls");
}
//清空所有联系人
void cleanperson(addressbooks* abs)
{
	abs->m_size = 0;
	cout << "通讯录已清空\n";
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
		case 1://1.添加联系人
			addperson(&abs);//地址传递
			break;
		case 2://2.显示联系人
			showperson(&abs);
			break;
		case 3://3.删除联系人
			deleteperson(&abs);
		break; 
		case 4://4.查找联系人
			findperson(&abs);
			break;
		case 5://5.修改联系人
			modifyperson(&abs);
			break;
		case 6://6.清空联系人
			cleanperson(&abs);
			break;
		case 0://0.退出通讯录系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}
