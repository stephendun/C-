#pragma once   //��ֹͷ�ļ��ظ�����
#include<iostream>   
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;
#include"worker.h"
#include"employee.h"
#include"boss.h"
#include"manager.h"
class WorkerManager
{
public:
	WorkerManager();

	void Show_Menu();
	void ExitSystem();
	int m_EmpNum;//��¼ְ������
	//ְ������ָ��
	Worker** m_EmpArray;
	//���ְ������
	void Add_Emp();
	//�����ļ�
	void save();
	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;
	//ͳ���ļ��е�����
	int get_EmpNum();
	//��ʼ��ְ��
	void init_Emp();
	//��ʾְ��
	void Show_Emp();
	//�ж�ְ���Ƿ����,�����ڷ�����������λ�ã������ڷ���-1
	int IsExist(int id);
	//ɾ��ְ��
	void Del_Emp();
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//����ְ��
	void Sort_Emp();
	//����ļ�
	void Clean_File();
	~WorkerManager();
};