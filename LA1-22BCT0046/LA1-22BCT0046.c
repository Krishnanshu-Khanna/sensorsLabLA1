#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    

#include "LA1-22BCT0046.h"  // Header file containing sensor structure definitions and function declarations

// Function to log sensor readings into a CSV file
// Takes a file pointer and sensor readings as arguments
void log_to_csv(FILE *file, int time, float te_temp, float tr_temp, float to_temp, float ta_temp, float avg_temp, const char *action) {
    fprintf(file, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n", time, te_temp, tr_temp, to_temp, ta_temp, avg_temp, action);
}

int main() {
    int N_READINGS;  // Variable to store the number of sensor readings
    srand(time(NULL));  // Seed the random number generator with the current time
    
    // Declare sensor objects for different sensor types
    ThermoelectricSensor te_sensor;
    ThermoresistiveSensor tr_sensor;
    ThermoOpticalSensor to_sensor;
    ThermoAcousticSensor ta_sensor;

    // Initialize each sensor with a unique ID
    init_thermoelectric(&te_sensor, 1);
    init_thermoresistive(&tr_sensor, 2);
    init_thermo_optical(&to_sensor, 3);
    init_thermo_acoustic(&ta_sensor, 4);

    // Open a CSV file for writing sensor data
    FILE *file = fopen("./data/LA1-22BCT0046_DATA.csv", "w");
    if (!file) {  // Check if file opening was successful
        printf("Error opening CSV file!\n");
        return 1;  // Exit program with error code
    }
    
    // Write CSV header row
    fprintf(file, "Time,Thermoelectric,Thermoresistive,Thermo-Optical,Thermo-Acoustic,Avg Temp,Action\n");
    
    // Ask user for the number of sensor readings to take
    printf("Input Number of sensor readings needed:- ");
    scanf("%d", &N_READINGS);
    
    // Loop through the number of readings specified by the user
    for (int t = 0; t < N_READINGS; t++) {
        // Read temperature values from each sensor
        float te_temp = get_thermoelectric_temp(&te_sensor, 1);
        float tr_temp = get_thermoresistive_temp(&tr_sensor, 1);
        float to_temp = get_thermo_optical_temp(&to_sensor, 1);
        float ta_temp = get_thermo_acoustic_temp(&ta_sensor, 1);

        // Calculate the average temperature from all four sensors
        float avg_temp = (te_temp + tr_temp + to_temp + ta_temp) / 4;
        
        // Determine if an action needs to be taken based on the temperature
        char action[20] = "None";  // Default action is "None"
        if (avg_temp > 35) {  // If average temperature is above 35°C
            snprintf(action, 20, "Fan ON");  // Activate cooling fan
        } else if (avg_temp < 10) {  // If average temperature is below 10°C
            snprintf(action, 20, "Heater ON");  // Activate heater
        }

        // Log sensor data and action taken to the CSV file
        log_to_csv(file, t, te_temp, tr_temp, to_temp, ta_temp, avg_temp, action);
    }

    // Close the file after writing data
    fclose(file);
    
    // Notify the user that data logging is complete
    printf("%d Sensor data logged successfully!\n", N_READINGS);

    return 0; 
}
