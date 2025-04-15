#ifndef SENSORS_H
#define SENSORS_H

#include <math.h>

// Universal gas constant (J/(mol·K))
#define R 8.314 

// Boltzmann constant (J/K) for MOS sensor calculations
#define K_B 1.380649e-23 

// Structure to represent a MOS (Metal-Oxide-Semiconductor) sensor
typedef struct {
    double Ra; // Resistance at a reference temperature (ohms)
    double Ea; // Activation energy (eV)
    double T;  // Temperature (Kelvin)
} MOS_Sensor;

// Structure to represent a pH sensor
typedef struct {
    double E0; // Standard electrode potential (volts)
    double pH; // pH value of the solution
} PH_Sensor;

// Structure to represent an airbag system
typedef struct {
    double n;            // Number of moles of gas
    double V;            // Volume of the airbag (m^3)
    double T;            // Temperature (Kelvin)
    double surface_area; // Surface area of the airbag (m^2)
} Airbag;

// // Function prototypes
// double calculate_mos_resistance(MOS_Sensor sensor); // Calculates MOS sensor resistance
// double calculate_potential(PH_Sensor sensor);       // Calculates potential of a pH sensor
// double calculate_pressure(Airbag airbag);          // Calculates pressure inside an airbag
// double calculate_force(double pressure, double area); // Calculates force exerted by pressure on a surface

// Function to calculate the resistance of a MOS sensor
double calculate_mos_resistance(MOS_Sensor sensor) {
    // Convert activation energy from eV to Joules
    double Ea_joules = sensor.Ea * 1.60218e-19;  
    // Calculate resistance using the Arrhenius equation
    return sensor.Ra * exp(-Ea_joules / (K_B * sensor.T));
}

// Function to calculate the potential of a pH sensor
double calculate_potential(PH_Sensor sensor) {
    // Nernst equation for pH sensor potential
    return sensor.E0 - (0.0591 * sensor.pH);
}

// Function to calculate the pressure inside an airbag
double calculate_pressure(Airbag airbag) {
    // Ideal gas law: P = (nRT) / V
    return (airbag.n * R * airbag.T) / airbag.V;
}

// Function to calculate the force exerted by pressure on a surface
double calculate_force(double pressure, double area) {
    // Force = Pressure × Area
    return pressure * area;
}

#endif
