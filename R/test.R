v <- c(TRUE,TRUE,TRUE)

isTRUE(v)

vapply(v, isTRUE, numeric(1))

log(c(2,4,5))-exp(3)

1:3 + 2:5

length(5:12)
length(-2:1)

length(1:3)
length(2:5)

(1:10)[c(0,-5,-5,-20000)]

x <- rep(TRUE,100)
x[-1]
x[2:length(x)]
