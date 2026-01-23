stack1 = [-1 for i in range(10)]
stack2 = [-1 for j in range(10)]

start_pointer1 = 0
end_pointer1 = -1
start_pointer2 = 0
end_pointer2 = -1

def add(value):
    global end_pointer1
    stack1[end_pointer1 + 1] = value
    end_pointer1 += 1

def remove():
    global end_pointer2, end_pointer1, start_pointer1
    while start_pointer1 != end_pointer1:
        stack2[end_pointer2 + 1] = stack1[end_pointer1 + 1]
        end_pointer1 -= 1
        end_pointer2 += 1
    stack1[end_pointer1 + 1] = -1
    start_pointer1 += 1
    for index in range(end_pointer2 + 1, start_pointer2, -1):
        add(stack2[index])

def Output():
    global end_pointer2, end_pointer1, start_pointer1
    while start_pointer1 != end_pointer1:
        stack2[end_pointer2 + 1] = stack1[end_pointer1 + 1]
        end_pointer1 -= 1
        end_pointer2 += 1
    for i in range(end_pointer2 + 1, start_pointer2, -1):
        print (stack2[i])
    

choice = int(input("1. ADD  2. REMOVE  3. OUTPUT  4. EXIT: "))
while choice != 4:
    if choice == 1:
        value = int(input("Enter the value u want to add: "))
        add(value)
    elif choice == 2:
        remove()
    elif choice == 3:
        Output()
    choice = int(input("1. ADD  2. REMOVE  3. OUTPUT  4. EXIT: "))
