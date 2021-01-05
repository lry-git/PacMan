#pragma once
#include<string>
#include<vector>
#include<unordered_map>
#include<iostream>
#include"config.h"
using namespace std;
//class Bullet;

class Object {
public:
	virtual void Display() = 0;//提供一个接口，展示一个实体的图像
	void Clear() {//清理当前位置的实体
		Config::gotoxy(col * 2, row);
		cout << "  ";
	}
	void SetVisit(bool b=1) {//isVis==1 实体可见，否则实体不可见
		isVis = b;// 1:visible 0:invisible
	}
	bool  IsVisible() {//判断实体是否可见
		return isVis;
	}
	int GetRow() {//获得row
		return row;
	}
	int GetCol() {//获得column
		return col;
	}
	char GetMovDir() {//获得移动实体的移动方向
		return movDir;
	}
	bool IsAlive() {//判断实体是否存在
		return HP > 0;
	}
	void SetPos(int r, int c) {//设置实体的位置
		row = r; col = c;
	}
	void SetMovDir(char dir) {//设置实体的移动方向
		movDir = dir;
	}
	void SetColor(short x) {//设置实体的颜色
		color = x;
	}
	void SetHp(int x) {//设置实体的生命值
		HP = x;
	}
	void InHp(int x) {//加HP
		HP += x; //suppose it will not overflow
		if (HP >= 100)
			HP = 100;
	}
	void DeHp(int x) {//减HP
		HP -= x;
		if (HP <= 0) {
			HP = 0;
			isVis = 0;//invisible
		}
	}
protected:
	int row, col, HP;//排数，列数，生命值
	short color,speed;//颜色，速度
	bool isVis;	//是否可见
	char movDir;//移动方向
};

class Man:public Object {
public:
	//初始化玩家或小怪的图形，row，column，生命值，移动方向
	void Init(const string* s, int r, int c, int hp = 1, char mD = LEFT);
	bool Move();//让玩家或小怪移动一格
	//void Fire(vector<Bullet> & bullet);
	void Display() {//展示玩家或小怪的图形
		Config::gotoxy(col*2, row);
		Config::setConsoleColor(color);
		cout << graph[movDir];
	}
	/*void SetFireDir(char dir) {
		fireDir = dir;
	}*/
	bool IsCold() {//小怪是否被冰冻
		return coolDown>0;
	}
	int GetCD() {//获得冰冻的剩余时间
		return coolDown;
	}
	void SetCD(unsigned x) {//设置小怪的冰冻时间
		coolDown = x;
	}
	void InCD(unsigned x) {//增加小怪的冰冻时间
		coolDown += x;
		if (coolDown >= Cold2)
			coolDown = Cold2;
	}
	void DeCD() {//减少小怪的冰冻时间
		coolDown--;
		if (coolDown <= 0)
			coolDown = 0;
	}
protected:
	string graph[4];//玩家或小怪在游戏中的图像
	//char fireDir;
	int coolDown;//冰冻的时间
};

//class MyTank :public Man{
//public:
//	/*MyTank() {};
//	MyTank(const string* s, int r, int c , int hp=1) {
//		MyTank::Init(s, r, c, hp, UP);
//	}*/
//	void Init(const string* s, int r, int c, int hp = 1, char fD = UP);
//	//void Move();
//	void Display() {
//		Config::gotoxy(col * 2, row);
//		Config::setConsoleColor(color);
//		cout << graph[fireDir];
//	}
//	void SetFireDir(char dir) {
//		fireDir = dir;
//	}
//
//private:
//	char fireDir;
//
//};

//class Bullet :public Man {
//public:
//	void Init(const string* s, int r, int c, int hp = 1,char tp=0);
//	void Display() {
//		if (row<1 || row>RowMax || col<1 || col>ColMax) {
//			HP = 0;
//			return;
//		}
//		Config::gotoxy(col * 2, row);
//		Config::setConsoleColor(color);
//		cout << graph[b_type];
//	}
//private:
//	//string graph[2];
//	char b_type;//0:normal 1:special
//};

class Barrier :public Object {
public://初始化障碍物的图形，row，column，生命值，类型（包括墙、豆子、草、巢穴、空、食物）
	void Init(const string* s, int r, int c, int hp = 1,char tp=Wall);
	void SetType(char tp);//设定类型
	char GetType() {//获得类型
		return type;
	}
	void Display() {//展示图形
		Config::gotoxy(col * 2, row);
		Config::setConsoleColor(color);
		cout << graph;
	}
private:
	//string graph[5];
	string graph;//图形
	char type;//类型
};
