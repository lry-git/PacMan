#pragma once
#include"graphic.h"
#include<cstdlib>
class Control {//only control the direction
public:
	struct CrossPoint//交叉路口
	{
		int row, col, parentId;//排数，列数，父节点在closePath中的id
		int disToSrc, cost;//当前点到源点的距离，权值
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
	int MinCostId();//获取openPath中权值最小的CrossPoint的id
	char GetControl(Graph & graph);//获取玩家输入
	void ControlEnemy(Graph & graph);//根据寻路算法，控制各个小怪的方向
	char SearchNext(Graph& graph, char dir, int id,int pId);//在一个交叉路口寻找下一个交叉路口
	int FindPoint(vector<CrossPoint> &vec,int r, int c)const;//查看vec中有没有row==r且col==c的CrossPoint
	int GetDis(int r0, int c0, int r1, int c1) {//获得两个点构成的矩形的长和宽的和
		return (r0 > r1 ? r0 - r1 : r1 - r0) +
			(c0 > c1 ? c0 - c1 : c1 - c0);
	}
	int Random(int left, int right) {//获得[left,right)之间的随机数
		//srand(timeCnt);
		return rand() % (right - left) + left;
	}
	void SetEnemyNum(int n=1) {//初始化path和tarPos的大小
		path.resize(n);
		tarPos.resize(n);
	}
	/*char SearchNext(Graph& graph, char dir, int& row, int& col)const;*/
private:
	int timeCnt;//计时
	int preRow, preCol;//上一个点的排数和列数
	int rowTar, colTar;//目标点的排数和列数
	vector<Pos> tarPos;//各个小怪的目标点
	short dirState[4];//获取方向键 0:W 1:S 2:A 3:D
	short actState[4];//获取功能键 0:J 1:K 2:R 3:H
	vector<CrossPoint> openPath;//寻路算法中，记录待选的CrossPoint
	vector<CrossPoint> closePath;//寻路算法中，记录选定的CrossPoint
	vector<vector<CrossPoint>> path;//保存寻路算法选好的各个小怪的路径
};