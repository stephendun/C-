#include "manager.h"
//���캯��
Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_DeptId = dId;
}
//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ������ϰ彻�������񣬲����·������Ա��" << endl;
}
//��ȡְλ����
string Manager::getDeptName()
{
	return string("����");
}