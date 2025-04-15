#ifndef LA3_22BCT0046_H   // If this header is not defined...
#define LA3_22BCT0046_H   // Define it to prevent multiple inclusions

// ✅ Including Necessary Standard Libraries
#include <stdio.h>  // Standard Input-Output library (for printf, snprintf, etc.)
#include <stdlib.h> // Standard library (for rand(), memory allocation, etc.)
#include <math.h>   // Math library (for mathematical operations, not used here but included)
#include <time.h>   // Time library (for seeding random values)

// ✅ Defining the Capacitive Sensor Structure
typedef struct {
    int id;           // Unique ID for the sensor
    char type[20];    // Type of sensor (e.g., "Soil Moisture Sensor")
    float last_value; // Last recorded capacitance value
    float capacitance;// Current capacitance value
} CapacitiveSensor;

// Function Declarations for Capacitive Sensor (Defined Later)
void init_capacitive(CapacitiveSensor *sensor, int id);
float get_capacitance(CapacitiveSensor *sensor, int variation);

// ✅ Defining the Magneto-Resistance Sensor Structure
typedef struct {
    int id;           // Unique ID for the sensor
    char type[20];    // Type of sensor (e.g., "Magneto Sensor")
    float last_value; // Last recorded resistance value
    float resistance; // Current resistance value
} MagnetoSensor;

// Function Declarations for Magneto-Resistance Sensor
void init_magnetoresistance(MagnetoSensor *sensor, int id);
float get_magneto_resistance(MagnetoSensor *sensor, int variation);

// ✅ Function to Initialize the Capacitive Sensor
void init_capacitive(CapacitiveSensor *sensor, int id) {
    sensor->id = id;                             // Assigning sensor ID
    sensor->capacitance = (rand() % 60) + 10;    // Generating a random capacitance value between 10 and 69
}

// ✅ Function to Initialize the Magneto-Resistance Sensor
void init_magnetoresistance(MagnetoSensor *sensor, int id) {
    sensor->id = id;                            // Assigning sensor ID
    sensor->resistance = (rand() % 100) + 20;   // Generating a random resistance value between 20 and 119
}

// ✅ Function to Get a Random Capacitance Reading
float get_capacitance(CapacitiveSensor *sensor, int variation) {
    sensor->capacitance += (rand() % (variation * 2 + 1)) - variation; // Adding random variation to the value

    // Ensuring the capacitance value remains within valid range (5 - 60)
    if (sensor->capacitance < 5) sensor->capacitance = 5;
    if (sensor->capacitance > 60) sensor->capacitance = 60;

    return sensor->capacitance; // Returning updated capacitance value
}

// ✅ Function to Get a Random Magneto-Resistance Reading
float get_magneto_resistance(MagnetoSensor *sensor, int variation) {
    sensor->resistance += (rand() % (variation * 2 + 1)) - variation; // Adding random variation to the value

    // Ensuring the resistance value remains within valid range (20 - 100)
    if (sensor->resistance < 20) sensor->resistance = 20;
    if (sensor->resistance > 100) sensor->resistance = 100;

    return sensor->resistance; // Returning updated resistance value
}

#endif // End of Header File Guard
