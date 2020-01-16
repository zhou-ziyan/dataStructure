#pragma once

const int maxrow = 10, maxcol = 20; // grid dimensions

class Life {
public:
	void initialize(); //初始化设置，初始化一个二维数组
	void print(); //输出当前配置，数组状态
	void update(); //一次迭代

private:
	int grid[maxrow + 2][maxcol + 2]; //这个为什么是private 还可以在下面访问？？
	int neighbor_count(int row, int col);
};