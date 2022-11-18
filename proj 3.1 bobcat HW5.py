import numpy as np
from icecream import ic


"""
MAKE 16 X 16 MATRIX
"""

#make initial row
A =np.array([0.63,0.63])
#append 14 1.2's
for x in range(14):
   np.append(A,[1.2])
ic(A)
matA = np.mat(A)


#second row

A =np.array([0.34])
#add 15 0's
for x in range(15):
    np.append(A,[0])

ic(A)
m = np.mat(A)
#append second row to matrix



np.r_[matA,m]

ic(matA)
ic(testM)

for x in range(15):
    b1 = [0]*16