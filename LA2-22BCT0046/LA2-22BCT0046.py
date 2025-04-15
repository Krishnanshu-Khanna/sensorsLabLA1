import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import numpy as np

# Define the size of the grid
GRID_SIZE = 10

# File containing sensor data
SENSOR_FILE = "data/LA2-22BCT0046.csv"

# Dictionary to store previous positions of animals to create movement trails
animal_trails = {}

# Set the plot style to a dark background
plt.style.use("dark_background")


def read_next_step(file):
    """
    Reads the next step's data from the sensor data file.
    
    Returns:
    - step (int): The step number in the simulation.
    - fire_positions (list): List of fire events with (x, y, temperature, voltage).
    - animal_positions (list): List of animal movements with (id, x, y, heat).
    - new_data (bool): Whether new data is available or not.
    """
    fire_positions = []
    animal_positions = []
    step = None
    file_pos = file.tell()  # Store file position before reading
    
    while True:
        line = file.readline()
        if not line:
            return step, fire_positions, animal_positions, False  # No new data yet
        
        parts = line.strip().split()
        
        if parts[0] == "STEP":
            if step is not None:  # If a new step is found, rewind and return the previous step's data
                file.seek(file_pos)
                return step, fire_positions, animal_positions, True
            step = int(parts[1])
        elif parts[0] == "FIRE":
            # Fire data includes x, y, temperature, and voltage
            fire_positions.append((int(parts[1]), int(parts[2]), float(parts[3]), float(parts[5])))
        elif parts[0] == "ANIMAL":
            # Animal data includes id, x, y, and heat signature
            animal_positions.append((int(parts[1]), float(parts[2]), float(parts[3]), float(parts[4])))

        file_pos = file.tell()  # Update file position


def calculate_light_intensity(voltage):
    """
    Converts voltage into light intensity.
    
    Formula: Light Intensity = Voltage / 1000
    """
    return voltage / 1000.0


def update_plots(frame):
    """
    Updates three subplots:
    1. Left subplot (ax1): Displays fire and animal positions.
    2. Middle subplot (ax2): Shows fire voltage.
    3. Right subplot (ax3): Shows fire light intensity.
    """
    # Clear previous frame data from subplots
    ax1.cla()
    ax2.cla()
    ax3.cla()

    # Read the latest sensor data
    step, fire_positions, animal_positions, new_data = read_next_step(file)

    if new_data:
        # Configure the first subplot (fire and animal positions)
        ax1.set_xlim(-4, 15)
        ax1.set_ylim(-4, 15)
        ax1.set_title(f"22BCT0046\nWildlife & Fire Monitoring\nusing CCD & AFIR Sensors for Step {step}", fontsize=14, fontweight="bold")
        ax1.set_xlabel("X-Coordinate", fontsize=12)
        ax1.set_ylabel("Y-Coordinate", fontsize=12)
        ax1.grid(True, linestyle="--", alpha=0.5)

        # Plot fire positions with temperature-based color coding
        if fire_positions:
            fire_x = [x for x, _, _, _ in fire_positions]
            fire_y = [y for _, y, _, _ in fire_positions]
            fire_temps = [temp for _, _, temp, _ in fire_positions]
            ax1.scatter(fire_x, fire_y, c=fire_temps, cmap='hot', s=70, marker='x', alpha=0.7, label="CCD - Fire")

        # Plot animal movements and trails
        for animal_id, x, y, heat in animal_positions:
            if animal_id not in animal_trails:
                animal_trails[animal_id] = []
            animal_trails[animal_id].append((x, y))

            # Keep only the last 10 positions for trails
            if len(animal_trails[animal_id]) > 10:
                animal_trails[animal_id].pop(0)

            # Color mapping based on heat signature (more heat = redder)
            color = (1, max(0, 1 - heat/50), 0)

            # Plot animal's current position
            ax1.scatter(x, y, color=color, s=80, marker="o", label="AFIR - Animal" if (x, y) == animal_positions[0][1:3] else "")

            # Draw the movement trail
            if len(animal_trails[animal_id]) > 1:
                trail_x, trail_y = zip(*animal_trails[animal_id])
                ax1.plot(trail_x, trail_y, linestyle="dotted", color=color, alpha=0.6)

        # Remove duplicate legend entries
        handles, labels = ax1.get_legend_handles_labels()
        unique_labels = dict(zip(labels, handles))
        ax1.legend(unique_labels.values(), unique_labels.keys(), loc="upper right")

        # Configure the second subplot (fire voltage)
        ax2.set_xlim(-4, 15)
        ax2.set_ylim(-4, 15)
        ax2.set_title(f"22BCT0046\nFire Voltage Calculated\n(Step {step})", fontsize=14, fontweight="bold")
        ax2.set_xlabel("X-Coordinate", fontsize=12)
        ax2.set_ylabel("Y-Coordinate", fontsize=12)
        ax2.grid(True, linestyle="--", alpha=0.5)

        if fire_positions:
            volt_values = [volt for _, _, _, volt in fire_positions]
            ax2.scatter(fire_x, fire_y, c=volt_values, cmap='viridis', s=70, marker='s', alpha=0.7, label="Voltage (V)")

        # Configure the third subplot (fire light intensity)
        ax3.set_xlim(-4, 15)
        ax3.set_ylim(-4, 15)
        ax3.set_title(f"22BCT0046\nFire Light Intensity Calculated\n(Step {step})", fontsize=14, fontweight="bold")
        ax3.set_xlabel("X-Coordinate", fontsize=12)
        ax3.set_ylabel("Y-Coordinate", fontsize=12)
        ax3.grid(True, linestyle="--", alpha=0.5)

        if fire_positions:
            light_values = [calculate_light_intensity(volt) for _, _, _, volt in fire_positions]
            ax3.scatter(fire_x, fire_y, c=light_values, cmap='plasma', s=70, marker='^', alpha=0.7, label="Light Intensity")

        # Remove duplicate legend entries for ax2 and ax3
        handles2, labels2 = ax2.get_legend_handles_labels()
        unique_labels2 = dict(zip(labels2, handles2))
        ax2.legend(unique_labels2.values(), unique_labels2.keys(), loc="upper right")

        handles3, labels3 = ax3.get_legend_handles_labels()
        unique_labels3 = dict(zip(labels3, handles3))
        ax3.legend(unique_labels3.values(), unique_labels3.keys(), loc="upper right")

    else:
        print("Waiting for sensor data...")

    plt.pause(0.5)  # Pause to simulate real-time data streaming


# Initialize the figure and three subplots
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(18, 6))

# Open the sensor data file for reading
file = open(SENSOR_FILE, "r")

# Set up animation to update the plots dynamically
ani = animation.FuncAnimation(fig, update_plots, interval=500)

# Display the plots
plt.show()
