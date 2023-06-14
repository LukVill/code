import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# import sklearn as sk
import seaborn as sns
import os
from icecream import ic


# make filepath for project folder
# ALWAYS MAKE STATS21 BE THE LAST FOLDER
currwd = os.path.abspath(os.getcwd())

# make filepath for SPI dataset (social progress index)
spiFilepath = os.path.abspath(currwd + "/SPI.csv")

# make dataset for whi23
whi15 = pd.read_csv(os.path.abspath(currwd + "/WHI15.csv"))
whi16 = pd.read_csv(os.path.abspath(currwd + "/WHI16.csv"))
whi17 = pd.read_csv(os.path.abspath(currwd + "/WHI17.csv"))
whi18 = pd.read_csv(os.path.abspath(currwd + "/WHI18.csv"))
whi19 = pd.read_csv(os.path.abspath(currwd + "/WHI19.csv"))
whi20 = pd.read_excel(os.path.abspath(currwd + "/WHI20.xls"))
whi21 = pd.read_excel(os.path.abspath(currwd + "/WHI21.xls"))
whi22 = pd.read_excel(os.path.abspath(currwd + "/WHI22.xls"))
whi23 = pd.read_excel(os.path.abspath(currwd + "/WHI23.xls"))

# WHI15 useful cols: Country, Happiness Score
whi15 = whi15[["Country","Happiness Score"]]
# WHI16 useful cols: Country, Happiness Score
whi16 = whi16[["Country","Happiness Score"]]
# WHI17 useful cols: Country, Happiness.Score
whi17 = whi17[["Country","Happiness.Score"]]
# WHI18 useful cols: Country or region, Score
whi18 = whi18[["Country or region", "Score"]]
# WHI19 useful cols: Country or region, Score
whi19 = whi19[["Country or region", "Score"]]
# WHI20 useful cols: Country name, Ladder score
whi20 = whi20[["Country name", "Ladder score"]]
# WHI21 useful cols: Country name, Ladder score
whi21 = whi21[["Country name", "Ladder score"]]
# WHI22 useful cols: Country, Happiness score
whi22 = whi22[["Country", "Happiness score"]]
# WHI23 useful cols: Country name, Ladder score
whi23 = whi23[["Country name","Ladder score"]]

# make dictionary of the dataframes
whi = dict(list(enumerate([whi15,whi16,whi17,whi18,whi19,whi20,whi21,whi22,whi23])))

# get unique countries of 23 because it has the least
# countries surveyed (for the sake of scope and accuracy)
len(np.sort(pd.unique(whi23.iloc[:,0])))
unique_countries = np.sort(pd.unique(whi23.iloc[:,0]))

# but this is not enough, we must double check if each dataset has
# every unique_countries entry

# with indexing issues, naming issues came up

# Special Case 1, Czech Republic vs Czechia
for key in whi:
    df = whi[key]
    print("WHI ", key+15)       
    for i in range(len(df)):
        # check if contains Czech
        if "Czech" in df.iloc[i,0]:
            print("Row",i)
            print("Name:",df.iloc[i,0], "\n")

# STOPPED HERE: decide via SPI to choose czech republic or czechia

# for each unique country, make array for scores
# get unique country name, use it as key in dictionary,
# dict[country] = array of scores (sorted by year)
country_happiness = dict()
i = 0
for country in unique_countries:
    country_happiness[country] = list()
    # parse through each year for each country and add score 
    # to dict
    country_happiness[country].append(whi15[whi15.iloc[:,0] == country].iloc[0,1])



# visualize scores of each country for each year
#sns.lineplot(whi15, "Happiness Score", )

# 

# # make dataset for spi
# spi = pd.read_csv(spiFilepath)

# # exclude countries with World
# spi = spi.loc[spi["country"] != "World",:]

# # after cleaning, reset index
# spi.reset_index()

# # first observation of SPI
# spi.iloc[0,:]


