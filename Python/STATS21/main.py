import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from PIL import Image
import seaborn as sns
from scipy import interpolate
from sklearn.cluster import KMeans
from sklearn.preprocessing import MinMaxScaler
import os
from icecream import ic
import sys
import statsmodels.formula.api as sm
import lineardiag as ld



def main():
    res = StatsSummary()
    res.start()

# Class purpose:
# 1. to ask the user which group to see
# 2. 
class StatsSummary():
    # set attribute for rep countries
    france_df = pd.read_csv("france_df.csv").iloc[:,1:]
    mont_df = pd.read_csv("mont_df.csv").iloc[:,1:]
    ethio_df = pd.read_csv("ethio_df.csv").iloc[:,1:]
    medianData_df = pd.read_csv("medianData_df.csv").iloc[:,1:]
    france_m = sm.ols("WHI ~ SPI + GDP + WGI",france_df).fit()
    mont_m = sm.ols("WHI ~ SPI + GDP + WGI",mont_df).fit()
    ethio_m = sm.ols("WHI ~ SPI + GDP + WGI",ethio_df).fit()

    def diagModel(self,model):
        model_diag = ld.LinearRegDiagnostic(model)
        fig,axs = plt.subplots(ncols=2,nrows=2,figsize=(15,10))
        sns.set_style("darkgrid")
        model_diag.residual_plot(ax=axs[0,0])
        model_diag.qq_plot(ax=axs[0,1])
        model_diag.scale_location_plot(ax=axs[1,0])
        model_diag.leverage_plot(ax=axs[1,1])
        plt.subplots_adjust(hspace=0.35)
        plt.show()
        print(model_diag.vif_table())

    def start(self):
        print("Hello! Welcome to the Statistics Summary applet on the behavior of World Happiness Index via Social Progress, Gross Domestic Product, and World Giving Index.")
        c = input("Please select which Group you would like to analyze: 0, 1, or 2:")
        while(c != "0" and c != "1" and c != "2"):
            c = input("Whoops! Incorrect input. Please try again. Please pick 0, 1, or 2:")
        if(c == "0"):
            self.group0()
        if(c == "1"):
            self.group1()
        if(c == "2"):
            self.group2()
            
    def displayKMeans(self):
        image = Image.open("kmeansplot.png")
        image.show()

    def displayStats(self,countryStr,model,datadf):
        # display summary plots
        fig, axs = plt.subplots(2,2, figsize = (12,8))
        sns.set_style("darkgrid")

        sns.lineplot(x = "Year", y = "WHI", data = datadf, color = "red", ax = axs[0,0])
        sns.lineplot(x = "Year", y = "SPI", data = datadf, color="blue", ax = axs[0,1])
        sns.lineplot(x = "Year", y = "GDP", data = datadf, color = "green", ax = axs[1,0])
        sns.lineplot(x = "Year", y = "WGI", data = datadf, color = "black", ax = axs[1,1])
        title = "Time Series of Variables - " + countryStr
        fig.suptitle(title)

        plt.show()

    def group0(self):
        print("""
              Group 0 is observed to be
              the group with a high median happiness
              score with a high SPI. The groups can be seen
              via the following K-Means plot:
              """)
        self.displayKMeans()
        input("Press Enter to continue...")
        print("""
              The representative of this group is France.
              \n\n
              The following are the basic graphs of 
              the country's variables:
              """)
        self.displayStats("France",self.france_m,self.france_df)
        input("Press Enter to continue...")
        print("""
              The following is the summary of the stats of 
              the multiple linear regression model (where World 
              Happiness Index is the response variable, and 
              Social Progress Index, Gross Domestic Product,
              and World Giving Index are the predictor
              variables):
              """)
        print(self.france_m.summary())
        input("Press Enter to continue...")
        print("""
              The following are the diagnostic plots and 
              VIF table of the model:
              """)
        self.diagModel(self.france_m)
        print("Program ending...")


    def group1(self):
        print("""
              Group 1 is observed to be
              the group with an average median happiness
              score with an average SPI. The groups can be seen
              via the following K-Means plot:
              """)
        self.displayKMeans()
        input("Press Enter to continue...")
        print("""
              The representative of this group is Montenegro.
              \n\n
              The following are the basic graphs of 
              the country's variables:
              """)
        self.displayStats("Montenegro",self.mont_m,self.mont_df)
        input("Press Enter to continue...")
        print("""
              The following is the summary of the stats of 
              the multiple linear regression model (where World 
              Happiness Index is the response variable, and 
              Social Progress Index, Gross Domestic Product,
              and World Giving Index are the predictor
              variables):
              """)
        print(self.mont_m.summary())
        input("Press Enter to continue...")
        print("""
              The following are the diagnostic plots and 
              VIF table of the model:
              """)
        self.diagModel(self.mont_m)
        print("Program ending...")


    def group2(self):
        print("""
              Group 2 is observed to be
              the group with a low median happiness
              score with a low SPI. The groups can be seen
              via the following K-Means plot:
              """)
        self.displayKMeans()
        input("Press Enter to continue...")
        print("""
              The representative of this group is Ethiopia.
              \n\n
              The following are the basic graphs of 
              the country's variables:
              """)
        self.displayStats("Ethiopia",self.ethio_m,self.ethio_df)
        input("Press Enter to continue...")
        print("""
              The following is the summary of the stats of 
              the multiple linear regression model (where World 
              Happiness Index is the response variable, and 
              Social Progress Index, Gross Domestic Product,
              and World Giving Index are the predictor
              variables):
              """)
        print(self.ethio_m.summary())
        input("Press Enter to continue...")
        print("""
              The following are the diagnostic plots and 
              VIF table of the model:
              """)
        self.diagModel(self.ethio_m)
        print("Program ending...")

    # constructor
    def __init__(self):
        pass
    


if __name__ == "__main__":
    main()