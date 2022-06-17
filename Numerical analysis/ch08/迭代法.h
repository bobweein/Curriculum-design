#ifndef _DIEDAIFA_H
#include <iomanip>
#include <cmath>
#define N 5
using namespace std;
void Printd(const double arr[N][N]);//打印函数
void Printd(const double arr[N][1]);
void Printd(const double arr[N][2 * N]);
void Printd(const double arr[N]);

double* matrix_multi(double  arr[N][N], double arr1[N][N]);//矩阵乘法函数
double* matrix_multi(double  arr[N][N], double arr1[N][1]);

void guassai(double  b[N][1], double Bs[N][N]);//高斯塞尔德迭代函数入口
void jacobi(double b[N][1], double Bj[N][N]);//雅各比迭代函数入口
void diedai(double arr1[N][1], double arr[N][N], double arr2[N][1], double b,int n);//实现迭代功能

double* Init(double arr[N][N]);//矩阵求逆入口
double** Guass(double a[N][2 * N]);//利用高斯列主元消去法和高斯顺序消去法实现矩阵求逆运算！
int Guass(double a[N][N]);
void hao();
#endif
