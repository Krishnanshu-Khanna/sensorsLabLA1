import pandas as pd  # Import Pandas for data handling
import matplotlib.pyplot as plt  # Import Matplotlib for plotting

# Load CSV data into a DataFrame (Ensure the file path is correct)
df = pd.read_csv("data/LA1-22BCT0046_DATA.csv")

# Set the dark background style for better visibility on dark-themed environments
plt.style.use("dark_background")

# Create a figure with a specified size to make the plot more readable
plt.figure(figsize=(12,8))

# Plot temperature sensor readings over time with different styles for clarity
plt.plot(df["Time"], df["Thermoelectric"], label="Thermoelectric", linestyle="dotted")  # Dotted line for Thermoelectric sensor
plt.plot(df["Time"], df["Thermoresistive"], label="Thermoresistive", linestyle="dashed")  # Dashed line for Thermoresistive sensor
plt.plot(df["Time"], df["Thermo-Optical"], label="Thermo-Optical", linestyle="solid")  # Solid line for Thermo-Optical sensor
plt.plot(df["Time"], df["Thermo-Acoustic"], label="Thermo-Acoustic", linestyle="dashdot")  # Dash-dot line for Thermo-Acoustic sensor

# Highlight the average temperature with a thicker white line for visibility
plt.plot(df["Time"], df["Avg Temp"], label="Average Temp", linewidth=2, color="white")

# Loop through all rows to check if temperature thresholds are breached
for i in range(len(df)):
    if df["Avg Temp"][i] > 35:  # If average temperature exceeds 35°C
        plt.scatter(df["Time"][i], df["Avg Temp"][i], color="red", marker="o", s=100, label="Coolant Activated" if i == 0 else "")  # Mark the point in red
    elif df["Avg Temp"][i] < 10:  # If average temperature drops below 10°C
        plt.scatter(df["Time"][i], df["Avg Temp"][i], color="blue", marker="o", s=1-0, label="Heater Activated" if i==0 else "")  # Mark the point in blue

# Define custom legend markers for threshold-based actions
legend_labels = [
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='red', markersize=10, label='Coolant Injected (> 35°C)'),  # Red marker for coolant injection
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='blue', markersize=10, label='Heat Recovery Activated (< 10°C)')  # Blue marker for heating activation
]

# Draw horizontal threshold lines to indicate temperature limits
plt.axhline(y=35, color='red', linestyle='--', linewidth=1.5)  # Upper limit (coolant activation)
plt.axhline(y=10, color='blue', linestyle='--', linewidth=1.5)  # Lower limit (heater activation)

# Get legend handles and labels from existing plot lines
sensor_handles, sensor_labels = plt.gca().get_legend_handles_labels()

# Remove duplicate empty labels from scatter points (caused by the "if i == 0 else ''" logic)
filtered_legend_labels = []
filtered_legend_handles = []
for handle, label in zip(sensor_handles, sensor_labels):
    if label and label not in filtered_legend_labels:
        filtered_legend_handles.append(handle)
        filtered_legend_labels.append(label)

# Combine sensor legends with custom markers (Coolant & Heater Activation)
combined_handles = filtered_legend_handles + legend_labels
combined_labels = filtered_legend_labels + [l.get_label() for l in legend_labels]

# Apply the final legend with all components
plt.legend(combined_handles, combined_labels, loc="upper right", fontsize=10, facecolor="black")


# Label the axes for better understanding
plt.xlabel("Time")  # X-axis represents time
plt.ylabel("Temperature (°C)")  # Y-axis represents temperature in degrees Celsius

# Add a title to the graph
plt.title("22BCT0046 Temperature Sensor Readings Over Time")

# Ensure the default legend also appears alongside the custom one
plt.legend()

# Enable grid for better readability of the plot
plt.grid()

# Display the final plot
plt.show()
