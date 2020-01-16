#include "pch.h"
#include "life.h"
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Life::initialize() {
	int i, j;
	for (i = 0; i < maxrow + 2; i++) {
		for (j = 0; j < maxcol + 2; j++) {
			grid[i][j] = 0;//0Ϊ������
		}
	}

	for (i = 1; i < maxrow + 1; i++) {
		for (j = 1; j < maxcol + 1; j++) {
			grid[i][j] = rand() % 2 ;//0��1֮��������
		}
	}
   
}

void Life::print() {
	int i, j;
	for (i = 1; i < maxrow + 1; i++) {
		for (j = 1; j < maxcol + 1; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

void Life::update(){
	int i, j;
	int flag[maxrow + 2][maxcol + 2];
	for (i = 0; i < maxrow + 2; i++) {
		for (j = 0; j < maxcol + 2; j++) {
			flag[i][j] = 0;
		}
	}
	int n;
	for (i = 1; i < maxrow + 1; i++) {
		for (j = 1; j < maxcol + 1; j++) {
			n = neighbor_count(i, j);
			if (n <= 1 || n >= 4) {
				//cout << "��" << i << "��" << j << "n=" << n << "die" << endl;
				flag[i][j] = -1;//����
			}
			else if (n == 3) {
				//cout << "��" << i << "��" << j << "n=" << n << "live" << endl;
				flag[i][j] = 1;//����
			}
		}
	}
	for (i = 1; i < maxrow + 1; i++) {
		for (j = 1; j < maxcol + 1; j++) {
			if (flag[i][j] == -1) {
				grid[i][j] = 0;//����
			}
			else if (flag[i][j] == 1) {
				grid[i][j] = 1;//����
			}
		}
	}
	

}

int Life::neighbor_count(int row, int col) {
	int s = 0;
	s = grid[row + 1][col] + grid[row - 1][col] + grid[row][col + 1] + grid[row][col - 1] + grid[row + 1][col - 1] + grid[row - 1][col + 1] + grid[row - 1][col - 1] + grid[row + 1][col + 1];
	//cout << row << col << s << endl;
	return s;
}