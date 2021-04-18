//#include<iostream>
//#include<cstring>
//#include<conio.h>
//#include<windows.h>
//#include<time.h>
//using namespace std;
//struct player {
//	int x;
//	int y;
//	int color;
//	int scores;
//	int map[25][25];
//	int type;
//	int next_color=3;
//	int cube[4][4];
//	int next[4][4]= { 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 };
//	int Life=1;
//}pker[2];
//int blocks[7][4][4] = { 0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
//	0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,
//	0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,
//	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
//	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
//	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
//	0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 };
//void Setcolor(int color) {
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
//} //设置颜色：0黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色 8加强色
//
//void HideCursor() {
//	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
//	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
//} //隐藏光标
//void Gotoxy(int y, int x) {
//	COORD c;
//	c.X = x;
//	c.Y = y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
//	HideCursor();
//}//指定位置输出
//
//void Create(player &a) {
//	srand(time(0));
//	a.color = a.next_color;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)a.cube[i][j] = a.next[i][j];
//	a.x = 3; a.y = -1;
//	a.type = rand() % 7;
//	a.next_color = rand() % 6 + 1;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)a.next[i][j] = blocks[a.type][i][j];
//}
///*bool out(int i, int j) {//是否出界面边框
//	if (i < 0 || i >= 20) return true;
//	if (j < 0 || j >= 10) return true;
//	return false;
//}*/
//void cycle(player &a) {
//	int b[4][4];
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)b[3 - i][j] = a.cube[j][i];
//	int q = 0;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//			//if (b[i][j] && (out(a.y + i - 1, a.x + j - 1) || a.map[a.y + i][a.x + j]))  q = 1;
//			if (b[i][j] && ((a.y + i - 1)<0||(a.y + i - 1)>21||(a.x + j - 1)<0|| (a.x + j - 1)>11 || a.map[a.y + i][a.x + j]))  q = 1;
//
//	if (!q) {
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++)a.cube[i][j] = b[i][j];
//	}
//}
//void Move(player &a,int i, int j) {
//	a.y += i, a.x += j;
//	int q = 0;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++) {
//			if (a.cube[i][j] && ((a.y + i - 1) < 0 || (a.y + i - 1) > 21 || (a.x + j - 1) < 0 || (a.x + j - 1) > 11 || a.map[a.y + i][a.x + j]))q = 1;
//		}
//	if (q)a.y -= i, a.x -= j;
//}
//void Print() {
//	Gotoxy(3, 2);
//	cout << "*按键*";
//	Gotoxy(1, 18);
//	cout << "俄罗斯方块(玩家一)";
//	Gotoxy(3, 15);
//	cout << "旋转:W 左移:A 右移:D 加速:S";
//	Gotoxy(1, 64);
//	cout << "俄罗斯方块(玩家二)";
//	Gotoxy(3, 59);
//	cout << "旋转:I 左移:J 右移:L 加速:K";
//	for (int i = 0; i < 12; i++)pker[0].map[0][i] = pker[0].map[21][i] = 7, pker[1].map[0][i] = pker[1].map[21][i] = 7;
//	for (int i = 0; i < 22; i++)pker[0].map[i][0] = pker[0].map[i][11] = 7, pker[1].map[i][0] = pker[1].map[i][11] = 7;
//	for (int i = 0; i < 22; i++) {
//		Gotoxy(5 + i, 15);
//		for (int j = 0; j < 12; j++) {
//			if (pker[0].map[i][j]) {
//				Setcolor(pker[0].map[i][j]);
//				cout << "■";
//				continue;
//			}
//			if (((pker[0].y <= i && i <= pker[0].y+3) && (pker[0].x <= j && j <= pker[0].x+3))&& pker[0].cube[i - pker[0].y][j - pker[0].x])
//			{
//				Setcolor(pker[0].color);
//				cout << "■";
//				continue;
//			}
//			cout << "  ";
//		}
//		Gotoxy(5 + i, 60);
//		for (int j = 0; j < 12; j++) {
//			if (pker[1].map[i][j]) {
//				Setcolor(pker[1].map[i][j]);
//				cout << "■";
//				continue;
//			}
//			if (((pker[1].y <= i && i <= pker[1].y + 3) && (pker[1].x <= j && j <= pker[1].x + 3)) && pker[1].cube[i - pker[1].y][j - pker[1].x])
//			{
//				Setcolor(pker[1].color);
//				cout << "■";
//				continue;
//			}
//			cout << "  ";
//		}
//		cout << endl;
//	}
//	Gotoxy(10, 43);
//	cout << "Next:";
//	for (int i = 0; i < 4; i++)
//	{
//		Gotoxy(11 + i, 43);
//		for (int j = 0; j < 4; j++)
//		{
//			Setcolor(pker[0].next_color);
//			if (pker[0].next[i][j])
//				cout << "■";
//			else cout << "  ";
//		}cout << endl;
//	}
//	Gotoxy(15, 43);
//	Setcolor(7);
//	cout << "分数：";
//	Gotoxy(16, 43);
//	cout << pker[0].scores << endl;
//
//	Gotoxy(10, 88);
//	cout << "Next:";
//	for (int i = 0; i < 4; i++)
//	{
//		Gotoxy(11 + i, 88);
//		for (int j = 0; j < 4; j++)
//		{
//			Setcolor(pker[1].next_color);
//			if (pker[1].next[i][j])
//				cout << "■";
//			else cout << "  ";
//		}cout << endl;
//	}
//	Gotoxy(15, 88);
//	Setcolor(7);
//	cout << "分数：";
//	Gotoxy(16, 88);
//	cout << pker[1].scores << endl;
//}
//int check(player &a) {
//	for (int i = 1; i < 11; i++)
//		if (a.map[1][i])return 0;
//	int q = 0;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//			if (a.cube[i][j] && a.map[a.y + i + 1][a.x + j]) q = 1;
//	if (q) {
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++) if (a.cube[i][j]) a.map[a.y + i][a.x + j] = a.color;
//		return 1;
//	}
//	return 3;
//}
//void Delete(player &a) {
//	int q, lines = 0;
//	for (int i = 1; i < 21; i++) {
//		q = 0;
//		for (int j = 1; j < 11; j++)if (!a.map[i][j])q = 1;
//		if (!q) {
//			a.map[i][1] = 7;
//			lines++;
//		}
//	}
//	for (int i = 20; i > 0; i--) {
//		if (a.map[i][1] == 7) {
//			for (int j = i; j > 1; j--)
//				for (int k = 1; k < 11; k++)
//					a.map[j][k] = a.map[j - 1][k];
//			a.scores += 10;
//		}
//	}
//	a.scores += (lines / 2) * 20;
//	Print();
//}
//void Control(player &a, player &b) {
//	int instru;
//	int i1 = 1, i2 = 1, k = 0, p = 0;
//	if (_kbhit()) {
//		DWORD start = ::GetTickCount();
//		while (_kbhit()) {
//			instru = _getch();
//			if (i1 && a.Life) {
//				if (instru == 119) { cycle(a); i1--; }
//				else if (instru == 97) { Move(a, 0, -1); i1--; }
//				else if (instru == 100) { Move(a, 0, 1); i1--; }
//				else if (instru == 115) { Move(a, 1, 0); i1--; k++; }
//			}
//			if (i2 && b.Life) {
//				if (instru == 105) { cycle(b); i2--; }
//				else if (instru == 106) { Move(b, 0, -1); i2--; }
//				else if (instru == 108) { Move(b, 0, 1); i2--; }
//				else if (instru == 107) { Move(b, 1, 0); i2--; p++; }
//			}
//			DWORD end = ::GetTickCount();
//			if (((end - start) >= 10)) {
//				break;
//			}
//		}if (i1 || k)Move(a, 1, 0);
//		if (i2 || p)Move(b, 1, 0);
//	}
//	if (i1 && i2) {
//		Move(a, 1, 0);
//		Move(b, 1, 0);
//	}
//	while (_kbhit())int a = _getch();
//}
//int main() {
//	//DWORD s1 = ::GetTickCount();
//		int reb=3, reb1=3;
//		Create(pker[0]);
//		Create(pker[1]);
//		while (1) {
//			if (pker[0].Life)Delete(pker[0]);
//			if (pker[1].Life)Delete(pker[1]);
//			if (pker[0].Life)reb = check(pker[0]);
//			if (pker[1].Life)reb1 = check(pker[1]);
//			if (reb == 0) {
//				pker[0].Life = 0;
//			}
//			if (reb1 == 0) {
//				pker[1].Life = 0;
//			}
//			if (!pker[0].Life && !pker[1].Life) {
//				Gotoxy(27, 40);
//				Setcolor(4 + 8);
//				cout << "Game Over:\t" << ((pker[0].scores > pker[1].scores) ? "玩家一 胜" : ((pker[0].scores == pker[1].scores) ? "平局" : "玩家二 胜")) << endl;
//				Setcolor(7);
//				break;
//			}
//			if (reb == 1) {
//				Create(pker[0]); continue;
//			}
//			if (reb1 == 1) {
//				Create(pker[1]); continue;
//			}
//			Control(pker[0],pker[1]);
//			
//			Print();
//			Sleep(180);
//			//DWORD s2 = ::GetTickCount();
//			//cout << s2 - s1;
//			//break;
//			
//		}
//		return 0;
//	}