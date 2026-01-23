from timeit import default_timer as timer
start = timer()
data = [1,2,3,4,5,6,7,8,9]
search = int(input("Enter a number you want to search: "))
first = 0
last = len(data) - 1
found = False
index = -1
while first <= last and not found:
    mid = int((first + last)/2)
    if search == data[mid]:
        found = True
        index = mid
    elif search < data[mid]:
        last = mid - 1
    elif search > data[mid]:
        first = mid + 1

print (found, index)
end = timer()
print (end - start)