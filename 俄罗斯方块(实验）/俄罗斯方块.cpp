#include<iostream>
#include<cstring>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
void Gotoxy(int y, int x) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}//指定位置输出

void Setcolor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
} //设置颜色：0黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色 8加强色

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
} //隐藏光标

int Map[25][15];
int blocks[7][4][4] = { 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,
	0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 };
int x, y, color, type, scores = 0,next_color=3;
int a[4][4], b[4][4], Next[4][4] = { 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 };

void Create() {
	srand(time(0));
	color = next_color;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)a[i][j] = Next[i][j];
	x = 3;y = -1; 
	type = rand() % 7;
	next_color = rand() % 6 + 1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)Next[i][j] = blocks[type][i][j];
}//生成俄罗斯方块
bool out(int i, int j) {//是否出界面边框
	if (i < 0 || i >= 20) return true;
	if (j < 0 || j >= 10) return true;
	return false;
}
//旋转
void cycle() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)b[3 - i][j] = a[j][i];
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (b[i][j] && (out(y + i - 1, x + j - 1) || Map[y + i][x + j]))  q = 1;
	if (!q) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)a[i][j] = b[i][j];
	}
}
bool Exist(int i,int j) {
	if (i<y || i>y + 3)return false;
	if (j<x || j>x + 3)return false;
	if (!a[i - y][j - x])return false;
	return true;
}
void Move(int i, int j) {
	y += i, x += j;
	int q = 0;
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++) {
			if(a[i][j]&&(out(y+i-1,x+j-1)||Map[y+i][x+j]))q=1;
		}
	if (q)y -= i, x -= j;
}
void Print() {
	Gotoxy(8, 47);
	cout << "俄罗斯方块";
	for (int i = 0; i < 12; i++)Map[0][i] = Map[21][i] = 7;
	for (int i = 0; i < 22; i++)Map[i][0] = Map[i][11] = 7;
	for (int i = 0; i < 22; i++) {
		Gotoxy(10 + i, 40);
		for (int j = 0; j < 12; j++) {
			if (Map[i][j]) {
				Setcolor(Map[i][j]);
				cout << "■";
				continue;
			}
			if (Exist(i, j)) {
				Setcolor(color);
				cout << "■";
				continue;
			}
			cout << "  ";
		}
		cout << endl;
	}
	Gotoxy(15, 68);
	cout << "Next:";

	for (int i = 0; i < 4; i++)
	{
		Gotoxy(16 + i, 68);
		for (int j = 0; j < 4; j++)
		{
			Setcolor(next_color);
			if (Next[i][j])
				cout << "■";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(20, 68);
	Setcolor(7);
	cout << "分数：";
	Gotoxy(21, 68);
	cout << scores << endl;
}
void Step() {
	int instru;
	if (_kbhit()) {
		instru = _getch();
		instru = _getch();
		if (instru == 72) cycle();
		if (instru == 75) Move(0, -1);
		if (instru == 77) Move(0, 1);
		if (instru == 80) Move(1, 0);
	}
}
int check() {
	for (int i = 1; i < 11; i++)
		if (Map[1][i])return 0;
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) 
			if (a[i][j] && Map[y + i + 1][x + j]) q = 1;
	if (q) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) if (a[i][j]) Map[y + i][x + j] = color;
		return 1;
	}
	return 2;
}
void Delete() {
	int q, lines=0;
	for (int i = 1; i < 21; i++) {
		q = 0;
		for (int j = 1; j < 11; j++)if (!Map[i][j])q = 1;
		if (!q) {
			Map[i][1] = 7;
			lines++;
		}
	}
	for (int i = 20; i > 0; i--) {
		if (Map[i][1] == 7) {
			for (int j = i; j > 1; j--)
				for (int k = 1; k < 11; k++)
					Map[j][k] = Map[j - 1][k];
			scores += 10;
		}
	}
	scores += (lines / 2) * 20;
	Print();
}
int main() {
	int reb;
	HideCursor();
	Create();
	while (1) {
		Delete();
		reb = check();
		if (reb == 0) {
			Gotoxy(32, 45);
			Setcolor(4 + 8);
			cout << "Game Over!!!\n";
			Setcolor(7); break;
		}
		if (reb == 1) {
			Create(); continue;
		}
		Move(1, 0);
		Step();
		Print();
		Sleep(200);
	}
	return 0;
}