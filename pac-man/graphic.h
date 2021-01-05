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
	Graph(int n=1);//���캯����ʼ��
	friend class Control;//Control��Graph����Ԫ
	void initBackground();//��ʼ������ͼ��
	void startUp();//��ӡ��ʼ��ͼ��
	void drawMap();//����ʱ������ͼ
	void MoveMe();//��������ķ�������ƶ�һ��
	void MoveEnemy();//����Control������ķ��򽫸���С���ƶ�һ��
	void MovePointer(char ch);//�ƶ���ʼʱ��ѡ��ָ��
	void InTime();//ʱ���ۼӣ�����MoveMe��MoveEnemy
	bool CheckIntersect(Object& obj0, Object& obj1)const;//��������û�к�С���غ�
	bool IsBeanEnd();//��鶹����û�г���
	bool IsMeCaught();//��������û�б�ץס
	void PrtScore(bool win);//��ӡ�÷�
	int GetRank() {//����Ѷȵȼ�
		return rank;
	}
	void SetMeDir(char dir) {//����Control��õ����������������ҵ��ƶ�����
		me.SetMovDir(dir);
		if (barrier[me.GetRow()][me.GetCol()].GetType() != Grass)
			me.Display();
	}
	//bool GetControl();
	//void ControlEnemy(Man & enemy,int rowTar,int colTar);
	//void Fire(Man& enemys, vector<Bullet>& bullet);
	//vector<Bullet> myBullet, bullet;
protected:
	static string ManG[4];//������ҵ�ͼ��
	static string EnemysG[4];//����С�ֵ�ͼ��
	static string BarrierG[8];//�����ϰ����ͼ��
	static short speedEnemy[6];//����С�ֵ��ٶ�
	Man me;//������ҵĶ���
	vector<Man> enemys;//����С�ֵĶ���
	short speedMe;//������ҵ��ٶ�
	string pointerG;//����ѡ��ָ���ͼ��
	int nestRow, nestCol;//���泲Ѩ������������
	Barrier barrier[RowMax+2][ColMax+2];//�����ͼ���ϰ���
	int preRow, preCol,timeCnt,beanCnt;//��¼��һ��������������ʱ�䣬��������
	short freezeTm, immortalTm;//�����ı���
	char getDir , preDir, getDirCnt,rank;//��¼�������ķ�����һ������ʶ��ļ��ĸ������ȼ�
	char isCrossing[RowMax + 2][ColMax + 2];//��¼����·��
	//string bulletG[2] = { "��","��" };
	//vector<Bullet> myBullet,bullet;
	//Bullet bulletTem;
};