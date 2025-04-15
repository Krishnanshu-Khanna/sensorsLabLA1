import pandas as pd
import matplotlib.pyplot as plt
import os

# File path
file_path = "./data/LA3-22BCT0046_DATA.csv"

# Check if file exists
if not os.path.exists(file_path):
    print("Error: CSV file not found!")
    exit()

# Load CSV
df = pd.read_csv(file_path)

# Ensure required columns exist
required_columns = {"Time", "Capacitance", "MagnetoResistance"}
if not required_columns.issubset(df.columns):
    print("Error: CSV missing required columns!")
    exit()

# Define Pump ON/OFF based on Capacitance threshold (35)
df["Pump Status"] = df["Capacitance"].apply(lambda x: "ON" if x <= 35 else "OFF")

# Create figure and axes
fig, axs = plt.subplots(2, 1, figsize=(14, 10), facecolor='black')
plt.style.use("dark_background")
fig.suptitle("LA3-22BCT0046 Data Visualization", fontsize=18, color="white", fontweight="bold")

# Common settings
for ax in axs:
    ax.set_facecolor("black")  # Full dark mode
    ax.grid(True, linestyle='dashed', linewidth=0.5, color="gray", alpha=0.6)  # Grid settings
    ax.tick_params(axis="both", colors="white", labelsize=12)  # White axis labels
    ax.spines["bottom"].set_color("white")
    ax.spines["left"].set_color("white")

# --------- Capacitance Graph (Top) ---------
axs[0].plot(df["Time"], df["Capacitance"], label="Capacitance (pF)", color="red", marker="o", linewidth=2, markersize=5)
axs[0].axhline(y=35, color='red', linestyle='dashed', linewidth=1.5, label="Threshold (35 pF)")
# Highlight Pump ON/OFF points
for i in range(len(df)):
    if df["Pump Status"][i] == "ON":
        axs[0].scatter(df["Time"][i], df["Capacitance"][i], color="lime", s=50, label="Pump ON" if i == 0 else "")
        axs[0].text(df["Time"][i], df["Capacitance"][i], "ON", fontsize=10, ha="right", color="lime", weight="bold")
    elif df["Pump Status"][i] == "OFF":
        axs[0].scatter(df["Time"][i], df["Capacitance"][i], color="red", s=50, label="Pump OFF" if i == 0 else "")
        axs[0].text(df["Time"][i], df["Capacitance"][i], "OFF", fontsize=10, ha="right", color="red", weight="bold")

axs[0].set_ylabel("Capacitance (pF)", fontsize=14, color="white")
axs[0].set_title(" Capacitance & Pump Status", fontsize=16, color="lime", fontweight="bold")
axs[0].legend(facecolor="black", edgecolor="white", fontsize=12)

# --------- MagnetoResistance Graph (Bottom) ---------
axs[1].plot(df["Time"], df["MagnetoResistance"], label="MagnetoResistance (Ω)", color="deepskyblue", marker="s", linewidth=2, markersize=5)
axs[1].set_xlabel("Time", fontsize=14, color="white")
axs[1].set_ylabel("MagnetoResistance (Ω)", fontsize=14, color="white")
axs[1].set_title(" MagnetoResistance Readings", fontsize=16, color="deepskyblue", fontweight="bold")
axs[1].legend(facecolor="black", edgecolor="white", fontsize=12)

# Adjust layout
plt.tight_layout()
plt.show()
