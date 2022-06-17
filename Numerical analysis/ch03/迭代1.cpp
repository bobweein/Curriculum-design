#include <iostream>
#include"diedai.h"


int main()
{ 
	//牛顿迭代法
	double xk1=0.5, xk=0;
	int i = 0;
	cout << "牛顿迭代公式：\n";
	diedai(xk1, xk, 1);

	xk1 = 1.5;
	cout << "\n求方程x^3-x^2-1=0的根\n";
	
	cout << "迭代公式为  xk1=pow(1.0 + xk * xk, double(1.0 / 3.0))\n";
	diedai(xk1, xk, 2);

	cout << "迭代公式为  xk1=1.0 + pow(xk, double(-2))\n";
	diedai(xk1, xk, 3);

	cout << "迭代公式为  xk1= 1 / sqrt(xk - 1)\n";
	diedai(xk1, xk, 4);

	cout << "迭代公式为  xk1=sqrt(xk * xk * xk - 1)\n";
	diedai(xk1, xk, 5);

	//弦割法
	double a = 0, b = m / 4;
	diedai(a, b);

	return 0;
}
