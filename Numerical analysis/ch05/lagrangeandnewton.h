#ifndef _newtonn_h

#define N 3
void newton(double a[N][N], double x[], double y[], double x0);
void lagrange(double x[], double y[], double x0);
void newton(double a[N][N], double x[], double y[], double x0)
{
    void Print(double a[N][N]);
    double w(double x[], double x0, int i);
    printf("初始化好的矩阵：\n");
    Print(a);
    //构建差商表
    printf("将y向量的转置放在矩阵的a的第一列\n");
    for (int i = 0; i < N; i++)
        a[i][0] = y[i];
    printf("查看插入第一列后的矩阵：\n");
    Print(a);
    printf("牛顿差商表为：\n");
    for (int j = 1; j < N; j++)
        for (int i = j; i < N; i++)
            a[i][j] = (a[i - 1][j - 1] - a[i][j - 1]) / (x[i - j] - x[i]);
    Print(a);
    //不再重新开辟空间来存储需要的差商，考虑到差商表是一个下三角，
    //所以可以把对角线元素全部放到第一行,来达到节省空间的目的
    printf("对差商表进行调整：(将对角线元素放到第一行)\n");
    for (int i = 1; i < N; i++)
        a[0][i] = a[i][i];
    Print(a);
    //利用牛顿插值公式计算x0处f(x0)的近似值！
    double f = 0;
    for (int i = 0; i < N; i++)
    {
        double b = w(x, x0, i);
        f += a[0][i] * b;
    }
    printf("利用牛顿插值公式计算x0点出的近似值f(x0)为：%16.12lf\n", f);

}
double  w(double x[], double x0, int i)
{
    if (i == 0) return 1;
    double s = 1;
    for (int j = 0; j < i; j++)
        s *= (x0 - x[j]);
    return s;
}
void Print(double a[N][N])
{//用二维数组模拟矩阵
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%16.12lf", a[i][j]);
        }
        printf("\n");
        printf("\n");
    }
}

void lagrange(double x[], double y[], double x0)
{
    double li[N];
    double sum = 0;
    for (int i = 0; i < N; i++)
        li[i] = 1;
    printf("拉格朗日插值基函数的值为： ");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == i) continue;
            li[i] *= (x0 - x[j]) / (x[i] - x[j]);
        }
        printf("%16.10lf", li[i]);
        sum += li[i] * y[i];
    }
    printf("\n");
    printf("\n利用拉格朗日插值公式计算x0处的f(x0)的近似值为:%16.12lf\n", sum);
    printf("\n");
}
#endif#pragma once
