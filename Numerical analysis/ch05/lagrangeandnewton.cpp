#include <stdio.h>
#include <string.h>
#include "newton.h"
//现在设定的插值结点为6个，如果需要增加或减少插值结点的个数的话，请到头文件"newtonANDlagrange.h"
//找到  #define N 6 这个地方，把数字改成你想要的插值结点的个数就行 
int main()
{
    double a[N][N];
    double x0=1.54;//近似值
    memset(a, 0, sizeof(a));//初始化
    double  x[N] = {1.4,1.5,1.6};
    double y[N] = {1.602,1.837,2.121};
    printf("请输入插值结点：");
    for (int i = 0; i < N; i++)
        printf("%lf", x[i]);
    printf("\n");
    printf("请输入插值结点对应的函数值：");
    for (int i = 0; i < N; i++)
        printf("%lf", y[i]);
    printf("\n");
    printf("请输入需要求函数近似值的x0:");
    printf("%lf", x0);
    printf("\n");
    lagrange(x, y, x0); //调用拉格朗日插值函数
    newton(a, x, y, x0);//调用牛顿插值函数
    return 0;
}
