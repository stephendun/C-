#include<iostream>
#include<cstring>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
struct player {//��Ҷ���
	int x = 3;
	int y = 0;//�������Ͻǵ�����
	int color;//��ǰ�������ɫ
	int scores;//����
	int map[25][25];//��ͼ
	int type;//��������
	int next_color = 5;//��һ��������ɫ����ʼΪ��ɫ
	int cube[4][4];//��ǰ����
	int next[4][4] = { 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 };//��һ�����飬��ʼΪz��
	int Life = 1;//����Ƿ�ʧ�ܣ�0Ϊʧ��
}pker[2];
int blocks[7][4][4] = {
	0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,
	0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 };//����˹�����7�ֶ���
void Setcolor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + 8);
} //������ɫ��0��ɫ 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ 8��ǿɫ

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
} //���ع��
void Gotoxy(int y, int x) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HideCursor();
}//ָ��λ�����
void Create(player& a) {//    ������������һ����Ҷ�      ����һ�����鸶����ǰ���飬�������������һ�����飬
	srand(time(0));
	a.color = a.next_color;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)a.cube[i][j] = a.next[i][j];//����һ�����鸳����ǰ����
	a.x = 3; a.y = 0;//�����ʼ�ķ������Ͻ�����
	a.type = rand() % 7;//��һ�����������
	a.next_color = rand() % 6 + 1;//��һ���������ɫ
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)a.next[i][j] = blocks[a.type][i][j];//����һ�����鶨��
}
void Cycle(player& a) {//������������    ����ҵĵ�ǰ������ת
	int b[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)b[3 - i][j] = a.cube[j][i];//���浱ǰ�ķ���
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (b[i][j] && ((a.y + i - 1) < 0 || (a.y + i - 1) > 21 || (a.x + j - 1) < 0 || (a.x + j - 1) > 11 || a.map[a.y + i][a.x + j]))  q = 1;
	if (!q) {//�����������ת�����¸���ԭ���ķ���
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)a.cube[i][j] = b[i][j];
	}
}
void Move(player& a, int i, int j) {//��ǰ������ƶ�
	a.y += i, a.x += j;
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (a.cube[i][j] && ((a.y + i - 1) < 0 || (a.y + i - 1) > 21 || (a.x + j - 1) < 0 || (a.x + j - 1) > 11 || a.map[a.y + i][a.x + j]))q = 1;
		}
	if (q)a.y -= i, a.x -= j;
}
void Print() {//��ӡ��Ϸ����
	Setcolor(7);
	Gotoxy(3, 2);
	cout << "*����*";
	Gotoxy(1, 18);
	cout << "����˹����(���һ)";
	Gotoxy(3, 15);
	cout << "��ת:W ����:A ����:D ����:S";
	Gotoxy(1, 64);
	cout << "����˹����(��Ҷ�)";
	Gotoxy(3, 59);
	cout << "��ת:I ����:J ����:L ����:K";
	for (int i = 0; i < 12; i++)pker[0].map[0][i] = pker[0].map[21][i] = 7, pker[1].map[0][i] = pker[1].map[21][i] = 7;//��Ϸ��Χ�߿��ɫ
	for (int i = 0; i < 22; i++)pker[0].map[i][0] = pker[0].map[i][11] = 7, pker[1].map[i][0] = pker[1].map[i][11] = 7;
	for (int i = 0; i < 22; i++) {
		Gotoxy(5 + i, 15);
		for (int j = 0; j < 12; j++) {
			if (pker[0].map[i][j]) {
				Setcolor(pker[0].map[i][j]);
				cout << "��";
				continue;
			}
			if (((pker[0].y <= i && i <= pker[0].y + 3) && (pker[0].x <= j && j <= pker[0].x + 3)) && pker[0].cube[i - pker[0].y][j - pker[0].x])
			{
				Setcolor(pker[0].color);
				cout << "��";
				continue;
			}
			cout << "  ";
		}
		Gotoxy(5 + i, 60);
		for (int j = 0; j < 12; j++) {
			if (pker[1].map[i][j]) {
				Setcolor(pker[1].map[i][j]);
				cout << "��";
				continue;
			}
			if (((pker[1].y <= i && i <= pker[1].y + 3) && (pker[1].x <= j && j <= pker[1].x + 3)) && pker[1].cube[i - pker[1].y][j - pker[1].x])
			{
				Setcolor(pker[1].color);
				cout << "��";
				continue;
			}
			cout << "  ";
		}
		cout << endl;
	}
	Gotoxy(10, 43);
	Setcolor(7);
	cout << "Next:";
	for (int i = 0; i < 4; i++)
	{
		Gotoxy(11 + i, 43);
		for (int j = 0; j < 4; j++)
		{
			Setcolor(pker[0].next_color);
			if (pker[0].next[i][j])
				cout << "��";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(15, 43);
	Setcolor(7);
	cout << "������";
	Gotoxy(16, 43);
	cout << pker[0].scores << endl;
	Gotoxy(10, 88);
	cout << "Next:";
	for (int i = 0; i < 4; i++)
	{
		Gotoxy(11 + i, 88);
		for (int j = 0; j < 4; j++)
		{
			Setcolor(pker[1].next_color);
			if (pker[1].next[i][j])
				cout << "��";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(15, 88);
	Setcolor(7);
	cout << "������";
	Gotoxy(16, 88);
	cout << pker[1].scores << endl;

}
int Check(player& a) {//��鷽����ƶ��Ƿ�������Լ�����Ƿ�ʧ��
	for (int i = 1; i < 11; i++)
		if (a.map[1][i]) {
			a.Life = 0;
			return 0;
		}//�������з��飬�����ʧ��
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (a.cube[i][j] && a.map[a.y + i + 1][a.x + j]) q = 1;//��������ͼ�����еķ����غ�������
	if (q) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) if (a.cube[i][j]) a.map[a.y + i][a.x + j] = a.color;//����޷��ƶ����ͽ����ӡ����
		return 1;
	}
	return 3;//�����ƶ���������3
}
void Delete(player& a) {//����Ѿ����еĲ���
	int q, lines = 0;
	for (int i = 1; i < 21; i++) {
		q = 0;
		for (int j = 1; j < 11; j++)if (!a.map[i][j])q = 1;
		if (!q) {
			a.map[i][1] = 7;
			lines++;
		}
	}
	for (int i = 20; i > 0; i--) {
		if (a.map[i][1] == 7) {
			for (int j = i; j > 1; j--)
				for (int k = 1; k < 11; k++)
					a.map[j][k] = a.map[j - 1][k];
			a.scores += 10;
		}
	}
	a.scores += (lines / 2) * 20;
	Print();
}
void Control(player& a, player& b) {//�Ӽ��̶�ȡ��ҵĿ��Ʋ���
	int instru;
	int i1 = 1, i2 = 1, k = 0, p = 0;//i1��i2�������һ���Ĳ�����Ϣ�Ƿ��Ѿ���ȡ��k��p��������Ƿ񰴵ļ��ٲ���
	if (_kbhit()) {
		DWORD start = ::GetTickCount();//�����ȡ�ĳ�ʼʱ��
		while (_kbhit()) {
			instru = _getch();
			if (i1 && a.Life) {//��Ҳ�����ȡ����������Ѿ�ʧ�ܾͲ��ٶ�ȡ���Ĳ�����Ϣ
				if (instru == 119) { Cycle(a); i1--; }//��ת
				else if (instru == 97) { Move(a, 0, -1); i1--; }//����
				else if (instru == 100) { Move(a, 0, 1); i1--; }//����
				else if (instru == 115) { Move(a, 1, 0); i1--; k++; }//����
			}
			if (i2 && b.Life) {
				if (instru == 105) { Cycle(b); i2--; }//��ת
				else if (instru == 106) { Move(b, 0, -1); i2--; }//����
				else if (instru == 108) { Move(b, 0, 1); i2--; }//����
				else if (instru == 107) { Move(b, 1, 0); i2--; p++; }//����
			}
			DWORD end = ::GetTickCount();//��ȡ������ʱ��
			if (((end - start) >= 10)) {//һ�ζ�ȡʱ�䲻�ܳ���10ms
				break;
			}
		}if (i1 || k)Move(a, 1, 0);//������û�������������������ļ��ٲ�������ô�䷽��������ƶ�һ��
		if (i2 || p)Move(b, 1, 0);
	}
	if (i1 && i2) {//�����λ��Ҷ�û������ ����ô�������ƶ�һ��
		Move(a, 1, 0);
		Move(b, 1, 0);
	}
	while (_kbhit())int a = _getch();//������뻺�����İ���������������´β���Ӱ��
}
int main() {
	int reb[2] = { 3,3 };
	Create(pker[0]);
	Create(pker[1]);
	while (1) {
	label:for (int i = 0; i < 2; i++) {
		if (pker[i].Life) {
			Delete(pker[i]);
			reb[i] = Check(pker[i]);
		}
	}
	if (!pker[0].Life && !pker[1].Life) {
		Gotoxy(27, 40);
		Setcolor(4);
		cout << "Game Over:\t" << ((pker[0].scores > pker[1].scores) ? "���һ ʤ" : ((pker[0].scores == pker[1].scores) ? "ƽ��" : "��Ҷ� ʤ")) << endl;
		Setcolor(7);
		break;
	}
	for (int i = 0; i < 2; i++) {
		if (reb[i] == 1) {
			Create(pker[i]);
			goto label;
		}
	}
	Control(pker[0], pker[1]);
	Print();
	Sleep(180);
	}
	return 0;
}