# function to output Temperature transition matrix based on:
# UPPER: all 5 degree, RIGHT: all 5 degree, LEFT: all 
# 5 degree DOWN: all 0 degree
# Parameters: int n for dimension of nxn matrix
# Returns: matrix of size n for internal square matrix of T's
def upperleftright5degree(dim):

    #change dim to be dimension of square matrix in the middle
    dim = (dim-2) ** 2

    #make first row for matrix
    assert(dim>=4)
    if dim >= 4:
        matrix = np.array([4,-1,0,-1])
        matrix = np.append(matrix,[0]*(dim-4))
        matrix = np.mat(matrix)
    if dim >= 3:
        matrix = np.array([4,-1,0])
        matrix = np.append(matrix,[0]*(dim-3))
        matrix = np.mat(matrix)
    if dim >= 2:
        matrix = np.array([4,-1])
        matrix = np.append(matrix,[0]*(dim-2))
        matrix = np.mat(matrix)

    #set variable for np array
    row = np.array([0]*dim)

    # set index of main diagonal to 4
    for main in range(1,dim):
        #main diag
        row[main] = 4
        #diag+1
        if(dim-1) - main >= 1:
            row[main+1] = -1
        #diag+3
        if(dim - 1) - main >= 3:
            row[main+3] = -1
        #diag-1
        if main>=1:
            row[main-1] = -1
        #diag -3
        if main>=3:
            row[main-3] = -1
        #double 0 first occurence
        if main != dim-1 and (main+1)%3 == 0:
            row[main+1] = 0
        #double 0 second occurence
        if main != dim-1 and main%3 == 0:
            row[main-1] = 0
        #append row to matrix
        matrix = np.r_[matrix,[row]]

        #reset row's values
        row = np.array([0]*dim)

    #return resulting matrix
    return matrix