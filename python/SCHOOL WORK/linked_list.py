class Node:
    def __init__(self, datap, pointP):
        self.Data = datap
        self.Pointer = pointP

list = ["" for i in range(6)]
nullptr = "-1"
Fptr = "0"
start = nullptr

def CreateList():
    for i in range(5):
        list[i] = Node("", str(i + 1))
    list[5] = Node("", str(nullptr))

def Add(val):
    global Fptr, start
    added = False
    if Fptr != nullptr:
        current = Fptr
        list[int(current)].Data = val
        Fptr = list[int(current)].Pointer
        ThisNode = start
        previous = nullptr
        while ThisNode != nullptr and list[int(ThisNode)].Data < val:
            previous = ThisNode
            if val > list[int(ThisNode)].Data:
                ThisNode = list[int(ThisNode)].Pointer
        if previous == nullptr:
            list[int(current)].Pointer = start
            start = current
        else:
            #adjust pointers for insert node
            list[int(current)].Pointer = list[int(previous)].Pointer
            list[int(previous)].Pointer = current
    else:
        print ("No Space")

def Delete(val):
    global start
    Temp2Start = start
    tempprev = start
    found = False
    if start == nullptr:
        print ("list empty")
    else:
        while Temp2Start != nullptr and not found:
            if list[int(Temp2Start)].Data == val:
                found = True
                break
            tempprev = Temp2Start
            Temp2Start = list[int(Temp2Start)].Pointer
        if found:
            if Temp2Start == tempprev:
                start = list[int(Temp2Start)].Pointer
            list[int(Temp2Start)].Data = ""
            list[int(tempprev)].Pointer = list[int(Temp2Start)].Pointer
            list[int(Temp2Start)].Pointer = ""

def Output():
    print ("Next Free Location : " + str(Fptr))
    print ("start +  : " + str(start))
    print ("")
    TempStart = start
    if TempStart == nullptr:
        print ("list empty")
    else:
        while TempStart != nullptr:
            try:
                print(list[int(TempStart)].Data, "    ", list[int(TempStart)].Pointer)
                TempStart = list[int(TempStart)].Pointer
            except:
                pass
             

def rec_Output(TempStart):
    if TempStart == nullptr:
        return TempStart
    else:
        print (list[int(TempStart)].Data, " ", list[int(TempStart)].Pointer)
        return rec_Output(list[int(TempStart)].Pointer)
    
def Search():
    Pointer = start
    found = -1
    FlowerName = input("Enter name: ")
    index = 0
    while Pointer != -1 and found == -1:
        if list[int(Pointer)].Data == FlowerName:
            found  = Pointer
            Pointer = 0
        else:
            Pointer = list[int(Pointer)].Pointer
    if Pointer == 0:
        print (FlowerName + " Found at index location: ", found)
    else:
        print (FlowerName + " Not found")
    
CreateList()

Add("C")
Add("B")
Add("D")
Add("A")
Add("E")
Add("F")
Add("A")

print ("")
for i in range(len(list)):
    print (i, " ", list[i].Data, " ",list[i].Pointer)
print ("")
Output()

Delete("E")
print ("")
print ("")
rec_Output(start)
print ("")
Search()