word = str(input("Enter: "))
def check():
    comp_word = ""
    for n in range(len(word) - 1, - 1 , - 1):
        comp_word += word[n]
    if comp_word == word:
        return "The word is palindrome"
    else:
        return "The word is not a palindrome"

print (check())