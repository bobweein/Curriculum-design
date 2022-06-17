#include<iostream>
#include <iomanip>
using namespace std;
#define N 4
void Printd(double* arr, int m, int n);
void  Guass(double  a[N][N + 1]);
double* X(double a[N][N + 1]);
int main()
{
	double a[N][N + 1] = { {3,2,-1,2,-2},{1,4,0,2,1},{2,1,2,-1,3},{1,1,-1,3 ,4} };
	Guass(a);
	Printd(&a[0][0], N, N + 1);
	cout << endl;
	cout << "\tx0     \t\tx1     \t\tx2    \t\tx3\n";
	Printd(X(a), 1, N);
	return 0;
}

void  Guass(double  a[N][N + 1])
{
	int i = 0;
	double* p[N] = { a[0],a[1],a[2],a[3] };//用指针数组指向对应的行
	double* temp = NULL;
	while (i < N - 1)
	{
		int j, k = i, z;
		double max = fabs(p[i][i]);
		for (j = i + 1; j < N; j++)//第i列绝对值最大的元素
		{
			if (fabs(p[j][i]) > max)
			{
				max = fabs(p[j][i]);
				k = j;
			}
		}
		if (fabs(max) > 1e-6)//如果大于0，就交换两行
		{
			temp = p[i];
			p[i] = p[k];
			p[k] = temp;
		}
		double Lik = 0;
		for (z = i + 1; z < N; z++)//开始相减
		{
			if (*(*(p + z) + i) != 0)
			{
				Lik = *(*(p + z) + i) / (*(*(p + i) + i));
				for (j = i; j < N + 1; j++)
				{
					*(*(p + z) + j) -= *(*(p + i) + j) * Lik;
				}
			}
			Printd(*p, N, N + 1);
			cout << endl;
		}
		i++;
	}
}
double* X(double a[N][N + 1])
{
	int i, j;
	double* x = new double [N] {};
	double sum = 0;
	*(x + N - 1) = a[N - 1][N] / a[N - 1][N - 1];
	for (i = N - 2; i >= 0; i--)
	{
		sum = a[i][N];
		for (j = i + 1; j < N + 1; j++)
			sum -= a[i][j] * (*(x + j));
		*(x + i) = sum / a[i][i];
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
