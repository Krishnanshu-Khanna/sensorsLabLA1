import pandas as pd
import matplotlib.pyplot as plt

# Load CSV data
df = pd.read_csv("data/sensor_data.csv")

# Plot sensor temperatures
plt.style.use("dark_background")
plt.figure(figsize=(16, 8))
plt.plot(df["Time"], df["Thermoelectric"], label="Thermoelectric", linestyle="dotted")
plt.plot(df["Time"], df["Thermoresistive"], label="Thermoresistive", linestyle="dashed")
plt.plot(df["Time"], df["Thermo-Optical"], label="Thermo-Optical", linestyle="solid")
plt.plot(df["Time"], df["Thermo-Acoustic"], label="Thermo-Acoustic", linestyle="dashdot")
plt.plot(df["Time"], df["Avg Temp"], label="Average Temp", linewidth=2, color="white")

# Highlight control actions
for i in range(len(df)):
    if df["Avg Temp"][i] > 35:
        plt.scatter(df["Time"][i], df["Avg Temp"][i], color="red", marker="o", s=100, label="Coolant Activated" if i == 0 else "")
    elif df["Avg Temp"][i] < 10:
        plt.scatter(df["Time"][i], df["Avg Temp"][i], color="blue", marker="o", s=100, label="Heater Activated" if i == 0 else "")


# Add a legend with a red and blue button-like indicator
legend_labels = [
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='red', markersize=10, label='Coolant Injected (> 35°C)'),
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='blue', markersize=10, label='Heat Recovery Activated (< 10°C)')
]
# Add threshold lines
plt.axhline(y=35, color='red', linestyle='--', linewidth=1.5)
plt.axhline(y=10, color='blue', linestyle='--', linewidth=1.5)
plt.legend(handles=legend_labels, loc="upper right", fontsize=10, facecolor="black")

plt.xlabel("Time")
plt.ylabel("Temperature (°C)")
plt.title("22BCT0046 Temperature Sensor Readings Over Time")
plt.legend()
plt.grid()
plt.show()
