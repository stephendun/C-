#pragma once
#include <iostream>
#include<string>
using namespace std;
//职工抽象基类
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取职位名称
	virtual string getDeptName() = 0;
	//职工编号
	int m_Id;
	//职工姓名
	string m_name;
	//职工所在部门名称编号
	int m_DeptId;
};