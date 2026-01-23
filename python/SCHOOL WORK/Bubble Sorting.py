num = [70,77,1,69,1]
temp_num = 0
swap = True
n = len(num) - 2
while swap:
    swap = False
    for index in range(0, n + 1):
        if num[index] > num[index + 1]:
            temp_num = num[index]
            num[index] = num[index + 1]
            num[index + 1] = temp_num
            swap = True
    n -= 1
print (num)
