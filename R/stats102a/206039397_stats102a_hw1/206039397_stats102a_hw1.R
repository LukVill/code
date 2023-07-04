gcd <- function(val1,val2)
{
  
  # error handling for NA/NAN, and NULL
  if(is.na(val1) | is.null(val2) | is.na(val2) | is.null(val1))
  {stop("Input is NA, NAN, or NULL")}
  
  # error handling for whole numbers
  if(!(val1%%1 == 0) | !(val2%%1 == 0))
  {stop("Error: input is not an integer")}
  
  # declare variables
  bigval = numeric(0)
  smallval = numeric(0)
  
  # find biggest value to use first
  if(val1 > val2)
  {
    bigval = val1
    smallval = val2
  }
  else
  {
    bigval = val2
    smallval = val1
  }
  
  # get remainder
  rval = bigval%%smallval
  
  # repeat process until
  # rval is 0, then use last
  # small val as GCD
  while(rval != 0)
  {
    bigval = smallval
    smallval = rval
    rval = bigval%%smallval
  }
  
  # make all vals positive
  smallval <- abs(smallval)
  smallval
  
}

lcm <- function(vec)
{
  
  # error handling for NA/NAN, and NULL
  if(any(is.na(vec)) | any(is.null(vec)))
  {stop("Input has NA, NAN, or NULL")}
  
  # error check for less than 100
  if(length(vec) < 2 | length(vec) > 100)
  {stop("Incorrect vector length")}
  
  # error handling for whole numbers
  if(any(vec%%1!=0))
  {stop("Error: input is not an integer")}
  
  # set total as first elem
  total <- vec[1]
  vec <- vec[-1]
  # for each elem in vec
  for(i in seq_along(vec))
  {
    # multiply to total
    # divide by gcd
    total <- (total * vec[i])/gcd(total,vec[i])
  }
  
  # make lcm positive
  return(abs(total))
  
}

# num is vector
is_prime <- function(num)
{
  
  # error handling for NA/NAN, and NULL
  if(any(is.na(num)) | any(is.null(num)))
  {stop("Input has NA, NAN, or NULL")}
  
  # error handling for whole numbers
  if(any(num%%1 != 0))
  {stop("Error: input is not an integer")}

  res <- logical(length(num))
  
  # for each numbers in num
  for(i in seq_len(length(num)))
  {
    # bool if there does not exist any other prime num in num
    primebool <- TRUE

    # make list of all numbers before num
    vec <- seq_len(num[i])
    # remove 1 and num
    vec <- vec[c(-1,-num[i])]
    
    # for all numbers in possible prime num list
    for(j in vec)
    {
      # if the num is divisible by i, then num is not prime
      if(num[i] %% j == 0)
      {
        primebool = FALSE
        break
      }
    }
   
    # make res at i the bool val
    res[i] <- primebool
  }
  
  return(res)
  
}

get_factors <- function(n)
{
 
  # error handling for NA/NAN, and NULL
  if(is.na(n) | is.null(n))
  {stop("Input is NA, NAN, or NULL")}
    
  # error handling for whole numbers
  if(!(n%%1 == 0))
  {stop("Error: input is not an integer")}
  
  # change input into positive
  n <- abs(n)
    
  res <- list()
  
  # make list of nums before n
  vec <- seq_len(n)
  # remove 1 and n
  vec <- vec[c(-1,-n)]
  
  for(i in vec)
  {
    # if i is prime, n is divisible by i, and i is unique
    if(is_prime(i) & n %% i == 0 & !(i %in% res$primes))
    {
      # declare expcount
      expcount <- 0
      # make temp_num
      temp_num <- n
      # while divisible
      while(temp_num%%i == 0)
      {
        # increment exponent count
        expcount <- expcount + 1
        # divide temp_num
        temp_num <- temp_num / i
      }
      # update primes and exponents
      res$primes <- c(res$primes, i)
      res$exponents <- c(res$exponents, expcount)
    }
  }
  
  # if list is empty, add the number as factor
  if(length(attributes(res)) == 0)
  {
    res$primes <- c(res$primes,n)
    res$exponents <- c(res$exponents,1)
  }
  
  # add 1 to primes and exponents
  res$primes <- c(1,res$primes)
  res$exponents <- c(1,res$exponents)

  return(res)
  
}

