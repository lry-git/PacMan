#pragma once
enum Num{Num0=1,Num1=3,IntMax=0x7fffffff};
enum Pos{RowMax=28,ColMax=25,RowP=20,ColP=12};//��ͼ�������������������ʼ�����������������
enum Dir { UP, DOWN, LEFT, RIGHT };
enum Type{Wall,Bean,Nothing,Nest,Grass,Pause,Immortal};//�ϰ�������
enum Time{Cold0=100,Cold1=200,Cold2=360,MaxTime=12000};//2.5s 5s 10s 300s
enum Speed { V0 = 1, V1 = 3, V2 = 7, V3 = 15, V4 = 31,V5=63 };
enum SpeedNew{v0=4,v1=6,v2=8,v3=10,v4=12,v5=16,vBoss=5};
enum ForeColor {Black,Blue,Green,Cyan,Red,Pink,Yellow,White,HighLight};
class Config {
public:
	static void gotoxy(int x, int y);//������ƶ���x�У�y��
	static void clrscr();//������Ļ
	static bool setConsoleColor(short wAttributes);//������ɫ
};
