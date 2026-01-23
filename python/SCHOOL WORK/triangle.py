import matplotlib.pyplot as plt
X1  = float(input("Enter X1 coordinates of the triangle: "))
Y1 = float(input("Enter Y1 coordinates of the triangle: "))
X2 = float(input("Enter X2 coordinates of the triangle: "))
Y2 = float(input("Enter Y2 coordinates of the triangle: "))
X3 = float(input("Enter X3 coordinates of the triangle: "))
Y3 = float(input("Enter Y3 coordinates of the triangle: "))

A = [X1,Y1]
B = [X2,Y2]
C = [X3,Y3]

def triangle_check():
    AB = ((A[0] - B[0])**2 + (A[1] - B[1])**2)**0.5
    BC = ((B[0] - C[0])**2 + (B[1] - C[1])**2)**0.5
    CA = ((C[0] - A[0])**2 + (C[1] - A[1])**2)**0.5
    sides = [AB, BC, CA]
    side_max = max(sides)
    total = 0
    for x in range(3):
        if sides[x] != side_max:
            total += sides[x]**2

    if AB == BC and AB == CA:
        return "TRIANGLE IS EQUILATERAL"
    elif side_max == total**0.5:
        return "TRIANGLE IS RIGHT ANGLED"
    elif AB == BC or AB == CA or BC == CA:
        return "TRIANGLE IS ISOSCELES"
    else:
        return "TRIANGLE IS SCALENE"
    
x = [X1,X2,X3]
y = [Y1,Y2,Y3]
plt.title(triangle_check())
plt.plot(x,y,"o")
plt.show()