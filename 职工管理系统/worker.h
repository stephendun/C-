#pragma once
#include <iostream>
#include<string>
using namespace std;
//ְ���������
class Worker
{
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡְλ����
	virtual string getDeptName() = 0;
	//ְ�����
	int m_Id;
	//ְ������
	string m_name;
	//ְ�����ڲ������Ʊ��
	int m_DeptId;
};