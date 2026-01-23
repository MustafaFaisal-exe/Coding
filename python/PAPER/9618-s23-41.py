#Q1
#(a) i
#Declare DataArray : array [0-24] of integer
DataArray = [0 for i in range(25)]                                                              # 1

#(a) ii
try:
    file = open("Data.txt","r")
    for index in range(25):
        data = file.readline().strip()
        DataArray[index] = int(data)                                                            # 3
except IOError:
    print ("File not found!")

#(b) i
def PrintArray(int_array):
    for index in range(len(int_array)):                                                         # 1
        print (int_array[index])

#(b) ii
PrintArray(DataArray)                                                                           # 1 + 0

#(c)
def LinearSearch(array, val):
    count = 0
    for loc in range(len(array)):                                                               # 3
        if val == array[loc]:
            count += 1
    return count

#(d) i
num = int(input("Enter a number between 0 - 100 (inclusive): "))
while num < 0 or num > 100:                                                                     # 4 + 1
    num = int(input("INVALID ENTRY!!! Enter a number between 0 - 100 (inclusive): "))

count_num = LinearSearch(DataArray, num)
print ("The number ", num, " is found ", count_num, " times")

                                                                                                 # Q1 total = 14

class Vehicle:
#(a) i
#Q2

    #PRIVATE ID : String
    #PRIVATE MaxSpeed : Integer
    #PRIVATE CurrentSpeed : Integer
    #PRIVATE IncreaseAmount : Integer
    #PRIVATE HorizontalPosition : integer
    def __init__(self, identify, speed_max, inc_amount):
        self.__ID = identify                                                                       # 5
        self.__MaxSpeed = speed_max
        self.__CurrentSpeed = 0
        self.__IncreaseAmount = inc_amount
        self.__HorizontalPosition = 0

    
    #(a) ii
    def GetCurrentSpeed(self):
        return self.__CurrentSpeed
    
    def GetIncreaseAmount(self):
        return self.__IncreaseAmount
                                                                                                   # 3
    def GetHorizontalPosition(self):
        return self.__HorizontalPosition
    
    def GetMaxSpeed(self):
        return self.__MaxSpeed
    

    #(a) iii
    def SetCurrentSpeed(self, speed_current):
        self.__CurrentSpeed = speed_current
                                                                                                   # 3
    def SetHorizontalPosition(self, position_hor):
        self.__HorizontalPosition = position_hor

    #(a) iv
    def IncreaseSpeed(self):
        self.__CurrentSpeed += self.__IncreaseAmount
        if self.__CurrentSpeed > self.__MaxSpeed:                                                  # 2
            self.__CurrentSpeed = self.__MaxSpeed
        self.__HorizontalPosition += self.__CurrentSpeed

    #(c)
    def Output(self):
        print ("Horizontal Position: ", self.__HorizontalPosition)                                 
        print ("Speed: ", self.__CurrentSpeed)
    
#(b) i
class Helicopter(Vehicle):
    #Private VerticalPosition : integer
    #Private VerticalChange : integer
    #Private MaxHeight : integer
    def __init__(self, id, speed_max, amount_inc, change_vert, max_height):                        # 3
        Vehicle.__init__(self, id, speed_max, amount_inc)
        self.__VerticalChange = change_vert
        self.__MaxHeight = max_height
        self.__VerticalPosition = 0
    
#(b) ii
    def IncreaseSpeed(self):
        self.__VerticalPosition += self.__VerticalChange
        if self.__VerticalPosition > self.__MaxHeight:
            self.__VerticalChange += self.__MaxHeight                                               # 3
        Vehicle.SetCurrentSpeed(self, Vehicle.GetCurrentSpeed(self) + Vehicle.GetIncreaseAmount(self))
        if Vehicle.GetCurrentSpeed(self) > Vehicle.GetMaxSpeed(self):
            Vehicle.SetCurrentSpeed(self.__MaxSpeed)
        Vehicle.SetHorizontalPosition(self, Vehicle.GetCurrentSpeed(self) + Vehicle.GetHorizontalPosition(self))
        
    #(c)
    def Output(self):
        print ("Horizontal Position: ", Vehicle.GetHorizontalPosition(self))
        print ("Speed: ", Vehicle.GetCurrentSpeed(self))                                           # 3
        print ("Vertical Position: ", self.__VerticalPosition)


#(d) i
car1 = Vehicle("Tiger", 100, 20)
helicopter1 = Helicopter("Lion", 350, 40, 3, 100)
car1.IncreaseSpeed()
car1.IncreaseSpeed()                                                                               # 5 + 0
car1.Output()
helicopter1.IncreaseSpeed()
helicopter1.IncreaseSpeed()
helicopter1.Output()                  

                                                                                                  # Q3 total = 27

#Q3

#(a)
#Declare Animal : array[0-19] of string
#Declare Colour : array[0-9] of string
#Declare AnimalTopPointer of integer
#Declare ColourTopPointer of integer

Animal = [ ]
Colour = [ ]
                                                                                                  # 3
AnimalTopPointer = 0
ColourTopPointer = 0

#(b) i
def PushAnimal(DataToPush):
    global AnimalTopPointer
    if AnimalTopPointer == 20:
        return False
    else:                                                                                         # 3
        Animal.append(DataToPush)
        AnimalTopPointer += 1
        return True

#(b) ii
def PopAnimal():
    global AnimalTopPointer
    #Declare ReturnData : String
    ReturnData = ""
    if AnimalTopPointer == 0:
        return ""
    else:
        ReturnData = Animal[AnimalTopPointer - 1]                                                 # 3
        AnimalTopPointer -= 1
        return ReturnData
    
#(b) iii
def ReadData():
    try:
        Animal_file = open("AnimalData.txt", "r")
        for index in range(20):
            Animal_name = Animal_file.readline().strip()                                          # 5 + 1
            status = PushAnimal(Animal_name)
    except IOError:
        print ("File not found")

    try:
        Colour_file = open("ColourData.txt", "r")
        for index in range(10):
            Colour_name = Colour_file.readline().strip()
            status = PushColour(Colour_name)
    except IOError:
        print ("File not found")

#(b) iv
def PushColour(DataToPush):
    global ColourTopPointer
    if ColourTopPointer == 10:
        return False
    else:
        Colour.append(DataToPush)
        ColourTopPointer += 1
        return True
                                                                                                  # 2
def PopColour():
    global ColourTopPointer
    #Declare ReturnData : String
    ReturnData = ""
    if ColourTopPointer == 0:
        return ""
    else:
        ReturnData = Colour[ColourTopPointer - 1]
        ColourTopPointer -= 1
        return ReturnData
    

#(c)
def OutputItem():
    Pop_animal = PopAnimal()
    Pop_colour = PopColour()
    if Pop_colour == "":
        print ("No colour")
        status = PushAnimal(Pop_animal)
    elif Pop_animal == "":                                                                         # 5
        print ("No animal")
        status = PushColour(Pop_colour)
    else:
        print (Pop_colour, " ", Pop_animal)

#(d) i
ReadData()
OutputItem()
OutputItem()                                                                                      # 1 + 0
OutputItem()
OutputItem()

                                                                                                  # Q3 total = 23









                                                                # TOTAL = 64/75              A*