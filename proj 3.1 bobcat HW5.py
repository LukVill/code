from xml.dom.pulldom import DOMEventStream
import numpy as np
from icecream import ic


"""
MAKE 16 X 16 MATRIX
"""
DIMENSION = 16
#make initial row
A =np.array([0.63,0.63])
#append 14 1.2's
for x in range(14):
    A = np.append(A,[1.2])

A = np.mat(A)

#make second row

r = np.array([0.34])
#add 15 0's
for x in range(DIMENSION-1):
    r = np.append(r,[0])
ic(r)

#append second row to first

A = np.r_[A,[r]]

#every following row will be similar form, so use for loop
#append 14 rows
for x in range(DIMENSION-2):
    temp = [0.0] * 16
    #change into np array
    temp = np.array(temp)
    temp[x+1] = 0.71
    #append row to matrix
    A = np.r_[A,[temp]]
ic(A)

#get eigenvalues
eVal,eVec = np.linalg.eig(A)

print("Eigenvalues: \n",eVal)
print("Eigenvectors: \n",eVec)

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

print("\n")

print("Eigenvalues of the Bobcat Transition Matrix:")
print(realVal,"\n")
print("Example Eigenvectors of the Bobcat Transition Matrix (columns respective to eigenvalue indices):")
print(realVec,"\n where column @index 0 is the e-vector for e-val @ index 0, and column @ index 1 is the e-vector for e-val @ index 1")

#sum column 1
sum = 0
for x in range(DIMENSION):
    sum+=realVec[x,0]
sum = np.real(sum)
print("Sum of Population Vectors of the Dominant Eigenvalue's Eigenvector: \n",sum)


#make dom eval array and dom eval eigen vector
domEval = np.max(realVal)
domEval.reshape(1,1)
idx = np.where(np.max(realVal))
ic(idx)
domEvec = realVec[:,idx]
domEvec = domEvec.flatten()
domEvec = np.real(domEvec)

ic(domEvec)
ic(domEvec.shape)

domEvec = np.multiply(domEvec,np.reciprocal(sum))

print("This is the eigenvector with its values summing to 1 (i.e. proportion vector):",domEvec)

total = 0
for x in range(DIMENSION):
    total += domEvec[0,x]

print("Total of eigenvector values: \n",total,"\n So, we know the values are proportions now")
for x in range(DIMENSION):
    print("Bobcat Age Class - ", x+1, " Proportion: ",np.format_float_positional(domEvec[0,x]))


"""
TODO: 
wait for professor to clarify if the table implies that there is an 
Age Class 17

Since there is a survival rate for Age Class 16 is 0.71
"""

"""
APPLYING MATRIX OVER 10 YEARS
"""

#transition matrix is variable A

#make initial probability vector 
init = np.r_[0,100,50,50,25,10, [0]*10]
print("\n Initial Population Vector: \n", init)


for x in range(1,11):
    print("\n")
    print("Probability Vector after ", x, "years: \n")
    init = np.matmul(A,init)
    init = np.reshape(init,(16,1))
    print(init)