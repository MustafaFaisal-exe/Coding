import random

randnum = [0 for i in range(50)]

index = 0
no_of_randomcalls = 0

while index < 50:
    num_random = random.randint(0, 49)
    no_of_randomcalls += 1

    if randnum[num_random] == 0:
        randnum[num_random] = num_random
    
        index += 1
    
boundary = 49

noswap = False

while not noswap:
    noswap = True
    for i in range(boundary):
        if randnum[i] < randnum[i + 1]:
            temp = randnum[i + 1]
            randnum[i + 1] = randnum[i]
            randnum[i] = temp
            noswap = False
    boundary -= 1

print (randnum)
print (no_of_randomcalls)