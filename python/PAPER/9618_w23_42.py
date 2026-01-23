#Declare StackVowel : Array[0:99] as char
StackVowel = ["" for i in range(100)]

#Declare StackConsonant : Array[0:99] as char
StackConsonant = ["" for i in range(100)]

#Declare VowelTop : integer
VowelTop = 0

#Declare ConsonantTop : integer
ConsonantTop = 0


def PushData(letter):
    global VowelTop, ConsonantTop
    if letter == "a" or letter == "e" or letter == "i" or letter == "o" or letter == "u":
        if VowelTop != 100:
            StackVowel[VowelTop] = letter
            VowelTop += 1
        else:
            print ("Stack Full")
    else:
        if ConsonantTop != 100:
            StackConsonant[ConsonantTop] = letter
            ConsonantTop += 1
        else:
            print ("Stack Full")


def ReadData():
    try:
        file = open("StackData.txt", "r")
    except IOError:
        print ("File not found")
    for index in range(100):
        temp = file.readline().strip()
        PushData(temp)
    file.close()

def PopVowel():
    global VowelTop
    if VowelTop == 0:
        return "No Data"
    else:
        removed = StackVowel[VowelTop - 1]
        StackVowel[VowelTop - 1] = ""
        VowelTop -= 1
        return removed

def PopConsonant():
    global ConsonantTop
    if ConsonantTop == 0:
        return "No Data"
    else:
        removed = StackConsonant[ConsonantTop - 1]
        StackConsonant[ConsonantTop - 1] = ""
        ConsonantTop -= 1
        return removed

ReadData()

instring = ""
for i in range(5):
    choice = input("vowel or consonant: ")
    while choice != "vowel" and choice != "consonant":
        choice = input("Invalid! Enter either Vowel or Consonant: ")
    if choice == "vowel":
        status = PopVowel()
        if status == "No Data":
            print ("Vowel Stack Empty")
        else:
            instring += status
    else:
        status = PopConsonant()
        if status == "No Data":
            print ("Consonant Stack Empty")
        else:
            instring += status
print (instring)

def IterativeCalculate(number):
    ToFind = number
    Total = 0
    while number != 0:
        if ToFind % number == 0:
            Total += number
        number -= 1
    return Total

print (IterativeCalculate(50))


def RecursiveValue(number, ToFind):
    if number == 0:
        return 0
    else:
        if ToFind % number == 0:
            return number + RecursiveValue(number - 1, ToFind)
        else:
            return RecursiveValue(number - 1, ToFind)

print (RecursiveValue(50, 50))


import datetime

class Character:
    #Declare CharacterName : string
    #Declare DateOfBirth : date
    #Declare Intelligence : real
    #Declare Speed : integer
    def __init__(self, char_name, DOB, intel, SpeedP):
        self.__CharacterName = char_name
        self.__DateOfBirth = DOB
        self.__Intelligence = intel
        self.__Speed = SpeedP
    
    def GetIntelligence(self):
        return self.__Intelligence
    
    def GetName(self):
        return self.__CharacterName
    
    def SetIntelligence(self, intel_update):
        self.__Intelligence += intel_update

    def Learn(self):
        self.__Intelligence *= 1.1

    def ReturnAge(self):
        return 2023 - self.__DateOfBirth.year

    
FirstCharacter = Character("Royal",datetime.datetime(2019, 1, 1), 70, 30)

FirstCharacter.Learn()

print ("Name: ", FirstCharacter.GetName())
print ("Intelligence: ", FirstCharacter.GetIntelligence())
print ("Age: ", FirstCharacter.ReturnAge())


class MagicCharacter(Character):
    #Declare Element : string
    def __init__(self,char_name, DOB, intel, SpeedP, elementP):
        Character.__init__(self, char_name, DOB, intel, SpeedP)
        self.__Element = elementP
    
    def Learn(self):
        if self.__Element == "fire" or self.__Element == "water":
            Character.SetIntelligence(self, Character.GetIntelligence(self)*1.2)
        elif self.__Element == "earth":
            Character.SetIntelligence(self, Character.GetIntelligence(self)*1.3)
        else:
            Character.SetIntelligence(self, Character.GetIntelligence(self)*1.1)

FirstMagic = MagicCharacter("Light", datetime.datetime(2018, 3, 3), 75, 22, "fire")
FirstMagic.Learn()

print ("Name: ", FirstMagic.GetName())
print ("Intelligence: ", FirstMagic.GetIntelligence())
print ("Age: ", FirstMagic.ReturnAge())


#Marks = 71/75