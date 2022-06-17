#include  <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double  jingque(double x, int i);
double weifen(double x, double y, int i);
double diedai(double x0, double y0, double a, double  b, double h, int j);
double gonshi(double xn, double yn, double h, int j);
double  jingque(double x,int i)//微分方程的原函数
{
	if (i == 0)
		return  x*2 + exp(-x);//欧拉方法
	if (i == 1)
		return 2 * exp(x) - x - 1;//改进欧拉方法
	return 0;//算不那个igamma,没有这个函数
}

double weifen(double x, double y,int i)//微分方程组中的第一个式子
{
	if (i == 0) return -y + 2 * (x + 1);
	if (i == 1)    return x + y;
	if (i == 2)   return x * x + pow(x, 3) * y;
	return 0;
}
double gonshi(double xn, double yn, double h, int j)//迭代公式
{
	if (j == 0) return yn + h *weifen(xn, yn, j);//显示欧拉方法的迭代公式
	if (j == 1)//改进后的欧拉方法的迭代公式
	{
		double yn0 = yn + h * weifen(xn, yn,j);
		double yn1 = yn + h / 2 * (weifen(xn, yn, j) + weifen((xn * 10 + 1) / 10, yn0, j));
		return yn1;
	}
	if (j == 2)//四阶龙格库塔方法的迭代公式
	{
		double K1 = weifen(xn, yn, j);
		double K2 = weifen(xn + h / 2, yn + h / 2 * K1,j);
		double K3 = weifen(xn + h / 2, yn + h / 2 * K2, j);
		double K4 = weifen(xn + h, yn + h * K3,j);
		return yn + h / 6 * (K1 + 2 * K2 + 2 * K3 + K4);
	}
		return 0;
}
double diedai(double x0, double y0,double a,double  b, double h,int j)//进行迭代操作
{
	double xn = x0, yn =y0,yn1=y0;
	cout << "X0:" << x0 << "\t" << "Y0:" << y0 << endl;
	double  n = (b - a) / h,i=0;
	cout << "y(n+1) \t\t\t" << "精确解\n";
	while (i < n)
	{
		yn = yn1; xn = a+h*i;
		yn1 = gonshi(xn,yn,h,j);//计算y(n+1);
		cout << setiosflags(ios::fixed) << setprecision(12) ;
		cout <<yn1 << "\t" << jingque((i+1)/ n, j) << "\n ";
		i++;
	}
	cout << "\n\n";
	return 0;
}
int main()
{
	diedai(0,1,0,1,0.1,0);//使用显示欧拉方法
	//这里的参数分别为  x0  y0  区间左端点  区间右端点 步长  i（表示使用某种方法）！
	diedai(0,1,0,1,0.1,1);//使用改进后的欧拉方法

	diedai(1,1,1,2,0.2,2);//使用四阶龙格库塔方法
	return 0;
}
