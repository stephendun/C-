#pragma once   //防止头文件重复包含
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
	int m_EmpNum;//记录职工人数
	//职工数组指针
	Worker** m_EmpArray;
	//添加职工函数
	void Add_Emp();
	//保存文件
	void save();
	//判断文件是否为空 标志
	bool m_FileIsEmpty;
	//统计文件中的人数
	int get_EmpNum();
	//初始化职工
	void init_Emp();
	//显示职工
	void Show_Emp();
	//判断职工是否存在,若存在返回在数组中位置，不存在返回-1
	int IsExist(int id);
	//删除职工
	void Del_Emp();
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//排序职工
	void Sort_Emp();
	//清空文件
	void Clean_File();
	~WorkerManager();
};