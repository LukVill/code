import random as rd

success = 0
fail = 0
for x in range(1000):
    val = rd.randint(1,25)
    print(val)
    if val == 1:
        success+=1
    else:
        fail += 1
print(success/fail)