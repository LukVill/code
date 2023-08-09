
# PROBLEM 1

pqnumber <- function(s,p,q,nums)
{
  # input validation
  
  # s
  if(!isTRUE(all.equal(s,1)) & !isTRUE(all.equal(s,-1)))
  {stop("input s should be the integer 1 or -1")}
  
  # p and q
  if(!is.numeric(p) | !is.numeric(q) | p %% 1 != 0 | q %% 1 != 0)
  {stop("input p and q should be numeric and integers")}
  
  # vec
  if(!is.numeric(nums) | any(nums %% 1 != 0))
  {stop("input nums should all be integers")}
  if(p + q + 1 != length(nums))
  {stop("input nums has different number of numbers, it should be p+q+1 numbers")}
  if(any(nums < 0 | nums > 9))
  {stop("input nums should only have numebers between 0 and 9, inclusive")}
    
  structure(list(sign = s, p = p, q = q, nums = nums), class = "pqnumber")
  
}

is_pqnumber <- function(obj)
{
  # check if attributes exist
  if(!is.null(attr(obj,"sign")) | !is.null(attr(obj,"p")) | !is.null(attr(obj,"q")) | !is.null(attr(obj,"nums")))
  {
    return(FALSE)
  }
  if(!isTRUE(all.equal(obj$s,1)) & !isTRUE(all.equal(obj$s,-1)))
  {
    return(F)
  }
  if(!is.numeric(obj$p) | !is.numeric(obj$q) | obj$p %% 1 != 0 | obj$q %% 1 != 0)
  {
    return(F)
  }
  if(obj$p + obj$q + 1 != length(obj$nums))
  {
    return(F)
  }
  if(any(obj$nums < 0 | obj$nums > 9))
  {
    return(F)
  }
  return(T)
}

# pqnumber object input
print.pqnumber <- function(obj, DEC = FALSE)
{
  if(DEC == TRUE)
  {
    svals <- seq(-obj$p, obj$q)
    n <- obj$nums
    s <- obj$sign
    
    return(print(s * sum(n * 10**svals), digits = obj$p+obj$q+1))
  }
  else
  {
    print(paste0("sign = ", obj$sign), quote = F)
    print(paste0("p = ", obj$p), quote = F)
    print(paste0("q = ", obj$q), quote = F)
    print(paste0("nums = "), quote = F)
    print(paste0(obj$nums), quote = F)
  }
}

as_pqnumber <- function(x,p,q)
{
  structure(list(sign = 1, p = p, q = q, nums = x), class = "pqnumber")
}

# converting pqnumber into numeric vector
as_numeric <- function(obj)
{
  obj$nums
}

# helper function for add()
# takes in numeric vec and fixes carry overs
carry_over <- function(l)
{
  overflow <- 0
  indx <- seq_along(l)
  for(i in indx)
  {
    l[i] <- l[i] + overflow
    if(l[i] > 9)
    {
      overflow <- 1
      l[i] <- l[i] - 10
    }
    else
    {
      overflow <- 0
    }
    
    
    # check for last integer and overflow exists
    if(i == indx[length(indx)] & overflow == 1)
    {
      temp <- l
      l <- numeric(length(l) + 1)
      
      # set equal to l
      for(j in seq_along(l))
      {
        l[j] <- temp[j]
      }
      
      l[i+1] <- 1
    }
  }
  
  return(l)
  
}

# helper function
# takes in vec and if there are negatives, it borrows from next non 0 int
borrowing <- function(v)
{
  # v <- c(1,2,3,-5,4,2)
  indx <- seq_along(v)
  
  # while there exists negatives
  while(any(v < 0))
  {
    for(i in indx)
    {
      if(v[i] < 0)
      {
        # needs to borrow from next number
        # subtract next num
        v[i+1] <- v[i+1] - 1
        # add 10 to current num
        v[i] <- v[i] + 10
      }
    }
  }
  
  return(v)

}

# assume the placement of the digits are the ones being added
add <- function(x,y)
{
  # input validation

  # q
  if(x$q != y$q)
  {stop("input x and y have to have the same q")}
  # p
  if(x$p != y$p)
  {stop("input x and y have to have the same p")}
  
  res_sign <- numeric(0)
  rs <- numeric(0)
  xs <- x$nums
  ys <- y$nums
  svals <- seq(-x$p, x$q)
  
  # L + R
  if(x$sign == 1 & y$sign == 1)
  {
    rs <- xs + ys
    res_sign <- 1
  }
  
  # L + -R = L - R
  # if R > L, then -(R-L)
  if(x$sign == 1 & y$sign == -1)
  {
    if(max(which(x$nums > y$nums)) > max(which(y$nums > x$nums)))
    {
      rs <- xs - ys
      res_sign <- 1
    }
    else
    {
      rs <- ys - xs
      res_sign <- -1
    }
  }
  
  # -L + R = R - L
  # if L > R, then -(L-R)
  if(x$sign == -1 & y$sign == 1)
  {
    if(max(which(x$nums > y$nums)) > max(which(y$nums > x$nums)))
    {
      rs <- xs - ys
      res_sign <- -1
    }
    else
    {
      rs <- ys - xs
      res_sign <- 1
    }
  }
  
  # -L + -R = -(L+R)
  if(x$sign == -1 & y$sign == -1)
  {
    rs <- xs + ys
    res_sign <- -1
  }
  
  while(any(rs > 9) | any(rs < 0))
  {
    rs <- carry_over(rs)
    rs <- borrowing(rs)
  }
  
  # check svals 
  while(length(svals) < length(rs))
  {
    svals <- c(svals,svals[length(svals)]+1)
  }

  # s is 1
  return(print(res_sign * sum(rs * 10**svals), digits = length(svals)))
}


subtract <- function(x,y)
{
  # input validation
  
  # q
  if(x$q != y$q)
  {stop("input x and y have to have the same q")}
  # p
  if(x$p != y$p)
  {stop("input x and y have to have the same p")}
  
  res_sign <- numeric(0)
  xs <- x$nums
  ys <- y$nums
  rs <- numeric(0)
  svals <- seq(-x$p, x$q)
  
  # pick left and right values based on size and signs
  
  # L - R
  # if R > L, then -(R-L)
  if(x$sign == 1 & y$sign == 1)
  {
    if(max(which(x$nums > y$nums)) < max(which(y$nums > x$nums)))
    {
      rs <- ys - xs
      res_sign <- -1
    }
    else
    {
      rs <- xs - ys
      res_sign <- 1
    }
  }

  
  # - L - R = -(L + R)
  if(x$sign == -1 & y$sign == 1)
  {
    rs <- xs + ys
    res_sign <- -1
  }
  
  # L - -R = L+R
  if(x$sign == 1 & y$sign == -1)
  {
    rs <- xs + ys
    res_sign <- 1
  }
  
  # - L - - R = R - L
  # if L > R, then -(L-R)
  if(x$sign == -1 & y$sign == -1)
  {
    if(max(which(x$nums > y$nums)) > max(which(y$nums > x$nums)))
    {
      rs <- xs - ys
      res_sign <- -1
    }
    else
    {
      rs <- ys - xs
      res_sign <- 1
    }
  }
  
  while(any(rs > 9) | any(rs < 0))
  {
    rs <- carry_over(rs)
    rs <- borrowing(rs)
  }
  
  # check svals 
  while(length(svals) != length(rs))
  {
    svals <- c(svals,svals[length(svals)]+1)
  }
  
  # s is 1
  return(print(res_sign * sum(rs * 10**svals), digits = length(svals)))
}