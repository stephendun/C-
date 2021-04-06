#include"workerManager.h"
WorkerManager::WorkerManager()
{
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open())
	{
		cout << "�ļ�������\n";
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ����ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ�����Ϊ��
		char ch;
		ifs >> ch;
		if(ifs.eof())
		{
			cout << "�ļ�Ϊ�գ�\n";
			//��ʼ����¼����
			this->m_EmpNum = 0;
           //��ʼ���ļ��Ƿ�Ϊ��
			this->m_FileIsEmpty = true;
			//��ʼ������ָ��
			this->m_EmpArray = NULL;
			ifs.close();
			return;
		}

	
		//�ļ����ڣ����Ҽ�¼����
		int num = this->get_EmpNum();
	//	cout << "ְ�������� " << num << endl;
		this->m_EmpNum= num;
		//���ٿռ�
		this->m_EmpArray = new Worker * [this->m_EmpNum];
		//���ļ��е����ݣ��浽������
		this->init_Emp();
	/*	for (int i = 0; i < this->m_EmpNum; i++)
		{
			cout << "ְ�����:  " << this->m_EmpArray[i]->m_Id << " "
				<< "������ " << this->m_EmpArray[i]->m_name << " "
				<< "���ű�ţ� " << this->m_EmpArray[i]->m_DeptId << endl;
		}*/
}

void WorkerManager:: Show_Menu()
{
	cout << "**************************" << endl;
	cout << "***��ӭʹ��ְ������ϵͳ!**"<<endl;
	cout << "******0.�˳��������******"<<endl;
	cout << "******1.����ְ����Ϣ******" << endl;
	cout << "******2.��ʾְ����Ϣ******" << endl;
	cout << "******3.ɾ����ְְ��******" << endl;
	cout << "******4.�޸�ְ����Ϣ******" << endl;
	cout << "******5.����ְ����Ϣ******" << endl;
	cout << "******6.���ձ������******" << endl;
	cout << "******7.��������ĵ�******" << endl;
	cout << "**************************" << endl;
	cout << endl;
}
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��\n";
	system("pause");
	exit(0);//�˳�����
}
//���ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְ����������\n";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{//���
		//������ӵ��¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
}
		}
		//�������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "������� " << i + 1 << " ����ְ����ţ�\n";
			cin >> id;
			cout << "������� " << i + 1 << " ����ְ��������\n";
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��\n";
			cout << "1.��ְͨ��\n"<<"2.����\n"<<"3.�ϰ�\n";
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
			//������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[]this->m_EmpArray;
		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		//�����µ�ְ������
		this->m_EmpNum = newSize;
		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		//��ʾ
		cout << "�ɹ����" << addNum << "����ְ����" << endl;
		//�������ݵ��ļ���
		this->save();
	}
	else
	{
		cout << "������������\n";
	}
	system("pause");
	system("cls");
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�������ʽ���ļ���������д�ļ�
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
	ifs.open(FILENAME, ios::in);//���ļ�--���ļ�
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//��¼����
		num++;
	}
	ifs.close();
	return num;
}
//��ʼ��ְ��
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
		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//����
		{
			worker = new Manager(id, name, dId);
		}
		else//�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}
//��ʾְ��
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�\n";
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");

}
//�ж�ְ���Ƿ����,�����ڷ�����������λ�ã������ڷ���-1
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

//ɾ��ְ��
void WorkerManager:: Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��!\n";
	}
	else
	{
		cout << "��������Ҫɾ��ְ�����: \n";
		int id = 0;
		cin >> id;
		int index=this->IsExist(id);
		if (index != -1)//˵��ְ������
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼��Ա����
			this->save();
			cout << "ɾ���ɹ�!\n";
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��!\n";
		}
		system("pause");
		system("cls");
	}
}
//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�\n";
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�\n";
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newname = "";
			int dSelect = 0;
			cout << "�鵽��" << id << "��ְ��\n ��������ְ����: \n";
			cin >> newId;
			cout << " �������λ��\n";
			cout << " 1.��ְͨ��\n" << " 2.����\n" << " 3.�ϰ�\n";
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
			cout << "�޸ĳɹ���" << this->m_EmpArray[ret]->m_DeptId << endl;
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���\n";
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�\n";
	}
	else
	{
		cout << "��������ҵķ�ʽ��\n" << "1.��ְ����Ų���\n" << "2.����������\n";
		int select = 0;
		cin >> select;
		if (select == 1)//��ְ����Ų���
		{
			int id;
			cout << "��������ҵ�ְ����ţ�\n";
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ���\n��ְ����Ϣ���£�\n";
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���\n";
			}
		}
		else if(select==2)//����������
		{
			string name;
			cout << "��������ҵ�ְ��������\n";
			cin >> name;
			bool flag = false;//���ҵ��ı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ:" << m_EmpArray[i]->m_Id
						<< "�ŵ���Ϣ����:\n";
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{//���޴���
				cout << "����ʧ�ܣ����޴���\n";
			}
		}
		else
		{
			cout << "����ѡ������\n";
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ:\n";
		cout << "1.��ְ���Ž�������\n" << "2.��ְ���Ž��н���\n";
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//������Сֵ �� ���ֵ �±�
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)//����
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else//����
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
			cout << "����ɹ����������Ϊ��\n";
			this->save();
			this->Show_Emp();

		}

	}
}
//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�\n" << "1.ȷ��\n" << "2.����\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽios::trunc  �������ɾ���ļ������´���
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
		cout << "��ճɹ���\n";
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