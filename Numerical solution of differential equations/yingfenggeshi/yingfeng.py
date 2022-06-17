from math import *
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D #3d模块
from scipy import sparse

def init():
    a ,b = 0, 1
    c ,d = 0, 1
    alpha = -1
    h ,tao = 0.05, 0.04
    J ,N = ceil((b-a)/h), ceil((d-c)/tao)
    x = np.linspace(a,b,J+1)
    t = np.linspace(c,d,N+1)
    U = np.zeros((N+1,J+1))
    temp = np.sin(np.multiply(pi,x))
    U[0,:] = np.power(temp, 40)
    r = alpha*tao/h

    
    v1 = [1+r]* (J)
    v2 = [-r]*(J)
    matrix = np.array([v2,v1])
    #三对角矩阵
    B = sparse.spdiags(matrix,[-1,0],J,J).T.A
    B[J-1][0] = -r 
    #np.savetxt(r"C:\Users\c2752\Desktop\resources\weifenfangchengcode\yingfenggeshi\data1.txt",B)
    return B, U, J, N, x, t
    
def yingfeng(B,U,J,N):
    #print(U[0,:])
    Un = np.array(U[0,:-1]).T
    #print(Un)
    for i in range(N):
        Un1 = np.dot(B, Un)
        U[i+1,:-1] = Un1.T
        Un = Un1 

    U[:,J] =U[:,0]
    #np.savetxt(r"C:\Users\c2752\Desktop\resources\weifenfangchengcode\yingfenggeshi\data.txt",U)
    
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
    np.savetxt(r"C:\Users\c2752\Desktop\resources\weifenfangchengcode\yingfenggeshi\data2.txt",X)
    np.savetxt(r"C:\Users\c2752\Desktop\resources\weifenfangchengcode\yingfenggeshi\data3.txt",Y)
    # TODO 查清楚x, t 的位置关系。
    # TODO 将精确解的图像话出来比较一下。
    ax.plot_surface(X,Y,U,cmap=plt.cm.winter)
    plt.title(["shuzhijie"])
    plt.show()

def precise(x,t):
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
    temp = np.sin(np.multiply(pi,X+Y))
    U = np.power(temp,40)
    ax.plot_surface(X,Y,U,cmap=plt.cm.winter)
    plt.title(["jingquejie"])
    plt.show()
    return U 

def plotdata2(U,U1,x):
    T = [0.00 ,0.12, 0.20, 0.80]
    tn = [ceil(i/0.04) for i in T]
    plt.plot(x,U[tn[0],:])
    plt.plot(x,U1[tn[0],:])
    plt.title("t = 0.00")
    plt.legend(["shuzhijie","jingquejie"])
    plt.show()
    plt.plot(x,U[tn[1],:])
    plt.plot(x,U1[tn[1],:])
    plt.legend(["shuzhijie","jingquejie"])
    plt.title("t = 0.12")
    plt.show()
    plt.plot(x,U[tn[2],:])
    plt.plot(x,U1[tn[2],:])
    plt.legend(["shuzhijie","jingquejie"])
    plt.title("t = 0.20")
    plt.show()
    plt.plot(x,U[tn[3],:])
    plt.plot(x,U1[tn[3],:])
    plt.legend(["shuzhijie","jingquejie"])
    plt.title("t = 0.80")
    plt.show()
def main():
    B, U, J, N, x, t = init()
    U = yingfeng(B,U,J,N)
    plotdata(x,t,U)
    U1 = precise(x, t)
    plotdata2(U,U1,x)
main()