#include "pch.h"
#include "Maze.h"

Maze::Maze()
{
	//ctor//conductor
}

Maze::~Maze()
{
	//dtor
}

bool Maze::cango_(Pos &cur) {//传入要判断的地方的地址
	return matrix[cur.row][cur.col] != 0 ? false : true;
}

void Maze::InitMaze(int *p_matrix, int n_colrow) {//传入一个指针（用来传入一维数组），传入数组大小
	for (int z = 0; z <= n_colrow + 1; z++) {//把周围一圈设为1，建墙
		matrix[0][z] = 1;
		matrix[n_colrow + 1][z] = 1;
		matrix[z][0] = 1;
		matrix[z][n_colrow + 1] = 1;
	}
	for (int z = 1; z <= n_colrow; z++) {//中间部分复制一维数组，把它变成二维的
		for (int zz = 1; zz <= n_colrow; zz++) {
			matrix[z][zz] = p_matrix[(z - 1)*n_colrow + zz - 1];
		}
	}
	pstart.row = 1;
	pstart.col = 1;
	pend.row = n_colrow;
	pend.col = n_colrow;
	n_colrow_ = n_colrow;//这句用来干嘛？（左右两边不一样的）

}
void Maze::DFS_(Pos cur, int step) {//用递归实现DFS
	//传入一个Pos结构表示位置的横纵坐标，传入一个Int（会递增的）
	if (cur.row == pend.row && cur.col == pend.col) {//递归停止条件，现在所在的位置在终点处
		PrintMaze();//那就打印maze
		return;
	}
	int dir[4][2] = {
		{1,0},
		{0,1},
		{-1,0},
		{0,-1} 
	};//其它情况下，建一个方向数组
	Pos next;//一个叫Next的点
	for (int z = 0; z < 4; z++) {//0123
		next.row = cur.row + dir[z][0];//row+row，左边一列
		next.col = cur.col + dir[z][1];//col+col，右边一列
		// Try next pos
		if (cango_(next)) {//如果下一个是0（可以走）
			matrix[next.row][next.col] = step + 1;//标记一个递增1的数字给它
			DFS_(next, step + 1);//再往下走一个
			// matrix[next.row][next.col]=0;
		}
	}
}
void Maze::PrintPathDFS() {
	matrix[pstart.row][pstart.col] = 2;//第一个设为2
	DFS_(pstart, 2);//从2开始递增1
}



void Maze::PrintPathStack() {
	mazestack_.push(pstart);//这个栈里加进pstart
	matrix[pstart.row][pstart.col] = 5;//走过了就设为5
	int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	while (!mazestack_.empty()) {//非空？？？
		Pos cur = mazestack_.top();
		if (cur.col == pend.col && cur.row == pend.row) {
			PrintMaze();
			return;//如果栈顶上是终点了，结束
		}
		Pos next;
		bool canexpand = false;
		for (int z = 0; z < 4; z++) {
			next.row = cur.row + dir[z][0];
			next.col = cur.col + dir[z][1];
			if (cango_(next)) {
				canexpand = true;
				matrix[next.row][next.col] = 5;
				mazestack_.push(next);//把next压栈
				break;
			}
		}
		if (!canexpand) {
			matrix[cur.row][cur.col] = 9;//走过而走不下去设为9
			mazestack_.pop();//走不动就出栈
		}
	}
}

void Maze::PrintPathBFS() {
	// the direction of movement
	int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

	//if(matrix[cur.row+1][cur.col])

	//Initilize the auxilary matrix
	for (int z = 1; z <= n_colrow_; z++) {
		for (int zz = 1; zz <= n_colrow_; zz++) {
			visitedBFS_[z][zz] = 0;// decide wheather in the queue (0 no)
			backPathBFS_[z][zz].row = 0;//find the path
			backPathBFS_[z][zz].col = 0;
		}
	}
	//Push the entranace
	while (!mazequeue_.empty()) {//queue<Pos> mazequeue_;
		mazequeue_.pop();
	}
	//begin our algorithm
	mazequeue_.push(pstart);//推入起点
	visitedBFS_[pstart.row][pstart.col] = 1;// decide wheather in the queue (1 yes)
	//The framework of BFS
	
	//这里本来有/*
	while(mazequeue_.empty()==false){
		//1. qu top
		Pos cur=mazequeue_.front();
		if(cur.row==pend.row &&cur.col==pend.col){
			BackTrackPath();//这里本来没有参数
			return;
		}
		mazequeue_.pop();
		for(int z=0;z<4;z++){
			Pos next;
			next.row=cur.row+dir[z][0];
			next.col=cur.col+dir[z][1];
			if(cango_(next) && visitedBFS_[next.row][next.col]==0){
				mazequeue_.push(next);
				visitedBFS_[next.row][next.col]=1;
				backPathBFS_[next.row][next.col]=cur;
			}
		}


	}
	//cout<<"Can not find a path!"<<endl;//这里本来没有//
	//这里本来有*/
	
	while (!mazequeue_.empty()) {
		Pos cur = mazequeue_.front();//现在这个位置是队列最前面的数
		// cout<<cur.row<<","<<cur.col<<endl;
		mazequeue_.pop();//把最前面的数丢掉
		if (cur.row == pend.row && cur.col == pend.col) {//如果它是终点
			BackTrackPath(cur);//倒回去找路径
			return;//终止循环和寻找
		}
		// find the adjacent 邻
		for (int z = 0; z < 4; z++) {
			Pos next;
			next.row = cur.row + dir[z][0];
			next.col = cur.col + dir[z][1];
			if (cango_(next) && visitedBFS_[next.row][next.col] == 0) {//如果下一个可以走并且它没有进过队列
				visitedBFS_[next.row][next.col] = 1;//先标记它进过队列了
				backPathBFS_[next.row][next.col].row = cur.row;//find the path
				backPathBFS_[next.row][next.col].col = cur.col;
				mazequeue_.push(next);
			}
		}
	}
	//cout << " Can not find a path!" << endl;//什么鬼为什么不管咋样都说自己找不到，我//了
}


void Maze::BackTrackPath(Pos cur) {
	//Print the BFS track matrix
	/*for(int z=1;z<=n_colrow_;z++){
		for(int zz=1;zz<=n_colrow_;zz++){
			cout<<backPathBFS_[z][zz].row<<","<<backPathBFS_[z][zz].col<<" ";
		}
		cout<<endl;
	}*/
	while (cur.row != pstart.row || cur.col != pstart.col) {
		cout << cur.row << "," << cur.col << "-->";
		cur = backPathBFS_[cur.row][cur.col];
	}
	cout << cur.row << "," << cur.col << endl;

}

void Maze::PrintMaze() {
	for (int z = 1; z <= n_colrow_; z++) {
		for (int zz = 1; zz <= n_colrow_; zz++)
			cout << matrix[z][zz] << " ";
		cout << endl;
	}
	cout << "-----------------------------------" << endl;
}
