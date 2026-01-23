alphabet = []
for i in range(25):
    alphabet.append(0)
data = str(input("Enter:  "))
for index in range(len(data)):
    if data[index] != " ":
        alphabet[ord(data[index].lower()) - 97] += 1
for n in range(25):
    if alphabet[n] != 0:
        print (chr(n + 97), " ",alphabet[n])