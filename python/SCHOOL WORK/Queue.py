queue = [ ]
def initialise():
    for x in range(10):
        queue.append(-1)
    start_pointer = 0
    end_pointer = 0
    return queue, start_pointer, end_pointer

def add(value, end_pointer):
    queue[end_pointer] = value
    end_pointer += 1
    return queue, end_pointer

def remove(start_pointer):
    queue[start_pointer] = -1
    start_pointer += 1
    return queue, start_pointer

queue, start_pointer, end_pointer = initialise()
operation = int(input("1. ADD, 2. REMOVE, 3. OUTPUT, 4. EXIT: "))
while operation != 4:
    if operation == 1:
        if end_pointer == len(queue):
            print ("No space left to add")
        else:
            value = int(input("Enter the value you want to add: "))
            queue, end_pointer = add(value, end_pointer)
    elif operation == 2:
        if end_pointer == start_pointer:
            print ("nothing left to remove")
        else:
            queue, start_pointer = remove(start_pointer)
    elif operation == 3:
        print (queue)
    operation = int(input("1. ADD, 2. REMOVE, 3. OUTPUT, 4. EXIT: "))

print ("FINISHED!")