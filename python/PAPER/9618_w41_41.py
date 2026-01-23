#def Unknown(x, y):
#    if x < y:
#        print (x + y)
#        return (Unknown(x+1, y) * 2)
#    elif x == y:
#        return 1
#    else:
#        print (x + y)
#        return (Unknown(x - 1, y) // 2)
#    
#
#print (10, " ", 15)
#print(Unknown(10, 15))
#
#print (" ")
#
#print (10, " ", 10)
#print(Unknown(10, 10))
#
#print (" ")
#
#print (15, " ", 10)
#print(Unknown(15, 10))
#
#
#def IterativeUnknown(x, y):
#    temp = 1
#    while x != y:
#        if x < y:
#            print (x + y)
#            temp = temp * 2
#            x += 1
#        else:
#            print (x + y)
#            temp = temp // 2
#            x -= 1
#    return temp
#
#print (" ")
#print (10, " ", 15)
#print(IterativeUnknown(10, 15))
#
#print (" ")
#
#print (10, " ", 10)
#print(IterativeUnknown(10, 10))
#
#print (" ")
#
#print (15, " ", 10)
#print(IterativeUnknown(15, 10))







# Q2


#class Picture:
#    #PRIVATE Description : string
#    #PRIVATE Width : integer
#    #PRIVATE Height : integer
#    #PRIVATE FrameColour : string
#    def __init__(self, Descp, widhtp, heightp, colorp):
#        self.__Description = Descp
#        self.__Width = widhtp
#        self.__Height = heightp
#        self.__FrameColour = colorp
#
#
#
#    def GetDescription(self):
#        return self.__Description
#    
#    def GetHeight(self):
#        return self.__Height
#    
#    def GetWidth(self):
#        return self.__Width
#    
#    def GetFrameColour(self):
#        return self.__FrameColour
#    
#    def SetDescription(self, new_Desc):
#        self.__Description = new_Desc
#
#
#
## Declare ArrayPicture : Array[0:99] of Picture
#
#ArrayPicture = [ ]
#
#def ReadData():
#    No_Of_Pictures = 0
#    try:
#        file = open("Pictures.txt", "r")
#        Flower_Desc = file.readline().strip()
#        while Flower_Desc != "":
#            flower_width = int(file.readline().strip())
#            flower_height = int(file.readline().strip())
#            flower_color = file.readline().strip()
#            ArrayPicture.append(Picture(Flower_Desc, flower_width, flower_height, flower_color))
#            No_Of_Pictures += 1
#            Flower_Desc = file.readline().strip()
#        return No_Of_Pictures
#    except IOError:
#        print ("File not found")
#
#
#flower_number = ReadData()
#
#
#print ("YOUR FLOWER REQUIREMENTS")
#
#user_color = str(input("Enter flower's color: "))
#user_max_width = int(input("Enter flower's max width: "))
#user_max_height = int(input("Enter flower's max height: "))
#
#for Flower in ArrayPicture:
#    if Flower.GetFrameColour() == user_color.lower():
#        if Flower.GetHeight() < user_max_height and Flower.GetWidth() < user_max_width:
#            print (" ")
#            print (Flower.GetDescription())
#            print (Flower.GetWidth())
#            print (Flower.GetHeight())
#            print (Flower.GetFrameColour())
#            print (" ")
#
#    




# Q3


# Declare ArrayNodes : Array[0:2, 0: 19] of integer
# Declare RootPointer : integer
# Declare FreeNode : integer

ArrayNodes = [[-1 for i in range(3)] for j in range(20)]

RootPointer = -1
FreeNode = 0

def AddNode(ArrayNodes, RootPointer, FreeNode):
    NodeData = int(input("Enter the data: "))
    if FreeNode <= 19:
        ArrayNodes[FreeNode][0] = -1
        ArrayNodes[FreeNode][1] = NodeData
        ArrayNodes[FreeNode][2] = -1
        if RootPointer == -1:
            RootPointer = 0
        else:
            placed = False
            CurrentNode = RootPointer
            while not placed:
                if NodeData < ArrayNodes[CurrentNode][1]:
                    if ArrayNodes[CurrentNode][0] == -1:
                        ArrayNodes[CurrentNode][0] = FreeNode
                        placed = True
                    else:
                        CurrentNode = ArrayNodes[CurrentNode][0]
                else:
                    if ArrayNodes[CurrentNode][2] == -1:
                        ArrayNodes[CurrentNode][2] = FreeNode
                        placed = True
                    else:
                        CurrentNode = ArrayNodes[CurrentNode][2]
        FreeNode = FreeNode + 1
    else:
        print ("Tree is full")
    return RootPointer, FreeNode




def PrintAll():
    for Node in ArrayNodes:
        print (Node[0], "  ", Node[1], "  ", Node[2])
    


for i in range(10):
    RootPointer, FreeNode = AddNode(ArrayNodes, RootPointer, FreeNode)



PrintAll()


print ("")

def InOrder(temproot):
    if temproot != -1:
        if ArrayNodes[temproot][0] != -1:
            InOrder(ArrayNodes[temproot][0])

        print (ArrayNodes[temproot][1])

        if ArrayNodes[temproot][2]:
            InOrder(ArrayNodes[temproot][2])
    
InOrder(RootPointer)