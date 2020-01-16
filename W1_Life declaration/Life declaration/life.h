#pragma once

const int maxrow = 10, maxcol = 20; // grid dimensions

class Life {
public:
	void initialize(); //��ʼ�����ã���ʼ��һ����ά����
	void print(); //�����ǰ���ã�����״̬
	void update(); //һ�ε���

private:
	int grid[maxrow + 2][maxcol + 2]; //���Ϊʲô��private ��������������ʣ���
	int neighbor_count(int row, int col);
};