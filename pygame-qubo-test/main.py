import pygame
from elements.board import Board
from elements.player import Player
from elements.food import Food

pygame.init()

CELL_SIDE = 10

TOTAL_COLS = 40
TOTAL_ROWS = 40

WIDTH = TOTAL_COLS*CELL_SIDE 
HEIGHT = TOTAL_ROWS*CELL_SIDE  

screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

board = Board(TOTAL_ROWS, TOTAL_COLS)

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    board.step()
    board.draw(screen, CELL_SIDE)
    pygame.display.flip()

    clock.tick(60)


    if(board.game_over()):
        print("[!] game over")
        running = False
    

pygame.quit()