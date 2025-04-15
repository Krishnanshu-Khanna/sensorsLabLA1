#ifndef LA2_22BCT0046_H
#define LA2_22BCT0046_H

// Include necessary libraries for input/output, memory management, math, and time
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Define constants for fire detection threshold and grid size
#define FIRE_THRESHOLD 60.0 
#define GRID_SIZE 10 

// Define a struct for CCD sensors
typedef struct {
    int id; // Unique identifier for the sensor
    char type[20]; // Type of sensor (e.g., "CCD")
    float last_value; // Last measured value by the sensor
} CCDSensor;

// Define a struct for AFIR sensors
typedef struct {
    int id; // Unique identifier for the sensor
    char type[20]; // Type of sensor (e.g., "AFIR")
    float last_value; // Last measured value by the sensor
} AFIRSensor;

// Function prototypes for initializing sensors
void init_ccd(CCDSensor *sensor, int id); // Initialize a CCD sensor
void init_afir(AFIRSensor *sensor, int id); // Initialize an AFIR sensor

// Function prototypes for temperature and fire detection
float get_temperature(int min_temp, int max_temp); 
int detect_fire(float temp); 

// Function prototype for calculating voltage
float calculate_voltage(float temp, float emissivity, float area, float responsivity, float resistance);

// Function to initialize an AFIR sensor
void init_afir(AFIRSensor *sensor, int id) {
    sensor->id = id; // Set the sensor ID
    snprintf(sensor->type, sizeof(sensor->type), "AFIR"); // Set the sensor type
    sensor->last_value = 0.0; // Initialize the last measured value
}

// Function to initialize a CCD sensor
void init_ccd(CCDSensor *sensor, int id) {
    sensor->id = id; // Set the sensor ID
    snprintf(sensor->type, sizeof(sensor->type), "CCD"); // Set the sensor type
    sensor->last_value = 0.0; // Initialize the last measured value
}

// Function to generate a random temperature within a specified range
float get_temperature(int min_temp, int max_temp) {
    return min_temp + (rand() % (max_temp - min_temp + 1)); // Random temperature between min_temp and max_temp
}

// Function to calculate voltage based on temperature and physical parameters
float calculate_voltage(float temp, float emissivity, float area, float responsivity, float resistance) {
    return temp * emissivity * area * responsivity / resistance; // Calculate voltage using the formula
}

// Function to detect fires based on temperature
int detect_fire(float temp) {
    return temp >= FIRE_THRESHOLD; // Return true if temperature is above or equal to the fire threshold
}

// Define a struct for animals
typedef struct {
    int id; // Unique identifier for the animal
    float x, y; // Position coordinates of the animal
    float heat_signature; // Heat signature of the animal
} Animal;

// Function prototype to track an animal's movement
void track_animal(Animal *animal);

// Function to track an animal's movement
void track_animal(Animal *animal) {
    int dx = (rand() % 3) - 1; // Random change in x-coordinate (-1, 0, or 1)
    int dy = (rand() % 3) - 1; // Random change in y-coordinate (-1, 0, or 1)

    // Update animal's position within grid boundaries
    animal->x = fmax(0, fmin(animal->x + dx, GRID_SIZE - 1));
    animal->y = fmax(0, fmin(animal->y + dy, GRID_SIZE - 1));

    // Update animal's heat signature randomly between 35 and 40
    animal->heat_signature = 35.0 + (rand() % 6);
}

#endif
