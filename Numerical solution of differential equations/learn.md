# 矩阵运算

1. 生成对角矩阵

```python
from scipy import sparse

matrix = np.array([[3.5,   13. ,   28.5,   50. ,   77.5],
                   [-5. ,  -23. ,  -53. ,  -95. , -149. ],
                   [2.5,   11. ,   25.5,   46. ,   72.5]]

sparse.spdiags(matrix, (1,0,-1), 5, 5).T.A
# array([[  -5. ,    2.5,    0. ,    0. ,    0. ],
#        [  13. ,  -23. ,   11. ,    0. ,    0. ],
#        [   0. ,   28.5,  -53. ,   25.5,    0. ],
#        [   0. ,    0. ,   50. ,  -95. ,   46. ],
#        [   0. ,    0. ,    0. ,   77.5, -149. ]])
```

2. 对角矩阵

 ~~~python

E=np.eye(N*N,k=0)

 ~~~
