import random
#
# # Declare StackData:Array[0:9] of integer
#
# StackData = [-1 for i in range(10)]
#
# # Declare StackPointer : integer
#
# StackPointer = 0
#
#
# def Output():
#     for index in range(10):
#         print(StackData[index])
#     print ("")
#     print ("Stack Pointer", StackPointer)
#
#
# def Push(val):
#     global StackPointer
#     if StackPointer > 9:
#         return False
#     else:
#         StackData[StackPointer] = val
#         StackPointer += 1
#         return True
#
#
# for i in range(11):
#     value = int(input("Enter a number you want to add in stack: "))
#     status = Push(value)
#     if status:
#         print ("Value pushed successfully")
#     else:
#         print ("Value not pushed successfully")
#
# Output()
#
# def Pop():
#     global StackPointer
#     if StackPointer == 0:
#         return -1
#     else:
#         StackPointer -= 1
#         temp = StackData[StackPointer]
#         StackData[StackPointer] = -1
#         return temp
#
# print ("___________")
# print(Pop())
# print(Pop())
# print ("___________")
#
# Output()




# Q2

#Declare ArrayData:Array[0:9, 0:9] of integer
# ArrayData = [[-1 for j in range(10)] for i in range(10)]
# for rows in range(10):
#     for colums in range(10):
#         ArrayData[rows][colums] = random.randint(1,100)
# def output():
#   for i in range(10):
#     for j in range(10):
#       print(ArrayData[i][j],end=" ")
#     print ("\n")
# output()
#
# ArrayLength = 10
# for x in range(ArrayLength):
#   for y in range(ArrayLength - 1):
#     for z in range (ArrayLength - y - 1):
#       if ArrayData[x][z] > ArrayData[x][z + 1]:
#         Tempvalue = ArrayData[x][z]
#         ArrayData[x][z] = ArrayData[x][z + 1]
#         ArrayData[x][z + 1] = Tempvalue
# print ("")
# print ("")
# print ("")
# print ("")
# print ("")
# output()
# def binarysearch(SearchArray,Lower,Upper,SearchValue):
#   if Upper >= Lower:
#     mid = (Lower + Upper - 1) // 2
#     if SearchArray[0][mid] == SearchValue:
#       return mid
#     else:
#       if SearchArray[0][mid] > SearchValue:
#         return binarysearch(SearchArray,Lower, mid - 1, SearchValue)
#       else:
#         return binarysearch(SearchArray, mid + 1, Upper, SearchValue)
#   return -1
# x = int(input("Input number to be searched: "))
# print(binarysearch(ArrayData,0,10, x))
#
# Q3
class Card:
  def __init__(self, num, colorp):
    self.__number = num
    self.__color = colorp
  def GetNumber(self):
    return self.__number
  def GetColor(self):
    return self.__color
# Declare ArrayCard:Array[0:30] OF card
ArrayCard = [ ]
try:
  file = open('CardValues.txt', 'r')
  for i in range(30):
    line_number = file.readline().strip()
    line_color = file.readline().strip()
    ArrayCard.append(Card(line_number, line_color))
  file.close()
except IOError:
  print ("File not found")
selected = []
def ChooseCard():
  location = int(input("Choose index number: "))
  while location < 1 or location > 30:
    location = int(input("Enter valid index!(1-30): "))
  IsSelected = False
  index = 0
  while not IsSelected and index < len(selected):
    if selected[index] == location:
      IsSelected = True
    index += 1
  if IsSelected:
    return ChooseCard()
  else:
    selected.append(location)
    return location
# Declare Player1:Array[0:3] of Card
Player1 = []
for i in range(4):
  loc = ChooseCard()
  Player1.append(Card(ArrayCard[loc - 1].GetNumber(), ArrayCard[loc - 1].GetColor()))
  print (Player1[i].GetNumber(), Player1[i].GetColor())