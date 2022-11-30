from icecream import ic
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# nxn
# form nxn with 5 degrees on top, left, right, and 0 on bottom
def nxn(row,col):
    #set first row
    matrix = np.array([5.0]*col)
    matrix = np.mat(matrix)

    #set edges to 5
    for x in range(row-2):
        r = np.array(5.0)
        r = np.append(r,[None]*(col-2))
        r = np.append(r,5.0)
        matrix = np.r_[matrix,[r]]
    # set bottom row to 0
    matrix = np.r_[matrix, [[0.0]*col]]
    return matrix


# distanceParser
# Function: increment count while negatively parsing left and up 
# a matrix, COUNTING ONLY NONE's
# Parameters: source matrix, target i (row), target j (col); 
# OPTIONAL isNegative = bool (parsing left or right)
# Returns: distance of target node from current node VIA NONE's
def distanceParser(matrix, curI, curJ, tarI, tarJ, isNegative = False):
    # Row and Col of matrix
    nrow = matrix.shape[0]
    ncol = matrix.shape[1]
    
    # Assert indices are within matrx
    assert tarI >= 0 and tarI < nrow and tarJ >= 0 and tarJ < ncol

    # Distance counter
    count = 0
    # Found target bool
    isFound = False


    # Normal forward parse
    if isNegative == False:
        # While target not found
        while (isFound == False):
            # Case 1: If col is at end, move to next row
            if curJ == ncol-1:
                curI += 1
                curJ = 0
            # Case 2: Normal parse thru cols
            else:
                curJ+=1

            # Check if new index is None (temp node), increment count
            if matrix[curI,curJ] == None:
                count+=1
            # Check if new index is target
            if curI == tarI and curJ == tarJ:
                return count
            # Impossible to reach end and not find target
            assert not(curI==nrow-1 and curJ==ncol-1 and \
                isFound==False), "Parsed but not found"


    # Negative parse
    else:
        # While target not found
        while (isFound == False):
            # Case 1: If col is at beginning, move to previous row
            if curJ == 0:
                curI -= 1
                curJ = ncol-1
            # Case 2: Normal parse thru cols
            else:
                curJ-=1

            # Check if new index is None (temp node), increment count
            if matrix[curI,curJ] == None:
                count+=1
            # Check if new index is target
            if curI == tarI and curJ == tarJ:
                return count
            # Impossible to not have found target
            assert not(curI==0 and curJ==0 and \
                isFound==False), "Parsed but not found"

# tempModel
# function to create matrix of initial temperature and null
# Parameters: initialCond matrix FORMED as object already
# Assumptions: None's are the Temp nodes (aka, not heated)
# Returns: matrix A, that is transition matrix of temperature nodes 
# size (dim-2)^2; vertical array B of initial boundary vals
def tempModel(initialCond):
    # temp nodes exist within boundary lines (i.e. index = 1,1 
    # and ends dim-2,dim-2 including)
    # 
    # find temp nodes by listing out indices of empty nodes
    # formula to find temp nodes: find which order of Temp node adds
    # into curr temp node, and then change A[i,order-1] = -1
    # general equation, 
    #                             IFF j>0     IFF j<DIM-1  IFF i>0   IFF i<DIM-1
    # temp node = 1/4 ( e[i][j-1] + e[i][j+1] + e[i-1][j] e[i+1][j]

    # Rows of initial condition matrix
    nrows = initialCond.shape[0]
    # Cols of initial condition matrix
    ncols = initialCond.shape[1]
    # Tracks current Temp node
    node_count = 0

    # Make A matrix for values of Temp nodes
    # Find total of Nones in initialCond
    totalNone = 0
    for i in range(nrows):
        for j in range(ncols):
            if initialCond[i,j] == None:
                totalNone += 1
    # Use totalNone to make transitionary matrix for Temp nodes
    A = np.zeros((totalNone,totalNone))
    # Make B matrix for temp initials for transitionary matrix
    B = np.array([0]*totalNone)

    # Make diagonal of A be all 4's
    for x in range(len(A)):
        A[x,x] = 4.0

    # Array indices
    i = 0
    j = 0
    # Check properties of cells
    for iterate in range(nrows*ncols):
        # if true, then current index is Temp node
        if initialCond[i,j] == None:
            node_count+=1               
            # Check up, left, right, and down of curr cell
            # Case 1: Check up
            # boundary check
            if i > 0:
                # if curr index is Temp node
                if initialCond[i-1,j] == None:
                    # Get distance
                    d = distanceParser(initialCond, i, j, i-1, j, \
                        isNegative = True)
                    order = node_count-d
                    # Mark A a -1 at order of Temp node
                    A[node_count-1][order-1] = -1.0
                # if not Temp node
                else:
                    # add value to B 
                    B[node_count-1] += initialCond[i-1,j]
            # Case 2: Check down
            # boundary check
            if i < nrows-1:
                # if curr index is Temp node
                if initialCond[i+1,j] == None:
                    # Get distance
                    d = distanceParser(initialCond, i, j, i+1, j, \
                        isNegative = False)
                    order = node_count + d
                    # Mark A a -1 at order of Temp node
                    A[node_count-1][order-1] = -1.0
                # if not Temp node
                else:
                    # add value to B 
                    B[node_count-1] += initialCond[i+1,j]
            # Case 3: Check left
            # boundary check
            if j > 0:
                # if curr index is Temp node
                if initialCond[i,j-1] == None:
                    # Get distance
                    d = distanceParser(initialCond, i, j, i, j-1, \
                        isNegative = True)
                    order = node_count - d
                    # Mark A a -1 at order of Temp node
                    A[node_count-1][order - 1] = -1.0
                # if not Temp node
                else:
                    # add value to B 
                    B[node_count-1] += initialCond[i,j-1]
            # Case 3: Check right
            # boundary check
            if j < ncols-1:
                # if curr index is Temp node
                if initialCond[i,j+1] == None:
                    # Get distance
                    d = distanceParser(initialCond, i, j, i, j+1, \
                        isNegative = False)
                    order = node_count + d
                    # Mark A a -1 at order of Temp node
                    A[node_count-1][order - 1] = -1.0
                # if not Temp node
                else:
                    # add value to B 
                    B[node_count-1] += initialCond[i,j+1]
        # whether true or false, parse
        # check if reached the end of initialCond matrix
        if i == nrows-1 and j == ncols -1:
            return A,B 
        # if at last col, move to next row
        if j == ncols - 1:
            i += 1
            j = 0
        # else, normal column parse
        else:
            j+=1


    # Assert to double check parsing logic
    assert node_count == totalNone, "Node Index does not match number\
    of Nones in original matrix"
    

# findTNodes
# function to find values of T1-Tn
# Parameters: transition matrix, initial conditions of temperature 
# based on diagram
# Returns: internal vector of T's
def findTNodes(transMat, initialCond):
    A = transMat
    B = initialCond
    Ainv = np.linalg.inv(A)
    print("\nInverse of A: ", A,"\n")
    # To solve for T, T = A^-1B
    T = np.matmul(Ainv,B)
    return T

# insertTNodes
# Function: inserts TNodes into initial condition matrix (aka,
# boundary matrix with initial temps) into the None values
# Parameters: T vector (for vals of T nodes); initial temp matrix
# Returns: a new matrix with boundary temps AND temp nodes
# (ready for graphing)
def insertTNodes(Tvec,initialCond):
    # For every node encountered, that node is in order, same order
    # as the Temp node resulting vector

    # Rows of initialCond
    nrows = initialCond.shape[0]
    # Columns of initialCond
    ncols = initialCond.shape[1]

    # Node counter to track which node we are on
    node_counter = 0


    # Array indices
    i = 0
    j = 0
    # For each element in initialCond
    for iterate in range(nrows*ncols):
        # if the elem is node
        if initialCond[i,j] == None:
            # increment counter
            node_counter+=1
            # extract value in resultant vector
            initialCond[i,j] = Tvec[node_counter-1] #-1 bc index
        # whether found or not, parse
        # if at last col, move to next row
        if j == ncols - 1:
            i += 1
            j = 0
        # else, normal column parse
        else:
            j+=1

    # When finished, return newly edited initialCond
    return initialCond

# plotAsHeatmap
# Function: takes a matrix formatted as a heatmap
# and converts it into a table with columns (i,j,val)
# based on row,col, and val of that cell
# Parameters: tempModel matrix, x and y dimensions of desired
# portrayed dimension of heatmap, units as str 
# Returns: displays graph of heatmap with proper dimension units
def plotAsHeatmap(mat,dimx,dimy,units):

    # Rows and Cols of matrix
    nrows = mat.shape[0]
    ncols = mat.shape[1]

    # gap between node on physical model
    xval = dimy/nrows
    yval = dimx/ncols


    # indices of matrix
    i = 0
    j = 0
    # make dictionary for vals
    r = {"row":[],"col":[],"val":[]}

    # for all elems
    for i in range(nrows):
        for j in range(ncols):
            r["row"].append(i*xval)
            r["col"].append(j*yval)
            r["val"].append(mat[i,j])
    # after parsed, convert dict to df
    df = pd.DataFrame(r)
    #.pivot(index = "row", \
     #columns = "col", values = "val")

    plt.xlim(df["col"].max(),df["col"].min())
    plt.ylim(df["row"].max(),df["row"].min())

    sns.set_palette("flare")

    sns.kdeplot(data = df, x = "col", y = "row", weights = "val", \
        thresh = 0, levels = 100, fill = True, cbar = True, cut = 0)\
        .set(xlabel ="Width in "+str(units), ylabel = "Length in "+str(units))


    plt.show()

mat = nxn(60,60)
A,B = tempModel(mat)
ic(A)
T = findTNodes(A,B)
ic(T)
result = insertTNodes(T,mat)
ic(result)
plotAsHeatmap(result,5,5,"cm")




