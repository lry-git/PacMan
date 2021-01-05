#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<conio.h>
#include<ctime>
#include<iomanip>
#include"object.h"
//#include"control.h"
using namespace std;
//class Graph;
class Graph {
public :
	Graph(int n=1);//构造函数初始化
	friend class Control;//Control是Graph的友元
	void initBackground();//初始化背景图像
	void startUp();//打印开始的图像
	void drawMap();//运行时画出地图
	void MoveMe();//沿着输入的方向将玩家移动一格
	void MoveEnemy();//沿着Control类决定的方向将各个小怪移动一格
	void MovePointer(char ch);//移动开始时的选择指针
	void InTime();//时间累加，调用MoveMe和MoveEnemy
	bool CheckIntersect(Object& obj0, Object& obj1)const;//检查玩家有没有和小怪重合
	bool IsBeanEnd();//检查豆子有没有吃完
	bool IsMeCaught();//检查玩家有没有被抓住
	void PrtScore(bool win);//打印得分
	int GetRank() {//获得难度等级
		return rank;
	}
	void SetMeDir(char dir) {//根据Control获得的玩家输入来设置玩家的移动方向
		me.SetMovDir(dir);
		if (barrier[me.GetRow()][me.GetCol()].GetType() != Grass)
			me.Display();
	}
	//bool GetControl();
	//void ControlEnemy(Man & enemy,int rowTar,int colTar);
	//void Fire(Man& enemys, vector<Bullet>& bullet);
	//vector<Bullet> myBullet, bullet;
protected:
	static string ManG[4];//保存玩家的图形
	static string EnemysG[4];//保存小怪的图形
	static string BarrierG[8];//保存障碍物的图形
	static short speedEnemy[6];//保存小怪的速度
	Man me;//创建玩家的对象
	vector<Man> enemys;//创建小怪的对象
	short speedMe;//保存玩家的速度
	string pointerG;//保存选择指针的图形
	int nestRow, nestCol;//保存巢穴的排数和列数
	Barrier barrier[RowMax+2][ColMax+2];//保存地图的障碍物
	int preRow, preCol,timeCnt,beanCnt;//记录上一个排数，列数，时间，豆子数量
	short freezeTm, immortalTm;//保留的变量
	char getDir , preDir, getDirCnt,rank;//记录玩家输入的方向，上一个方向，识别的键的个数，等级
	char isCrossing[RowMax + 2][ColMax + 2];//记录交叉路口
	//string bulletG[2] = { "·","◎" };
	//vector<Bullet> myBullet,bullet;
	//Bullet bulletTem;
};