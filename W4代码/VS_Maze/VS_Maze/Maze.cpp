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

bool Maze::cango_(Pos &cur) {//����Ҫ�жϵĵط��ĵ�ַ
	return matrix[cur.row][cur.col] != 0 ? false : true;
}

void Maze::InitMaze(int *p_matrix, int n_colrow) {//����һ��ָ�루��������һά���飩�����������С
	for (int z = 0; z <= n_colrow + 1; z++) {//����ΧһȦ��Ϊ1����ǽ
		matrix[0][z] = 1;
		matrix[n_colrow + 1][z] = 1;
		matrix[z][0] = 1;
		matrix[z][n_colrow + 1] = 1;
	}
	for (int z = 1; z <= n_colrow; z++) {//�м䲿�ָ���һά���飬������ɶ�ά��
		for (int zz = 1; zz <= n_colrow; zz++) {
			matrix[z][zz] = p_matrix[(z - 1)*n_colrow + zz - 1];
		}
	}
	pstart.row = 1;
	pstart.col = 1;
	pend.row = n_colrow;
	pend.col = n_colrow;
	n_colrow_ = n_colrow;//�������������������߲�һ���ģ�

}
void Maze::DFS_(Pos cur, int step) {//�õݹ�ʵ��DFS
	//����һ��Pos�ṹ��ʾλ�õĺ������꣬����һ��Int��������ģ�
	if (cur.row == pend.row && cur.col == pend.col) {//�ݹ�ֹͣ�������������ڵ�λ�����յ㴦
		PrintMaze();//�Ǿʹ�ӡmaze
		return;
	}
	int dir[4][2] = {
		{1,0},
		{0,1},
		{-1,0},
		{0,-1} 
	};//��������£���һ����������
	Pos next;//һ����Next�ĵ�
	for (int z = 0; z < 4; z++) {//0123
		next.row = cur.row + dir[z][0];//row+row�����һ��
		next.col = cur.col + dir[z][1];//col+col���ұ�һ��
		// Try next pos
		if (cango_(next)) {//�����һ����0�������ߣ�
			matrix[next.row][next.col] = step + 1;//���һ������1�����ָ���
			DFS_(next, step + 1);//��������һ��
			// matrix[next.row][next.col]=0;
		}
	}
}
void Maze::PrintPathDFS() {
	matrix[pstart.row][pstart.col] = 2;//��һ����Ϊ2
	DFS_(pstart, 2);//��2��ʼ����1
}



void Maze::PrintPathStack() {
	mazestack_.push(pstart);//���ջ��ӽ�pstart
	matrix[pstart.row][pstart.col] = 5;//�߹��˾���Ϊ5
	int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	while (!mazestack_.empty()) {//�ǿգ�����
		Pos cur = mazestack_.top();
		if (cur.col == pend.col && cur.row == pend.row) {
			PrintMaze();
			return;//���ջ�������յ��ˣ�����
		}
		Pos next;
		bool canexpand = false;
		for (int z = 0; z < 4; z++) {
			next.row = cur.row + dir[z][0];
			next.col = cur.col + dir[z][1];
			if (cango_(next)) {
				canexpand = true;
				matrix[next.row][next.col] = 5;
				mazestack_.push(next);//��nextѹջ
				break;
			}
		}
		if (!canexpand) {
			matrix[cur.row][cur.col] = 9;//�߹����߲���ȥ��Ϊ9
			mazestack_.pop();//�߲����ͳ�ջ
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
	mazequeue_.push(pstart);//�������
	visitedBFS_[pstart.row][pstart.col] = 1;// decide wheather in the queue (1 yes)
	//The framework of BFS
	
	//���ﱾ����/*
	while(mazequeue_.empty()==false){
		//1. qu top
		Pos cur=mazequeue_.front();
		if(cur.row==pend.row &&cur.col==pend.col){
			BackTrackPath();//���ﱾ��û�в���
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
	//cout<<"Can not find a path!"<<endl;//���ﱾ��û��//
	//���ﱾ����*/
	
	while (!mazequeue_.empty()) {
		Pos cur = mazequeue_.front();//�������λ���Ƕ�����ǰ�����
		// cout<<cur.row<<","<<cur.col<<endl;
		mazequeue_.pop();//����ǰ���������
		if (cur.row == pend.row && cur.col == pend.col) {//��������յ�
			BackTrackPath(cur);//����ȥ��·��
			return;//��ֹѭ����Ѱ��
		}
		// find the adjacent ��
		for (int z = 0; z < 4; z++) {
			Pos next;
			next.row = cur.row + dir[z][0];
			next.col = cur.col + dir[z][1];
			if (cango_(next) && visitedBFS_[next.row][next.col] == 0) {//�����һ�������߲�����û�н�������
				visitedBFS_[next.row][next.col] = 1;//�ȱ��������������
				backPathBFS_[next.row][next.col].row = cur.row;//find the path
				backPathBFS_[next.row][next.col].col = cur.col;
				mazequeue_.push(next);
			}
		}
	}
	//cout << " Can not find a path!" << endl;//ʲô��Ϊʲô����զ����˵�Լ��Ҳ�������//��
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
