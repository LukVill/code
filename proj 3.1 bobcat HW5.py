import numpy as np
from icecream import ic


"""
MAKE 16 X 16 MATRIX
"""

#make initial row
A =np.array([0.63,0.63])
#append 14 1.2's
for x in range(14):
    A = np.append(A,[1.2])

A = np.mat(A)

#make second row

r = np.array([0.34])
#add 15 0's
for x in range(15):
    r = np.append(r,[0])
ic(r)

#append second row to first

A = np.r_[A,[r]]

#every following row will be similar form, so use for loop
#append 14 rows
for x in range(14):
    temp = [0.0] * 16
    #change into np array
    temp = np.array(temp)
    temp[x+1] = 0.71
    #append row to matrix
    A = np.r_[A,[temp]]
ic(A)

#get eigenvalues
eVal,eVec = np.linalg.eig(A)

ic(eVal)

#find real evals and their respective evectors
realVal = np.array([]) #array of real evals
realVec = np.array([]) #array of real evecs

#get arr of indices of real evals
idx = np.where(np.isreal(eVal))

#subset eval and evec to those indices
realVal = eVal[idx]
#each index of eval, extract evec via col (meaning, [:,i])
for x in idx:
    realVec = np.c_[eVec[:,x]]

testmat = np.mat([[1,2],[0,3]])
testval,testvec = np.linalg.eig(testmat)

ic(realVal)
ic(realVec)

"""
TODO:
i have acquired eigenvalues and eigenvectors
reference the notes, but the evals are row oriented. their index corresponds to the evec's but on the column
meaning, eval @ 1 is eval for the evec @ [:,1]

need to apply matrix to prob. vector for 10 iterations
"""

"""
APPLYING MATRIX OVER 10 YEARS
"""

#transition matrix is variable A

#make initial probability vector 
init = np.r_[0,100,50,50,25,10, [0]*10]
ic(init)

ic(A.shape)
ic(init.shape)

res = np.matmul(A,init)
ic(res)