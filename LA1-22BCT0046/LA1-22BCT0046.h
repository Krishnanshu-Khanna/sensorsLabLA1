#ifndef LA1_22BCT0046_H
#define LA1_22BCT0046_H

#include <stdio.h>  // Include standard I/O library for snprintf
#include <stdlib.h> // Include standard library for rand
#include <math.h>   // Include math library for mathematical functions
#include <time.h>   // Include time library for seeding rand

// Define constants for ThermoAcousticSensor
#define TA_MIN_TEMP 0
#define TA_MAX_TEMP 60
#define TA_ACCURACY 2.0
#define TA_DRIFT 0.6 

// Define constants for ThermoOpticalSensor
#define TO_MIN_TEMP 0
#define TO_MAX_TEMP 60
#define TO_ACCURACY 1.5
#define TO_DRIFT 0.6

// Define constants for ThermoelectricSensor
#define TE_MIN_TEMP 0
#define TE_MAX_TEMP 60
#define TE_ACCURACY 2.5
#define TE_DRIFT 0.6  // 0.6% per year

// Define constants for ThermoresistiveSensor
#define TR_MIN_TEMP 0
#define TR_MAX_TEMP 60
#define TR_ACCURACY 1.0
#define TR_DRIFT 0.6  

// Define constants for RTD (Resistance Temperature Detector)
#define R0 100.0       // Resistance at 0°C (ohms)
#define ALPHA 0.00385  // Temperature coefficient of resistance (1/°C)
#define A 3.9083e-3    // Callendar-Van Dusen constant A
#define B -5.775e-7    // Callendar-Van Dusen constant B
#define C -4.183e-12   // Callendar-Van Dusen constant C (used for T < 0°C)

// Define structure for ThermoAcousticSensor
typedef struct {
    int id; //sensor id
    char type[20]; //sensor type
    float last_value; //latest value
} ThermoAcousticSensor;

// Function prototypes for ThermoAcousticSensor
void init_thermo_acoustic(ThermoAcousticSensor *sensor, int id);
float get_thermo_acoustic_temp(ThermoAcousticSensor *sensor, int years);

// Initialize ThermoAcousticSensor
void init_thermo_acoustic(ThermoAcousticSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermo-Acoustic");
    sensor->last_value = 0.0;
}

// Get temperature for ThermoAcousticSensor
float get_thermo_acoustic_temp(ThermoAcousticSensor *sensor, int years) {
    float base_temp = (rand() % (TA_MAX_TEMP - TA_MIN_TEMP + 1)) + TA_MIN_TEMP;
    float noise = ((rand() % 100) / 100.0) * TA_ACCURACY * ((rand() % 2) ? 1 : -1);
    float drift = (base_temp * TA_DRIFT * years) / 100;
    float temp = base_temp + noise + drift;
    
    if (temp < TA_MIN_TEMP) temp = TA_MIN_TEMP;
    if (temp > TA_MAX_TEMP) temp = TA_MAX_TEMP;

    sensor->last_value = temp;
    return temp;
}

// Define structure for ThermoOpticalSensor
typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoOpticalSensor;

// Function prototypes for ThermoOpticalSensor
void init_thermo_optical(ThermoOpticalSensor *sensor, int id);
float get_thermo_optical_temp(ThermoOpticalSensor *sensor, int years);

// Initialize ThermoOpticalSensor
void init_thermo_optical(ThermoOpticalSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermo-Optical");
    sensor->last_value = 0.0;
}

// Get temperature for ThermoOpticalSensor
float get_thermo_optical_temp(ThermoOpticalSensor *sensor, int years) {
    float base_temp = (rand() % (TO_MAX_TEMP - TO_MIN_TEMP + 1)) + TO_MIN_TEMP;
    float noise = ((rand() % 100) / 100.0) * TO_ACCURACY * ((rand() % 2) ? 1 : -1);
    float drift = (base_temp * TO_DRIFT * years) / 100;
    float temp = base_temp + noise + drift;

    // Constants for heat calculation
    const double stefanBoltzmann = 5.67e-8; // Stefan-Boltzmann constant (W/m²·K⁴)
    const double AreaTire = 0.8;            // Tire area in square meters
    const double EpsilonTire = 0.9;         // Emissivity of the tire surface

    // Calculate heat emitted by the tire
    float heat = EpsilonTire * stefanBoltzmann * AreaTire * pow(temp, 4);

    if (temp < TO_MIN_TEMP) temp = TO_MIN_TEMP;
    if (temp > TO_MAX_TEMP) temp = TO_MAX_TEMP;

    sensor->last_value = temp;
    return temp;
}

// Define structure for ThermoelectricSensor
typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoelectricSensor;

// Function prototypes for ThermoelectricSensor
void init_thermoelectric(ThermoelectricSensor *sensor, int id);
float get_thermoelectric_temp(ThermoelectricSensor *sensor, int years);

// Initialize ThermoelectricSensor
void init_thermoelectric(ThermoelectricSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermoelectric");
    sensor->last_value = 0.0;
}

// Get temperature for ThermoelectricSensor
float get_thermoelectric_temp(ThermoelectricSensor *sensor, int years) {
    float base_temp = (rand() % (TE_MAX_TEMP - TE_MIN_TEMP + 1)) + TE_MIN_TEMP;
    float noise = ((rand() % 100) / 100.0) * TE_ACCURACY * ((rand() % 2) ? 1 : -1);
    float drift = (base_temp * TE_DRIFT * years) / 100;
    float temp = base_temp + noise + drift;

    // Example: Piezoelectric coefficient (material property)
    const double piezoelectricCoefficient = 10e-12; // Coulombs/Newton (example)
    float charge = piezoelectricCoefficient * temp;

    if (temp < TE_MIN_TEMP) temp = TE_MIN_TEMP;
    if (temp > TE_MAX_TEMP) temp = TE_MAX_TEMP;

    sensor->last_value = temp;
    return temp;
}

// Define structure for ThermoresistiveSensor
typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoresistiveSensor;

// Function prototypes for ThermoresistiveSensor
void init_thermoresistive(ThermoresistiveSensor *sensor, int id);
float get_thermoresistive_temp(ThermoresistiveSensor *sensor, int years);

// Linear approximation formula for RTD temperature calculation
double rtd_temperature_linear(double resistance) {
    return (resistance - R0) / (R0 * ALPHA);
}

// Callendar-Van Dusen equation for more accuracy
double rtd_temperature_cvd(double resistance) {
    double t = (-A + sqrt(A * A - 4 * B * (1 - resistance / R0))) / (2 * B);
    if (t < 0) {
        t += C * (t - 100) * t * t;  // Apply CVD correction for T < 0°C
    }
    return t;
}

// Initialize ThermoresistiveSensor
void init_thermoresistive(ThermoresistiveSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermoresistive");
    sensor->last_value = 0.0;
}

// Get temperature for ThermoresistiveSensor
float get_thermoresistive_temp(ThermoresistiveSensor *sensor, int years) {
    float base_temp = (rand() % (TR_MAX_TEMP - TR_MIN_TEMP + 1)) + TR_MIN_TEMP;
    float noise = ((rand() % 100) / 100.0) * TR_ACCURACY * ((rand() % 2) ? 1 : -1);
    float drift = (base_temp * TR_DRIFT * years) / 100;
    float temp = base_temp + noise + drift;

    if (temp < TR_MIN_TEMP) temp = TR_MIN_TEMP;
    if (temp > TR_MAX_TEMP) temp = TR_MAX_TEMP;

    sensor->last_value = temp;
    return temp;
}

#endif