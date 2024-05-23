import pygame
from elements.board import Board

pygame.init()
pygame.font.init()

CELL_SIDE = 10

TOTAL_COLS = 40
TOTAL_ROWS = 40

WIDTH = TOTAL_COLS*CELL_SIDE 
HEIGHT = TOTAL_ROWS*CELL_SIDE  

screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

board = Board(TOTAL_ROWS, TOTAL_COLS)

running = True

font = pygame.font.SysFont("../assets/pressstart.ttf", 20)

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    board.step()
    board.draw(screen, CELL_SIDE)
    
    score_text = font.render(f'Score: {board.score}', False, (255,255,255))
    
    screen.blit(score_text, (10, 5)) 
    pygame.display.flip()

    clock.tick(60)

    if(board.game_over()):
        print("[!] game over")
        running = False
   


pygame.quit()
