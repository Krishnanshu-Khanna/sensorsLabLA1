import pandas as pd
import matplotlib.pyplot as plt

# Set dark theme for the plots
plt.style.use('dark_background')

# Prompt the user to input the sensor type they want to visualize
sensor = input("Enter sensor type to plot (mos/ph/airbag): ").strip().lower()

# Load the sensor data from a CSV file into a pandas DataFrame
df = pd.read_csv("LA4-22BCT0046.csv")

# Set the main title for the visualization
plt.suptitle("Sensor Data Visualization - 22BCT0046", fontsize=16, fontweight='bold')

# Check the sensor type and plot the corresponding data
if sensor == "mos":
    # Plot Resistance vs Temperature for MOS sensor
    plt.plot(df["Temperature"], df["Resistance"], color="#00FFFF", linewidth=2, marker='o', label="Resistance")
    plt.title("MOS Sensor: Resistance vs Temperature", fontsize=14)
    plt.xlabel("Temperature (K)", fontsize=12)
    plt.ylabel("Resistance (Ohms)", fontsize=12)
elif sensor == "ph":
    # Plot Potential vs pH for Potentiometric sensor
    plt.plot(df["pH"], df["Potential"], color="#FF69B4", linewidth=2, marker='s', label="Potential")
    plt.title("Potentiometric Sensor: Potential vs pH", fontsize=14)
    plt.xlabel("pH Value", fontsize=12)
    plt.ylabel("Potential (V)", fontsize=12)
elif sensor == "airbag":
    # Plot Force and Pressure vs Temperature for Airbag sensor
    plt.plot(df["Temperature"], df["Force"], color="#00FF7F", linewidth=2, marker='^', label="Force")
    plt.plot(df["Temperature"], df["Pressure"], color="#FFD700", linewidth=2, marker='x', label="Pressure")
    plt.title("Airbag Sensor: Force & Pressure vs Temperature", fontsize=14)
    plt.xlabel("Temperature (K)", fontsize=12)
    plt.ylabel("Force / Pressure", fontsize=12)
    plt.legend()  # Add a legend to distinguish between Force and Pressure
else:
    # Handle invalid sensor type input
    print("Invalid sensor type.")
    exit()

# Add a grid to the plot for better readability
plt.grid(True, linestyle="--", alpha=0.5)

# Adjust the layout to prevent overlapping of elements
plt.tight_layout()

# Display the plot
plt.show()
