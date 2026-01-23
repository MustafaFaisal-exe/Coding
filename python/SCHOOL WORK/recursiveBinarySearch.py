array = [1,2,3,4,5,6,7,8,9,10]
def recursiveBinarySearch(upper, lower, searchValue):
    mid = (lower + (upper - lower) // 2) 
    if upper < lower:
        return -1
    elif array[mid] < searchValue:
        return recursiveBinarySearch(upper, mid + 1, searchValue)
    elif array[mid] > searchValue:
        return recursiveBinarySearch(mid - 1, lower, searchValue)
    else:
        return mid

print (recursiveBinarySearch(9,0,6))