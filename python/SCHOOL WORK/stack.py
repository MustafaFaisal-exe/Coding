#const null
null = -1

def initialise():
    stack = [0,0,0,0,0,0,0,0,0,0]
    for index in range(10):
        stack[index] = null
    stackpointer = null
    return stack, stackpointer

def push(stack, stackpointer):
    if stackpointer >= 9:
        print ("Stack Full")
    else:
        value = int(input("Enter the vaue you want to push: "))
        stackpointer += 1
        stack[stackpointer] = value
    return stack, stackpointer
        
def pop(stack, stackpointer):
    if stackpointer >= 0:
        pop_val = stack[stackpointer]
        stack[stackpointer] = -1
        stackpointer -= 1
        return pop_val, stackpointer
    
def output(stack):
    return stack

def menu():
    valid = True
    stack, stackpointer = initialise()
    while valid:
        choice = int(input("1.Push     2.Pop      3.Output      4.Exit: "))
        if choice == 1:
            stack, stackpointer = push(stack, stackpointer)
        elif choice == 2:
            try:
                pop_val, stackpointer = pop(stack, stackpointer)
                print (pop_val)
            except TypeError:
                print ("Nothing left to pop")
        elif choice == 3:
            print (output(stack))
        elif choice == 4:
            valid = False
            print ("BYE BYE")
        else:
            print ("invalid input")
            
menu()