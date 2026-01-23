circular_queue = [ ]
start_pointer = 0
end_pointer = 0
def initialise():
    for x in range(4):
        circular_queue.append(-1)
    return circular_queue

def add(value, end_pointer):
    if start_pointer != 0 and end_pointer == len(circular_queue):
        end_pointer = 0
    circular_queue[end_pointer] = value
    end_pointer += 1
    return circular_queue, end_pointer

def remove(start_pointer):
    if start_pointer == len(circular_queue):
        start_pointer = 0
    circular_queue[start_pointer] = -1
    start_pointer += 1
    return circular_queue, start_pointer

circular_queue = initialise()
operation = int(input("1. ADD, 2. REMOVE, 3. OUTPUT, 4. EXIT: "))
while operation != 4:
    if operation == 1:
        if (start_pointer == 0 and end_pointer == len(circular_queue)) or (end_pointer == start_pointer and start_pointer != 0):
            print ("No space left to add")
        else:
            value = int(input("Enter the value you want to add: "))
            circular_queue, end_pointer = add(value, end_pointer)
    elif operation == 2:
        if end_pointer == start_pointer and start_pointer == 0:
            print ("nothing left to remove")
        else:
            circular_queue, start_pointer = remove(start_pointer)
    elif operation == 3:
        print (circular_queue)
    operation = int(input("1. ADD, 2. REMOVE, 3. OUTPUT, 4. EXIT: "))
    null_counter = 0
    for index in range(len(circular_queue)):
        if circular_queue[index] == -1:
            null_counter += 1
    if null_counter == 4:
        start_pointer = 0
        end_pointer = 0

print ("FINISHED!")