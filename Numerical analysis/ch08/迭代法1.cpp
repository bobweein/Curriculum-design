#include <iostream>
#include"diedaifa.h"
#include <stdlib.h>
#define M 100000
double* Init(double arr[N][N])
{
	double temp[N][2*N]{};
	double pmet[N][N]{};
	
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			temp[i][j] = arr[i][j];
		temp[i][N + i] = 1;
	}
	cout << "\t\t\t【A I】 -------【I A^】\n【A I】:" << endl;
	Printd(temp);

	cout << endl << "【I A^】:\n";
	double** p = NULL;
	p = Guass(temp);
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 2 * N; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(4);
			cout << setw(8) << p[i][j];
		}
		cout << "\n\n";
	}

	cout << endl;
	
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			pmet[i][j] = p[i][N+j];
	cout << "D+L的逆\n";
	return &pmet[0][0];
}
int  Guass(double a[N][N])
{
	int i = 0,q;
	double b[N][N]{}; double c[N][N]{ };
	for (i = 0; i < N; i++)
		for (q = 0; q < N; q++)
			b[i][q] = a[i][q];
	cout << "迭代矩阵为：\n";
	Printd(b);
	double** p = new double* [N] {b[0], b[1], b[2], b[3], b[4]};//用指针数组指向对应的行
	double* temp = NULL; double max;
	i = 0;
	while (i < N - 1)
	{
		int k = i, j, z;
		max = fabs(p[i][i]);
		for (j = i + 1; j < N; j++)//第i列绝对值最大的元素
		{
			if (fabs(p[j][i]) > max)
			{
				max = fabs(p[j][i]);
				k = j;
			}
		}
		if (fabs(max) > 1e-6 && k != i)//如果大于0，就交换两行
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
				Lik = p[z][i] / p[i][i];
				for (j = i; j < N; j++)
				{
					p[z][j] -= p[i][j] * Lik;
				}
			}
		}
		i++;
		
	}
	cout << "        \n\n求谱范数的矩阵为：" << endl;
	for (int J = 0; J < N; J++)
		for (q = 0; q < N; q++)
			c[J][q] = p[J][q];
	cout << "矩阵为：\n";
	Printd(c);
	max = fabs(c[0][0]);
	for (i = 1; i < N; i++)
		if (fabs(c[i][i]) > max) max = fabs(c[i][i]);
	if (max >= 1)
	{
		cout <<"谱半径为 ："<<max<< "   该迭代矩阵的谱半径不小于1，不收敛！\n";
		return 0;
	}
	else return 1;
}
double** Guass(double a[N][2*N])
//借用高斯列主元消去法求矩阵的逆【A I】=【I A^】
{//先借用高斯列主元消去法对这个5*10的矩阵进行初等行变换，化成类似于上三角矩阵的形式.
	int i = 0;
	double** p = new double* [N] {a[0], a[1], a[2], a[3], a[4]};//用指针数组指向对应的行
	double* temp = NULL; double max;
	while (i < N - 1)
	{
		int k = i, j, z;
		max = fabs(p[i][i]);
		for (j = i + 1; j < N; j++)//第i列绝对值最大的元素
		{
			if (fabs(p[j][i]) > max)
			{
				max = fabs(p[j][i]);
				k = j;
			}
		}
		if (fabs(max) > 1e-10 && k != i)//如果大于0，就交换两行
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
				Lik = p[z][i] / p[i][i];
				for (j = i; j < 2 * N; j++)
				{
					p[z][j] -= p[i][j] * Lik;
				}
			}
		}
		i++;
	}

	int k, z; double sum;
	//从这里对使用完一部分初等行变换的矩阵的每行除这一行中的第一个元素，将矩阵中类似于对角线的部分化为1;
	for (k = 0; k < N; k++)
	{
		sum = p[k][k];
		if (sum == 0)
		{
			cout << "这个矩阵不是满秩的，无法求逆！";
			return NULL;
		}
		for (z = k; z < 2 * N; z++)
			p[k][z] /= sum;
	}
	
	//将这个5*10的矩阵的前5*5 化为I（前面的部分已经做了一些处理了，）
	//这里只需要把那个5*5的中上三角的部分（除对角线以外的部分）化为0
	//再次利用类似于高斯消去法的方法，继续对矩阵进行初等行变换。
	//将左边的5*5的矩阵化为I ,得到的右边的矩阵就是原来5*5矩阵的逆；
	for (i = N - 1; i > 0; i--)
	{
		for (k = i - 1; k >= 0; k--)
		{
			sum = p[k][i];
			for (z = i; z < 2 * N; z++)
				p[k][z] = p[k][z] - p[i][z] * sum;
		}
	}
	
	return p;
}
double* matrix_multi(double  arr[N][N], double arr1[N][N])
//矩阵乘法函数 第一个矩阵的行数5 第一个矩阵的列数和第二个矩阵的行数 5，第二个矩阵的列数 5 
{
	double* T = new double[N*N];

	
	double sum;
	int i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			sum = 0;
			for (k = 0; k < N; k++)
			{
				sum += arr[i][k] * arr1[k][j];
			}
			*(T+i*N+j) = sum;
		}
	}
	return T;
}
double* matrix_multi(double  arr[N][N], double arr1[N][1])//(函数重载)
//矩阵乘法函数 第一个矩阵的行数5 第一个矩阵的列数和第二个矩阵的行数 5，第二个矩阵的列数 1 
{
	double*T = new double [N]{};


	double sum;
	int i=0, j=0, k=0;
	for (i = 0; i < N; i++)
	{
			sum = 0;
			for (k = 0; k < N; k++)
			{
				sum += arr[i][k] * arr1[k][0];
			}
			T[i] = sum;
	}
	return T;
}
void jacobi(double b[N][1], double Bj[N][N])//雅各比迭代函数入口
{
	int i, j;
	double bn[N][1]{}; double bj[N][N]{};
	for (i = 0; i < N; i++)
	{
		bn[i][0] = b[i][0] / Bj[i][i];
		for (j = 0; j < N; j++)
			if (j != i) bj[i][j] = ( - 1)*Bj[i][j] / Bj[i][i];
		bj[i][i] = 0;
	}
	Printd(bn);

	//Printd(bj);
	double x0[][1] = { 1,1,1,1,1 };
	int a=Guass(bj);
	if (a == 0)
	{
		   
			cout << " 想继续查看执行结果吗？别看了吧！！！！！！！(再按一下按回车)\n";
			cin.get();
	        return;
	}
	diedai(bn, bj, x0, 1,1);
}
void diedai(double b0[N][1], double BJ[N][N], double x0[N][1], double b,int n)
//雅各比迭代和高斯塞尔德迭代共用一个迭代公式
{
	if (b < 1e-5||n==200)
		return;
	cout << "打印x0[N][1]\n";
	Printd(x0);
	
	int i, j;
	double xk[N][1]{};
	double* p = matrix_multi(BJ, x0);
	for (i = 0; i < N; i++)
		xk[i][0] =  * (p + i);
	cout << "计算xk(迭代中的计算出来的新的x)\n";
	for (i = 0; i < N; i++)
		xk[i][0] = xk[i][0] + b0[i][0];	
	Printd(xk);

	b = fabs(xk[0][0] - x0[0][0]);
	for (j = 1; j < N; j++)
		if (fabs(xk[j][0] - x0[j][0]) > b)
			b = fabs(xk[j][0] - x0[j][0]);
	cout <<"无穷范数:||x(k+1)-x(k)||oo "<< b << "\n\n";
	n = n + 1;
	diedai(b0, BJ, xk, b,n);
}
void guassai(double  b[N][1], double Bs[N][N])//高斯塞尔德迭代法入口
{
	double DL[N][N]{}; double U[N][N]{};//计算（D+L）,和U这两个矩阵
	double bn[N][1]{};
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (j > i) { DL[i][j] = 0;   U[i][j] = Bs[i][j]; }
			else { DL[i][j] = Bs[i][j];   U[i][j] = 0; }
		}
	}
	/*cout << "DL\n";
	Printd(DL);
	cout << "U\n";
	Printd(U);*/
	
	double* p = Init(DL);//计算(D+L)矩阵的逆
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			DL[i][j] = *(p + i * N + j);
	/*Printd(DL);*/

	cout << "计算（D+L）的逆和b 的乘积  bn\n";
	double *q = matrix_multi(DL, b);//计算（D+L）的逆和b 的乘积  bn
	for (i = 0; i < N; i++)
		bn[i][0] = *(q + i);
	Printd(bn);

	cout << "计算出迭代矩阵\n";
	double *l = matrix_multi(DL, U);
	double bs[N][N]{};
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			bs[i][j] = ( - 1 * (*(l + i * N + j)));
	//Printd(bs);

	double x0[N][1] = { 1,1,1,1,1 };
	int a = Guass(bs);
	if (a == 0)
	{
		for (i = 0; i < N; i++)
			cout << "                            想继续查看执行结果吗？请输入1（继续）0（结束）\n";
		cin >> a;
		if (a != 0)
		{
			cout << "请按回车确认！\n";
			cin.get(); cin.get();
			hao();
		}
		else return;
	}
	diedai(bn, bs, x0, 1,1);//调用递归函数
	cout << "高斯塞尔德迭代法已完成！\n";
}


void Printd(const double arr[N][N])//打印函数  m表示行数，n表示列数
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(4);
			cout << setw(8) << arr[i][j];
		}
		cout << "\n\n";
	}
}
void Printd(const double arr[N][2*N])//打印函数  (函数重载)
{
	int i, j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 2*N; j++)
		{
			cout << setiosflags(ios::fixed) << setprecision(4);
			cout << setw(8) << arr[i][j];
		}
		cout << "\n\n";
	}
}

void Printd( const double arr[N][1])//打印函数，（函数重载）
{
	int i;
	for (i = 0; i < N; i++)
		cout << arr[i][0] << endl;
	cout << endl;
}
void Printd(const double arr[N])
{
	int i = 0;
	for (i = 0; i < N; i++)
		cout << arr[i] << endl;
}


void hao()
{
	for (int j = 0; j <M; j++)
		cout << "危！";
	cout << endl;
}
