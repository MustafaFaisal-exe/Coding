from timeit import default_timer as timer
start = timer()
data = [1,2,3,4,5]
guess = int(input("Enter a number: "))
found = False
index = 0
while found == False and index < len(data):
    if guess == data[index]:
        found = True
        loc = index
    index += 1
if found:
    print ("your number was found at ", loc, " location")
end = timer()
print (end - start)