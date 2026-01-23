#swap without using a third variable
a = "mustafa"
b = "mujtaba"


a = a + b
b = "" + a[:len(a) - len(b)]
a = a[len(b):]


print (a)
print (b)


a = 10
b = 20


a=a+b
b=a-b
a=a-b


print (a)
print (b)