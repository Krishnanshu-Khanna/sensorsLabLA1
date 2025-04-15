// Include necessary libraries for input/output, memory management, time, and Unix-specific functions
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> 
#include "LA2-22BCT0046.h" // Custom header file for simulation-specific functions

// Define constants for grid size and number of animals
#define GRID_SIZE 10 
#define NUM_ANIMALS 5 

int main() {
    // Seed the random number generator with the current time to ensure different random numbers each run
    srand(time(NULL));

    // Print a message to indicate the start of the simulation
    printf("Starting simulation...\n");

    // Prompt the user to enter the number of simulation steps
    printf("Enter the number of simulation steps: ");
    int SIMULATION_STEPS; 
    scanf("%d", &SIMULATION_STEPS); 

    // Declare variables for physical parameters
    float emissivity, area, responsivity, resistance;

    // Prompt the user to enter physical parameters and Read the values from the user
    printf("Enter area in m^2: ");
    scanf("%f", &area); 
    printf("Enter responsivity: ");
    scanf("%f", &responsivity); 
    printf("Enter resistance: ");
    scanf("%f", &resistance); 
    printf("Enter emissivity: ");
    scanf("%f", &emissivity); 

    // Initialize an array of animals with random positions and a fixed heat signature
    Animal animals[NUM_ANIMALS];
    for (int i = 0; i < NUM_ANIMALS; i++) {
        animals[i].id = i + 1; // Assign a unique ID to each animal
        animals[i].x = rand() % GRID_SIZE; // Random x-coordinate within the grid
        animals[i].y = rand() % GRID_SIZE; // Random y-coordinate within the grid
        animals[i].heat_signature = 36.0; // Fixed heat signature for all animals
    }

    // Attempt to open a file for writing simulation data
    FILE *file = fopen("data/LA2-22BCT0046.csv", "w");
    if (!file) {
        // Handle error if file cannot be created
        perror("Error: Could not create LA2-22BCT0046.csv");
        return EXIT_FAILURE; // Exit with failure status
    }
    fclose(file); // Close the file after creation

    // Perform the simulation for the specified number of steps
    for (int step = 0; step < SIMULATION_STEPS; step++) {
        // Open the file for appending data at each step
        file = fopen("data/LA2-22BCT0046.csv", "a");
        if (!file) {
            // Handle error if file cannot be opened for writing
            perror("Error: Could not open LA2-22BCT0046.csv for writing");
            return EXIT_FAILURE; // Exit with failure status
        }

        // Write the current step number to the file
        fprintf(file, "STEP %d\n", step);
        printf("Step %d completed....\n", step); // Print progress to the console

        // Iterate over each grid cell to simulate temperature and detect fires
        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                // Generate a random temperature between 30 and 70 degrees
                float temp = get_temperature(30, 70);

                // Check if a fire is detected at the current temperature
                if (detect_fire(temp)) {
                    // Calculate the voltage based on the temperature and physical parameters
                    float voltage = calculate_voltage(temp, emissivity, area, responsivity, resistance);

                    // Write fire detection data to the file
                    fprintf(file, "FIRE %d %d %.2f VOLTAGE %.2f\n", x, y, temp, voltage);
                }
            }
        }

        // Update and track each animal's position
        for (int i = 0; i < NUM_ANIMALS; i++) {
            track_animal(&animals[i]); // Update animal position

            // Write animal tracking data to the file
            fprintf(file, "ANIMAL %d %.1f %.1f %.1f\n", animals[i].id, animals[i].x, animals[i].y, animals[i].heat_signature);
        }

        // Close the file after writing data for this step
        fclose(file);

        // Pause the simulation for 1 second
        sleep(1);
    }

    printf("Data successfully saved to LA2-22BCT0046.csv\n");
    return EXIT_SUCCESS; 
}
