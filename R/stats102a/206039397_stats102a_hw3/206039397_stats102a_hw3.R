library(stringr)

names <- read.csv("names.txt", sep = "\n", header = F) %>% rename(names = V1)
passwords <- read.csv("passwords.txt", sep = "\n", header = F) %>% rename(passwords = V1)
cards <- read.csv("cards.txt", sep = "\n", header = F) %>% rename(cards = V1)
load("wordlists.RData")

# uses names
pat_1_a <- function(vec)
{
  vec[str_detect(vec, "\\d+")]
}

pat_1_b <- function(vec)
{
  vec[str_detect(vec,"^[a-zA-Z]{4}$")]
}

pat_1_c <- function(vec)
{
  vec[str_detect(vec, "^([A-Z][a-z]+ )([A-Z][a-z]+ )*?([A-Z][a-z]+)$")]
}

# uses cards
pat_2_a <- function(vec)
{
  res <- vec[str_detect(vec, "^5(\\D*?\\d\\D*?){15}$")]
  
  # replace all whitespace with no char
  res1 <- str_replace_all(res, "\\D","")
  
  # print with correct whitespace
  return(str_replace_all(res1,"^(\\d{4})(\\d{4})(\\d{4})(\\d{4})$","\\1 \\2 \\3 \\4"))
}

pat_2_b <- function(vec)
{
  res <- vec[str_detect(vec, "^4(\\D*?\\d\\D*?){12,15}$")]
  
  # replace all whitespace with no char
  res1 <- str_replace_all(res, "\\D","")
  
  # print with correct whitespace
  return(str_replace_all(res1, "^(\\d{4})(\\d{4})(\\d{4})(\\d+)$", "\\1 \\2 \\3 \\4"))
}

# uses passwords
pat_3_a <- function(vec)
{
  # condition: check if exists 1 letter, 1 number, restrict to at least 8 matches
  vec[str_detect(vec, "^(?=.*[a-zA-Z]+.*)(?=.*[0-9]+.*).{8,}$")]
}

pat_3_b <- function(vec)
{
  # 1 upper, 1 lower, 1 digit, min 8 chars
  vec[str_detect(vec, "^(?=.*[A-Z].*)(?=.*[a-z].*)(?=.*\\d.*).{8,}$")]
}

# match x and none of y
pat_4_a <- function(x,y)
{
  pattern <- "^(?!.*[g-z].*).*$"
  # contains only letters from a-f
  print("x matches:")
  print(x[str_detect(x,pattern)])
  print("y matches:")
  print(y[str_detect(y,pattern)])
}

pat_4_b <- function(x,y)
{
  pattern <- "^(\\w{3}).*\\1.*$"
  # 3 length phrase at beginning is repeated twice in string
  print("x matches:")
  print(x[str_detect(x, pattern)])
  print("y matches:")
  print(y[str_detect(y, pattern)])
}

pat_4_c <- function(x,y)
{
  pattern <- "^.*ick$"
  # words ending with ick
  str_view_all(x, pattern)
  print("x matches:")
  print(x[str_detect(x, pattern)])
  print("y matches:")
  print(y[str_detect(y, pattern)])
}
