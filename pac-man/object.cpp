#include<iostream>
#include<string>
#include<Windows.h>
#include"object.h"
using namespace std;

//Man::Man(const string* s, int r, int c , int hp) {
//	/*row = r;
//	col = c;
//	graph[0] = s[0];
//	graph[1] = s[1];
//	graph[2] = s[2];
//	graph[3] = s[3];
//	movDir = DOWN;
//	HP = hp;*/
//	Init(s, r, c, hp, DOWN);
//}
void Man::Init(const string* s, int r, int c, int hp , char mD) {
	row = r;
	col = c;
	graph[0] = s[0];
	graph[1] = s[1];
	graph[2] = s[2];
	graph[3] = s[3];
	movDir =mD;
	//fireDir = mD;
	HP = hp;
	coolDown = 0;
}
bool Man::Move() {
	bool b = 1;
	//Clear();
	switch (movDir)
	{
	case UP:
		if (row > 1)
			row--;
		else
			b= 0;
		break;
	case DOWN:
		if (row < RowMax)
			row++;
		else
			b= 0;
		break;
	case LEFT:
		if (col > 1)
			col--;
		else
			b= 0;
		break;
	case RIGHT:
		if (col < ColMax)
			col++;
		else
			b= 0;
		break;
	default:
		break;
	}
	//Display();
	return b;
}

//void Man::Fire(vector<Bullet>& bullet) {
//	if (coolDown == 0) {
//		int len = bullet.size(),i;
//		Bullet bt;
//		for (i = 0; i < len; i++) {
//			if (!bullet[i].IsAlive())
//				break;
//		}
//		if (i >= len) {
//			bt.Init()
//		}
//		coolDown = 20;
//	}
//}
//void MyTank::Init(const string* s, int r, int c, int hp , char fD) {
//	Man::Init(s, r, c, hp);
//	fireDir = fD;
//}

//void Bullet::Init(const string* s, int r, int c, int hp,char tp ) {
//	graph[0] = s[0];
//	graph[1] = s[1];
//	color = White;
//	b_type = tp;
//	row = r;
//	col = c;
//	HP = hp;
//}

void Barrier::Init(const string* s, int r, int c, int hp,char tp) {
	/*graph[0] = s[0];
	graph[1] = s[1];
	graph[2] = s[2];
	graph[3] = s[3];
	graph[4] = s[4];*/
	graph = s[tp];
	row = r;
	col = c;
	HP = hp;
	SetType(tp);
}
void Barrier::SetType(char tp) {
	type = tp;
	switch (type)
	{
	case Wall: case Nothing: case Nest:
		color = White; break;
	case Bean:
		color = Yellow; break;
	case Grass:
		color = Green; break;
	case Pause:
		color = Red; break;
	case Immortal:
		color = Blue|HighLight; break;
	default:
		break;
	}
}
//void MyTank::Move() {
//	Clear();
//	switch (movDir)
//	{
//	case UP:
//		if (row > 1)
//			row--;
//		break;
//	case DOWN:
//		if (row < RowMax)
//			row++;
//		break;
//	case LEFT:
//		if (col > 1)
//			col--;
//		break;
//	case RIGHT:
//		if (col < ColMax)
//			col++;
//		break;
//	default:
//		break;
//	}
//	Display();
//	
//}
