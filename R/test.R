v <- c(TRUE,TRUE,TRUE)

isTRUE(v)

vapply(v, isTRUE, numeric(1))
