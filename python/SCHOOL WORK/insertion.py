from timeit import default_timer as timer
start = timer()
data = [0,6,5,19,16,18,15,21,1,9,10,7,23,20,-1,-1,-1,-1,-1]
for pointer in range(1, len(data)):
    insert = data[pointer]
    found = True
    counter = pointer - 1
    while counter > -1 and found:
        if insert < data[counter]:
            data[counter + 1] = data[counter]
            counter -= 1
        else:
            found = False
    data[counter + 1] = insert
print (data)
end = timer()
print (end - start)