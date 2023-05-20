library(tidyverse)
mussels <- read.delim(paste0("C:/Users/lavil/Downloads/mussels.txt"))
glimpse(mussels)
mussels
m1 <- lm(thickness ~ food + temp + seastar.density + waves + human.use, data = mussels)
m2 <- lm(thickness ~ food + temp + seastar.density + human.use + waves, data = mussels)
summary(m1)
anova(m1)
anova(m2)
