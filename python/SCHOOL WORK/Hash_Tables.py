hash = [ ]     
def initialise():
    for i in range(10):
        temp = [ ]
        for x in range(3):
            temp.append(0)
        hash.append(temp)
    return hash

def hashing_algorithm():
    x = int(input("Enter location: "))
    return x

def insert():
    stID = int(input("Enter student ID: "))
    stName = str(input("Enter student name: "))
    stEmail = str(input("Enter student Email: "))
    location = hashing_algorithm()
    temp_loc  = location
    loc_empty = True
    while hash[temp_loc][0] != 0 and loc_empty:
        temp_loc += 1
        if temp_loc > 9:
            temp_loc = 0
        if temp_loc == location:
            print ("No space left")
            loc_empty = False
    if not loc_empty:
        hash[temp_loc][0] = stID
        hash[temp_loc][1] = stName
        hash[temp_loc][2] = stEmail
        
hash = initialise()
insert()
insert()
insert()
