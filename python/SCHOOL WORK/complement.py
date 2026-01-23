A1 = [1, 3, 6, 9, 10]
A2 = [2, 3, 10, 12, 14]
A3 = [0 for i in range(5)]

location = 0
def complement(index):
    global location
    if index > len(A1) - 1:
        return A1[len(A1) - 1]
    else:
        counter = 0
        found = False
        while counter < len(A1) and not found:
            if A1[index] == A2[counter]:
                found = True
            counter += 1
        if not found:
            A3[location] = A1[index]
            location += 1
        return complement(index + 1)

complement(0)
for index in range(len(A3)):
    if A3[index] != 0:
        print (A3[index])
