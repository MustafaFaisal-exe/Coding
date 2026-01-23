class Node:
    # Declare data : integer
    # Declare NextNode : integer
    def __init__(self, datap, nextnodep):
        self.data = datap
        self.NextNode = nextnodep
# Declare LinkedList:Array[0:9] of node
# Declare startpointer : integer
# Declare emptylist : integer
LinkedList = []
startpointer = 0
emptylist = 5
LinkedList.append(Node(1,1))
LinkedList.append(Node(5,4))
LinkedList.append(Node(6,7))
LinkedList.append(Node(7,-1))
LinkedList.append(Node(2,2))
LinkedList.append(Node(0,6))
LinkedList.append(Node(0,8))
LinkedList.append(Node(56,3))
LinkedList.append(Node(0,9))
LinkedList.append(Node(0,-1))
def OutputNodes(LinkedList, startpointer):
    pointer = startpointer
    for i in range(len(LinkedList)):
        print(LinkedList[pointer].data)
        pointer = LinkedList[pointer].NextNode
def AddNode(LinkedList, startpointer, value):
    global emptylist
    if emptylist != -1:
        pointer = startpointer
        while LinkedList[pointer].NextNode != -1:
            pointer = LinkedList[pointer].NextNode
        LinkedList[emptylist].data = value
        LinkedList[pointer].NextNode = emptylist
        emptylist = LinkedList[emptylist].NextNode
        LinkedList[emptylist].NextNode = -1
        return True
    else:
        return False
OutputNodes(LinkedList, startpointer)
if AddNode(LinkedList, startpointer, 5):
    print ("Node added successfully")
else:
    print ("Node not added successfully")
OutputNodes(LinkedList, startpointer)

# Q2 
# Declare arrayData : Array[0:9] of integer
#arrayData = [10, 5, 6, 7, 1, 12, 13, 15, 21, 8]
#def LinearSearch(ValueToBeSearched):
#    index = 0
#    while index < len(arrayData):
#        if ValueToBeSearched == arrayData[index]:
#            return True
#        index += 1
#    return False
#value = int(input("Enter the value to be searched: "))
#if LinearSearch(value):
#    print("Value found")
#else:
#    print("Value not found")
#def bubblesort():
#    global arrayData
#    for x in range(len(arrayData)):
#        for y in range(len(arrayData) - 1):
#            if arrayData[y] < arrayData[y + 1]:
#                temp = arrayData[y]
#                arrayData[y] = arrayData[y + 1]
#                arrayData[y + 1] = temp

#Q3
#class TreasureChest:
#    # PRIVATE Declare question : string
#    # PRIVATE Declare answer : integer
#    # PRIVATE Declare points : integer
#    def __init__(self, questionp, answerp, pointp):
#        self.__question = questionp
#        self.__answer = answerp
#        self.__point = pointp
#    def GetQuestion(self):
#        return self.__question
#    def CheckAnswer(self, User_Ans):
#        if User_Ans == self.__answer:
#            return True
#        return False
#    def getPoints(self, trials):
#        if trials == 1:
#            return self.__point
#        elif trials == 2:
#            return self.__point // 2
#        elif trials == 3 or trials == 4:
#            return self.__point // 4
#        else:
#            return 0
## Declare ArrayTreasure : Array of TreasureChest
#ArrayTreasure = [ ]
#def ReadData():
#    try:
#        file = open("TreasureChestData.txt", "r")
#        questions = file.readline().strip()
#        while questions != "":
#            answers = int(file.readline().strip())
#            points = int(file.readline().strip())
#            ArrayTreasure.append(TreasureChest(questions, answers, points))
#            questions = file.readline()
#    except IOError:
#        print ("File not found")
#ReadData()
#question_num = int(input("Enter question number (1-5): "))
#print (ArrayTreasure[question_num - 1].GetQuestion())
#attempts = 1
#user_answer = int(input("Enter your answer: "))
#while not ArrayTreasure[question_num - 1].CheckAnswer(user_answer):
#    attempts += 1
#    user_answer = int(input("Incorrect answer! Enter correct answer: "))
#points_acheived = ArrayTreasure[question_num - 1].getPoints(attempts)
#print ("You got " + str(points_acheived) + " points")