import numpy as np
from icecream import ic
import random as rd
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns



DIMENSION = 17

INITIAL_POP = np.r_[0,100,50,50,25,10, [0]*11]

print("Best Case Rates for Bobcat Population: \n")


"""
MAKE 17X17 MATRIX
1st row: 0.63 0.63 1.2 ... 1.2 0
2nd row: 0.34 0 ... 0
3rd row: 0 0.71 ... 0
iterate until last row
last row: 0 ... 0.71 0
"""
def bestCaseMatrix():
    #make initial row
    m =np.array([0.63,0.63])
    #append 14 1.2's (bc class 17 doesnt have a birth rate)
    for x in range(DIMENSION-3):
        m = np.append(m,[1.2])
    #append a 0 at the end for class 17
    m = np.append(m,0)

    m = np.mat(m)

    #make second row

    r = np.array([0.34])
    #add 16 0's
    for x in range(DIMENSION-1):
        r = np.append(r,[0])
    #append second row to first

    m = np.r_[m,[r]]

    #every following row will be similar form, so use for loop
    #append 15 rows
    for x in range(DIMENSION-2):
        temp = [0.0] * (DIMENSION)
        #change into np array
        temp = np.array(temp)
        temp[x+1] = 0.71
        #append row to matrix
        m = np.r_[m,[temp]]
    return m

matA = bestCaseMatrix()
print(matA)

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

    print("\n\nDominant Eigenvalue:",domEval)

    sum = 0
    for x in range(DIMENSION):
        sum+=realVec[x,domEvalidx]
    sum = np.real(sum)
    print("\n\nSum of Population Vectors of the Dominant Eigenvalue's Eigenvector: \n",sum)


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
init = INITIAL_POP
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

def worstCaseMatrix():
    # make first row
    m = np.array([0.6,0.6])
    # append 14 1.15's
    for x in range(DIMENSION-3):
        m = np.append(m,1.15)
    #append a 0
    m = np.append(m,0)
    m = np.mat(m)

    # make second row
    r = np.array([0.32])
    # append 16 0's
    for x in range(DIMENSION-1):
        r = np.append(r,0)
    #append second row
    m = np.r_[m,[r]]
 
    #make rows 3-17
    for x in range(DIMENSION-2):
        r = np.array([0.0]*DIMENSION)
        r[x+1] = 0.68
        m = np.r_[m,[r]]
    return m

matA = worstCaseMatrix()

print(matA)

#calculate worstMatrix eigen vals and vecs
displayEigen(matA)

#initial conditions
#make initial probability vector 
init = INITIAL_POP
print("\n Initial Population Vector: \n", init)

simulate(matA,init,10)


"""

REPEAT FOR BEST CASE MATRIX BUT HAVE CATASTROPHE CHANCE

"""

#let matA = best case
matA = bestCaseMatrix()

#create function that returns bool if catastrophe occurs
def isCatastrophe():
    #generate num from 1-25
    val = rd.randint(1,25)
    if val == 1:
        return True
    else:
        return False
    
# create function that calculates iteration of the matrix FOR ONE YEAR
# if the 
#Returns matrix and resulting population vector
def simNoPrint(matrix,initial):
    #check if catastrophe occurs
    catastrophe = isCatastrophe()
    if catastrophe == True:
        matrix[0,:] *= 0.7
    initial = np.matmul(matrix,initial)
    initial = np.reshape(initial,(DIMENSION,1))
    return matrix,initial

#initial conditions
#make initial probability vector 
init = INITIAL_POP
print("\n Initial Population Vector: \n", init)

df = pd.DataFrame()

for x in range(2):
    #create data fram for one simulation
    for x in range(10):
        matB = matA
        initB = init
        matB, initB = simNoPrint(matB,initB)
        res = initB.tolist()
        df["Year",x+1] = res


    """
    EXTRACT DATA FROM DATAFRAME
    FORMAT AS DICTIONARY 
    """
    data = []
    #for each indiviual columns in total columns
    for targetCol in df.columns:
        #for each index and cell returns by items() operator
        for indx, cell in df[targetCol].items():
            #for each value IN the cell
            for val in cell:
                #set dictionary with labels
                #age group is index+1, 
                d = {"Age Group":indx+1,"Years":targetCol[1],"Population Count":val}
                data.append(d)
    print(data)
    finalData = pd.DataFrame(data)

    print("\n\n",finalData)

    graph = sns.lineplot(data = finalData, x = "Years", y = "Population Count", hue = "Age Group", legend = "full")

graph.legend(fontsize = 5, title = "Age Group:", shadow = True)
plt.show()