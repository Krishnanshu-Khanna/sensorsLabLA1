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
greenLight_color = (0, 255, 127)
redLight_color = (255, 99, 71)

# Game display setup
game_layout_display = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('F1 Racing Dashboard')
time_clock = pygame.time.Clock()

# Load assets
car_photo = pygame.image.load(os.getcwd() + '\\images\\car.png')
photo_obstacle = pygame.image.load(os.getcwd() + '\\images\\obstacle.png')
image_background = pygame.image.load(os.getcwd() + '\\images\\background.png')
bckgrndRect = image_background.get_rect()

welcome_1 = pygame.mixer.Sound(os.getcwd() + '\\audio\\intro1.wav')
welcome_2 = pygame.mixer.Sound(os.getcwd() + '\\audio\\intro2.wav')
audio_crash = pygame.mixer.Sound(os.getcwd() + '\\audio\\car_crash.wav')
audio_ignition = pygame.mixer.Sound(os.getcwd() + '\\audio\\ignition.wav')

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

def crash_function():
    pygame.mixer.music.stop()
    pygame.mixer.Sound.play(audio_crash)
    message_display_screen("YOU CRASHED", 0, 0, red_color, 0)
    while True:
        playAgain = button("Play Again", btn_starting_x, nw_gm_y, btn_width, btn_height, green_color, green_color)
        exit_game = button("Quit", btn_starting_x, exit_y, btn_width, btn_height, red_color, red_color)
        for event in pygame.event.get():
            if event.type == pygame.QUIT or exit_game == 1 or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                pygame.quit()
                quit()
            if playAgain == 1 or (event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE):
                main_game()
        pygame.display.update()
        time_clock.tick(15)

def button(messages, x, y, wid, hei, in_act_color, act_color):
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()
    if x + wid > mouse[0] > x and y + hei > mouse[1] > y:
        pygame.draw.rect(game_layout_display, act_color, (x, y, wid, hei))
        if click[0] == 1:
            return 1
    else:
        pygame.draw.rect(game_layout_display, in_act_color, (x, y, wid, hei))

    small_txt = pygame.font.Font('freesansbold.ttf', 20)
    TxtSurf, TxtRect = text_objects(messages, small_txt, white_color)
    TxtRect.center = (x + wid / 2, y + hei / 2)
    game_layout_display.blit(TxtSurf, TxtRect)

def text_objects(text, font, color):
    txtSurf = font.render(text, True, color)
    return txtSurf, txtSurf.get_rect()

def message_display_screen(txt, sh_x, sh_y, color, time_sleeping):
    lar_txt = pygame.font.Font('freesansbold.ttf', 50)
    txtSurf, TxtRect = text_objects(txt, lar_txt, color)
    TxtRect.center = (screen_width / 2 - sh_x, screen_height / 2 - sh_y)
    game_layout_display.blit(txtSurf, TxtRect)
    pygame.display.update()
    time.sleep(time_sleeping)

def title_message_display(sh_x, sh_y, color):
    lar_txt = pygame.font.Font('freesansbold.ttf',60)
    txtSurf, TxtRect = text_objects("F1 Racing Game", lar_txt, color)
    TxtRect.center = ((screen_width / 2 - sh_x), (screen_height / 3 - sh_y))
    game_layout_display.blit(txtSurf, TxtRect)
    time.sleep(0.15)
    pygame.display.update()

def title_msg():
    animation_height=screen_height
    pygame.mixer.Sound.play(welcome_1)
    while animation_height > -600:
        game_layout_display.fill(white_color)
        things(screen_width / 2 - t_width / 2, animation_height)
        animation_height-=1.5
        pygame.display.update()
    title_message_display(0, 0, black_color)
    time.sleep(0.1)
    pygame.mixer.Sound.play(welcome_2)

def things(x, y):
    game_layout_display.blit(car_photo, (x, y))

# Enhanced Dashboard Display
def display_dashboard(dodged, high_score, speed, temp, pressure, humidity, brake_temp, fuel_level):
    font = pygame.font.SysFont('Arial', 22, bold=True)
    
    # Left Panel (Game Stats)
    game_stats = [
        f"DODGED: {dodged}",
        f"HIGH SCORE: {high_score}",
        f"GAME SPEED: {speed}km/h"
    ]
    
    # Right Panel (Sensor Data)
    sensor_stats = [
        f"ENGINE TEMP: {temp}°C",
        f"PRESSURE: {pressure} PSI",
        f"HUMIDITY: {humidity}%",
        f"BRAKE TEMP: {brake_temp}°C",
        f"FUEL LEVEL: {fuel_level}%"
    ]

    # Define spacing
    gap = 30  # Increase the gap between stats for better readability

    # Render and position text for game stats
    for idx, stat in enumerate(game_stats):
        text = font.render(stat, True, green_color)
        game_layout_display.blit(text, (20, 20 + (gap * idx)))

    # Render and position text for sensor stats
    for idx, stat in enumerate(sensor_stats):
        color = red_color if idx == 1 and temp > 35 else white_color
        text = font.render(stat, True, color)
        game_layout_display.blit(text, (screen_width - 300, 20 + (gap * idx)))

def welcome_gameplay():
    welcome = True
    game_layout_display.fill(white_color)
    title_msg()
    exit_game=0
    while welcome:
        for event in pygame.event.get():
            if event.type == pygame.QUIT or exit_game == 1 or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                pygame.quit()
                quit()
        playGame = button("New game", btn_starting_x, nw_gm_y, btn_width, btn_height, greenLight_color, green_color)
        exit_game = button("Quit", btn_starting_x, exit_y, btn_width, btn_height, redLight_color, red_color)
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                exit_game = 1
        if playGame or (event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE):
            welcome = False
            main_game()

        pygame.display.update()
        time_clock.tick(15)


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
    pygame.mixer.music.load(os.getcwd() + '\\audio\\running.wav')
    pygame.mixer.music.play(-1)  # Play music indefinitely
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
            crash_function()
        
        # Collision detection
        if car_y < obstacle_y + t_height:
            if (car_x > obstacle_x and car_x < obstacle_x + t_width) or \
               (car_x + c_width > obstacle_x and car_x + c_width < obstacle_x + t_width):
                crash_function()
        
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
            csv_pressure = float(csv_data[current_csv_index][2])
            csv_humidity = float(csv_data[current_csv_index][3])
            csv_brake_temp = float(csv_data[current_csv_index][4])
            csv_fuel_level = float(csv_data[current_csv_index][5])
        except:
            csv_speed = 0.0
            csv_temp = 0.0
            csv_pressure = 0.0
            csv_humidity = 0.0
            csv_brake_temp = 0.0
            csv_fuel_level = 0.0

        # Render frame
        game_layout_display.blit(image_background, (0, 0))
        display_dashboard(dodged, 0, obstacle_speed*10, csv_temp, csv_pressure, csv_humidity, csv_brake_temp, csv_fuel_level)
        game_layout_display.blit(photo_obstacle, (obstacle_x, obstacle_y))
        game_layout_display.blit(car_photo, (car_x, car_y))
        
        pygame.display.update()
        time_clock.tick(60)

    pygame.quit()

# Start the game
if __name__ == "__main__":
    welcome_gameplay()  # Start with the welcome screen
