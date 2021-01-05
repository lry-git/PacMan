#pragma once
#include"graphic.h"
#include<cstdlib>
class Control {//only control the direction
public:
	struct CrossPoint//����·��
	{
		int row, col, parentId;//���������������ڵ���closePath�е�id
		int disToSrc, cost;//��ǰ�㵽Դ��ľ��룬Ȩֵ
		CrossPoint(int r=1, int c=1) {
			row = r;
			col = c;
			parentId = 0;
			disToSrc = 0;
			cost = IntMax;
		}
	};
	struct Pos
	{
		int row, col;
	};
	int MinCostId();//��ȡopenPath��Ȩֵ��С��CrossPoint��id
	char GetControl(Graph & graph);//��ȡ�������
	void ControlEnemy(Graph & graph);//����Ѱ·�㷨�����Ƹ���С�ֵķ���
	char SearchNext(Graph& graph, char dir, int id,int pId);//��һ������·��Ѱ����һ������·��
	int FindPoint(vector<CrossPoint> &vec,int r, int c)const;//�鿴vec����û��row==r��col==c��CrossPoint
	int GetDis(int r0, int c0, int r1, int c1) {//��������㹹�ɵľ��εĳ��Ϳ�ĺ�
		return (r0 > r1 ? r0 - r1 : r1 - r0) +
			(c0 > c1 ? c0 - c1 : c1 - c0);
	}
	int Random(int left, int right) {//���[left,right)֮��������
		//srand(timeCnt);
		return rand() % (right - left) + left;
	}
	void SetEnemyNum(int n=1) {//��ʼ��path��tarPos�Ĵ�С
		path.resize(n);
		tarPos.resize(n);
	}
	/*char SearchNext(Graph& graph, char dir, int& row, int& col)const;*/
private:
	int timeCnt;//��ʱ
	int preRow, preCol;//��һ���������������
	int rowTar, colTar;//Ŀ��������������
	vector<Pos> tarPos;//����С�ֵ�Ŀ���
	short dirState[4];//��ȡ����� 0:W 1:S 2:A 3:D
	short actState[4];//��ȡ���ܼ� 0:J 1:K 2:R 3:H
	vector<CrossPoint> openPath;//Ѱ·�㷨�У���¼��ѡ��CrossPoint
	vector<CrossPoint> closePath;//Ѱ·�㷨�У���¼ѡ����CrossPoint
	vector<vector<CrossPoint>> path;//����Ѱ·�㷨ѡ�õĸ���С�ֵ�·��
};