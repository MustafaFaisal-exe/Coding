# Q1 - TOTAL = 19
# (a)                                                                             3

#declare Jobs : array[0:99,0:1] of integer
Jobs = []
NumberOfJobs = int

# (b)                                                                             3
def Initialise():
    global  NumberOfJobs
    NumberOfJobs = 0
    for i in range(99):
        temp = [-1,-1]
        Jobs.append(temp)

# (c)                                                                             3
def AddJob(job_num, priority_index):
    index = 0
    empty = False
    while not empty and index < len(Jobs):
        if Jobs[index] == [-1,-1]:
            empty = True
            Jobs[index][0] = job_num
            Jobs[index][1] = priority_index
            print ('ADDED')
        index += 1
    if not(index < len(Jobs)):
        print ('NOT ADDED')

# (d)                                                                              2

Initialise()
AddJob(12, 10)
AddJob(526, 9)
AddJob(33, 8)
AddJob(12, 9)
AddJob(78, 1)

# (e)                                                                              4
def InsertionSort():
    for i in range(1, len(Jobs)):
        found = True
        ItemToBeChecked = Jobs[i]
        index = i - 1
        while found and index > -1:
            if ItemToBeChecked[1] < Jobs[index][1]:
                Jobs[index + 1] = Jobs[index]
                index -= 1
            else:
                found = False
        Jobs[index + 1] = ItemToBeChecked

# (f)                                                                              2
def PrintArray():
    for i in range(len(Jobs)):
        temp = Jobs[i]
        print (str(temp[0]), "Priority", str(temp[1]))

# (g) i                                                                            1 + 1
InsertionSort()
PrintArray()
# Q2 - TOTAL = 29

#(a)                                                                               4
class Character:
    # Declare private Name as string
    # Declare private XCoordinate as integer
    # Declare private YCoordinate as integer
    def __init__(self, namep, x_cor, y_cor):
        self.__Name = namep
        self.__XCoordinate = x_cor
        self.__YCoordinate = y_cor

    # (b)                                                                          3
    def GetName(self):
        return self.__Name

    def GetX(self):
        return self.__XCoordinate

    def GetY(self):
        return self.__YCoordinate

    # (c)                                                                          2
    def ChangePosition(self, x_change, y_change):
        self.__XCoordinate += x_change
        self.__YCoordinate += y_change

# (d)                                                                              5

#declare char_array : array[0:9] of string
char_array = []

try:
    file_char = open("Characters.txt", "r")
    name = file_char.readline().strip()
    while name != "":
        x_cordinate = int(file_char.readline().strip())
        y_coordinate = int(file_char.readline().strip())
        temp = Character(name, x_cordinate, y_coordinate)
        char_array.append(temp)
        name = file_char.readline().strip()
except IOError:
    print ("File not found!!!")

# (e)                                                                              5
found = False
char_name = input("Input character's name: ")
while not found:
    index = 0
    while index < len(char_array) and not found:
        if char_array[index].GetName() == char_name:
            char_index = index
            found = True
        else:
            index += 1
    if not found:
        char_name = input("Input character's name: ")

# (f)                                                                              7
char_move = input("W - forward\nA - left\nS - down\nD - right\nEnter: ")
while char_move.lower() != "w" and char_move.lower() != "a" and char_move.lower() != "s" and char_move.lower() != "d":
    char_move = input("CHOOSE A VALID OPTION!!\nW - forward\nA - left\nS - down\nD - right\nEnter: ")

if char_move.lower() == "w":
    char_array[char_index].ChangePosition(0, 1)
elif char_move.lower() == "a":
    char_array[char_index].ChangePosition(-1, 0)
elif char_move.lower() == "s":
    char_array[char_index].ChangePosition(0, -1)
else:
    char_array[char_index].ChangePosition(1, 0)

#(f)                                                                               2 + 1
character_temp = char_array[char_index]

print (character_temp.GetName(), "has change coordinates to X =",character_temp.GetX(), "and Y =", character_temp.GetY())

# Q3 - TOTAL = 20

# (a)                                                                              3

# Declare Queue : array[0-99] of integer
# Declare HeadPointer of integer
# Declare TailPointer of integer

Queue = [0 for i in range(100)]
HeadPointer = -1
TailPointer = 0

# (b)                                                                              6

def Enqueue(store):
    global TailPointer, HeadPointer
    if TailPointer == len(Queue):
        return False
    else:
        Queue[TailPointer] = store
        TailPointer += 1
        if TailPointer == 1:
            HeadPointer = 0
        return True
# (c)                                                                              4

status = True
index = 0
while status and index < 21:
    status = Enqueue(index)
    index += 1
if not status:
    print ("Unsuccessful")
else:
    print ("Successfull")

# (d)                                                                              6

def RecursiveOuput(start):
    global total
    if start == HeadPointer:
        return Queue[HeadPointer]
    else:
        return RecursiveOuput(start - 1) + Queue[start]

# (e) i                                                                            0 + 1
print (RecursiveOuput(21))





#                                                 MARKS = 68/75 A*