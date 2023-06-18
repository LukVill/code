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


# make filepath for project folder
# ALWAYS MAKE STATS21 BE THE LAST FOLDER IN DIRECTORY PATH
currwd = os.path.abspath(os.getcwd())

# make filepath for SPI dataset (social progress index)
spiFilepath = os.path.abspath(currwd + "/SPI.csv")

# ----------
# WHI
# ----------

# make dataset for whi23
whi15 = pd.read_csv(os.path.abspath(currwd + "/WHI15.csv"))
whi16 = pd.read_csv(os.path.abspath(currwd + "/WHI16.csv"))
whi17 = pd.read_csv(os.path.abspath(currwd + "/WHI17.csv"))
whi18 = pd.read_csv(os.path.abspath(currwd + "/WHI18.csv"))
whi19 = pd.read_csv(os.path.abspath(currwd + "/WHI19.csv"))
whi20 = pd.read_excel(os.path.abspath(currwd + "/WHI20.xls"))
whi21 = pd.read_excel(os.path.abspath(currwd + "/WHI21.xls"))
whi22 = pd.read_excel(os.path.abspath(currwd + "/WHI22.xls"))

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

# make dictionary of the dataframes
whi = dict(list(enumerate([whi15,whi16,whi17,whi18,whi19,whi20,whi21,whi22])))

# change name for columns for each dataframe to Country, Happiness Score
for key in whi:
    whi[key].columns = ["Country","Happiness Score"]

# clean names from asterisks from each dataset
for key in whi:
    df = whi[key].copy()
    for i in range(len(df["Country"])):
        if "*" in df.iloc[i,0]:
            df.iloc[i,0] = df.iloc[i,0].replace("*","")
    whi[key].update(df)

# find country with leads countries
for key in whi:
    print(len(whi[key]))

# get unique countries of '22 because it has the least
# countries surveyed (for the sake of scope and accuracy)
len(np.sort(pd.unique(whi22.iloc[:,0])))
unique_countries = np.sort(pd.unique(whi22.iloc[:,0]))

# I don't know why xx is a country, but get that out of here
unique_countries = unique_countries[:len(unique_countries)-1]

def findCountryinWHI(str, repl = ""):
    for key in whi:
        df = whi[key].copy()
        print("WHI ", key+15)       
        for i in range(len(df)):
            # check if contains Czech
            if str in df.iloc[i,0]:
                print("Row",i)
                print("Name:",df.iloc[i,0], "\n")
                # if replacement exists, replace
                if repl != "":
                    print(df.iloc[i,0], " replaced with ", repl)
                    df.iloc[i,0] = repl
        whi[key].update(df)

# but this is not enough, we must double check if each dataset has
# every unique_countries entry

# with indexing issues, naming issues came up

# Special Case 1: Czech Republic vs Czechia
# easy fix: change it all to Czechia
findCountryinWHI(str = "Czech", repl = "Czechia")

# Special Case 2: Taiwan vs Taiwan Province of China
# easy fix: change it all to Taiwan
findCountryinWHI(str = "Taiwan", repl = "Taiwan")

# Special Case 3: Congo vs Congo ()
findCountryinWHI("Congo")
# there are two Congo's until 2022, no easy fix

# Special Case 4: Hong Kong
# easy fix: change it all to Hong Kong
findCountryinWHI(str = "Hong Kong", repl = "Hong Kong")

# Special Case 5: Macedonia vs North Macedonia
# easy fix: change it all to Macedonia
findCountryinWHI(str = "Macedonia", repl = "Macedonia")

# after name changes, update unique_countries
unique_countries = np.sort(pd.unique(whi22.iloc[:,0]))
unique_countries = unique_countries[:len(unique_countries)-1]

# decide which countries to omit from prev dataframes

# check if any values aren't the same in each dataset
countries_not_in_all_df = list()
for key in whi:
    df = whi[key].copy()
    # check if any df not in unique_countries
    b = np.invert(np.isin(df["Country"], unique_countries))
    print("WHI: ", (key + 15))
    print(any(b))
    # print countries not in the unique_countries
    print(df.loc[b,"Country"])
    print(len(df.loc[b,"Country"]), " countries")

    # parse through all df, make all unique countries not 
    # in at least one df
    
    # append all countries not unique_countries
    countries_not_in_all_df.append(list(df.loc[b,"Country"]))

# two dimensional list flattening function
def flatten_list2d(ls):
    res = list()
    for l in ls:
        for elem in l:
            res.append(elem)
    return res

# change into array
countries_not_in_all_df = flatten_list2d(countries_not_in_all_df)
countries_not_in_all_df = pd.DataFrame(countries_not_in_all_df)

# after adding to the list, sum all occurences in countries_not_in_all_df
sum_missing_countries = countries_not_in_all_df.value_counts()

# make list of just the countries
sum_missing_countries_list = list()
for item in sum_missing_countries.index:
    sum_missing_countries_list.append(item[0])

# figure out if which countries can utilize interpolation to fill
# in missing happiness data
# AVOID ANY EXTRAPOLATION

# return list of df's that each country is in
def findDfWHI(country):
    res = list()
    for key in whi:
        df = whi[key].copy()  
        # each country in df
        isIn = False
        for i in range(len(df)):
            # check if str does not contain
            if country in df.iloc[i,0]:
                # add df number to res
                isIn = True
        if isIn == True:
            res.append(key+15)
    return res

# for each of the countries missing in at least 1 df,
# make a dictionary of each country and their array of df's
dict_missing_countries = dict()
for country in sum_missing_countries_list:
    dict_missing_countries[country] = findDfWHI(country)

dict_missing_countries

# CLEANING DECISION:
# sequentially have 2+ years missing aren't eligible to be interpolated
# Eligible Countries: 
# Burundi, Congo (Brazzaville), Haiti, Congo (Kinshasa)

# make target countries list
interp_countries = ["Burundi","Congo (Brazzaville)", "Haiti", "Congo (Kinshasa)"]

indx = np.invert(np.isin(sum_missing_countries_list,interp_countries))
target_countries = pd.DataFrame(sum_missing_countries_list).loc[indx]

# remove all the rest from all df's
def removeCountryFromWHI(country):
    for key in whi:
        df = whi[key].copy()
        # if df had row == country
        if(np.isin(country,df.Country)):
            df = df.drop(df[df.Country == country].index[0])
        whi[key] = df

# for every country in target_countries,
# remove from WHI
for country in target_countries[0].tolist():
    removeCountryFromWHI(country)

np.isin(interp_countries,whi[7].Country.unique())

# add missing countries to 2022 unique countries
unique_countries = np.append(whi[7].Country.unique(),interp_countries)

# double check now that every df has the same
# country as unique_countries

# for every whi, print out if all countries are in
for key in whi:
    print(all(np.isin(whi[key].Country,unique_countries,)))

# MAKE ONE BIG DATAFRAME: whi_df

# cols: Country, Year, Happiness Score
data_df = pd.DataFrame(columns=["Country","Year","WHI","SPI","GDP","WGI"])

# for each year (start at 0), for each df,
# if country is that unique country, make row that is
# set Year val = year + 15,
# Happiness Score = happiness
for key in whi:
    df = whi[key].copy()
    for i in range(len(df)):
        data_df.loc[len(data_df)] = [df.iloc[i,0],key + 2015,df.iloc[i,1],0,0,0]

# add in countries with missing years

# find which countries don't have all years

year_list = list(range(2015,2023))

for country in unique_countries:
    country_years = data_df.groupby(by = "Country").get_group(country)
    # get years in the data_df
    year_bool = np.isin(year_list,country_years)
    year_not_bool = np.invert(year_bool)
    # if any years not in data_df for the country
    if any(year_not_bool):
        # add row of country name and missing year
        for i in range(len(year_not_bool)):
            # if i is the missing year, add that year as row
            if year_not_bool[i] == True:
                data_df.loc[len(data_df)] = [country,year_list[i],0,0,0,0]

# DATA_DF IS THE TOTAL DATAFRAME FOR ALL DATA NOW

# ----------
# SPI
# ----------

# make dataset for spi
spi = pd.read_csv(spiFilepath)

# exclude countries with World
spi = spi.loc[spi["country"] != "World",:]

# after cleaning, reset index
spi = spi.reset_index()

# just need country, spiyear, score_spi
spi = spi[["country","spiyear","score_spi"]]

# check for countries that do not have an spi score
spi_country_nospi = spi.loc[spi["score_spi"].isnull()]["country"].unique()


# indices in spi with spi
indx = np.invert(np.isin(spi["country"],spi_country_nospi))
# filter out spi
spi = spi.iloc[indx,:]

# check SPI is cleaned
spi.isnull().any()

# SPI IS CLEANED

# check how many countries have spi
spi_unique_country = spi["country"].unique()

# rename columns
spi.columns = ["Country","Year","SPI Score"]

# ----------
# GDP
# ----------

# import gdp
gdp = pd.read_csv(os.path.abspath(currwd + "/gdpcsvupdated.csv"))

gdp = gdp.loc[:, ~gdp.columns.isin(["Country Code","Indicator Name","Indicator Code"])]

year_list = list(range(2015,2023))
for i in range(len(year_list)):
    year_list[i] = str(year_list[i])

# melt values into usable format
gdp = pd.melt(gdp, id_vars = ["Country Name"], value_vars=year_list)

# rename cols: Country Name, Year, Value
gdp.columns = ["Country", "Year", "GDP"]


# ----------
# WGI
# ----------

wgi15 = pd.read_csv(os.path.abspath(currwd + "/WGI" + "/2015.csv"), delimiter= ";")
wgi16 = pd.read_csv(os.path.abspath(currwd + "/WGI" + "/2016.csv"), delimiter= ";")
wgi17 = pd.read_csv(os.path.abspath(currwd + "/WGI" + "/2017.csv"), delimiter= ";")
wgi18 = pd.read_csv(os.path.abspath(currwd + "/WGI" + "/2018.csv"), delimiter= ";")
wgi21 = pd.read_csv(os.path.abspath(currwd + "/WGI" + "/2021.csv"), delimiter= ";")
wgi22 = pd.read_csv(os.path.abspath(currwd + "/WGI" + "/2022.csv"), delimiter= ";")

wgi = {0:wgi15, 1:wgi16, 2:wgi17, 3:wgi18, 6:wgi21, 7:wgi22}

# important cols: Country, Total Score
# and change col names
for key in wgi:
    wgi[key] = wgi[key][["Country", "Total Score"]]
    wgi[key].columns = ["Country", "WGI"]


# change each score for each country for each wgi from str to int
for key in wgi:
    for i in range(len(wgi[key]["WGI"])):
        # make copy df
        df = wgi[key].copy()
        # remove % from str
        if "%" in df["WGI"][i]:
            s = df.loc[i,"WGI"]
            df.loc[i,"WGI"] = float(s.replace("%",""))
        # update original 
        wgi[key].update(df)

# make wgi_df
wgi_df = pd.DataFrame(columns=["Country","Year","WGI"])

for key in wgi:
    df = wgi[key].copy()
    for i in range(len(df)):
        wgi_df.loc[len(wgi_df)] = [df.iloc[i,0],key + 2015,df.iloc[i,1]]

wgi_df.Year.unique()


# ----------
# DATA MANIPULATION
# ----------

# countries to cross reference between whi, spi,
# gdp, and wgi : Czechia, Taiwan, Congo, Congo (Brazzaville)
# Hong Kong, Congo (Kinshasa), Burundi, Haiti
# remove any countries that would complicate analysis

# SPI CROSS REFERENCE

# find a country's row in SPI
def findCountryinSPI(str, repl = ""):  
    df = spi    
    for i in range(len(df)):
        # check if contains str
        if str in df.iloc[i,0]:
            print("Row",i)
            print("Name:",df.iloc[i,0], "\n")
            # if replacement exists, replace
            if repl != "":
                print(df.iloc[i,0], " replaced with ", repl)
                df.iloc[i,0] = repl
    spi.update(df)

# find country in data_df
def findCountryinData_df(str, repl = ""):  
    df = data_df    
    for i in range(len(df)):
        # check if contains str
        if str in df.iloc[i,0]:
            print("Row",i)
            print("Name:",df.iloc[i,0], "\n")
            # if replacement exists, replace
            if repl != "":
                print(df.iloc[i,0], " replaced with ", repl)
                df.iloc[i,0] = repl
    data_df.update(df)

# countries that have WHI but no SPI
no_spi = data_df["Country"].unique()[np.invert(np.isin(data_df["Country"].unique(),spi.Country.unique()))]

# came across lots of countries with no SPI

# going to work on special cases

# Special Case 1: South Korea
# easy fix: rename SPI to South Korea
findCountryinSPI("Korea", "South Korea")

# Special Case 2: North Cyprus vs Cyprus
# easy fix: rename DATA_DF to Cyprus
findCountryinData_df("Cyprus","Cyprus")

# Special Case 3: Macedonia vs Republic of North Macedonia
# easy fix: rename SPI to Macedonia
findCountryinSPI("Macedonia", "Macedonia")

# Special Case 4: Gambia vs The Gambia
# easy fix: rename SPI to Gambia
findCountryinSPI("Gambia","Gambia")

# Special Case 5: Congo (Brazzaville)
# easy fix: rename SPI Congo, Republic of, to Congo (Brazzaville)
findCountryinSPI("Congo, Republic of", "Congo (Brazzaville)")

# Special Case 6: Congo (Kinshasa)
# easy fix: rename SPI Congo Democratic Republic of, to Congo (Kinshasa)
findCountryinSPI("Congo, Democratic Republic of", "Congo (Kinshasa)")

# Special Case 7: Eswatini
# easy fix: rename DATA_DF to Eswatini
findCountryinData_df("Eswatini", "Eswatini")

# REMOVE FROM DATA_DF:
# Taiwan, Kosovo, Hong Kong, Ivory Coast, Gambia, Congo, 
# Palestinian Territories

# if row has Country inside no_spi, drop it
for i in range(len(data_df)):
    if data_df.loc[i,"Country"] in no_spi:
        data_df = data_df.drop(i)

# GDP CROSS REFERENCE

def findCountryinGdp(str, repl = ""):  
    df = gdp    
    for i in range(len(df)):
        # check if contains str
        if str in df.iloc[i,0]:
            print("Row",i)
            print("Name:",df.iloc[i,0], "\n")
            # if replacement exists, replace
            if repl != "":
                print(df.iloc[i,0], " replaced with ", repl)
                df.iloc[i,0] = repl
    gdp.update(df)


# found countries that do not have a gdp
no_gdp = data_df["Country"].unique()[np.invert(np.isin(data_df["Country"].unique(),gdp.Country.unique()))]

# Special Case 1: Venezuela
# change GDP to Venezuela
findCountryinGdp("Venezuela","Venezuela")

# Special Case 2: Czechia
# change GDP to Czechia
findCountryinGdp("Czech", "Czechia")

# Special Case 3: South Korea
# change GDP to South Korea
findCountryinGdp("Korea", "South Korea")

# Special Case 4: Russia vs Russian Federation
# change GDP to Russia
findCountryinGdp("Russia", "Russia")

# Special Case 5: Macedonia
# change GDP to Macedonia
findCountryinGdp("Macedonia","Macedonia")

# Special Case 6: Iran
# change GDP to Iran
findCountryinGdp("Iran","Iran")

# Special Case 7: Congo, Dem. Rep.
# change GDP of Congo, Dem. Rep. to Congo (Kinshasa)
findCountryinGdp("Congo, Dem. Rep.","Congo (Kinshasa)")

# Special Case 8: Congo, Rep
# change GDP of Congo, Rep. to Congo ()
findCountryinGdp("Congo, Rep.", "Congo (Brazzaville)")

# Special Case 9: Egypt, Arab Rep.
# change GDP Egypt, Arab Rep. to Egypt
findCountryinGdp("Egypt","Egypt")

# Special Case 10: Yemen, Rep.
# change GDP Yemen, Rep. to Yemen
findCountryinGdp("Yemen","Yemen")

# Special Case 11: Gambia
# change Gdp
findCountryinGdp("Gambia","Gambia")

# update no_gdp
no_gdp = data_df["Country"].unique()[np.invert(np.isin(data_df["Country"].unique(),gdp.Country.unique()))]

# reset index
data_df = data_df.reset_index().drop(columns="index")

# REMOVE FROM DATA_DF
# Slovakia, Kyrgyzstan, Laos, Eswatini
indx = list(np.where(np.isin(data_df["Country"],no_gdp) == True))
for i in indx:
    data_df = data_df.drop(i)

# reset index
data_df = data_df.reset_index().drop(columns="index")

# WGI CROSS REFERENCE

def findCountryinWgi(str, repl = ""):  
    df = wgi_df    
    for i in range(len(df)):
        # check if contains str
        if str in df.iloc[i,0]:
            print("Row",i)
            print("Name:",df.iloc[i,0], "\n")
            # if replacement exists, replace
            if repl != "":
                print(df.iloc[i,0], " replaced with ", repl)
                df.iloc[i,0] = repl
    wgi_df.update(df)

# found countries that do not have a wgi
no_wgi = data_df["Country"].unique()[np.invert(np.isin(data_df["Country"].unique(),wgi_df.Country.unique()))]

# Special Case 1: United States
# change wgi_df to United States
findCountryinWgi("United States", "United States")

# Special Case 2: Czechia
# change wgi_df to Czechia
findCountryinWgi("Czech", "Czechia")

# update no_wgi
no_wgi = data_df["Country"].unique()[np.invert(np.isin(data_df["Country"].unique(),wgi_df.Country.unique()))]

# drop Comoros in DATA_DF
data_df = data_df.reset_index().drop(columns="index")
indx = np.where(data_df["Country"] == "Comoros")
for i in indx:
    data_df = data_df.drop(i)

# NAMING CONVENTION FIX
spi_df = spi
gdp_df = gdp

# change gdp year into int
for i in range(len(gdp_df)):
    gdp_df.iloc[i,1] = int(gdp_df.iloc[i,1])


# reset all indices
data_df = data_df.reset_index().drop(columns="index")
spi_df = spi_df.reset_index().drop(columns="index")
wgi_df = wgi_df.reset_index().drop(columns="index")
gdp_df = gdp_df.reset_index().drop(columns="index")

# drop any unnecessary years in all df's
indx = np.where(spi_df["Year"] < 2015)
for i in indx:
    spi_df = spi_df.drop(i)
indx = np.where(gdp_df["Year"] < 2015)
for i in indx:
    gdp_df = gdp_df.drop(i)

# reset indices
spi_df = spi_df.reset_index().drop(columns="index")
gdp_df = gdp_df.reset_index().drop(columns="index")


# TODO: insert corresponding countries' data into data_df
# algorithm: for spi, wgi, and gdp, 
# for each row in spi, find matching row in data_df,
# insert val in corresponding column

# inserting spi
# for every row in spi
for i in range(len(spi_df)):
    vals = spi_df.iloc[i,:]
    country = vals[0]
    year = vals[1]
    spi = vals[2]
    # parse through all of data_df
    for j in range(len(data_df)):
        # find matching row
        if data_df.iloc[j,0] == country and data_df.iloc[j,1] == year:
            # set spi to that row
            data_df.iloc[j,3] = spi

# inserting wgi
for i in range(len(wgi_df)):
    vals = wgi_df.iloc[i,:]
    country = vals[0]
    year = vals[1]
    wgi = vals[2]
    # parse through all of data_df
    for j in range(len(data_df)):
        # find matching row
        if data_df.iloc[j,0] == country and data_df.iloc[j,1] == year:
            # set spi to that row
            data_df.iloc[j,5] = wgi

# inserting gdp
for i in range(len(gdp_df)):
    vals = gdp_df.iloc[i,:]
    country = vals[0]
    year = vals[1]
    gdp = vals[2]
    # parse through all of data_df
    for j in range(len(data_df)):
        # find matching row
        if data_df.iloc[j,0] == country and data_df.iloc[j,1] == year:
            # set spi to that row
            data_df.iloc[j,4] = gdp

# get all rows with 0's
empty_rows = list()
# for all rows in data_df
for i in range(len(data_df)):
    # if any col val is 0, add i to empty_rows
    if data_df.iloc[i,2] == 0 or data_df.iloc[i,3] == 0 or data_df.iloc[i,4] == 0 or data_df.iloc[i,5] == 0:
        empty_rows.append(i)

row_sum_missing_vals = pd.DataFrame(columns=["Row","Missing Vals"])

# fill na and nan with 0
data_df = data_df.fillna(0)

# for each row in data_df, sum
df = row_sum_missing_vals
for row in range(len(data_df)):
    df.loc[len(df)] = [row,0]
    addSum = 0
    for col in data_df:
        # if col val is 0, add 1 to sum
        if data_df.loc[row,col] == 0:
            addSum+=1
    df.iloc[row,1] = addSum
row_sum_missing_vals = df

# make column on data_df describing how many
# missing col vals there are
data_df["# Missing Vals"] = row_sum_missing_vals["Missing Vals"]

data_df = data_df.reset_index().drop(columns="index")

# FINAL VERSION OF DATA_DF WITHOUT DATA INTERPOLATION/EXTRAPOLATION
data_df.to_csv("data_df_noInterp.csv")
