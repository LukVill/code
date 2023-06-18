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

data_df = pd.read_csv(os.path.abspath(currwd + "/data_df_final.csv")).iloc[:,1:]

# ----------
# INITIAL VISUALIZATION
# ----------

# TODO: plot k mean plots to segregate countries into groups

# make new dataframe holding median WHI for each country
medianData_df = pd.DataFrame(columns = ["Country","WHIMed","SPIMed","GDPMed","WGIMed"])
for country in data_df.Country.unique():
    whimed = data_df.groupby("Country").get_group(country).WHI.median()
    spimed = data_df.groupby("Country").get_group(country).SPI.median()
    gdpmed = data_df.groupby("Country").get_group(country).GDP.median()
    wgimed = data_df.groupby("Country").get_group(country).WGI.median()
    medianData_df.loc[len(medianData_df)] = [country,whimed,spimed,gdpmed,wgimed]

def distanceForm(val,target):
    return np.sqrt((target-val)**2)

# K means
# find which variable provides the most distinct groups
# use 3 groups

fig, axes = plt.subplots(ncols=3,figsize = [10,10])
palette = sns.color_palette("bright")
sns.set_palette(palette)

# prepare spi and whi for k means
spi_whi_med = pd.DataFrame({"SPIMed":medianData_df["SPIMed"],"WHIMed":medianData_df["WHIMed"]})
spi_whi = list()
for i in range(len(spi_whi_med)):
    spi_whi.append(spi_whi_med.loc[i])

kmeans = KMeans(n_clusters=3, n_init=10, max_iter=15)
kmeans.fit(spi_whi)

spi_labels = kmeans.fit_predict(spi_whi)
spi_centroids = kmeans.cluster_centers_

# spi 
spi_kplot = sns.scatterplot(x = spi_whi_med["SPIMed"], y = spi_whi_med["WHIMed"], hue = spi_labels, ax = axes[0], palette=palette)
spi_kplot.set(title = "Median Happiness \n vs Median SPI")
spi_kplot.legend([],[],frameon = False)

# prepare gdp and whi for k means

gdp_whi_med = pd.DataFrame({"GDPMed":medianData_df["GDPMed"],"WHIMed":medianData_df["WHIMed"]})
gdp_whi = list()
for i in range(len(gdp_whi_med)):
    gdp_whi.append(gdp_whi_med.loc[i])

kmeans = KMeans(n_clusters=3, n_init=10, max_iter=15)
kmeans.fit(gdp_whi)

gdp_labels = kmeans.fit_predict(gdp_whi)

# gdp
gdp_kplot = sns.scatterplot(x = gdp_whi_med["GDPMed"], y = gdp_whi_med["WHIMed"], hue = gdp_labels, ax = axes[1], palette=palette)
gdp_kplot.set(title = "Median Happiness \n vs Median GDP")
gdp_kplot.set(ylabel = None)
gdp_kplot.legend([],[],frameon = False)

# prepare wgi and whi for k means

wgi_whi_med = pd.DataFrame({"WGIMed":medianData_df["WGIMed"],"WHIMed":medianData_df["WHIMed"]})
wgi_whi = list()
for i in range(len(wgi_whi_med)):
    wgi_whi.append(wgi_whi_med.loc[i])

kmeans = KMeans(n_clusters=3, n_init=10, max_iter=15)
kmeans.fit(wgi_whi)

wgi_labels = kmeans.fit_predict(wgi_whi)

# wgi 
wgi_kplot = sns.scatterplot(x = wgi_whi_med["WGIMed"], y = wgi_whi_med["WHIMed"], hue = wgi_labels, ax = axes[2], palette=palette)
wgi_kplot.set(title = "Median Happiness \n vs Median WGI")
wgi_kplot.set(ylabel = None)
wgi_kplot.legend([],[],frameon = False)

# make groups BASED ON SPI since the clustering
# looks to be the most coherent for SPI
medianData_df["Cluster"] = spi_labels

# find best representative for each group
# find whimed closest to centroid
def findCountryClosestCentroid(subsettedGroup,centroid):
    df = subsettedGroup
    df.reset_index(drop = True)
    dist = list()
    # for each country, calculate distance to WHI centroid
    for i in range(len(df)):
        dist.append(distanceForm(df.iloc[i,1],centroid))
    print(df.iloc[np.where(dist == min(dist))[0],0])
    
# group 0
spi0 = spi_centroids[0,1]
group0 = medianData_df.groupby("Cluster").get_group(0)
findCountryClosestCentroid(group0,spi0)

# group 1
spi1 = spi_centroids[1,1]
group1 = medianData_df.groupby("Cluster").get_group(1)
findCountryClosestCentroid(group1,spi1)

# group 2
spi2 = spi_centroids[2,1]
group2 =  medianData_df.groupby("Cluster").get_group(2)
findCountryClosestCentroid(group2,spi2)

# FRANCE, MONTENEGRO, AND ETHIOPIA

medianData_df.to_csv("medianData_df.csv")

plt.savefig("kmeansplot.png")

plt.show()
