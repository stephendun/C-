//��ͨԱ���ļ�
#pragma once
#include <iostream>
#include "worker.h"
using namespace std;
//Ա����
class Employee :public Worker
{
public:
	//���캯��
	Employee(int id, string name, int dId);
	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡְ����λ����
	virtual string getDeptName();

};