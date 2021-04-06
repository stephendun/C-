#include"workerManager.h"
WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open())
	{
		cout << "文件不存在\n";
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，数据为空
		char ch;
		ifs >> ch;
		if(ifs.eof())
		{
			cout << "文件为空！\n";
			//初始化记录人数
			this->m_EmpNum = 0;
           //初始化文件是否为空
			this->m_FileIsEmpty = true;
			//初始化数组指针
			this->m_EmpArray = NULL;
			ifs.close();
			return;
		}

	
		//文件存在，并且记录数据
		int num = this->get_EmpNum();
	//	cout << "职工人数： " << num << endl;
		this->m_EmpNum= num;
		//开辟空间
		this->m_EmpArray = new Worker * [this->m_EmpNum];
		//将文件中的数据，存到数组中
		this->init_Emp();
	/*	for (int i = 0; i < this->m_EmpNum; i++)
		{
			cout << "职工编号:  " << this->m_EmpArray[i]->m_Id << " "
				<< "姓名： " << this->m_EmpArray[i]->m_name << " "
				<< "部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;
		}*/
}

void WorkerManager:: Show_Menu()
{
	cout << "**************************" << endl;
	cout << "***欢迎使用职工管理系统!**"<<endl;
	cout << "******0.退出管理程序******"<<endl;
	cout << "******1.增加职工信息******" << endl;
	cout << "******2.显示职工信息******" << endl;
	cout << "******3.删除离职职工******" << endl;
	cout << "******4.修改职工信息******" << endl;
	cout << "******5.查找职工信息******" << endl;
	cout << "******6.按照编号排序******" << endl;
	cout << "******7.清空所有文档******" << endl;
	cout << "**************************" << endl;
	cout << endl;
}
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用\n";
	system("pause");
	exit(0);//退出程序
}
//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：\n";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{//添加
		//计算添加的新空间大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
}
		}
		//批量添加
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第 " << i + 1 << " 个新职工编号：\n";
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个新职工姓名：\n";
			cin >> name;
			cout << "请选择该职工的岗位：\n";
			cout << "1.普通职工\n"<<"2.经理\n"<<"3.老板\n";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;

			}
			//将创建职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[]this->m_EmpArray;
		//更改新空间的指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;
		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//提示
		cout << "成功添加" << addNum << "名新职工！" << endl;
		//保存数据到文件中
		this->save();
	}
	else
	{
		cout << "输入数据有误\n";
	}
	system("pause");
	system("cls");
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出方式打开文件；———写文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptId <<  endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件--读文件
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();
	return num;
}
//初始化职工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else//老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}
//显示职工
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！\n";
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");

}
//判断职工是否存在,若存在返回在数组中位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
	}
	}
	return index;
}

//删除职工
void WorkerManager:: Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!\n";
	}
	else
	{
		cout << "请输入想要删除职工编号: \n";
		int id = 0;
		cin >> id;
		int index=this->IsExist(id);
		if (index != -1)//说明职工存在
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			this->save();
			cout << "删除成功!\n";
		}
		else
		{
			cout << "删除失败，未找到该职工!\n";
		}
		system("pause");
		system("cls");
	}
}
//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！\n";
	}
	else
	{
		cout << "请输入修改职工的编号：\n";
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newname = "";
			int dSelect = 0;
			cout << "查到：" << id << "号职工\n 请输入新职工号: \n";
			cin >> newId;
			cout << " 请输入岗位：\n";
			cout << " 1.普通职工\n" << " 2.经理\n" << " 3.老板\n";
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newname, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newname, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newname, dSelect);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << this->m_EmpArray[ret]->m_DeptId << endl;
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人\n";
		}
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！\n";
	}
	else
	{
		cout << "请输入查找的方式：\n" << "1.按职工编号查找\n" << "2.按姓名查找\n";
		int select = 0;
		cin >> select;
		if (select == 1)//按职工编号查找
		{
			int id;
			cout << "请输入查找的职工编号：\n";
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！\n该职工信息如下：\n";
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人\n";
			}
		}
		else if(select==2)//按姓名查找
		{
			string name;
			cout << "请输入查找的职工姓名：\n";
			cin >> name;
			bool flag = false;//查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功！职工编号为:" << m_EmpArray[i]->m_Id
						<< "号的信息如下:\n";
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{//查无此人
				cout << "查找失败，查无此人\n";
			}
		}
		else
		{
			cout << "输入选项有误\n";
		}
	}
	system("pause");
	system("cls");
}
//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式:\n";
		cout << "1.按职工号进行升序\n" << "2.按职工号进行降序\n";
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值 或 最大值 下标
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else//降序
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				if (i != minOrMax)
				{
					Worker* temp = m_EmpArray[i];
					m_EmpArray[i] = m_EmpArray[minOrMax];
					m_EmpArray[minOrMax] = temp;
				}
			}
			cout << "排序成功，排序后结果为：\n";
			this->save();
			this->Show_Emp();

		}

	}
}
//清空文件
void WorkerManager::Clean_File()
{
	cout << "确认清空？\n" << "1.确认\n" << "2.返回\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式ios::trunc  如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！\n";
	}
	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}