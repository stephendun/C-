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

int Map[25][15], map[25][15];
int blocks[7][4][4] = { 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,
	0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 };
int x, y, color, type, scores = 0, next_color = 3;
int x1, y2,color1, type1, scores1 = 0,next_color1=3;
int s1 = 1, s2 = 1;
int a[4][4], b[4][4], Next[4][4] = { 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 };
int c[4][4], Next1[4][4] = { 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 };

void Create() {
	srand(time(0));
	color = next_color;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)a[i][j] = Next[i][j];
	x = 3; y = -1;
	type = rand() % 7;
	next_color = rand() % 6 + 1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)Next[i][j] = blocks[type][i][j];
}//生成俄罗斯方块
void Create1() {
	srand(time(0));
	color1 = next_color1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)c[i][j] = Next1[i][j];
	x1 = 3; y2 = -1;
	type1 = rand() % 7;
	next_color1 = rand() % 6 + 1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)Next1[i][j] = blocks[type1][i][j];
}
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
void cycle1() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)b[3 - i][j] = c[j][i];
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (b[i][j] && (out(y2 + i - 1, x1 + j - 1) || map[y2 + i][x1 + j]))  q = 1;
	if (!q) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)c[i][j] = b[i][j];
	}
}
bool Exist(int i, int j) {
	if (i<y || i>y + 3)return false;
	if (j<x || j>x + 3)return false;
	if (!a[i - y][j - x])return false;
	return true;
}
bool Exist1(int i, int j) {
	if (i<y2 || i>y2 + 3)return false;
	if (j<x1 || j>x1 + 3)return false;
	if (!c[i - y2][j - x1])return false;
	return true;
}
void Move(int i, int j) {
	y += i, x += j;
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (a[i][j] && (out(y + i - 1, x + j - 1) || Map[y + i][x + j]))q = 1;
		}
	if (q)y -= i, x -= j;
}
void Move1(int i, int j) {
	{
		y2 += i, x1 += j;
		int q = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (c[i][j] && (out(y2 + i - 1, x1 + j - 1) || map[y2 + i][x1 + j]))q = 1;
			}
		if (q)y2 -= i, x1 -= j;
	}
}
void Print() {
	Gotoxy(4, 2);
	cout << "*按键*";
	Gotoxy(3, 18);
	cout << "俄罗斯方块(玩家一)";
	Gotoxy(4, 15);
	cout << "旋转:W 左移:A 右移:D 加速:S";
	Gotoxy(3, 64);
	cout<< "俄罗斯方块(玩家二)";
	Gotoxy(4, 59);
	cout << "旋转:I 左移:J 右移:L 加速:K";
	for (int i = 0; i < 12; i++)Map[0][i] = Map[21][i] = 7, map[0][i] = map[21][i] = 7;
	for (int i = 0; i < 22; i++)Map[i][0] = Map[i][11] = 7,map[i][0]=map[i][11]=7;
	for (int i = 0; i < 22; i++) {
		Gotoxy(5 + i, 15);
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
		Gotoxy(5 + i, 60);
		for (int j = 0; j < 12; j++) {
			if (map[i][j]) {
				Setcolor(map[i][j]);
				cout << "■";
				continue;
			}
			if (Exist1(i, j)) {
				Setcolor(color1);
				cout << "■";
				continue;
			}
			cout << "  ";
		}
		cout << endl;
	}
	Gotoxy(10, 43);
	cout << "Next:";
	for (int i = 0; i < 4; i++)
	{
		Gotoxy(11 + i, 43);
		for (int j = 0; j < 4; j++)
		{
			Setcolor(next_color);
			if (Next[i][j])
				cout << "■";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(15, 43);
	Setcolor(7);
	cout << "分数：";
	Gotoxy(16, 43);
	cout << scores << endl;

	Gotoxy(10, 88);
	cout << "Next:";
	for (int i = 0; i < 4; i++)
	{
		Gotoxy(11 + i, 88);
		for (int j = 0; j < 4; j++)
		{
			Setcolor(next_color1);
			if (Next1[i][j])
				cout << "■";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(15, 88);
	Setcolor(7);
	cout << "分数：";
	Gotoxy(16, 88);
	cout << scores1 << endl;
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
int check1() {
	for (int i = 1; i < 11; i++)
		if (map[1][i])return 0;
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (c[i][j] && map[y2 + i + 1][x1 + j]) q = 1;
	if (q) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) if (c[i][j]) map[y2 + i][x1 + j] = color1;
		return 1;
	}
	return 2;
}
void Delete() {
	int q, lines = 0;
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
void Delete1() {
	int q, lines = 0;
	for (int i = 1; i < 21; i++) {
		q = 0;
		for (int j = 1; j < 11; j++)if (!map[i][j])q = 1;
		if (!q) {
			map[i][1] = 7;
			lines++;
		}
	}
	for (int i = 20; i > 0; i--) {
		if (map[i][1] == 7) {
			for (int j = i; j > 1; j--)
				for (int k = 1; k < 11; k++)
					map[j][k] = map[j - 1][k];
			scores1 += 10;
		}
	}
	scores1 += (lines / 2) * 20;
	Print();
}
void Step() {
	int instru;
	int i1 = 1, i2 = 1, k = 0, p = 0;
	if (_kbhit()) {
		DWORD start = ::GetTickCount();
		while (_kbhit()) {
			instru = _getch();
			if (i1&&s1) {
				if (instru == 119) { cycle(); i1--; }
				else if (instru == 97) { Move(0, -1); i1--; }
				else if (instru == 100) { Move(0, 1); i1--; }
				else if (instru == 115) { Move(1, 0); i1--; k++; }
			}
			if (i2&&s2) {
				if (instru == 105) { cycle1(); i2--; }
				else if (instru == 106) { Move1(0, -1); i2--; }
				else if (instru == 108) { Move1(0, 1); i2--; }
				else if (instru == 107) { Move1(1, 0); i2--; p++; }
			}
			DWORD end = ::GetTickCount();
			if ( ((end - start) >= 10)) {
				break;
			}
		}if (i1 || k)Move(1, 0);
		if (i2 || p)Move1(1, 0);
	}
	if (i1 && i2) {
		Move(1, 0);
		Move1(1, 0);
	}
	//if (_kbhit()) {
	//	//instru = _getch();
	//	instru = _getch();
	//	//if (instru == 119) { cycle(); Move1(1, 0);	     return 1; }//w
	//	//if (instru == 97) { Move(0, -1); Move1(1, 0);	 return 1; }//a
	//	//if (instru == 100) { Move(0, 1);   Move1(1, 0);   return 1; }//d
	//	//if (instru == 115) { Move(1, 0);     return 0; }//s

	//	//if (instru == 105) { cycle1();	 Move(1, 0);    return 1; }//i
	//	//if (instru == 106) { Move1(0, -1);	Move(1, 0); return 1; }//j
	//	//if (instru == 108) { Move1(0, 1);  Move(1, 0);  return 1; }//l
	//	//if (instru == 107) { Move1(1, 0);  return 0; }//k

	// //  if (instru == 72) { cycle1(); Move(1, 0); return 1; }//上 
	//	//if (instru == 75) { Move1(0, -1); Move(1, 0); return 1; }
	//	//if (instru == 77) { Move1(0, 1);  Move(1, 0); return 1; }
	//	//if (instru == 80) { Move1(1, 0); return 0; }
	//}
}

///*int Step1() {
//	int instru;
//	if (_kbhit()) {
//		//instru = _getch();
//	    instru = _getch();
//		if (instru == 72) { cycle1();  return 1; }
//		if (instru == 75) { Move1(0, -1);  return 1; }
//		if (instru == 77) { Move1(0, 1);  return 1; }
//		if (instru == 80) { Move1(1, 0); return 0; }
//	}
//	return 0;
//}

int main() {
	int reb,reb1;
	HideCursor();
	Create();
	Create1();
	while (1) {
		if (s1)Delete();
		if (s2)Delete1();
		if (s1)reb = check();
		if (s2)reb1 = check1();
		if (reb == 0) {
			s1 = 0;
		}
		if (reb1 == 0) {
			s2 = 0;
		}
		if (!s1 && !s2) {
			Gotoxy(27, 40);
			Setcolor(4 + 8);
			cout << "Game Over:\t" << ((scores > scores1) ? "玩家一 胜" : ((scores == scores1) ? "平局" : "玩家二 胜")) << endl;
			Setcolor(7);
			break;
		}

		///if (reb == 0||reb1==0) {
		///	Gotoxy(32, 45);
		///Setcolor(4 + 8);
		///	cout << "Game Over!!!\n";
		///Setcolor(7); break;
	///	}
		if (reb == 1) {
			Create(); continue;
		}
		if (reb1 == 1) {
			Create1(); continue;
		}
		Step();
		//if (Step1());
		//else{Move1(1, 0);}
		while (_kbhit())int a = _getch();
		Print();
		Sleep(200);
	}
	return 0;
}

/*
#include<iostream>
#include<cstring>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
int main() {
	int instru;

		instru = _getch();
		instru = _getch();
		cout << instru;
	
	return 0;
}*/