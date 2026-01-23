key_word = ["" for i in range(10)]
meaning = ["" for i in range(10)]
temploc = 0

def Hash(keyp):
    return ord(keyp[0]) % 10

def add(key, word):
    global temploc
    loc = Hash(key)
    array_full = False
    while key_word[loc] != "" and not array_full:
        loc += 1
        if loc > len(key_word) - 1:
            if key_word[temploc] == "":
                loc = 0
                temploc += 1
            else:
                print ("Array Full")
                array_full = True
                loc = 9
    if not array_full:
        key_word[loc] = key
        meaning[loc] = word

add("Computer", "A machine that processes data")
add("Cars","used for transport")
print (key_word)
print (meaning)  