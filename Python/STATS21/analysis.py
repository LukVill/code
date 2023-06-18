import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import os
from icecream import ic
import sys
import statsmodels.formula.api as sm
from scipy import stats 
import lineardiag as ld

currwd = os.path.abspath(os.getcwd())

data_df = pd.read_csv(os.path.abspath(currwd + "/data_df_final.csv")).iloc[:,1:]

# get group representatives
france_df = data_df.groupby("Country").get_group("France")
france_df = france_df.reset_index(drop=True)
france_df.to_csv("france_df.csv")
mont_df =  data_df.groupby("Country").get_group("Montenegro")
mont_df = mont_df.reset_index(drop = True)
mont_df.to_csv("mont_df.csv")
ethio_df =  data_df.groupby("Country").get_group("Ethiopia")
ethio_df = ethio_df.reset_index(drop = True)
ethio_df.to_csv("ethio_df.csv")

# Multiple Linear Regression models

france_m = sm.ols("WHI ~ SPI + GDP + WGI",france_df).fit()
mont_m = sm.ols("WHI ~ SPI + GDP + WGI",mont_df).fit()
ethio_m = sm.ols("WHI ~ SPI + GDP + WGI",ethio_df).fit()

# Diagnose linear models
def diagModel(model):
    model_diag = ld.LinearRegDiagnostic(model)

    model_diag.residual_plot()
    model_diag.qq_plot()
    model_diag.scale_location_plot()
    model_diag.leverage_plot()
    print(model_diag.vif_table())

diagModel(france_m)
# analysis: 
# Linearity: scattered randomly
# Normality: generally normal
# Variance: variance seems to be increasing
# Leverage: 3 points that are hurting the model
# Collinearity: SPI and WGI seem to be collinear
# Conclusion: need to at least transform

diagModel(mont_m)
# analysis: 
# Linearity: scattered
# Normality: follows line
# Variance: variance has negative trend
# Leverage: 2 points hurt model
# Collinearity: WGI and GDP are collinear
# Conclusion: try transform

diagModel(ethio_m)
# analysis: 
# Linearity: scattered
# Normality: follows well
# Variance: scattered
# Leverage: 1 point hurting the model
# Collinearity: GDP and SPI are collinear
# Conclusion: doesn't have to transform, but could help

# Collinearity seems to be inconsistent through the
# diagnosis. Just be aware that the p-values might
# be biased because of collinearity

# TRANSFORM DATA:

# # france

# france_df.loc[:,"WHI"], lmda = stats.boxcox(france_df.loc[:,"WHI"])
# print(lmda)
# # WHI^7 transformed
# france_m = sm.ols("WHI ~ SPI + GDP + WGI",france_df).fit()
# diagModel(france_m)

# # montenegro

# mont_df.loc[:,"WHI"], lmda = stats.boxcox(mont_df.loc[:,"WHI"])
# print(lmda)

# mont_m = sm.ols("WHI ~ SPI + GDP + WGI",mont_df).fit()
# diagModel(mont_m)

# transformations aren't working well

# the models are as good as they're going to get

# interpret statistics while keeping in mind:
# collinearity is high
# few leverage points
# too few samples to see a general scatter for 
# linearity and homeoscedasticity

france_m.summary()
# Intercept and SPI are not statistically 
# significant
# GDP and WGI are statistically significant
# under 10% significant
# GDP has a positive effect, WGI has negative effect

mont_m.summary()
# Intercept and SPI are not significant
# GDP and WGI are significant under 10%
# GDP is negative and WGI is negative

ethio_m.summary()
# Intercept is barely significant
# GDP and WGI are not significant
# SPI is significant under 10%, close to 5%
# SPI has negative effect

# print out basic time series of each country
fig, axs = plt.subplots(2,2, figsize = (20,10))
sns.set(style = "whitegrid")
sns.set_palette("bright")

sns.lineplot(x = "Year", y = "WHI", data = france_df, color = "red", ax = axs[0,0])
sns.lineplot(x = "Year", y = "SPI", data = france_df, color="blue", ax = axs[0,1])
sns.lineplot(x = "Year", y = "GDP", data = france_df, color = "green", ax = axs[1,0])
sns.lineplot(x = "Year", y = "WGI", data = france_df, color = "black", ax = axs[1,1])
fig.suptitle("Time Series - France")

plt.savefig("francestats.png")

plt.show()

# montenegro

fig, axs = plt.subplots(2,2, figsize = (20,10))
sns.set(style = "whitegrid")
sns.set_palette("bright")

sns.lineplot(x = "Year", y = "WHI", data = mont_df, color = "red", ax = axs[0,0])
sns.lineplot(x = "Year", y = "SPI", data = mont_df, color="blue", ax = axs[0,1])
sns.lineplot(x = "Year", y = "GDP", data = mont_df, color = "green", ax = axs[1,0])
sns.lineplot(x = "Year", y = "WGI", data = mont_df, color = "black", ax = axs[1,1])
fig.suptitle("Time Series - Montenegro")

plt.savefig("montstats.png")

plt.show()

# ethiopia

fig, axs = plt.subplots(2,2, figsize = (20,10))
sns.set(style = "whitegrid")
sns.set_palette("bright")

sns.lineplot(x = "Year", y = "WHI", data = ethio_df, color = "red", ax = axs[0,0])
sns.lineplot(x = "Year", y = "SPI", data = ethio_df, color="blue", ax = axs[0,1])
sns.lineplot(x = "Year", y = "GDP", data = ethio_df, color = "green", ax = axs[1,0])
sns.lineplot(x = "Year", y = "WGI", data = ethio_df, color = "black", ax = axs[1,1])
fig.suptitle("Time Series - Ethiopia")

plt.savefig("ethiostats.png")

plt.show()
