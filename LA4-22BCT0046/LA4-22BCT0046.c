#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LA4-22BCT0046.h"

// Function to write the CSV header based on the sensor type
void write_csv_header(FILE *file, const char *type) {
    if (strcmp(type, "mos") == 0) {
        // Header for MOS sensor data
        fprintf(file, "Temperature,Resistance\n");
    } else if (strcmp(type, "ph") == 0) {
        // Header for pH sensor data
        fprintf(file, "pH,Potential\n");
    } else if (strcmp(type, "airbag") == 0) {
        // Header for airbag sensor data
        fprintf(file, "Temperature,Pressure,Force\n");
    }
}

int main() {
    char sensor_type[20]; // Variable to store the sensor type input by the user

    // Prompt the user to enter the sensor type
    printf("Enter sensor type (mos/ph/airbag): ");
    scanf("%s", sensor_type);

    // Open a CSV file for writing
    FILE *file = fopen("LA4-22BCT0046.csv", "w");
    if (!file) {
        // Handle file creation error
        perror("Unable to create CSV");
        return 1;
    }

    // Write the appropriate CSV header based on the sensor type
    write_csv_header(file, sensor_type);

    // Check the sensor type and process accordingly
    if (strcmp(sensor_type, "mos") == 0) {
        // Initialize MOS sensor parameters
        MOS_Sensor mos = {500, 0.5, 300}; // Ra, Ea, T

        // Loop through temperature values and calculate resistance
        for (int t = 300; t <= 500; t += 20) {
            mos.T = t; // Update temperature
            double Rg = calculate_mos_resistance(mos); // Calculate resistance
            fprintf(file, "%d,%.4e\n", t, Rg); // Write data to CSV
        }

    } else if (strcmp(sensor_type, "ph") == 0) {
        // Initialize pH sensor parameters
        PH_Sensor ph = {0.7, 7}; // E0, pH

        // Loop through pH values and calculate potential
        for (double pH_val = 4.0; pH_val <= 10.0; pH_val += 1.0) {
            ph.pH = pH_val; // Update pH value
            double voltage = calculate_potential(ph); // Calculate potential
            fprintf(file, "%.1f,%.4f\n", pH_val, voltage); // Write data to CSV
        }

    } else if (strcmp(sensor_type, "airbag") == 0) {
        // Initialize airbag sensor parameters
        Airbag airbag = {0.05, 0.06, 300, 0.5}; // n, V, T, area

        // Loop through temperature values and calculate pressure and force
        for (int T = 300; T <= 600; T += 30) {
            airbag.T = T; // Update temperature
            double pressure = calculate_pressure(airbag); // Calculate pressure
            double force = calculate_force(pressure, airbag.surface_area); // Calculate force
            fprintf(file, "%d,%.2f,%.2f\n", T, pressure, force); // Write data to CSV
        }

    } else {
        // Handle invalid sensor type
        printf("Invalid sensor type.\n");
        fclose(file); // Close the file
        return 1;
    }

    // Close the file after writing data
    fclose(file);
    printf("Data saved to LA4-22BCT0046.csv\n");
    return 0; // Exit the program successfully
}
