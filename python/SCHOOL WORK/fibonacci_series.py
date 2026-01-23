#def fibonacci(n):
#    array = []
#    array.append(0)
#    array.append(1)
#    for i in range(2, n):
#        array.append(array[i - 1] + array[i - 2])
#    return array

#print (fibonacci(8))

def rec_fibonacci(index, n):
    if index == n:
        return -1
    else:
        array.append(array[index - 1] + array[index - 2])
        return rec_fibonacci(index + 1, n)
    

array = []
array.append(0)
array.append(1)
rec_fibonacci(2, 20)
print (array)