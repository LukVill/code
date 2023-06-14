x <- rnorm(100,0,10)
sigma <- 50

# data 1
y1 <- 10 + 15*x + 0.5*x^2+rnorm(100,0,sigma)
m1 <- lm(y1~x)
plot(rstandard(m1)~x)

# data 2
y2 <- 10 + 15*x + 0.5*x^2 + rnorm(100,0,sigma)
m2 <- lm(y2~x + I(x^2))
plot(rstandard(m2)~x)

# data 3
y3 <- 10 + 15*x + rnorm(100,0,(x+abs(min(x))+1)*sigma)
m3 <- lm(y3~x)
plot(rstandard(m3)~x)

# data 4
y4 <- 10 + 15*x + rnorm(100,0,(5*sigma)/(x+abs(min(x))+1))
m4 <- lm(y4~x)
plot(rstandard(m4)~x)
