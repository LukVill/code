# Function: to simulate a Redwood's population via stochastic approach (i.e. Markov chain)

import numpy as np
from icecream import ic
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

plt.ylim(0,1000000)

#initialize transition matrix that steps 50 years
matA = np.mat([[12,26,6],[0.3,0.92,0],[0,0.18,0.67]])
ic(matA)

#initialize intial population
initialPop = np.array([1696,485,82])
ic(initialPop)

#display total pop
ic(initialPop.sum())

#show initial age distribution
distr = initialPop/initialPop.sum()
ic(distr)

#resultant pop vector
res = np.array([])

#make df for plotting the results
df = pd.DataFrame([initialPop])


#transition 5 times
for x in range(5):
	initialPop = np.matmul(matA,initialPop)
	initialPop = initialPop.reshape(1,3)
	initialPop = np.array(initialPop)
	#put into df as row
	d = {
			"Year "+str(x*50): initialPop
			}
	df2 = pd.DataFrame(initialPop)
	df = pd.concat([df,df2], ignore_index = True)
	initialPop = initialPop.reshape(3,1)

print(df)

sns.lineplot(data=df).set(title = "Growth of Young, Mature, \
and Old Redwoods", xlabel = "Number of 50 Year Iterations", ylabel = "Population Count (unit: 1 million)")

#print final pop vector
for x in range(len(initialPop)):
	print("Tree Age Group :"+str(initialPop[x]), np.format_float_positional(x)+"\n")

#total of res
ic(res.sum())

#show res age distribution
distr = res/res.sum()
ic(distr)

plt.show()
