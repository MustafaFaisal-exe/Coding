import pygame 
import random

pygame.init()

screen = pygame.display.set_mode((1280, 650), pygame.RESIZABLE)

pygame.display.set_caption("Ludo Stars")

color = "white"

icon = pygame.image.load('ludo.jpeg')

pygame.display.set_icon(icon)

screen.fill(color)

pygame.draw.polygon(screen, "green", [[530, 250], [530, 400], [605, 325]])
pygame.draw.polygon(screen, "yellow", [[530, 250], [680, 250], [605, 325]])
pygame.draw.polygon(screen, "blue", [[680, 400], [680, 250], [605, 325]])
pygame.draw.polygon(screen, "red", [[530, 400], [680, 400], [605, 325]])

pygame.draw.rect(screen, "green", [370, 90, 160, 160], 20)
pygame.draw.rect(screen, "red", [370, 400, 160, 160], 20)
pygame.draw.rect(screen, "yellow", [680, 90, 160, 160], 20)
pygame.draw.rect(screen, "blue", [680, 400, 160, 160], 20)
pygame.draw.circle(screen, "green", [420, 140], 20)
pygame.draw.circle(screen, "green", [480, 140], 20)
pygame.draw.circle(screen, "green", [420, 200], 20)
pygame.draw.circle(screen, "green", [480, 200], 20)
pygame.draw.circle(screen, (0, 100, 0), [420, 135], 5)
pygame.draw.polygon(screen, (0, 100, 0), [[420, 135], [410, 150], [430, 150]])
pygame.draw.circle(screen, (0, 100, 0), [480, 135], 5)
pygame.draw.polygon(screen, (0, 100, 0), [[480, 135], [470, 150], [490, 150]])
pygame.draw.circle(screen, (0, 100, 0), [420, 195], 5)
pygame.draw.polygon(screen, (0, 100, 0), [[420, 195], [410, 210], [430, 210]])
pygame.draw.circle(screen, (0, 100, 0), [480, 195], 5)
pygame.draw.polygon(screen, (0, 100, 0), [[480, 195], [470, 210], [490, 210]])
pygame.draw.circle(screen, "red", [420, 450], 20)
pygame.draw.circle(screen, "red", [480, 450], 20)
pygame.draw.circle(screen, "red", [420, 510], 20)
pygame.draw.circle(screen, "red", [480, 510], 20)
pygame.draw.circle(screen, (139, 0, 0), [420, 445], 5)
pygame.draw.polygon(screen, (139, 0, 0), [[420, 445], [410, 460], [430, 460]])
pygame.draw.circle(screen, (139, 0, 0), [480, 445], 5)
pygame.draw.polygon(screen, (139, 0, 0), [[480, 445], [470, 460], [490, 460]])
pygame.draw.circle(screen, (139, 0, 0), [420, 505], 5)
pygame.draw.polygon(screen, (139, 0, 0), [[420, 505], [410, 520], [430, 520]])
pygame.draw.circle(screen, (139, 0, 0), [480, 505], 5)
pygame.draw.polygon(screen, (139, 0, 0), [[480, 505], [470, 520], [490, 520]])
pygame.draw.circle(screen, "yellow", [730, 140], 20)
pygame.draw.circle(screen, "yellow", [790, 140], 20)
pygame.draw.circle(screen, "yellow", [730, 200], 20)
pygame.draw.circle(screen, "yellow", [790, 200], 20)
pygame.draw.circle(screen, (139, 128, 0), [730, 135], 5)
pygame.draw.polygon(screen, (139, 128, 0), [[730, 135], [720, 150], [740, 150]])
pygame.draw.circle(screen, (139, 128, 0), [790, 135], 5)
pygame.draw.polygon(screen, (139, 128, 0), [[790, 135], [780, 150], [800, 150]])
pygame.draw.circle(screen, (139, 128, 0), [730, 195], 5)
pygame.draw.polygon(screen, (139, 128, 0), [[730, 195], [720, 210], [740, 210]])
pygame.draw.circle(screen, (139, 128, 0), [790, 195], 5)
pygame.draw.polygon(screen, (139, 128, 0), [[790, 195], [780, 210], [800, 210]])
pygame.draw.circle(screen, "blue", [730, 450], 20)
pygame.draw.circle(screen, "blue", [790, 450], 20)
pygame.draw.circle(screen, "blue", [730, 510], 20)
pygame.draw.circle(screen, "blue", [790, 510], 20)
pygame.draw.circle(screen, (0, 0, 139), [730, 445], 5)
pygame.draw.polygon(screen, (0, 0, 139), [[730, 445], [720, 460], [740, 460]])
pygame.draw.circle(screen, (0, 0, 139), [790, 445], 5)
pygame.draw.polygon(screen, (0, 0, 139), [[790, 445], [780, 460], [800, 460]])
pygame.draw.circle(screen, (0, 0, 139), [730, 505], 5)
pygame.draw.polygon(screen, (0, 0, 139), [[730, 505], [720, 520], [740, 520]])
pygame.draw.circle(screen, (0, 0, 139), [790, 505], 5)
pygame.draw.polygon(screen, (0, 0, 139), [[790, 505], [780, 520], [800, 520]])

pygame.draw.rect(screen, "black", [530, 90, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530 + 50, 90, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 90, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 90 + 160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "yellow", [530 + 50, 90 + 160/6, 50, 160/6])
pygame.draw.rect(screen, "yellow", [530 + (2*50) - 1, 90 + 160/6, 50, 160/6])
pygame.draw.rect(screen, "grey", [530, 90 + 2*160/6 - 1, 50, 160/6])
pygame.draw.rect(screen, "yellow", [530 + 50, 90 + 2*160/6 - 1, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 90 + 2*160/6 - 1, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 90 + 3*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "yellow", [530 + 50, 90 + 3*160/6, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 90 + 3*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 90 + 4*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "yellow", [530 + 50, 90 + 4*160/6, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 90 + 4*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 90 + 5*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "yellow", [530 + 50, 90 + 5*160/6, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 90 + 5*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 400, 50, 160/6], 2)
pygame.draw.rect(screen, "red", [530 + 50, 400, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 400, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 400 + 160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "red", [530 + 50, 400 + 160/6, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 400 + 160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 400 + 2*160/6 - 1, 50, 160/6], 2)
pygame.draw.rect(screen, "red", [530 + 50, 400 + 2*160/6 - 1, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 400 + 2*160/6 - 1, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 400 + 3*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "red", [530 + 50, 400 + 3*160/6, 50, 160/6])
pygame.draw.rect(screen, "grey", [530 + (2*50) - 1, 400 + 3*160/6, 50, 160/6])
pygame.draw.rect(screen, "red", [530, 400 + 4*160/6, 50, 160/6])
pygame.draw.rect(screen, "red", [530 + 50, 400 + 4*160/6, 50, 160/6])
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 400 + 4*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530, 400 + 5*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530 + 50, 400 + 5*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [530 + (2*50) - 1, 400 + 5*160/6, 50, 160/6], 2)
pygame.draw.rect(screen, "black", [370, 250, 160/6, 50], 2)
pygame.draw.rect(screen, "green", [370+160/6, 250, 160/6, 50])
pygame.draw.rect(screen, "black", [370+(2*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370+(3*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370+(4*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370+(5*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370, 300, 160/6, 50], 2)
pygame.draw.rect(screen, "green", [370+160/6, 300, 160/6, 50])
pygame.draw.rect(screen, "green", [370+(2*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "green", [370+(3*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "green", [370+(4*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "green", [370+(5*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "black", [370, 350, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370+160/6, 350, 160/6, 50], 2)
pygame.draw.rect(screen, "grey", [370+(2*160/6), 350, 160/6, 50])
pygame.draw.rect(screen, "black", [370+(3*160/6), 350, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370+(4*160/6), 350, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [370+(5*160/6), 350, 160/6, 50], 2)

pygame.draw.rect(screen, "black", [680, 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680+160/6, 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680+(2*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "grey", [680+(3*160/6), 250, 160/6, 50])
pygame.draw.rect(screen, "black", [680+(4*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680+(5*160/6), 250, 160/6, 50], 2)
pygame.draw.rect(screen, "blue", [680, 300, 160/6, 50])
pygame.draw.rect(screen, "blue", [680+160/6, 300, 160/6, 50])
pygame.draw.rect(screen, "blue", [680+(2*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "blue", [680+(3*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "blue", [680+(4*160/6), 300, 160/6, 50])
pygame.draw.rect(screen, "black", [680+(5*160/6), 300, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680, 350, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680+160/6, 350, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680+(2*160/6), 350, 160/6, 50], 2)
pygame.draw.rect(screen, "black", [680+(3*160/6), 350, 160/6, 50], 2)
pygame.draw.rect(screen, "blue", [680+(4*160/6), 350, 160/6, 50])
pygame.draw.rect(screen, "black", [680+(5*160/6), 350, 160/6, 50], 2)

dice_green = pygame.draw.rect(screen, "black", [370, 30, 50, 50], 2)
dice_yellow = pygame.draw.rect(screen, "black", [790, 30, 50, 50], 2)
dice_red = pygame.draw.rect(screen, "black", [370, 570, 50, 50], 2)
dice_blue = pygame.draw.rect(screen, "black", [790, 570, 50, 50], 2)

pygame.display.flip()

roll_dice = pygame.USEREVENT + 2

turns = [[1, 385, 45], [0, 805, 45], [0, 385, 585], [0, 805, 585]]

running = True
dice_rolled = False
while running:
    for event in pygame.event.get():
        if event.type == roll_dice:
            if not dice_rolled:
                number = random.randint(0, 7)
                dice_rolled = True
            font = pygame.font.Font('freesansbold.ttf', 32)
            text = font.render(str(number), True, "black", "white")
            for i in range(len(turns)):
                if turns[i][0] == 1:
                    break
            screen.blit(text, (turns[i][1], turns[i][2]))
            turns[i][0] = 0
            turns[4 % (i+1)][0] = 1
        if event.type == pygame.QUIT:
            running = False
    if dice_green.collidepoint(pygame.mouse.get_pos()): 
        pygame.event.post(pygame.event.Event(roll_dice))
    if dice_yellow.collidepoint(pygame.mouse.get_pos()): 
        pygame.event.post(pygame.event.Event(roll_dice))
    if dice_red.collidepoint(pygame.mouse.get_pos()): 
        pygame.event.post(pygame.event.Event(roll_dice))
    if dice_blue.collidepoint(pygame.mouse.get_pos()): 
        pygame.event.post(pygame.event.Event(roll_dice))
    
    pygame.display.update()


pygame.display.update()