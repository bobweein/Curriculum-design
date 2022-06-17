#include <iostream>
#include <iomanip>
using namespace std;
#define N 4//系数矩阵行数和列数
//函数声明
void Doolittle(double a[N][N]);
double* X(double a[N][N], double b[N]);
void Printd(double* arr, int m, int n);
int  main()
{
	double a[N][N]={3,2,-1,2,1,4,0,2,2,1,2,-1,1,1,-1,3};
	double b[N] = { -2,1,3,4 };
	Doolittle(a);
	cout << "L和U的紧凑存储矩阵为：\n";
	Printd(&a[0][0], N, N);
	double* p;
	cout << "X的转置为：";
    p=X(a, b);
	Printd(p, 1, 4);
	return 0;
}
void Doolittle(double a[N][N])//LU分解,并以紧凑存储方式存储
{
	int i,k, j,m;
	double sum=0,num = 0;
	for (i = 1; i < N; i++)
		a[i][0] = a[i][0] / a[0][0];

	for (k = 1; k < N; k++)
	{
		for (j = k; j < N;j++)
		{
			sum = a[k][j]; 
			for (m = 0; m <k; m++)
				sum -= a[k][m] * a[m][j];
			a[k][j] = sum;
			if (j > k )
			{
				num = a[j][k];
				for (m = 0; m < k ; m++)
				{
					num -= a[j][m] * a[m][k];
				}
				a[j][k] = num / a[k][k];
			}

		}
	}
}
double* X(double a[N][N],double b[N])//计算y,x;
{
	double y[N], x[N],sum=0,sum1=0;
	int k, j;
	y[0] = b[0];
	for (k = 1; k < N; k++)//计算y
	{
		sum = b[k];
		for (j = 0; j < k; j++)
		{
			sum -= a[k][j] * y[j];
		}
		y[k] = sum;
	}
	x[N - 1] = y[N - 1] / a[N - 1][N - 1];
	for (k = N - 1; k >= 0; k--)//计算x
	{
		sum1 = y[k];
		for (j = k + 1; j < N; j++)
			sum1 -= a[k][j] * x[j];
		x[k] = sum1 / a[k][k];

	}
	return x;
		
}
void Printd(double* arr, int m, int n)//打印函数
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(8);
			cout << setw(16) << *(arr + i * n + j);
		}
		cout << "\n\n";
	}
}
