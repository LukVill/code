import numpy as np
from icecream import ic


"""
MAKE 17X17 MATRIX
1st row: 0.63 0.63 1.2 ... 1.2 0
2nd row: 0.34 0 ... 0
3rd row: 0 0.71 ... 0
iterate until last row
last row: 0 ... 0.71 0
"""
DIMENSION = 17

print("Best Case Rates for Bobcat Population: \n")

#make initial row
matA =np.array([0.63,0.63])
#append 14 1.2's (bc class 17 doesnt have a birth rate)
for x in range(DIMENSION-3):
    matA = np.append(matA,[1.2])
#append a 0 at the end for class 17
matA = np.append(matA,0)

matA = np.mat(matA)

ic(matA.shape)

#make second row

r = np.array([0.34])
#add 16 0's
for x in range(DIMENSION-1):
    r = np.append(r,[0])
ic(r)

#append second row to first

matA = np.r_[matA,[r]]

#every following row will be similar form, so use for loop
#append 15 rows
for x in range(DIMENSION-2):
    temp = [0.0] * (DIMENSION)
    #change into np array
    temp = np.array(temp)
    temp[x+1] = 0.71
    #append row to matrix
    matA = np.r_[matA,[temp]]
ic(matA)
ic(matA.shape)

# Parameters: A = Numpy matrix 
def displayEigen(A):

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

    print("Real Eigenvalues of the Bobcat Transition Matrix:")
    print(realVal,"\n")
    print("Example Eigenvectors of the Bobcat Transition Matrix (columns respective to eigenvalue indices):")
    print(realVec,"\n where column @index 0 is the e-vector for e-val @ index 0, and column @ index 1 is the e-vector for e-val @ index 1")

    #sum col where val is biggest
    domEvalidx = realVal.argmax()
    domEval = realVal.max()

    sum = 0
    for x in range(DIMENSION):
        sum+=realVec[x,domEvalidx]
    sum = np.real(sum)
    print("Sum of Population Vectors of the Dominant Eigenvalue's Eigenvector: \n",sum)


    #make dom eval array and dom eval eigen vector
    domEvec = realVec[:,domEvalidx]

    domEvec = np.multiply(domEvec,np.reciprocal(sum))

    print("This is the eigenvector with its values summing to 1 (i.e. proportion vector): \n",domEvec)

    total = 0
    for x in range(DIMENSION):
        total += domEvec[x,0]

    print("Total of eigenvector values: \n",total,"\n So, we know the values are proportions now")
    for x in range(DIMENSION):
        print("Bobcat Age Class - ", x+1, " Proportion: ",np.format_float_positional(domEvec[x,0]))

#display eigen info for matA
displayEigen(matA)

"""
APPLYING MATRIX OVER 10 YEARS
"""

#transition matrix is variable A

#make initial probability vector 
init = np.r_[0,100,50,50,25,10, [0]*11]
ic(len(init))
print("\n Initial Population Vector: \n", init)

# Parameters: mat = matrix to multiply initials with, init = initial probability vectors,
# years = number of years for simulation
def simulate(mat, initial,years):
    
    for x in range(1,years+1):
        print("\n")
        print("Population Vector after ", x, "years: \n"\
                "--------------------------------------")
        try:
            initial = np.matmul(mat,initial)
        except ValueError:
            print("Matrix is not the right dimension for matrix multiplication")
        initial = np.reshape(initial,(DIMENSION,1))
        for x in initial:
            print(np.format_float_positional(x))

    #print total to compare to eigenvector proportion
    total = 0
    for x in initial:
        total +=x
    print("\nTotal of Population Vector Entries:",total)

    #calculate proportion from each Age Class
    for x in range(DIMENSION):
        prop = initial[x]/total
        print("Proportion of Age Class",x+1,"to Total Population:",prop)

simulate(matA,init,10)

"""
-----------------------------------------------------------------------------------------------------------
"""

"""
Repeat for Worst Case Matrix
"""

"""
MAKE 17X17 MATRIX FOR WORST CASE
"""

"""
Matrix Composition
1: 0.6 0.6 1.15 ... 1.15 0
2: 0.32 ... 0
3: 0 0.68 ... 0
...
17: 0 ... 0.68 0
"""

print("\n\n-------------------------------\n\n")
print("Worst Case Rates for Bobcat Population: \n")

# make first row
matA = np.array([0.6,0.6])
# append 14 1.15's
for x in range(14):
    matA = np.append(matA,1.15)
#append a 0
matA = np.append(matA,0)
matA = np.mat(matA)
# make second row
r = np.array([0.32])
# append 16 0's
for x in range(16):
    r = np.append(r,0)
#make rows 3 -