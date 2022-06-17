#include <iostream>
#include <stdio.h>
#define N 4
long double f(long double x, int i);
void qiudao(long double x,long double h, int i);
using namespace std;
void qiudao(long double x, long double h,int i)
{
	long double df1 = (f(x+h,i) - f(x,i)) / h;
	long double df2 = (f(x+h,i) - f(x-h,i)) / (h*2.0);
	cout << "df1=" << df1 << "\t" << "df2=" << df2 << endl;
}
long double f(long double x, int i)
{
	if (i == 0)
		return 5 * x + 10;
	if (i == 1)
		return 3 * pow(x, 3) + 5 * pow(x, 2) + 10;
	if (i == 2)
		return exp(x) + pow(x, 2) + 10;
	if (i == 3)
		return sin(x) +10;
}
long double jingque(long double x, int i)
{
	if (i == 0)
		return 5 ;
	if (i == 1)
		return 9* pow(x, 2) + 10 ;
	if (i == 2)
		return exp(x) + 2*x ;
	if (i == 3)
		return cos(x);
}
int main()
{
	int i = 0, n = 5; long double h = 1e-13;
	long double x = 1;
	for (int j = 0; j < 4; j++)
	{
		cout << j << endl;

		h = h / 10.0;
		n = 5;
		while (n)
		{
			if (j == 0) x = x + 1;
			if (j == 1)  x = 1 / (x * x) + 1 / 5 * x;
			if (j == 2) x = sin(x) + cos(x);
			if (j == 3) x = tgamma(x);
			cout << "x= " << x;
			cout << "  步长h= " << h << endl;
			for (i = 0; i < N; i++)
			{

				cout << "精确解" << jingque(x, i) << "   极限计算：";
				qiudao(x, h, i);

			}
			cout << endl;
			n--;
		}

	}
}
