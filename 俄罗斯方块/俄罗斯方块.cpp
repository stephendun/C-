#include<iostream>
#include<cstring>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
struct player {//玩家定义
	int x = 3;
	int y = 0;//方块左上角的坐标
	int color;//当前方块的颜色
	int scores;//分数
	int map[25][25];//地图
	int type;//方块种类
	int next_color = 5;//下一个方块颜色，初始为紫色
	int cube[4][4];//当前方块
	int next[4][4] = { 0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0 };//下一个方块，初始为z型
	int Life = 1;//玩家是否失败，0为失败
}pker[2];
int blocks[7][4][4] = {
	0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,
	0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0 };//俄罗斯方块的7种定义
void Setcolor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + 8);
} //设置颜色：0黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色 8加强色

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
} //隐藏光标
void Gotoxy(int y, int x) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	HideCursor();
}//指定位置输出
void Create(player& a) {//    传入参数：玩家一或玩家二      将下一个方块付给当前方块，并且生成玩家下一个方块，
	srand(time(0));
	a.color = a.next_color;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)a.cube[i][j] = a.next[i][j];//将下一个方块赋给当前方块
	a.x = 3; a.y = 0;//定义初始的方块左上角坐标
	a.type = rand() % 7;//下一个方块的种类
	a.next_color = rand() % 6 + 1;//下一个方块的颜色
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)a.next[i][j] = blocks[a.type][i][j];//将下一个方块定义
}
void Cycle(player& a) {//传入参数：玩家    将玩家的当前方块旋转
	int b[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)b[3 - i][j] = a.cube[j][i];//储存当前的方块
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (b[i][j] && ((a.y + i - 1) < 0 || (a.y + i - 1) > 21 || (a.x + j - 1) < 0 || (a.x + j - 1) > 11 || a.map[a.y + i][a.x + j]))  q = 1;
	if (!q) {//如果不可以旋转，重新赋予原来的方块
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)a.cube[i][j] = b[i][j];
	}
}
void Move(player& a, int i, int j) {//当前方块的移动
	a.y += i, a.x += j;
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (a.cube[i][j] && ((a.y + i - 1) < 0 || (a.y + i - 1) > 21 || (a.x + j - 1) < 0 || (a.x + j - 1) > 11 || a.map[a.y + i][a.x + j]))q = 1;
		}
	if (q)a.y -= i, a.x -= j;
}
void Print() {//打印游戏界面
	Setcolor(7);
	Gotoxy(3, 2);
	cout << "*按键*";
	Gotoxy(1, 18);
	cout << "俄罗斯方块(玩家一)";
	Gotoxy(3, 15);
	cout << "旋转:W 左移:A 右移:D 加速:S";
	Gotoxy(1, 64);
	cout << "俄罗斯方块(玩家二)";
	Gotoxy(3, 59);
	cout << "旋转:I 左移:J 右移:L 加速:K";
	for (int i = 0; i < 12; i++)pker[0].map[0][i] = pker[0].map[21][i] = 7, pker[1].map[0][i] = pker[1].map[21][i] = 7;//游戏周围边框白色
	for (int i = 0; i < 22; i++)pker[0].map[i][0] = pker[0].map[i][11] = 7, pker[1].map[i][0] = pker[1].map[i][11] = 7;
	for (int i = 0; i < 22; i++) {
		Gotoxy(5 + i, 15);
		for (int j = 0; j < 12; j++) {
			if (pker[0].map[i][j]) {
				Setcolor(pker[0].map[i][j]);
				cout << "■";
				continue;
			}
			if (((pker[0].y <= i && i <= pker[0].y + 3) && (pker[0].x <= j && j <= pker[0].x + 3)) && pker[0].cube[i - pker[0].y][j - pker[0].x])
			{
				Setcolor(pker[0].color);
				cout << "■";
				continue;
			}
			cout << "  ";
		}
		Gotoxy(5 + i, 60);
		for (int j = 0; j < 12; j++) {
			if (pker[1].map[i][j]) {
				Setcolor(pker[1].map[i][j]);
				cout << "■";
				continue;
			}
			if (((pker[1].y <= i && i <= pker[1].y + 3) && (pker[1].x <= j && j <= pker[1].x + 3)) && pker[1].cube[i - pker[1].y][j - pker[1].x])
			{
				Setcolor(pker[1].color);
				cout << "■";
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
				cout << "■";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(15, 43);
	Setcolor(7);
	cout << "分数：";
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
				cout << "■";
			else cout << "  ";
		}cout << endl;
	}
	Gotoxy(15, 88);
	Setcolor(7);
	cout << "分数：";
	Gotoxy(16, 88);
	cout << pker[1].scores << endl;

}
int Check(player& a) {//检查方块的移动是否成立，以及玩家是否失败
	for (int i = 1; i < 11; i++)
		if (a.map[1][i]) {
			a.Life = 0;
			return 0;
		}//如果最顶层有方块，则玩家失败
	int q = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (a.cube[i][j] && a.map[a.y + i + 1][a.x + j]) q = 1;//如果方块和图中已有的方块重合则不允许
	if (q) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) if (a.cube[i][j]) a.map[a.y + i][a.x + j] = a.color;//如果无法移动，就将其打印出来
		return 1;
	}
	return 3;//可以移动返回数字3
}
void Delete(player& a) {//清除已经满行的部分
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
void Control(player& a, player& b) {//从键盘读取玩家的控制操作
	int instru;
	int i1 = 1, i2 = 1, k = 0, p = 0;//i1，i2代表玩家一二的操作信息是否已经读取，k，p代表玩家是否按的加速操作
	if (_kbhit()) {
		DWORD start = ::GetTickCount();//定义读取的初始时间
		while (_kbhit()) {
			instru = _getch();
			if (i1 && a.Life) {//玩家操作读取过或者玩家已经失败就不再读取他的操作信息
				if (instru == 119) { Cycle(a); i1--; }//旋转
				else if (instru == 97) { Move(a, 0, -1); i1--; }//左移
				else if (instru == 100) { Move(a, 0, 1); i1--; }//右移
				else if (instru == 115) { Move(a, 1, 0); i1--; k++; }//加速
			}
			if (i2 && b.Life) {
				if (instru == 105) { Cycle(b); i2--; }//旋转
				else if (instru == 106) { Move(b, 0, -1); i2--; }//左移
				else if (instru == 108) { Move(b, 0, 1); i2--; }//右移
				else if (instru == 107) { Move(b, 1, 0); i2--; p++; }//加速
			}
			DWORD end = ::GetTickCount();//读取的最终时间
			if (((end - start) >= 10)) {//一次读取时间不能超过10ms
				break;
			}
		}if (i1 || k)Move(a, 1, 0);//如果玩家没有输入操作，或者输入的加速操作，那么其方块就往下移动一格
		if (i2 || p)Move(b, 1, 0);
	}
	if (i1 && i2) {//如果两位玩家都没有输入 ，那么都往下移动一格
		Move(a, 1, 0);
		Move(b, 1, 0);
	}
	while (_kbhit())int a = _getch();//清空输入缓冲区的按键操作，避免对下次操作影响
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
		cout << "Game Over:\t" << ((pker[0].scores > pker[1].scores) ? "玩家一 胜" : ((pker[0].scores == pker[1].scores) ? "平局" : "玩家二 胜")) << endl;
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