#include <stdio.h>
#include <stdlib.h>
#include <time.h>     
#include "LA3-22BCT0046.h"

// Function to log sensor readings into a CSV file
void log_to_csv(FILE *file, int time, float capacitance, float magnetoResistance, const char *action) {
    // Writes sensor data into the CSV file in the format: Time, Capacitance, MagnetoResistance, Action
    fprintf(file, "%d,%.2f,%.2f,%s\n", time, capacitance, magnetoResistance, action);
}

int main() {
    int N_READINGS;  // Variable to store the number of sensor readings required
    srand(time(NULL));  // Seed the random number generator with the current time for randomness

    // Create instances of sensor structures
    CapacitiveSensor c_sensor;    // Object for the capacitive sensor
    MagnetoSensor m_sensor;       // Object for the magneto-resistance sensor

    // Initialize the sensors with their respective IDs (Assuming 1 for capacitive, 2 for magneto-resistance)
    init_capacitive(&c_sensor, 1);
    init_magnetoresistance(&m_sensor, 2);

    // Open a CSV file for writing sensor data
    FILE *file = fopen("./data/LA3-22BCT0046_DATA.csv", "w");
    if (!file) {  // If file opening fails, print an error message and exit
        printf("Error opening CSV file!\n");
        return 1; // Exit with error code 1
    }

    // Write the CSV header row to label each column
    fprintf(file, "Time,Capacitance,MagnetoResistance,Action\n");

    // Prompt user for the number of readings required
    printf("Input number of sensor readings needed: ");
    scanf("%d", &N_READINGS); // Read user input for number of readings

    // Loop through the required number of readings
    for (int t = 0; t < N_READINGS; t++) {
        // Retrieve capacitance reading (Assuming function returns a float value)
        float capacitance = get_capacitance(&c_sensor, 4);
        // Retrieve magneto-resistance reading (Assuming function returns a float value)
        float magnetoResistance = get_magneto_resistance(&m_sensor, 4);

        // Determine the action based on capacitance value
        char action[20] = "None"; // Default action
        if (capacitance > 35) {   
            snprintf(action, sizeof(action), "Soil is wet"); // If capacitance is above 35, soil is wet
        } else if (capacitance < 30) {
            snprintf(action, sizeof(action), "Soil is dry"); // If capacitance is below 30, soil is dry
        }

        // Log the sensor readings and determined action to the CSV file
        log_to_csv(file, t, capacitance, magnetoResistance, action);
    }

    // Close the file to save the data properly
    fclose(file);

    // Print success message to console
    printf("%d sensor data logged successfully!\n", N_READINGS);

    return 0; // Program ends successfully
}
