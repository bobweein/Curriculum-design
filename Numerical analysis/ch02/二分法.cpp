#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int half_num(double a,double b,double e)//根据精度函数求解分半次数
{
	int k=0;
	k = (int)(log(b - a) - log(e)) / log(2)+1;
	return k;
}
double f( double x)//需要求零点的函数
{
	if (x < 1 && x>2) 
	{
		cout << "不在定义域内！\n"; 
		return 0;
	}
	return (x - pow(2, -x));
}
int main()
{
	double a = 0, b = 1;
	double e = 1e-8,c=0;
	int k;
	k=half_num(0, 1, e);
	cout << "需要区间分半次数为：" << k << endl;
	c = (a + b) / 2;
	cout << setiosflags(ios::fixed) << setprecision(14) << setw(16);
	cout   << "              a= " << a << "  " << "b=  " << b << "  " << "c= " << c << endl << endl;
	while (k>=0)
	{
		
		if (f(c) == 0)
		{
			cout << "中点c为函数零点：" << c << endl;
			break;
		}
		if (f(a) * f(c) < 0)
		{
			b = c;
			c = (a + b) / 2;
			cout << setiosflags(ios::fixed) << setprecision(14) << setw(16);
			cout << "k=  " << k << "  " << "a= " << a << "  " << "b=  " << b << "  " << "c= " << c << endl << endl;
			k--;//如果分半了就将分半次数减一
		}
		if (f(c) * f(b) < 0)
		{
			a = c;
			c = (a + b) / 2;
			cout  << setiosflags(ios::fixed) << setprecision(14) << setw(16);
			cout << "k=  " << k << "  " << "a= " << a << "  " << "b=  " << b << "  " << "c= " << c << endl << endl;
			k--;//如果分半了就将分半次数减一
		}	
	}
	return 0;
}
