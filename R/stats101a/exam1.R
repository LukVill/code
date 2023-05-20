batters <- read.csv(file = "C:/Users/Luke Villanueva/Downloads/battersExam.csv")
covid <- read.csv(file = "C:/Users/Luke Villanueva/Downloads/covidExam.csv")

la <- subset(covid, county == "Los Angeles")

nrow(la)
ncol(la)


la$name

colnames(la)

# group by neighborhoods then get mean of confirmed cases
la %>% group_by(name) %>% summarize(mean(confirmed_cases, na.rm = TRUE))
print(la %>% group_by(name) %>% summarize(mean(confirmed_cases, na.rm = TRUE)), n = 353)

glimpse(batters)


nrow(batters)

# SE based on sample standard deviation
SE <- sd(batters$HR)/sqrt(length(batters$HR) - 1)

#MOE
MOE <- qt(0.95, df = length(batters$HR) - 1) * SE

c(mean(batters$HR) - MOE, mean(batters$HR) + MOE)


plot(Height~Volume, data = trees)
ml <- lm(Height~Volume + Volume^2, data = trees)
ml <- lm(Height~Volume + I(Volume^2), data = trees)
ml <- lm(Height~(Volume + Volume^2), data = trees)
summary(ml)

help(nls)
help(transform)
