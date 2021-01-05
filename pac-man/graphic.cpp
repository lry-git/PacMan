#include <Windows.h>
#include"graphic.h"
#include"control.h"
#pragma warning (disable:4996)

short Graph::speedEnemy[6] = { v5,v4,v3,v2,v1,vBoss };
string Graph::ManG[4] = { "↑" ,"↓" ,"←" ,"→" };
string Graph::EnemysG[4] = { "◆","◆","◆","◆" };
string Graph::BarrierG[8] = { "■" ,"·" ,"  " ,"  " ,"※" ,"◎" ,"★" };
Graph::Graph(int n) {
	int color =0;
	nestRow = 13;
	nestCol = 13;
	pointerG = "★";
	rank = 0;
	getDir = -1;
	me.Init(ManG, RowMax, 9, 1);
	me.SetVisit(1);
	//enemys.resize(n);
	//for (int i = 0; i < n; i++) {
	//	color = i % 7+1;
	//	enemys[i].Init(EnemysG, nestRow, nestCol, 1);
	//	enemys[i].SetColor(color);
	//	enemys[i].SetCD(Cold0*(i+1));
	//	//color = (color+1)%8;
	//}
	
	timeCnt=freezeTm=immortalTm = 0;
}

bool Graph:: CheckIntersect(Object& obj0, Object& obj1)const {
	return (obj0.GetRow() == obj1.GetRow()) &&
		(obj0.GetCol() == obj1.GetCol());
}
bool Graph:: IsBeanEnd() {
	return beanCnt <= 0;
}
bool Graph:: IsMeCaught() {
	return !me.IsAlive();
}
void Graph::startUp() {
	//P M

	Config::gotoxy(ColP * 2 , RowP);
	cout << pointerG;
	Config::gotoxy(ColP * 2+2, RowP);
	cout << "EASY";
	Config::gotoxy(ColP * 2 + 2, RowP+1);
	cout << "NORMAL";
	Config::gotoxy(ColP * 2 + 2, RowP+2);
	cout << "HARD";
}
void Graph:: MovePointer(char ch) {
	Config::setConsoleColor(White);
	if (ch == UP&&getDirCnt==1) {
		Config::gotoxy(ColP * 2, RowP + rank);
		cout << "  ";
		rank = (rank - 1 + 3) % 3;
		Config::gotoxy(ColP * 2, RowP + rank);
		cout << pointerG;
	}
	else if (ch == DOWN&& getDirCnt == 1) {
		Config::gotoxy(ColP * 2, RowP + rank);
		cout << "  ";
		rank = (rank + 1) % 3;
		Config::gotoxy(ColP * 2, RowP + rank);
		cout << pointerG;
	}
}
void Graph::initBackground() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	
	rank = 0;
	//time= 0;
	timeCnt = 0;
	me.Init(ManG, RowMax, 9, 1);
	me.SetVisit(1);
	beanCnt = 0;
	//enemys.resize(rank * 2 + 2);
	for (int i = 0; i < ColMax + 12+4; i++) {
		cout << "□";
		if (i <= ColMax + 1) {
			barrier[0][i].SetType(Wall);
			isCrossing[0][i] = -1;
		}
	}
	cout << '\n';
	for (int i = 1; i <= RowMax; i++) {
		cout << "□";
		Config::gotoxy(ColMax*2+2, i);
		cout << "□                          □\n";//26 ' '
		barrier[i][0].SetType(Wall);
		barrier[i][ColMax + 1].SetType(Wall);
		isCrossing[i][0] = -1;
		isCrossing[i][ColMax + 1] = -1;
	}
	//Config::setConsoleColor(White);
	for (int i = 0; i < ColMax + 12+4; i++) {
		cout << "□";
		if (i <= ColMax + 1) {
			barrier[RowMax+1][i].SetType(Wall);
			isCrossing[RowMax + 1][i] = -1;
		}
	}//↑↓←→
	Config::gotoxy(ColMax * 2 + 8, RowP);
	cout << "W:上移 S:下移";
	Config::gotoxy(ColMax * 2 + 8, RowP+1);
	cout << "H:确定 R:重玩";
	Config::gotoxy(ColMax * 2 + 4, RowP + 2);
	cout << "W:↑  S:↓  A:←  D:→";
	////count beans;***
}

void Graph::drawMap() {
	//count beans;***
	int type;
	//speedMe = speedEnemy[3 + rank];
	if (rank == 0)
		speedMe = v1;
	else if (rank == 1)
		speedMe = v1;
	else 
		speedMe = v0;
	//speedMe = v0;
	enemys.resize(rank * 2 + 2);
	for (int i = 0; i < enemys.size(); i++) {
		//color = i % 7 + 1;
		enemys[i].Init(EnemysG, nestRow, nestCol, 1);
		enemys[i].SetColor((i % 6 +2) | HighLight);
		enemys[i].SetCD(Cold0 * (i + 1));
		//color = (color+1)%8;
	}
	//ifstream in_f("map0.txt", ios::in);
	FILE* f_in = fopen("map0.txt", "r");
	if (f_in == NULL) {
		Config::gotoxy(0, RowMax + 2);
		cout << "file error\n";
		exit(-1);
	}
	for (int i = 1; i <= RowMax; i++) {
		for (int j = 1; j <= ColMax; j++) {
			//in_f >> type;
			fscanf(f_in, "%d,", &type);
			barrier[i][j].Init(BarrierG, i, j, 1, type);
			barrier[i][j].Display();
			if (type == Bean)
				beanCnt++;
		}
	}
	//init isCrossing
	for (int i = 1; i <= RowMax; i++) {
		for (int j = 1; j <= ColMax; j++) {
			char crossing = 1;
			if (barrier[i][j].GetType() == Wall ||
				barrier[i][j].GetType() == Grass) {
				isCrossing[i][j] = -1;
				continue;
			}
			char type0 = barrier[i - 1][j].GetType();
			char type1 = barrier[i + 1][j].GetType();
			char type2 = barrier[i][j - 1].GetType();
			char type3 = barrier[i][j + 1].GetType();
			if ((type0 == Wall || type0 == Grass) && (type1 == Wall || type1 == Grass))
				crossing = 0;
			if ((type2 == Wall || type2 == Grass) && (type3 == Wall || type3 == Grass))
				crossing = 0;
			isCrossing[i][j] = crossing;
			//Config::gotoxy(j * 2, i);
			//cout << crossing;
		}
	}
	Barrier & bt = barrier[me.GetRow()][me.GetCol()];
	if (bt.GetType() == Bean) {
		beanCnt--;
		bt.DeHp(1);
	}
	//display enemys
	//enemys[0].Display();
	me.SetColor(White | HighLight);
	me.Display();
}
//void Graph::ControlEnemy(Man& enemy, int rowTar, int colTar) {
//
//}

void Graph::MoveMe() {
	preRow = me.GetRow();
	preCol = me.GetCol();
	bool movable=0;
	if (getDir >= 0 && getDir == preDir &&
		(getDirCnt == 1 || getDirCnt > 4 && (timeCnt % speedMe) == 0)) {
		movable=1;
		//MoveEnemy();
	}
	if (!movable)
		return;
	if (barrier[preRow][preCol].GetType() != Grass)
		me.Clear();
	else
		me.SetVisit(1);
		
	me.Move();
	Barrier& bt = barrier[me.GetRow()][me.GetCol()];//new position

	switch (bt.GetType())
	{
	case Bean:
		me.Display();
		if (bt.IsAlive() && beanCnt > 0) {
			beanCnt--;
			bt.DeHp(1);
		}
		break;
	case Wall:
		me.SetPos(preRow, preCol);
		if (barrier[preRow][preCol].GetType() != Grass) {	
			me.Display();
		}
		else
			me.SetVisit(0);
		break;
	case Pause:
		//freezeTm += Cold1;
		if (bt.IsAlive()) {
			for (int i = 0; i < enemys.size(); i++)
				enemys[i].InCD(Cold1);
		}
		/*for (int i = 0; i < enemys.size(); i++)
			enemys[i].InCD(Cold0);*/
		bt.DeHp(1);
		me.Display();
		break;
	case Immortal:
		if(bt.IsAlive())
			immortalTm += Cold1;
		bt.DeHp(1);
		me.Display();
		break;
	case Nothing: case Nest:
		me.Display();
		break;
	default: //Grass
		me.SetVisit(0);
		bt.Display();
		break;
	}
	int len = enemys.size();
	for (int i = 0; i < len; i++) {
		if (CheckIntersect(me, enemys[i])) {
			me.DeHp(1);
			enemys[i].Display();
			break;
		}
	}
}
void Graph::MoveEnemy() {
	int len = enemys.size(),preDir;
	for (int i = 0; i < len; i++) {
		if (!enemys[i].IsCold()&&
			(timeCnt% speedEnemy[i])==0) {
		
		/*if ((timeCnt % speedEnemy[i]) == 0) {*/
			preRow = enemys[i].GetRow();
			preCol = enemys[i].GetCol();
			preDir = enemys[i].GetMovDir();
			if (barrier[preRow][preCol].IsAlive())
				barrier[preRow][preCol].Display();
			else
				enemys[i].Clear();
			enemys[i].Move();

			//will keep still
			//int j = 0;
			//for (; j < len; j++) {
			//	if (j == i || !enemys[j].IsAlive() || enemys[j].IsCold())
			//		continue;
			//	if ( enemys[i].GetRow() == enemys[j].GetRow()
			//		&& enemys[i].GetCol() == enemys[j].GetCol())
			//		break;
			//}
			//if (j < len)//crash
			//{
			//	enemys[i].SetPos(preRow, preCol);
			//	enemys[i].Display();
			//	continue;
			//}

			Barrier & bt = barrier[enemys[i].GetRow()][enemys[i].GetCol()];//new position
			switch (bt.GetType())
			{
			case Bean: case Pause: case Immortal:case Nothing: case Nest:		
				enemys[i].Display();
				break;
			case Wall: case Grass:
				enemys[i].SetPos(preRow, preCol);
				enemys[i].Display();
				break;
			default: 
				break;
			}
			// check if enemy catched me
			if (CheckIntersect(me, enemys[i])) {
				me.DeHp(1);
				//enemys[i].Display();
				break;
			}
		}
		/*else {
			Config::setConsoleColor(White);
			Config::gotoxy(0, RowMax + 2+i);
			cout << "  ";
			cout << enemys[i].GetCD();
		}*/

	}
}

void Graph:: InTime() {	
	MoveMe();
	MoveEnemy();
	timeCnt++;
	float tm = (float)enemys[0].GetCD() / 40;
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i].DeCD();
	}
	//float tm = (float)enemys[0].GetCD()/40;
	Config::setConsoleColor(Yellow|HighLight);
	Config::gotoxy(ColMax * 2 + 4, 10);
	cout << "MinCD:" << setprecision(1) << setiosflags(ios::fixed) << tm<<" s";
	if (immortalTm > 0)
		immortalTm--;
	me.DeCD();//for recover
}

void Graph::PrtScore(bool win) {
	float score = 0;
	if (win&&timeCnt<=MaxTime) {
		if (timeCnt <= 2400)
			score = 100;
		else
			score = 100 - (float)(timeCnt - 2400) * 100 / (2400 * 40);
	}
	Config::setConsoleColor(White| HighLight);
	Config::gotoxy(ColMax * 2 + 4, 13);
	if(rank==0)
		cout << "Score:" << setprecision(1) << setiosflags(ios::fixed) << score << "(Easy)";
	else if(rank==1)
		cout << "Score:" << setprecision(1) << setiosflags(ios::fixed) << score << "(Normal)";
	else
		cout << "Score:" << setprecision(1) << setiosflags(ios::fixed) << score << "(Hard)";
}
//void Graph::Fire (Man& enemys, vector<Bullet>& bullet) {
//	if (enemys.GetCD()== 0) {
//		int len = bullet.size(),i;
//		Bullet bt;
//		for (i = 0; i < len; i++) {
//			if (!bullet[i].IsAlive())
//				break;
//		}
//		if (i >= len) {
//			//bt.Init(bulletG,)
//		}
//		enemys.SetCD(20);
//	}
//}