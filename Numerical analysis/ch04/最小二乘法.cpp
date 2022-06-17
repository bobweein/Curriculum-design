#include<iostream>
#include"zuixiao.h"
using namespace std;

int main()
{
	double x[M] = { 0.1,0.3,0.5,0.6,0.7,0.9 };
	double g[M] = { 0.61,0.92,1.12,1.52,1.47,2.04 };
	double* matrix_before = G(x, N);
	//double *matrix_before = new double[N * N]{3,2,-1,2,1,4,0,2,2,1,2,-1,1,1,-1,3};
	double *matrix_after=new double [N*N]{};
	//double *matrix_after1=new double [N*N]{};//测试矩阵
	double* f = Y(x,g,4);
	Printd(matrix_before,4,4);
	cout << endl;
	//矩阵求逆
	GetMatrixInverse(matrix_before, N, matrix_after);
	Printd(matrix_after,4,4);
	cout << endl;
	//将求逆后的矩阵Gn^和Fn相乘
	double *p=matrix_multi(matrix_after, f,N);
	cout << "最小二乘法拟合函数的系数为：\n\tC0\t\t C1\t\t C2\t\t C3\t\n";
	Printd(p, 1, 4);
	//测试
	double pt = 0;
	cout << endl<<"请输入测试值：";
	cin >> pt;
	test(p,4,pt);
	delete[]matrix_after; delete[]f; delete[]p;
	return 0;
}
