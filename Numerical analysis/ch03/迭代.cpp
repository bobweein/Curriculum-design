#include<iostream>
#include"diedai.h"
double f(double x, int i) //函数列表
{
	switch (i)
	{
	case 1://牛顿迭代法中函数
		return (x - 2 * sin(x + m / 3));
	
	case 2: //弦割法中函数
		return 2 * cos(x) - 1.0 - sin(x);
	default: return 0;
	}
}

double df(double x,int i)//牛顿迭代法法中的函数的导函数
{
	double e = 1e-10;//这个值不能过分的减小，太小会导致导函数的值变得很大，导致错误！
	//double r = (f(e+x) - f(x)) / e;//防止大数吃小数；
	if(i==1)//计算牛顿迭代公式的一阶导数值
		return   (1 - 2 * cos(x + m / 3));

	double xx = 1.5;//计算迭代公式的一阶导函数的值在x*处的值
	return  (gongshi(e + xx, i) - gongshi( xx, i)) /  e;
	

}
double gongshi(double xk, int i)//迭代公式列表
{
	switch (i)
	{
	case 1:
		return xk - f(xk, i) / df(xk);//牛顿迭代法公式
	case 2://以下是x^3-x^2-1=0的四个迭代公式
		return pow(1.0 + xk * xk, double(1.0 / 3.0));
	case 3:
		return 1.0 + pow(xk, double(-2));
	case 4:
		return 1 / sqrt(xk - 1);
	case 5:
		return sqrt(xk * xk * xk - 1);
	default: return 0;
	}
}


void diedai(double xk1, double xk, int i)//迭代函数
{
	int j = 0;
	int l=1;
	if (i != 1) l= jianyan(1.5, i);
	while (fabs(xk1 - xk) > 1e-8)//迭代过程
	{
		xk = xk1;
		xk1 = gongshi(xk, i);
		cout << setiosflags(ios::fixed) << setprecision(12) << setw(16);
		cout << "   x(k+1) ; " << xk1 << "           " << j++ << endl;
	}
	cout << endl;
}

int  jianyan(double x,int i)
{
	double yy=df(x,i);//计算一阶导数的值
	cout << "经人工检验在该迭代公式一阶导函数在x*的某邻域连续的，\n";
	if (fabs(yy) > 1)
	{
		cout << "但是该一阶导函数在x*处的值的绝对值大于1，该迭代法局部不收敛；\n";
		cout << "因为迭代公式的一阶导数在x*处的值的绝对值为 yy=" << yy << endl<<endl;

		return 0;
	}
	else
	{
		cout << "但是该一阶导函数在x*处的值的绝对值小于1，该迭代法局部收敛；\n\n";
		cout << "因为迭代公式的一阶导数在x*处的值的绝对值为 yy=" << yy << endl << endl;
		return 1;
	}

}
void diedai(double a,double b )//迭代函数重载，解决不同情况，弦割法。
{
	
	int k = 0,i=2;
	double zk_1 = 0, zk = f(a, i), zk1 = f(b, i);
	cout << "弦割法:\n";
	cout << setiosflags(ios::fixed) << setprecision(12) << setw(16);
	cout << "k: " << k++ << "      xk; " << zk << "  f(xk): " << f(zk1, i) << endl << endl;
	cout << setiosflags(ios::fixed) << setprecision(12) << setw(16);
	cout << "k: " << k++ << "      xk; " << zk1 << "  f(xk): " << f(zk1, i) << endl << endl;
	while (fabs(zk1 - zk) > 1e-8)//迭代过程
	{
		zk_1 = zk; zk = zk1;
		zk1 = zk - f(zk, i) * (zk - zk_1) / (f(zk, i) - f(zk_1, i));//迭代公式
		cout << setiosflags(ios::fixed) << setprecision(12) << setw(16);
		cout << "k: " << k++ << "      xk; " << zk1 << "  f(xk): " << f(zk1, i) << endl << endl;
	}
}
