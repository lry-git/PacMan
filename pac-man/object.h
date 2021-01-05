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
	virtual void Display() = 0;//�ṩһ���ӿڣ�չʾһ��ʵ���ͼ��
	void Clear() {//����ǰλ�õ�ʵ��
		Config::gotoxy(col * 2, row);
		cout << "  ";
	}
	void SetVisit(bool b=1) {//isVis==1 ʵ��ɼ�������ʵ�岻�ɼ�
		isVis = b;// 1:visible 0:invisible
	}
	bool  IsVisible() {//�ж�ʵ���Ƿ�ɼ�
		return isVis;
	}
	int GetRow() {//���row
		return row;
	}
	int GetCol() {//���column
		return col;
	}
	char GetMovDir() {//����ƶ�ʵ����ƶ�����
		return movDir;
	}
	bool IsAlive() {//�ж�ʵ���Ƿ����
		return HP > 0;
	}
	void SetPos(int r, int c) {//����ʵ���λ��
		row = r; col = c;
	}
	void SetMovDir(char dir) {//����ʵ����ƶ�����
		movDir = dir;
	}
	void SetColor(short x) {//����ʵ�����ɫ
		color = x;
	}
	void SetHp(int x) {//����ʵ�������ֵ
		HP = x;
	}
	void InHp(int x) {//��HP
		HP += x; //suppose it will not overflow
		if (HP >= 100)
			HP = 100;
	}
	void DeHp(int x) {//��HP
		HP -= x;
		if (HP <= 0) {
			HP = 0;
			isVis = 0;//invisible
		}
	}
protected:
	int row, col, HP;//����������������ֵ
	short color,speed;//��ɫ���ٶ�
	bool isVis;	//�Ƿ�ɼ�
	char movDir;//�ƶ�����
};

class Man:public Object {
public:
	//��ʼ����һ�С�ֵ�ͼ�Σ�row��column������ֵ���ƶ�����
	void Init(const string* s, int r, int c, int hp = 1, char mD = LEFT);
	bool Move();//����һ�С���ƶ�һ��
	//void Fire(vector<Bullet> & bullet);
	void Display() {//չʾ��һ�С�ֵ�ͼ��
		Config::gotoxy(col*2, row);
		Config::setConsoleColor(color);
		cout << graph[movDir];
	}
	/*void SetFireDir(char dir) {
		fireDir = dir;
	}*/
	bool IsCold() {//С���Ƿ񱻱���
		return coolDown>0;
	}
	int GetCD() {//��ñ�����ʣ��ʱ��
		return coolDown;
	}
	void SetCD(unsigned x) {//����С�ֵı���ʱ��
		coolDown = x;
	}
	void InCD(unsigned x) {//����С�ֵı���ʱ��
		coolDown += x;
		if (coolDown >= Cold2)
			coolDown = Cold2;
	}
	void DeCD() {//����С�ֵı���ʱ��
		coolDown--;
		if (coolDown <= 0)
			coolDown = 0;
	}
protected:
	string graph[4];//��һ�С������Ϸ�е�ͼ��
	//char fireDir;
	int coolDown;//������ʱ��
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
public://��ʼ���ϰ����ͼ�Σ�row��column������ֵ�����ͣ�����ǽ�����ӡ��ݡ���Ѩ���ա�ʳ�
	void Init(const string* s, int r, int c, int hp = 1,char tp=Wall);
	void SetType(char tp);//�趨����
	char GetType() {//�������
		return type;
	}
	void Display() {//չʾͼ��
		Config::gotoxy(col * 2, row);
		Config::setConsoleColor(color);
		cout << graph;
	}
private:
	//string graph[5];
	string graph;//ͼ��
	char type;//����
};
