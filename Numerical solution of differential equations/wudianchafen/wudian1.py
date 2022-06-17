from math import * 
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D #3d模块
def calculate(h,N,x,y):
    '''
    input :
    h : 步长
    N ：区间等分数
    x ,y : 网格节点向量
    output:
    A: 系数矩阵
    U： 网格矩阵
    B： 微分方程中右端项向量
    '''
    A=np.zeros((N*N,N*N))
    U=np.zeros((N*N,1))
    B=np.zeros((N*N,1))
    #先处理A
    ## 处理边界条件。（上下）
    e=np.eye(N*N)
    A[0:N,:]=e[0:N,:]
    A[N*N-N:N*N,:]=e[N*N-N:N*N,:]
    #B[0:N,0]=np.zeros((N,))
    #B[N*N-N:N*N,0]=np.zeros((N,))
    ## 处理左右边界上的点
    for i in range (1,N):
        A[i*N,:]=e[i*N,:]
       # B[i*N,0]=0
        A[(i+1)*N-1,:]=e[(i+1)*N-1,:]
       # B[(i+1)*N-1,:]=0
    ##处理内点
    for j in range (N,N*N-N,1):
        if not j%N==0 and  not (j+1)%N==0:
            A[j][j]=-4
            A[j][j-1]=1
            A[j][j+1]=1
            A[j][j-N]=1
            A[j][j+N]=1
            xx=x[j//N] #取商 
            yy=y[j%N]  #取余
            B[j,0]=h*h*(2*pi*pi)*exp(pi*(xx+yy))*(sin(pi*xx)*cos(pi*yy)+cos(pi*xx)*sin(pi*yy))



    return A,U,B
def initialize():
    '''
    input:

    output:
    h: 步长
    N： 区间等分数
    k: 网格点坐标值向量（题目中要求求解的网格点坐标）
    x,y :网格节点向量
    '''
    a=b=0
    c=d=1
    h=1/32
    N=int((c-a)/h+1)
    x=[a+h*i for i in range(N)]
    y=[b+h*j for j in range(N)]
    k=[1/4,1/2,3/4]
    return h,N,k,x,y



def shuzhi(U,k,h):
    '''
    imput :
    U： 网格矩阵
    k： 网格点坐标值向量（题目中要求求解的网格点坐标）
    h:  步长
    '''
    xy1,xy2,xy3=int(k[0]/h),int(k[1]/h),int(k[2]/h)
    a1=U[xy1][xy1]
    a2=U[xy2][xy2]
    a3=U[xy3][xy3]
    print(f"a1:{a1}  a2: {a2} a3: {a3}")
        
def precise(k):
    '''
    input :
    k:网格点坐标值向量（题目中要求求解的网格点坐标）
    '''
    res=[]
    for x in k:
        y=x
        prec=exp(pi*(x+y))*sin(pi*x)*sin(pi*y)
        res.append(prec)
    print(f"{res[0]}   {res[1]}   {res[2]}")


def plotdata(x,y,U):
    '''
    input :
    x,y :网格节点
    U： 网格点矩阵
    '''
    fig=plt.figure()
    ax=Axes3D(fig)
    [X,Y]=np.meshgrid(x,y)
    # TODO 查清楚x, y 的位置
     # TODO 将精确解的图像话出来比较一下。
    ax.plot_surface(X,Y,U,cmap=plt.cm.winter)
    plt.show()

def plotdata2(x,U):
    y = [1/4,1/2,3/4]
    h = 1/32
    j = [ceil(yy/h) for yy in y]
    Y =  U[j,:]
    plt.plot(x,Y[0,:])
    plt.plot(x,Y[1,:])
    plt.plot(x,Y[2,:])
    plt.show()


def main():
    #初始化
    h,N,k,x,y=initialize()
    #计算系数矩阵，和右端项
    A,U,B=calculate(h,N,x,y)
    #np.savetxt(r'C:\Users\c2752\Desktop\resources\weifenfangchengcode\wudianchafen\A.txt',A,fmt="%d")
    U=np.dot(np.linalg.inv(A),B)
    U_M=U.reshape(N,N)
    #np.savetxt(r'C:\Users\c2752\Desktop\resources\weifenfangchengcode\wudianchafen\U.txt',U)
    #np.savetxt(r'C:\Users\c2752\Desktop\resources\weifenfangchengcode\wudianchafen\U_M.txt',U_M)
    #print(U)
    #数值解
    shuzhi(U_M,k,h)
    #精确解
    precise(k)
    #画图
    plotdata(x,y,U_M)
    #画图
    plotdata2(x,U_M)

main()