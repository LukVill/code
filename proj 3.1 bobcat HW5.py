from xml.dom.pulldom import DOMEventStream
import numpy as np
from icecream import ic


"""
MAKE 16 X 16 MATRIX
1st row: 0.63 0.63 1.2 ... 1.2 0
2nd row: 0.34 0 ... 0
3rd row: 0 0.71 ... 0
iterate until last row
last row: 0 ... 0.71 0 0
"""
DIMENSION = 17
#make initial row
A =np.array([0.63,0.63])
#append 14 1.2's (bc class 17 doesnt have a birth rate)
for x in range(DIMENSION-3):
    A = np.append(A,[1.2])
#append a 0 at the end for class 17
A = np.append(A,0)

A = np.mat(A)

ic(A.shape)

#make second row

r = np.array([0.34])
#add 16 0's
for x in range(DIMENSION-1):
    r = np.append(r,[0])
ic(r)

#append second row to first

A = np.r_[A,[r]]

#every following row will be similar form, so use for loop
#append 15 rows
for x in range(DIMENSION-2):
    temp = [0.0] * (DIMENSION)
    #change into np array
    temp = np.array(temp)
    temp[x+1] = 0.71
    #append row to matrix
    A = np.r_[A,[temp]]
ic(A)
ic(A.shape)
#get eigenvalues
eVal,eVec = np.linalg.eig(A)

print("Eigenvalues: \n",eVal)
print("Eigenvectors: \n",eVec)

#find real evals and their respective evectors
realVal = np.array([]) #array of real evals
realVec = np.array([]) #array of real evecs

#get arr of indices of real evals
idx = np.where(np.isreal(eVal))
ic(idx)

#subset eval and evec to those indices
realVal = eVal[idx]
#each index of eval, extract evec via col (meaning, [:,i])
for x in idx:
    realVec = np.c_[eVec[:,x]]

print("\n")

print("Real Eigenvalues of the Bobcat Transition Matrix:")
print(realVal,"\n")
print("Example Eigenvectors of the Bobcat Transition Matrix (columns respective to eigenvalue indices):")
print(realVec,"\n where column @index 0 is the e-vector for e-val @ index 0, and column @ index 1 is the e-vector for e-val @ index 1")

#sum col where val is biggest
domEvalidx = realVal.argmax()
domEval = realVal.max()
ic(domEvalidx)
ic(domEval)
ic(realVal.shape)
sum = 0
for x in range(DIMENSION):
    sum+=realVec[x,domEvalidx]
sum = np.real(sum)
print("Sum of Population Vectors of the Dominant Eigenvalue's Eigenvector: \n",sum)


#make dom eval array and dom eval eigen vector
domEvec = realVec[:,domEvalidx]

ic(domEvec)
ic(domEvec.shape)


domEvec = np.multiply(domEvec,np.reciprocal(sum))

print("This is the eigenvector with its values summing to 1 (i.e. proportion vector):",domEvec)

total = 0
for x in range(DIMENSION):
    total += domEvec[x,0]

print("Total of eigenvector values: \n",total,"\n So, we know the values are proportions now")
for x in range(DIMENSION):
    print("Bobcat Age Class - ", x+1, " Proportion: ",np.format_float_positional(domEvec[x,0]))

"""
APPLYING MATRIX OVER 10 YEARS
"""

#transition matrix is variable A

#make initial probability vector 
init = np.r_[0,100,50,50,25,10, [0]*11]
ic(len(init))
print("\n Initial Population Vector: \n", init)


for x in range(1,11):
    print("\n")
    print("Population Vector after ", x, "years: \n"\
            "--------------------------------------")
    init = np.matmul(A,init)
    init = np.reshape(init,(DIMENSION,1))
    for x in init:
        print(np.format_float_positional(x))

#print total to compare to eigenvector proportion
total = 0
for x in init:
    total +=x
ic(total)

#calculate proportion from each Age Class
for x in range(DIMENSION):
    prop = init[x]/total
    print("Proportion of Age Class",x+1,"to Total Population:",prop)

#reprint eigenvector proportions
for x in range(DIMENSION):
    print("Bobcat Age Class - ", x+1, " Proportion: ",np.format_float_positional(domEvec[x,0]))