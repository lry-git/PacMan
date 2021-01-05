#include<iostream>
#include<string>
#include<Windows.h>
#include<string.h>
#include"object.h"
#include"graphic.h"
#include"control.h"
#pragma warning(disable:4996)
using namespace std;
//string tem = "↑↓←→·□★◎■◆*┣┫┳┻ ※～●▓"; 
////char tem0[5] = "1234";
//char a[2][2] = { {0,1},{2,3} };
//char (* b)[2] = a;
//
//class A {
//	int ax, ay;
//
//public:
//	virtual void f() {
//		cout << "A.f\n";
//		//MessageBox(NULL, tem0, tem0, NULL);
//	}
//	void g() {
//		f();
//	}
//};
//class B :public A {
//
//public:
//	void f() {
//		cout << "B.f\n";
//	}
//	
//};

int main() {
	char ch=0;
	/*int numOfEnemy=4;
	if (numOfEnemy >= 6)
		numOfEnemy = 6;*/

	Graph graph;
	Control control;

	/*graph.initBackground();*/
	//Man enemys;
	//while (1) {
	//	if (graph.IsMeCaught() || graph.IsBeanEnd()
	//		|| control.GetControl(graph)<0)
	//		break;
	//	control.ControlEnemy(graph);
	//	graph.InTime();
	//	Sleep(25);
	//	//Sleep(50);
	//}
	while (1) {
		ch = 0;
		Config::clrscr();
		graph.initBackground();
		graph.startUp();
		while (1) {
			ch = control.GetControl(graph);
			//ch = 0;
			if (ch == 4)//confirm
				break;
			else if (ch >=0)
				graph.MovePointer(ch);
			Sleep(25);
		}
		control.SetEnemyNum(graph.GetRank() * 2 + 2);
		graph.drawMap();
		while (1) {
			if (graph.IsMeCaught() || graph.IsBeanEnd())
				break;
			ch = control.GetControl(graph);
			if (ch < 0)
				break;
			if(ch<4)
				graph.SetMeDir(ch);
			control.ControlEnemy(graph);
			graph.InTime();
			Sleep(25);
			//Sleep(50);
		}
		Config::setConsoleColor(White);
		Config::gotoxy(ColMax * 2 + 4, 1);
		if (graph.IsBeanEnd()) {
			cout << "Congratulations!\n";
			graph.PrtScore(1);
		}
		else if (ch <0)
			continue;
		else //if(graph.IsMeCaught())
		{
			cout << "You are caught\n";
			graph.PrtScore(0);
		}
		Config::gotoxy(ColMax * 2 + 4, 3);
		cout << "play again?[y/n]";
		ch = 0;
		while (ch != 'n' && ch != 'y')
			ch=getch();
		Config::gotoxy(ColMax * 2 + 4, 4);
		cout << ch;
		if (ch == 'n')
			break;
	}

	Config::gotoxy(0, RowMax+3);
	
}