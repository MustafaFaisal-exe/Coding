class Node:
    def __init__(self, leftP, rightP, datap) -> None:
        self.LeftPointer = leftP
        self.RightPointer = rightP
        self.Data = datap

tree = ["" for i in range(6)]
NullPointer = -1
FreePointer = 0
root = NullPointer

def CreateTree():    
    data = 0
    for i in range(6):
        leftP = i + 1
        rightP = NullPointer
        tree[i] = Node(leftP, rightP, data)
    tree[5] = Node(NullPointer, rightP, data)
    
def Add(val):
    global root, FreePointer
    if FreePointer != NullPointer:
        #space available
        current = FreePointer
        tree[current].Data = val
        FreePointer = tree[current].LeftPointer
        tree[current].LeftPointer = NullPointer
        tree[current].RightPointer = NullPointer
        if root == NullPointer:
            root = current
        else:
            ThisNodePointer = root
            while ThisNodePointer != NullPointer:
                PreviousNode = ThisNodePointer
                if tree[ThisNodePointer].Data > val:
                    ThisNodePointer = tree[ThisNodePointer].LeftPointer
                    turnleft = True
                else:
                    ThisNodePointer = tree[ThisNodePointer].RightPointer
                    turnleft = False
            if turnleft:
                tree[PreviousNode].LeftPointer = current
            else:
                tree[PreviousNode].RightPointer = current
    else:   
        print ("Tree full")

def Search(val):
    found = False
    if root == -1:
        print ("root empty")
    else:
        ThisNode = root
        while ThisNode != -1 and found == False:
            if tree[ThisNode].Data == val:
                found = True
            elif tree[ThisNode].Data > val:
                ThisNode = tree[ThisNode].LeftPointer
            else:
                ThisNode = tree[ThisNode].RightPointer
    return found

def PreOrder(temproot):
    print (tree[temproot].Data)

    if tree[temproot].LeftPointer != NullPointer:
        PreOrder(tree[temproot].LeftPointer)
    if tree[temproot].RightPointer != NullPointer:
        PreOrder(tree[temproot].RightPointer)

def PostOrder(temproot):
    if tree[temproot].LeftPointer != NullPointer:
        PostOrder(tree[temproot].LeftPointer)
    if tree[temproot].RightPointer != NullPointer:
        PostOrder(tree[temproot].RightPointer)
    
    print (tree[temproot].Data)

def InOrder(temproot):
    if temproot != -1:
        if tree[temproot].LeftPointer != -1:
            InOrder(tree[temproot].LeftPointer)
        print (tree[temproot].Data)
        if tree[temproot].RightPointer != -1:
            InOrder(tree[temproot].RightPointer)
    
    


CreateTree()
Add("B")
Add("A")
Add("C")
Add("D")
Add("E")
Add("F")
Add("G")
for i in range(len(tree)):
    print (i, " ", tree[i].LeftPointer, " ", tree[i].Data, " ", tree[i].RightPointer)
print ("__________________PRE ORDER_________________")
PreOrder(root)
print ("__________________POST ORDER_________________")
PostOrder(root)
print ("__________________IN ORDER_________________")
InOrder(root)
if Search("F"):
    print ("found")
else:
    print ("Not found")