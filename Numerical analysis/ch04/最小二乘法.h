#ifndef _zuixiao_h
#include <iomanip>
#include <cmath>
#define N 4  //测试矩阵维数定义
#define M 6
using namespace std;
double getA(double* arcs, int m);
void  getAStart(double* arcs, int m, double* ans);
bool GetMatrixInverse(double* src, int m, double* des);
void Printd(double* arr, int m, int n);
double* Y(double x[M], double g[M], int n);
double* G(double arr[M], int n);
double* U(double x[], int i);
double* matrix_multi(double* arr, double* arr1, int m);
void test(double* arr,int n,double pt)
{
	double sum=0;
	sum = arr[0] * 1 + arr[1] * pt + arr[2] * sin(pt) + arr[3] * exp(pt);
	cout << "代入拟合函数后，值为：" << sum;
	    	
}
//按第一行展开计算|A|，大致的思路就是，先将A1i分别计算出来（用递归地思想），在将他们加起来，就算出来
double getA(double *arcs, int m)
{
	if (m == 1)//递归出口，当行列式为一阶的时候
	{
		return *arcs;
	}
	double ans = 0;
	double* temp=new double[N*N] {};
	int i, j, k;
	for (i = 0; i < m; i++)//按第一行展开（递归时，这里的m会逐次减小1，就达到了对目标行列式的第一行展开的目的，）
	{
		for (j = 0; j < m-1; j++)
		{
			for(k=0;k <m-1;k++)
			{
				*(temp+j*N+k) = *(arcs+(j+1)*N+((k >= i) ? k + 1 : k));//temp指向的矩阵就是高代里边的余子式
			}
		}
		double t = getA(temp,	m-1);
		if (i % 2 == 0)//将余子式变成代数余子式,直接根据列的值来判断
		{
			ans += *(arcs+i) * t;
		}
		else
		{
			ans -= *(arcs+i) * t;
		}
	}
	return ans;
}
//计算每一行每一列的每个元素所对应的余子式，组成A*
void  getAStart(double *arcs, int m, double *ans)
{
	if (m == 1)
	{
		*ans = 1;
		return;
	}
	int i, j, k, t;
	double * temp=new double [N*N];
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			for (k = 0; k < m - 1; k++)
			{
				for (t = 0; t < m - 1; t++)
				{
					*(temp+k*N+t) = *(arcs+(k >= i ? k + 1 : k)*N+(t >= j ? t + 1 : t));
				}
			}
			*(ans+j*N+i) = getA(temp, N-1);  //此处顺便进行了转置
			if ((i + j) % 2 == 1)
			{
				*(ans+j*N+i) = -*(ans+j*N+i);
			}
		}
	}
	delete[] temp;
}
//得到给定矩阵src的逆矩阵保存到des中。
bool GetMatrixInverse(double *src, int m, double *des)
{
	double flag = getA(src, N);
	double * t=new double [N*N];
	if (0 == flag)
	{
		cout << "原矩阵行列式为0，无法求逆。请重新运行" << endl;
		return false;//如果算出矩阵的行列式为0，则不往下进行
	}
	else
	{
		getAStart(src, N, t);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				*(des+i*N+j) = *(t+i*N+j) / flag;
			}
		}
	}
	delete[]t;
	return true;
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
double* Y(double x[M], double g[M], int n)//计算Fn
{
	int i, j;
	double* arr = new double[n] {};
	double* p = NULL;

	for (i = 0; i < n; i++)
	{
		double sum = 0;
		for (j = 0; j < M; j++)
		{
			p = U(x, i + 1);
			sum += p[j] * g[j];
		}
		arr[i] = sum;
	}
	return arr;
}
double* G(double arr[M], int n)//计算Gn
{
	double* Gn = new double[n * n]{};
	double* p = NULL, * q = NULL;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			double sum = 0;
			p = U(arr, i + 1); q = U(arr, j + 1);
			for (int z = 0; z < M; z++)
				sum += p[z] * q[z];
			*(Gn + i * n + j) = sum;
			if (j < i)
				*(Gn + j * n + i) = sum;
		}
	}
	return Gn;
}
double* U(double x[], int i)//1,x,sin(x),exp(x)
{
	double* arr2 = new double[M] {};
	int j;
	switch (i)
	{
	case 1:
	{
		for (j = 0; j < M; j++)
			arr2[j] = 1;
		break;
	}
	case 2:
	{
		for (j = 0; j < M; j++)
			arr2[j] = x[j];
		break;
	}
	case 3:
	{
		for (j = 0; j < M; j++)
			arr2[j] = sin(x[j]);
		break;
	}
	case 4:
	{
		for (j = 0; j < M; j++)
			arr2[j] = exp(x[j]);
		break;
	}
	}
	return arr2;
}
double* matrix_multi(double* arr, double* arr1, int m)//矩阵乘法函数
{
	double* arr2 = new double[N];
	double sum;
	for (int i = 0; i < m; i++)
	{
		sum = 0;
		for (int j = 0; j < m; j++)
		{
			sum += *(arr + i * m + j) * (*(arr1 + j));
		}
		arr2[i] = sum;
	}
	return arr2;
}
#endif
