#include"employee.h"
Employee::Employee(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_DeptId = dId;
}
void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id 
		<< "\tְ��������" << this->m_name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}
string Employee::getDeptName()
{
	return string("Ա��");
}