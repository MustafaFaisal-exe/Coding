#Q. Intersection of Union is an algorithm used to calculate the ratio of overlap between any 
# two intersecting rectangles. Given the coordinates of the upper left and lower right corners of 
# 2 rectangles in the x-y plane, A and B in the form (x1,y1,x2,y2)
# write an algorithm in Python to calculate the Intersection of Union between two rectangles and 
# throw an error if it is equal to 0. 
import numpy as np
x1a = int(input("x1a: "))
x2a= int(input("x2a: "))
x1b = int(input("x1b: "))
x2b = int(input("x2b: "))
y1a = int(input("y1a: "))
y2a = int(input("y2a: "))
y1b = int(input("y1b: "))
y2b = int(input("y2b: "))
def intersect():
    if y1b < y2a:
        return "ERROR"
    else:
        temp_x = x2a
        temp_y = y1b
        length = (x1b - temp_x)
        width = (temp_y - y2a)
        return np.abs(length * width)


def union():
    area_inter = intersect()
    if area_inter == "ERROR":
        return "ERROR"
    else:
        temp_x = x2a
        temp_y = y1a
        area_A = np.abs((x1a - temp_x))*np.abs((temp_y - y2a))
        temp_area = area_A - area_inter
        temp_x = x2b
        temp_y = y2b
        area_B = np.abs((x1b - temp_x))*np.abs((temp_y - y1b))
        return temp_area + area_B
    
if intersect() != "ERROR":
    IOU = intersect()/union()
    print (IOU)
else:
    print (intersect())