class Employee:
    def __init__(self, namep, phonep, agep):
        self.name = namep
        self.phone = phonep
        self.age = agep


employee1 = Employee("Mustafa","03221173435", 19)

print (employee1.name)
print (employee1.phone)
print (employee1.age)