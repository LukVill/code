import pandas as pd
import os
from icecream import ic

# make filepath for project folder
currwd = os.path.abspath("C:/Users/Luke Villanueva/source/repos/LukVill/code/Python/STATS21")

# make filepath for SPI dataset (social progress index)
spiFilepath = os.path.abspath(currwd + "/SPI.csv")

# make dataset for whi23
whi23 = pd.read_csv(os.path.abspath(currwd + "/WHI23.xls"))
print(whi23)

# make dataset for spi
spi = pd.read_csv(spiFilepath)

# first observation of WHI
whi.iloc[0,:]

# first observation of SPI
spi.iloc[0,:]


