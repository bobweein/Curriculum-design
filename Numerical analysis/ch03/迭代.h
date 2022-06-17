#ifndef _DIEDAI_H
#include <cmath>
#include<iomanip>
const double m = 3.1415926535897932384626433832795;
using namespace std;
double df(double x,int i=1);//求函数的一阶导数
double f(double x, int i);//“函数”列表
double gongshi(double xk, int i);//迭代公式列表
void diedai(double xk1, double xk, int i);//迭代函数
void diedai(double a, double b);//迭代公式2，（重载）
int jianyan(double x,int i);
//检验迭代公式的一阶导函数的x*处的值的绝对值是否小于1，
//（因为无法通过计算机证明一阶导数在整个区间I上的值的绝对值都小于1，所以需要人工检验一阶导数在x*处的连续性）
//因为只要证明迭代公式是自身映射以及他的一阶导数在I上的值的绝对值小于1，以及在x*出的值的绝对值小于，就可以证明
//迭代法局部收敛
//如果c++能使用符号常量就好了，应该就是让电脑证明单调性，然后再求最大值最小值；
#endif
