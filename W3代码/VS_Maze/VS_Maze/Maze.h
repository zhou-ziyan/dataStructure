#pragma once
#ifndef MAZE_H
#define MAZE_H

#include<iostream>
#include<stack>
#include<queue>

using namespace std;

const int maxcolrow = 20;

struct Pos {
	int row;
	int col;
};
class Maze
{
public:
	Maze();
	virtual ~Maze();
	void InitMaze(int *p_matrix, int n_colrow);
	void PrintPathDFS();
	void PrintPathStack();
	void PrintPathBFS();
	void PrintMaze();

protected:

private:
	void DFS_(Pos cur, int step);
	bool cango_(Pos &cur);
	void BackTrackPath(Pos cur);
	Pos pstart;
	Pos pend;
	int n_colrow_;
	int matrix[maxcolrow + 2][maxcolrow + 2];
	int visitedBFS_[maxcolrow + 2][maxcolrow + 2];  // decide wheather in the queue
	Pos backPathBFS_[maxcolrow + 2][maxcolrow + 2]; //find the path
	stack<Pos> mazestack_;
	queue<Pos> mazequeue_;
};

#endif // MAZE_H

