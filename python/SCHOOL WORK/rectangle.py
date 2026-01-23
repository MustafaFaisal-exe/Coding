import matplotlib.pyplot as plt
print ("    A(X1,Y1)" + "-----------------" + "B(X2,Y2)")
print ("            |                |           ")
print ("            |                |           ")
print ("            |                |           ")
print ("    D(X3,Y3)" + "-----------------" + "C(X4,Y4)")
print ("                                               ")

X1 = float(input("Enter the coordinates of X1: "))
Y1 = float(input("Enter the coordinates of Y1: "))
X2 = float(input("Enter the coordinates of X2: "))
Y2 = float(input("Enter the coordinates of Y2: "))
X3 = float(input("Enter the coordinates of X3: "))
Y3 = float(input("Enter the coordinates of Y3: "))
X4 = float(input("Enter the coordinates of X4: "))
Y4 = float(input("Enter the coordinates of Y4: "))

X = [X1,X2,X3,X4]
Y = [Y1,Y2,Y3,Y4]

AB = ((X1 - X2)**2 + (Y1 - Y2)**2)**0.5
BC = ((X2 - X4)**2 + (Y2 - Y4)**2)**0.5
AD = ((X1 - X3)**2 + (Y1 - Y3)**2)**0.5
DC = ((X3 - X4)**2 + (Y3 - Y4)**2)**0.5

diagonalAC = (AB**2 + BC**2)**0.5
diagonalBD = (AB**2 + AD**2)**0.5
    
def rectangle_identify():
    IsRectangle = True
    if diagonalAC == diagonalBD:
        return IsRectangle
    else:
        return not IsRectangle

point_x = float(input("Enter the x coordinates of point: "))
point_y = float(input("Enter the y coordinates of point: "))
AP = ((X1 - point_x)**2 + (Y1 - point_y)**2)**0.5
BP = ((X2 - point_x)**2 + (Y2 - point_y)**2)**0.5
CP = ((X4 - point_x)**2 + (Y4 - point_y)**2)**0.5
DP = ((X3 - point_x)**2 + (Y3 - point_y)**2)**0.5


def check_point():
    if rectangle_identify():
        S1 = (AP + BP + AB) / 2
        S2 = (BP + CP + BC) / 2
        S3 = (CP + DP + DC) / 2
        S4 = (AP + DP + AD) / 2
        A1 = float(S1 * (S1 - AP) * (S1 - BP) * (S1 - AB))**0.5
        A2 = float(S2 * (S2 - BP) * (S2 - CP) * (S2 - BC))**0.5
        A3 = float(S3 * (S3 - CP) * (S3 - DP) * (S3 - DC))**0.5
        A4 = float(S4 * (S4 - AP) * (S4 - DP) * (S4 - AD))**0.5
        AR = AB * BC
        if (A1 + A2 + A3 + A4) <= AR:
            return "THE POINT IS IN THE RECTANGLE"
        else:
            return "THE POINT IS NOT IN THE RECTANGLE"
    else:
        return "NOT A RECTANGLE"
    
print (check_point())
    


X.append(point_x)
Y.append(point_y)
plt.title(check_point())
plt.plot(X,Y, 'o')
plt.show()           