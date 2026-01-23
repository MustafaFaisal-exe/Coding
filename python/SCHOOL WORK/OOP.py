class TreasureChest:
    def __init__(self, question, answer, points):
        self.question = question
        self.answer = answer
        self.points = int(points)  # Convert points to an integer

# Initialize an empty list to store instances of TreasureChest
treasure_chests = []

# Read data from the file and create class instances
file = open("TreasureChestData.txt", "r")
question = file.readline().strip()
while question != "":
    answer = file.readline().strip()
    points = file.readline().strip()
    chest = TreasureChest(question, answer, points)
    treasure_chests.append(chest)
    question = file.readline().strip()
file.close()

# Now, treasure_chests is a list of TreasureChest objects
# You can access each object by its index in the list
for chest in treasure_chests:
    print("Question:", chest.question)
    print("Answer:", chest.answer)
    print("Points:", chest.points)
    print()