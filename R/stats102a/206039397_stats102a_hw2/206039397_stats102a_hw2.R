library(stringr)

# Prompt 1

# set seed to UID
set.seed(206039397)

# function to randomly generate a score from 0-100 inclusive
gen_score <- function()
{
  return(as.integer(runif(1,min = 0, max = 1) * 100))
}

# function to randomly generate a UID (9 digit number), can include optional vector of UID
# to make output unique from the vector
gen_UID <- function(uid_vec = NULL)
{
  
  # get number
  rnum <- runif(1,0,3)
  
  # substring from 1 - 11
  num <- substr(as.character(rnum),1,10)
  
  # get index of dot
  indx <- str_locate(num,".")
  
  # take out dot
  res <- paste0(substr(num,1,indx),substr(num,indx+2,nchar(num)))

  
  # OPTIONAL: if uid_vec is not null, check it
  if(!is.null(uid_vec))
  {
    # if res in uid_vec, redo generation
    while(res %in% uid_vec)
    {
      # get number
      rnum <- runif(1,0,3)
      
      # substring from 1 - 11
      num <- substr(as.character(rnum),1,10)
      
      # get index of dot
      indx <- str_locate(num,".")
      
      # take out dot
      res <- paste0(substr(num,1,indx),substr(num,indx+2,nchar(num)))
    }
  }
  
  return(as.numeric(res))
  
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
gradebook$UID <- unlist(gradebook$UID %>% map(gen_UID))
# grades
for(col in colnames(gradebook)[-1])
{
  gradebook$col <- gen_score()
}



# Prompt 2
