def GetStart(wordnum):
    space_count = 0
    index = -1
    pos = 0
    if wordnum == 1:
        index = 1
    else:
        while pos < len(data) and index == -1:
            if data[pos] == " ":
                space_count += 1
                if space_count == wordnum - 1:
                    index = pos + 2
            pos += 1
    return index

def GetWord(pos):
        term = False
        word = ""
        index = pos - 1
        last_char = data[len(data)-1]
        if pos != -1:
            while (data[index] != " " or data[index] == last_char) and not term:
                word += data[index]
                if index != len(data) - 1:
                    index += 1
                else:
                    term = True
        else:
            return "error"
        return word


data = str(input("Enter: "))
ignore = ["and","or","the","a","is","to", "for", "of"]
abb = ""
num = 0
pos = 0
while pos != -1:
    num += 1
    pos = GetStart(num)
    word = GetWord(pos)
    found  = False
    index = 0
    if word not in ignore and pos != -1:
        abb += word[0].upper()
print (abb)