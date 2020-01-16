#include "pch.h"
#include "life.h"
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	Life hilife; //记得设置一个life 对象
	hilife.initialize();
	hilife.print();
	cout << "是否继续y/n?" << endl;
	char c;
	while (cin >> c) {
		if (c == 'y') {
			hilife.update();
			hilife.print();
			cout << "是否继续y/n?" << endl;
		}
		else if (c == 'n') {
			cout << "End of declaration." << endl;
			return 0;
		}
	}
	return 0;
}

