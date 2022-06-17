import numpy as np
from math import * 
from scipy import sparse
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D #3d模块
def init():
    '''
    input:
    output:
    A: 系数矩阵
    U: 网格矩阵
    x,t: 网格节点 x为空间层,t 为时间层
    h,tao: 空间和时间上的步长
    J:  空间上的区间等分数
    N： 时间上的区间等分数
    '''
    x_0, x_J = 0, 1
    t_0, t_N =0, 1
    #时间和空间上的步长
    h, tao =1/80, 1/3200
    r= ceil((1/(h*h))/(1/tao))
    #列数
    J=int((x_J-x_0)/h)
    #行数
    N=int((t_N-t_0)/tao)
    
    x=[x_0+j*h  for j in range(J+1)]
    t=[t_0+n*tao for n in range(N+1)]
    # U
    U = np. zeros((N+1,J+1))
    U[0,:] = np.cos((np.multiply(pi,x)))
    
    # 设计A矩阵
    v1 = [1+2*r]* (J+1)
    v2 = [-r]*(J+1)
    matrix = np.array([v2,v1,v2])
    #三对角矩阵
    A = sparse.spdiags(matrix,[-1,0,1],J+1,J+1).T.A
    A[0][1], A[J][J-1] = -2*r, -2*r
    #TODO 这里的A[J][J-1]中的下标有没有错误
    return A,U,x,t,h,tao,J,N
def F(tao,t,J):
    '''
    input:
    tao: 时间上的步长
    t:   某一时刻
    J：   空间上的等分数
    output:
    B:   抛物方程中的右端项向量
    '''
    T = np.array([t]*(J+1))
    B = np.multiply(tao,np.sin(T))
    return B
       
def backforward(A,U,T,tao,J,N):
    '''
    input :
    A: 系数矩阵
    U： 网格矩阵
    T： 时间网格节点
    tao: 时间上的步长
    J： 空间上的区间等分数
    N： 时间上的区间等分数
    output:
    U: 网格矩阵
    '''
    Un = np.array(U[0,:]).T
    A_inv = np.linalg.inv(A)
    
    for i in range(N):
        B = F(tao,T[i+1],J)
        Un_1 = np.dot(A_inv,Un+B)
        U[i+1,:] = Un_1.T.tolist()
        Un=np.array(U[i+1,:]).T
    
    return U
   # np.savetxt(r"C:\Users\c2752\Desktop\resources\weifenfangchengcode\paowufangcheng\U.txt",U)


def jingquejie(x,t):
    '''
    input:
    x,t: 网格节点
    output:
    U : 精确解矩阵
    '''
    fig = plt.figure()
    ax = Axes3D(fig, auto_add_to_figure =False)
    fig.add_axes(ax)
    [X,Y] = np.meshgrid(x,t)
    U=np.exp(-pi*pi*Y)*np.cos(pi*X)+(1-np.cos(Y))
    ax.plot_surface(X,Y,U,cmap=plt.cm.winter)
    plt.show()
    return U




def plotdata(x,t,U):
    '''
    input:
    x,t : 网格节点
    U : 网格矩阵
    '''
    fig = plt.figure()
    ax = Axes3D(fig, auto_add_to_figure =False)
    fig.add_axes(ax)
    [X,Y] = np.meshgrid(x,t)
    # TODO 查清楚x, t 的位置关系。
    # TODO 将精确解的图像话出来比较一下。
    ax.plot_surface(X,Y,U,cmap=plt.cm.winter)
    plt.show()

# def collectdata(U,U1):
#     x = [16*i for i in range(1,6,1)]
#     a = []
#     b = []
#     for i in x:
#         a.append(U[-1,i])
#         b.append(U1[-1,i])
#     print(a,"\n",b)

def main():
    A,U,x,t,h,tao,J,N =init()
    
    U=backforward(A,U,t,tao,J,N)
    print(type(U))
    plotdata(x,t,U) 
    U1 = jingquejie(x,t)
    #collectdata(U,U1)


main()