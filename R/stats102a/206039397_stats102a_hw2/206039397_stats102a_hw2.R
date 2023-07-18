library(stringr)
library(tidyverse)
library(tidyr)

# Prompt 1

# ALL VALUES ARE CHARACTERS
gen_gradebook <- function()
{

  # set seed to UID
  set.seed(206039397)
  
  # function to randomly generate a score from 0-100 inclusive
  gen_score <- function()
  {
    return(as.integer(runif(1,min = 0, max = 1) * 100))
  }
  
  # function to randomly generate a UID (9 digit number)
  gen_UID <- function()
  {
    
    # get number
    rnum <- runif(1,0,3)
    
    # substring from 1 - 11
    num <- substr(as.character(rnum),1,10)
    
    # get index of dot
    indx <- str_locate(num,".")
    
    # take out dot
    res <- paste0(substr(num,1,indx),substr(num,indx+2,nchar(num)))
    
    return(res)
    
  }
  
  # number of students
  nStudents <- 100
  
  # declare gradebook
  gradebook <- data.frame(matrix(nrow = nStudents, ncol = 11))
  
  # change column names
  colnames(gradebook) <- c("UID","Homework_1",
                           "Homework_2","Homework_3",
                           "Homework_4","Homework_5",
                           "Quiz_1","Quiz_2","Quiz_3",
                           "Quiz_4","Quiz_5")
  
  # generate random values
  # for UID
  uid <- numeric(0)
  for(i in seq_len(nStudents))
  {
    uid <- c(uid,gen_UID())
  }
  gradebook$UID <- uid
  
  
  # grades
  for(col in colnames(gradebook)[-1])
  {
    grades <- numeric(0)
    for(i in seq_len(nStudents))
    {
      grades <- c(grades,gen_score())
    }
    gradebook[,col] <- grades
  }
  
  # format all values to character and two decimals
  for(col in colnames(gradebook)[-1])
  {
    gradebook[,col] <- format(round(gradebook[,col],2), nsmall = 2)
  }
  
  return(gradebook)
  
}


# messy_input

messy_impute <- function(df, center = "mean", margin,...)
{
  
  # INPUT VALIDATIONS

  # df
  if(!("tbl" %in% attributes(df)$class) & 
     !("data.frame" %in% attributes(df)$class))
  {stop("input df should be tibble and/or data.frame object")}
  # check col vals
  if(!all(colnames(df) %in% c("UID","Homework_1",
                     "Homework_2","Homework_3",
                     "Homework_4","Homework_5",
                     "Quiz_1","Quiz_2","Quiz_3",
                     "Quiz_4","Quiz_5")))
  {stop("input df should be gradebook object with correct column names")}
  # check num of cols
  if(length(colnames(df)) != 11)
  {stop("input df should have 11 columns")}
  if(!all(is.character(df$UID)))
  {stop("input df has invalid UID values")}
  # make sure dimensions of df are valid
  if(nrow(df) < 1 & ncol(df) < 1)
  {stop("input df has invalid dimensions")}

  # center
  if(!is.character(center) | length(center) > 1)
  {stop("input center should be type character and length 1")}
  if(center != "mean" & center != "median")
  {stop("input center can only be \"mean\" or \"median\"")}
  
  # margin
  if(!is.numeric(margin) | length(margin) > 1)
  {stop("input margin should be numeric and length 1")}
  if(margin != 1 & margin != 2)
  {stop("input margin can only be 1 or 2")}
  
  # ALGORITHM
  
  # INITIAL CONVERSION
  # convert df values to numeric
  for(col in colnames(df)[-1])
  {
    df[,col] <- as.numeric(df[,col])
  }
  
  # check if center is mean or median
  fun <- NULL
  if(center == "mean")
  {
    fun <- mean
  }
  else
  {
    fun <- median
  }

  # row wise NA change
  if(margin == 1)
  {
    for(row in seq_len(nrow(df)))
    {
      # if there is NA, impute algorithm
      if(any(is.na(df[row,])))
      {
        impute_val <- round(fun(as.numeric(as.vector(df[row,-1])), 
                                na.rm = T, ...), 
                            digits = 2)
        
        # for all NA's in df, change values
        for(i in which(is.na(df[row,])))
        {
          df[row,i] <- impute_val
        }
      }
    }
  }

  # col wise NA change
  else
  {
    for(col in seq_len(ncol(df)))
    {
      # if there is NA, impute algorithm
      if(any(is.na(df[,col])))
      {
        impute_val <- round(fun(as.numeric(as.vector(df[,col])), 
                                na.rm = T, ...), 
                            digits = 2)
        # for all NA's in df, change values
        for(i in which(is.na(df[,col])))
        {
          df[i,col] <- impute_val
        }
      }
    }
  }
  
  # format all values to character and two decimals
  for(col in colnames(gradebook)[-1])
  {
    df[,col] <- format(round(df[,col],2), nsmall = 2)
  }
  
  # done changing NAs
  return(df)
  
}

gradebook <- gen_gradebook()

# Prompt 2
