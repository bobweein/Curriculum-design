#ifndef _hanshu_h
#include<math.h>
#include<string.h>
#define N 12//复化梯形公式和复化辛普森公式中将区间N等分(即有N+1个插值结点)
#define eps0 1e-10  //区间逐次分半求积法中要求的误差
#define MAXSIZE 300//定义Romberg函数中二维数组的行数，该二维数组列数设为4
#define eps 0.5e-13//题中要求的误差在Romberg函数中使用
double f(double x,int i);//被积函数集合
double fhtx(double a, double b, int n);//复化梯形公式函数
double fhxps(double a, double b, int  n);//复化辛普森公式函数
double half_n(double a, double b);//区间逐次分半求积法函数
double T(double a, double b, int n,int z);//区间逐次分半求积法中复化梯形公式的递归公式（也可以用于龙贝格求积算法中）
double Romberg(double a, double b, int n);//龙贝格求积算法函数

double f(double x,int i)//通过i的值来使用不同的需要计算积分的被积函数
{
	if (i == 1)//复化梯形公式，复化辛普森需要使用的被积函数
	{
		if (x >= 1 && x <= 2)
			return x / (log(x + 1));
		else
		{
			printf("x不在定义域内！\n");
			return 0;
		}
	}
	else //龙贝格求积算法中需要使用的被积函数
	{
		if (x >= 0 && x <= 1)
			return 4 / (1 + x * x);
		else
		{
			printf("x不在定义域内！\n");
			return 0;
		}
	}
}
double fhtx(double a, double b, int  n)
{
	int i;
	double h, x[N];
	memset(x, 0, sizeof(x));
	h = (b - a) / n;//等分后的区间长度
	double sum;
	sum = f(a,1) + f(b,1);//先计算两个端点处的函数值
	for (i = 0; i < n - 1; i++)
	{
		x[i] = f(a + (i + 1) * h,1);//计算端点中间的各个点的函数值
		sum += 2 * x[i];//将所有点加起来
	}
	return sum * h / 2;//前面计算好了括号内的各个点的和，现在在乘上括号外的系数
}
double fhxps(double a, double b, int n)//计算想法跟上面差不多
{
	double x[N];
	memset(x, 0, sizeof(x));
	double h, sum = f(a,1) + f(b,1);//把两个端点拿出来
	int i;
	h = (b - a) / n;
	for (i = 0; i < n - 1; i = i + 2)//这两个循环分别计算奇数点和偶数点的函数值的和
	{
		x[i] = 4 * f(a + (i + 1) * h,1);
		sum += x[i];
	}
	for (i = 1; i < n - 1; i = i + 2)
	{
		x[i] = 2 * f(a + (i + 1) * h,1);
		sum += 2 * f(a + (i + 1) * h,1);
	}
	return sum * h / 3;//乘上括号外的系数
}
double T(double a, double b, int n,int z)
//这个函数是为了计算T（n）的值
//区间逐次分半求积法中的递推公式，写的是一个递归形式
{
	if (n == 1)//递归出口
		return  (b - a) * (f(a,z) + f(b,z)) / 2;
	else
	{//这里的想法还是跟前面的类似，都是想将完整的公式拆解
		double sum = T(a, b, n / 2,z) / 2;//递归思想，开始递归一直到递归出口，然后再回来时将公式的剩下一部分加上；
		double temp = 0;
		for (int i = 1; i <= n/2; i++)//用循环来计算公司的后半部分
			temp += f(a + (2 * i - 1) * (b - a) / (n),z);
		sum = sum + (b - a) /  n * temp;//将两部分加起来
		return sum;
	}
}
double half_n(double a, double b)//这里就是执行区间逐次分半算法的具体思想跟书上一样
{
	for (int n = 1;; n = n * 2)
	{
		double y = T(a, b, 2 * n,1);
		double np = y - T(a, b, n,1);
		static int nl = 1;
		if (fabs(np) <= eps0)
		{
			printf("\n总共进行了%d次区间逐次分半",nl);
			return y;
		}
		printf("第%2d次区间分半后为:%15.12lf  T(%d)\n", nl,y, 2 * n);
		printf("\n");
		nl++;
	}

}
double Romberg(double a, double b, int n)//初始值为4
{
	double romberg[MAXSIZE][4];
	memset(romberg, 0, sizeof(romberg));
	int  p = 0;
	double pri=1.0;
	while (fabs(pri) > eps && p < MAXSIZE)
	{
		//由于没有把数组设置的很大，所以这里使用两个判断条件，保证只会读取数组中的元素，而不会溢出
		int pt = (int)pow(2, p);//以下要区分四种情况
		romberg[p][0] = T(a, b,pt ,0);//第一列存放区间逐次求积算法计算的复化梯形公式的值
		for (int j = 1;j<n&&p>0&&p<MAXSIZE; j++)//循环里边就是给新加的一行的第1，2，3列元素进行处理
		{
			if (j == 1)//第二列使用S(2n)=(4/3)*T(2n)-(1/3)*T(n)公式
				romberg[p][j] = (4.0 / 3.0) * romberg[p][j - 1] - (1.0 / 3.0) * romberg[p - 1][j - 1];
			if (j == 2&&p>1)//第三列使用C(2n)=(16/15)S(2n)-(1/15)S(n)公式
				romberg[p][j] = (16.0 / 15.0) * romberg[p][j - 1] - (1.0 / 15.0) * romberg[p - 1][j - 1];
			if (j == 3&&p>2)//第四列使用R(2n)=(64/63)C(2n)-(1/63)C(n)公式
				romberg[p][j] = (64.0 / 63.0) * romberg[p][j - 1] - (1.0 / 63.0) * romberg[p - 1][j - 1];
		}
		if(p>=4)//先将p从0 到4依次取值（目的是为了等到R(p)所在的列至少有两个值在开始判断）
			pri=romberg[p][3] - romberg[p - 1][3];
		p++;
	}
	if (p >= MAXSIZE)//提示增大空间
	{
		printf("这个为数组小，请适当增加MAXSIZE的值。（没有将MAXSIZE设置很大，是为了节省空间）");
		return 0;
	}
	else
	{//这里输出龙贝格求积算法得到的表
		for (int i = 0; i <p; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (romberg[i][j] == 0) break;
				printf("%15.12lf", romberg[i][j]);
			}
			printf("\n");
			printf("\n");
		}
		return romberg[p-1][3];//返回符合精度的积分近似值
	}
}
#endif
