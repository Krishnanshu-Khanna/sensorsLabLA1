import pygame
import time
import random
import os
import csv

pygame.init()

# Screen dimensions
screen_width = 700
screen_height = 700

# Button dimensions
btn_starting_x = 250
nw_gm_y = 400
exit_y = 460
btn_width = 242
btn_height = 50

# Colors
black_color = (0, 0, 0)
white_color = (255, 255, 255)
red_color = (255, 0, 0)
green_color = (0, 255, 0)
blue_color = (0, 0, 255)

# Game display setup
game_layout_display = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('F1 Racing Dashboard')
time_clock = pygame.time.Clock()

# Load assets
car_photo = pygame.image.load(os.getcwd() + '\\images/car.png')
photo_obstacle = pygame.image.load(os.getcwd() + '\\images/obstacle.png')
image_background = pygame.image.load(os.getcwd() + '\\images/background.png')
bckgrndRect = image_background.get_rect()

# Car dimensions
(c_width, c_height) = car_photo.get_rect().size
(t_width, t_height) = photo_obstacle.get_rect().size

# CSV Handling
def preload_csv_data(file_path):
    """Load all CSV data at game start"""
    try:
        with open(file_path, 'r') as file:
            reader = csv.reader(file)
            next(reader)  # Skip header
            return list(reader)
    except Exception as e:
        print(f"CSV Error: {e}")
        return [['0', '0']]  # Fallback data

# Enhanced Dashboard Display
def display_dashboard(dodged, high_score, speed, temp):
    font = pygame.font.SysFont('Arial', 22, bold=True)
    
    # Left Panel (Game Stats)
    game_stats = [
        f"DODGED: {dodged}",
        f"HIGH SCORE: {high_score}",
        f"GAME SPEED: {speed}km/h"
    ]
    
    # Right Panel (CSV Data)
    csv_stats = [
        f"LIVE SPEED: {speed}km/h",
        f"ENGINE TEMP: {temp}°C"
    ]

    # Render and position text
    y_offset = 15
    for idx, stat in enumerate(game_stats):
        text = font.render(stat, True, green_color)
        game_layout_display.blit(text, (20, 20 + y_offset*idx))
    
    for idx, stat in enumerate(csv_stats):
        color = red_color if idx == 1 and temp > 35 else white_color
        text = font.render(stat, True, color)
        game_layout_display.blit(text, (screen_width-200, 20 + y_offset*idx))

# Main Game Loop
def main_game():
    # Initialize game state
    car_x = (screen_width * 0.4)
    car_y = (screen_height * 0.6)
    x_change = 0
    direction = 0
    
    # Obstacle setup
    obstacle_x = random.randrange(0, screen_width - t_width)
    obstacle_y = -600
    obstacle_speed = 5
    
    # CSV Integration
    csv_data = preload_csv_data('data.csv')
    current_csv_index = 0
    CSV_UPDATE_EVENT = pygame.USEREVENT + 1
    pygame.time.set_timer(CSV_UPDATE_EVENT, 1000)  # Update every 1 second
    
    dodged = 0
    running = True

    while running:
        # Event handling
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == CSV_UPDATE_EVENT:
                current_csv_index = (current_csv_index + 1) % len(csv_data)
            
            # Car controls
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x_change = -8
                    direction = -1
                elif event.key == pygame.K_RIGHT:
                    x_change = 8
                    direction = 1
                    
            if event.type == pygame.KEYUP:
                if event.key in (pygame.K_LEFT, pygame.K_RIGHT):
                    x_change = 0
                    direction = 0

        # Update positions
        car_x += x_change
        obstacle_y += obstacle_speed
        
        # Boundary checking
        if car_x > screen_width - c_width or car_x < 0:
            crash()
        
        # Collision detection
        if car_y < obstacle_y + t_height:
            if (car_x > obstacle_x and car_x < obstacle_x + t_width) or \
               (car_x + c_width > obstacle_x and car_x + c_width < obstacle_x + t_width):
                crash()
        
        # Reset obstacle
        if obstacle_y > screen_height:
            obstacle_y = -t_height
            obstacle_x = random.randrange(0, screen_width - t_width)
            dodged += 1
            obstacle_speed += 0.5
        
        # Get CSV data
        try:
            csv_speed = float(csv_data[current_csv_index][0])
            csv_temp = float(csv_data[current_csv_index][1])
        except:
            csv_speed = 0.0
            csv_temp = 0.0

        # Render frame
        game_layout_display.blit(image_background, (0,0))
        display_dashboard(dodged, 0, obstacle_speed*10, csv_temp)
        game_layout_display.blit(photo_obstacle, (obstacle_x, obstacle_y))
        game_layout_display.blit(car_photo, (car_x, car_y))
        
        pygame.display.update()
        time_clock.tick(60)

    pygame.quit()

# Start the game
if __name__ == "__main__":
    main_game()
