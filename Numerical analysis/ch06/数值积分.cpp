#include<stdio.h>
#include "hanshu.h"
int main()
{
	double a, b,c,d;
	int  n;
	a = 1, b = 2, n = 12;
	printf("复化梯形公式计算出的值为：%15.12lf\n ", fhtx(a, b, n));
	printf("\n复化辛普森公式计算出的值为：%15.12lf\n", fhxps(a, b, n));
	printf("\n区间逐次分半求积法计算出来的值为：%15.12lf\n", half_n(a, b));
	printf("请输入需要使用龙贝格求积算法的被积函数的积分区间：\n");
	printf("请输入区间左端点 c ,区间右端点 d \n");
	c = 0, d = 1;
	printf("\n使用龙贝格求积算法计算出来的积分值为%15.12lf\n", Romberg(c,d,4));
	return 0;
}
