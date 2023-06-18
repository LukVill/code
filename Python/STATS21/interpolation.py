import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate
from sklearn.cluster import KMeans
from sklearn.preprocessing import MinMaxScaler
import seaborn as sns
import os
from icecream import ic
import sys

currwd = os.path.abspath(os.getcwd())

data_df = pd.read_csv(os.path.abspath(currwd + "/data_df_noInterp.csv")).iloc[:,1:]

# UPDATES TO DATA_DF
# remove countries bc interpolation failed:
target_countries = ["Bahrain","Malaysia","Algeria"]
for i in range(len(target_countries)):
    data_df = data_df.drop(np.where(data_df["Country"] == target_countries[i])[0])
    data_df = data_df.reset_index(drop=True)

# TODO: make splines to evaluate WHI values for missing happiness
# IMPORTANT: MAKE NEW DATA_DF -> data_rev

# first and foremost, remove any countries with a ton
# of missing data

for country in data_df["Country"].unique():
    # just guess that 6 missing vals is a lot
    if data_df.groupby("Country").get_group(country).iloc[:,6].sum() > 6:
        print(country)
# remove Eswatini, Burundi, Libya, Cyprus, Mozambique
# Lesotho

target_countries = ["Eswatini", "Burundi", "Libya", "Cyprus", "Mozambique","Lesotho"]

for country in target_countries:
    indx = np.where(data_df["Country"] == country)[0]
    data_df = data_df.drop(indx)
    data_df = data_df.reset_index().drop(columns="index")


# TODO: interpolate for all empty values for each country
for country in data_df.Country.unique():
    df = data_df.groupby("Country").get_group(country).sort_values(by = "Year")
    # get indices for original dataframe
    original_indx = df.Year.sort_values().index
    # reset index for easier parsing
    df = df.reset_index().drop(columns = "index")
    # yvals = column vals of country
    for col in df.columns[2:6]:
        # if any are 0, interpolate and find values
        if(any(df[col] == 0)):
            # get indices where it's nonzero
            nonzeroIndx = np.where(df[col] != 0)[0]
            # zero indices
            zeroIndx = np.where(df[col] == 0)[0]
            # xvals = indices
            xvals = nonzeroIndx
            # yvals = nonzero vals
            yvals = np.array(df.loc[nonzeroIndx,col])
            # make interpolation spline
            spline = interpolate.splrep(xvals,yvals)

            # for every nonzero index, eval index and fill
            # in empty val
            for i in zeroIndx:
                df.loc[i,col] = interpolate.splev(i,spline)
    # update data_df
    df.index = original_indx
    for i in df.index:
        data_df.loc[i] = df.loc[i]

# remove missing val col
data_df = data_df.drop(columns="# Missing Vals")

# FINAL VERSION OF DATA_DF WITH INTERPOLATED DATA
data_df.to_csv("data_df_final.csv")