#include"control.h"
char Control::GetControl(Graph& graph) {
	graph.getDir = -1;
	Man& me = graph.me;
	//vector<Man>& enemys = graph.enemys;
	actState[2] = GetKeyState('R');
	actState[3] = GetKeyState('H');
	if (actState[2] < 0)
		return -1;//restart
	else if (actState[3] < 0)
		return 4;//confirm
	actState[0] = GetKeyState('J');
	actState[1] = GetKeyState('K');

	dirState[0] = GetKeyState('W');
	dirState[1] = GetKeyState('S');
	dirState[2] = GetKeyState('A');
	dirState[3] = GetKeyState('D');
	graph.preDir = me.GetMovDir();
	if (dirState[0] < 0) {
		//me.SetMovDir(UP);
		/*if (actState[1] >= 0)
			me.SetFireDir(UP);*/
		//enemys[0].SetMovDir(UP);
		graph.getDir = UP;
		if (graph.getDirCnt < 8)
			graph.getDirCnt++;
		return UP;
	}
	else if (dirState[1] < 0) {
		//me.SetMovDir(DOWN);
		/*if (actState[1] >= 0)
			me.SetFireDir(DOWN);*/
		//enemys[0].SetMovDir(DOWN);
		graph.getDir = DOWN;
		if (graph.getDirCnt < 8)
			graph.getDirCnt++;
		return DOWN;
	}
	else if (dirState[2] < 0) {
		//me.SetMovDir(LEFT);
		/*if (actState[1] >= 0)
			me.SetFireDir(LEFT);*/
		//enemys[0].SetMovDir(LEFT);
		graph.getDir = LEFT;
		if (graph.getDirCnt < 8)
			graph.getDirCnt++;
		return LEFT;
	}
	else if (dirState[3] < 0) {
		//me.SetMovDir(RIGHT);
		/*if (actState[1] >= 0)
			me.SetFireDir(RIGHT);*/
		//enemys[0].SetMovDir(RIGHT);
		graph.getDir = RIGHT;
		if (graph.getDirCnt < 8)
			graph.getDirCnt++;
		return RIGHT;
	}
	else
		graph.getDirCnt = 0;
	/*if(graph.barrier[me.GetRow()][me.GetCol()].GetType() != Grass)
		me.Display();*/
	return 5;
	
}

void Control::ControlEnemy(Graph& graph) {
	vector<Man>& enemys = graph.enemys;
	//rowTar = graph.me.GetRow();
	//colTar = graph.me.GetCol();
	for (int i = 0; i < tarPos.size(); i++) {
		tarPos[i].row= graph.me.GetRow();
		tarPos[i].col= graph.me.GetCol();
	}

	CrossPoint cpTem;
	int cnt,count=0;
	int len = enemys.size(),id=0;
	timeCnt = graph.timeCnt;
	/*if ((timeCnt & V1) != 0)
		return;*/
	for (int i = 0; i < len; i++) {
		cnt = 20+i*4;
		count = 10;
		if((timeCnt&V5)==0)
			path[i].clear();
		if (!enemys[i].IsAlive()||!path[i].empty()||
			(timeCnt % graph.speedEnemy[i]) != 0) {
			continue;
		}
		if (!graph.me.IsVisible()) {
			//path[i].clear();
			srand(timeCnt+i);
			while (1) {
				tarPos[i].row = Random(1, RowMax + 1);
				tarPos[i].col = Random(1, ColMax + 1);
				char tp = graph.barrier[tarPos[i].row][tarPos[i].col].GetType();
				if (count <= 0)
					break;
				if (tp != Wall && tp != Grass)
					break;
				count--;
				
			}
			/*srand(timeCnt+i);
			tarPos[i].row = Random(1, RowMax + 1);
			tarPos[i].col = Random(1, ColMax + 1);*/
		}
		rowTar = tarPos[i].row;
		colTar = tarPos[i].col;
		//Config::gotoxy(0, RowMax + 3+i);
		//cout << rowTar << ' ' << colTar;
		preRow = enemys[i].GetRow();
		preCol = enemys[i].GetCol();
		cpTem.row = preRow;
		cpTem.col = preCol;
		cpTem.disToSrc = 0;
		cpTem.cost = 0;
		char c;
		openPath.push_back(cpTem);
		while (!openPath.empty()) {
			id = MinCostId();
			closePath.push_back(openPath[id]);
			int size = closePath.size();
			c = SearchNext(graph, UP, id,size-1);
			if (c > 1)
				break;
			c = SearchNext(graph, DOWN, id, size - 1);
			if (c > 1)
				break;
			c = SearchNext(graph, LEFT, id, size - 1);
			if (c > 1)
				break;
			c = SearchNext(graph, RIGHT, id, size - 1);
			if (c > 1)
				break;
			openPath.erase(openPath.begin() + id);	
			if (cnt < 0)
				break;
			cnt--;
		}
		id = closePath.size() - 1;
		int pId;
		while (1) {
			path[i].push_back(closePath[id]);
			pId = closePath[id].parentId;
			if (closePath[pId].row == preRow && closePath[pId].col == preCol)
				break;
			id = pId;
		}
		openPath.clear();
		closePath.clear();
	}
	for (int i = 0; i < len; i++) {
		if (!enemys[i].IsAlive()||path[i].empty())
			continue;
		cpTem = path[i].back();
		preRow = enemys[i].GetRow();
		preCol = enemys[i].GetCol();
		if (cpTem.row == preRow && cpTem.col == preCol) {
			path[i].pop_back();
			if (path[i].empty())
				continue;
			cpTem = path[i].back();
		}
		if (cpTem.row == preRow) {
			if (cpTem.col < preCol)
				enemys[i].SetMovDir(LEFT);
			else
				enemys[i].SetMovDir(RIGHT);
		}
		else {
			if (cpTem.row < preRow)
				enemys[i].SetMovDir(UP);
			else
				enemys[i].SetMovDir(DOWN);
		}
	}
}

int Control::MinCostId() {
	int len = openPath.size(),id=0,min=IntMax;
	/*if (len <= 0)
		return -1;*/
	vector<int> minId;
	for (int i = 0; i < len; i++) {
		if (openPath[i].cost < min) {
			min = openPath[i].cost;
		}
	}
	for (int i = 0; i < len; i++)
		if (openPath[i].cost>= min &&openPath[i].cost <= min + 2)
			minId.push_back(i);
	len = minId.size();
	//id = rand() % len;
	srand(timeCnt);
	return minId[rand() % len];
}
int Control:: FindPoint(vector<CrossPoint>&vec,int r, int c)const {
	int i,len=vec.size();
	for (i = 0; i < len; i++)
		if (vec[i].row == r && vec[i].col == c)
			return i;
	if (i >= len)
		return -1;
}

char Control::SearchNext(Graph& graph, char dir,int id,int pId) {
	//int i;
	int row=1, col=1;
	CrossPoint cpTem;
	switch (dir)
	{
	case UP:
		row=openPath[id].row - 1;
		col=openPath[id].col;
		while (row >= 1) {
			if (graph.isCrossing[row][col] == 1 || graph.isCrossing[row][col] == -1
				|| row == rowTar && col == colTar)
				break;
			row--;
		}
		break;
	case DOWN:
		row = openPath[id].row + 1;
		col = openPath[id].col;
		while (row <= RowMax) {
			if (graph.isCrossing[row][col] == 1 || graph.isCrossing[row][col] == -1
				|| row == rowTar && col == colTar)
				break;
			row++;
		}
		break;
	case LEFT:
		row = openPath[id].row;
		col = openPath[id].col-1;
		while (col >= 1) {
			if (graph.isCrossing[row][col] == 1 || graph.isCrossing[row][col] == -1
				|| row == rowTar && col == colTar)
				break;
			col--;
		}
		break;
	case RIGHT:
		row = openPath[id].row;
		col = openPath[id].col +1;
		while (col <= ColMax) {
			if (graph.isCrossing[row][col] == 1 || graph.isCrossing[row][col] == -1
				|| row == rowTar && col == colTar)
				break;
			col++;
		}
		break;
	}
	if (row == rowTar && col == colTar) {
		cpTem.row = row;
		cpTem.col = col;
		cpTem.parentId = pId;
		closePath.push_back(openPath[id]);
		closePath.push_back(cpTem);
		return 2;
	}
	else if (graph.isCrossing[row][col] == 1) {
		if (FindPoint(closePath, row, col) < 0) {
			//no such point in closePath
			int index = FindPoint(openPath, row, col),newDis;
			newDis = openPath[id].disToSrc + 
				GetDis(row, col, openPath[id].row, openPath[id].col);
			if (index < 0) {//no such point in openPath
				cpTem.disToSrc = newDis;
				cpTem.cost = newDis + GetDis(row, col, rowTar, colTar);
				//cpTem.parentId = closePath.size();
				cpTem.parentId = pId;
				cpTem.row = row;
				cpTem.col = col;
				openPath.push_back(cpTem);
			}
			else {//there is such point in openPath
				if (newDis < openPath[index].disToSrc) {
					openPath[index].disToSrc = newDis;
					openPath[index].cost=newDis+ GetDis(row, col, rowTar, colTar);
					//openPath[index].parentId=closePath.size();
					openPath[index].parentId = pId;
				}

			}
			//closePath.push_back(openPath[id]);
			//openPath.erase(openPath.begin() + id);
		}
		return 1;
	}
	else
		return -1;
		
	//return graph.isCrossing[row][col];
}