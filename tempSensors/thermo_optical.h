#ifndef THERMO_OPTICAL_H
#define THERMO_OPTICAL_H

#include <stdio.h>  // Fix snprintf error
#include <stdlib.h> // Fix rand error
#include <math.h>
#define TO_MIN_TEMP 0
#define TO_MAX_TEMP 60
#define TO_ACCURACY 1.5
#define TO_DRIFT 0.6  

typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoOpticalSensor;

void init_thermo_optical(ThermoOpticalSensor *sensor, int id);
float get_thermo_optical_temp(ThermoOpticalSensor *sensor, int years);


void init_thermo_optical(ThermoOpticalSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermo-Optical");
    sensor->last_value = 0.0;
}

float get_thermo_optical_temp(ThermoOpticalSensor *sensor, int years) {
    float base_temp = (rand() % (TO_MAX_TEMP - TO_MIN_TEMP + 1)) + TO_MIN_TEMP;
    float noise = ((rand() % 100) / 100.0) * TO_ACCURACY * ((rand() % 2) ? 1 : -1);
    float drift = (base_temp * TO_DRIFT * years) / 100;
    float temp = base_temp + noise + drift;

    // Constants
    const double stefanBoltzmann = 5.67e-8; // Stefan-Boltzmann constant (W/m²·K⁴)
    const double AreaTire = 0.8;            // Tire area in square meters
    const double EpsilonTire = 0.9;         // Emissivity of the tire surface

    // Function to detect tire heat
    // Q = ε * σ * A * T⁴
    float heat= EpsilonTire * stefanBoltzmann * AreaTire * pow(temp, 4);

    if (temp < TO_MIN_TEMP) temp = TO_MIN_TEMP;
    if (temp > TO_MAX_TEMP) temp = TO_MAX_TEMP;

    sensor->last_value = temp;
    return temp;
}

#endif
