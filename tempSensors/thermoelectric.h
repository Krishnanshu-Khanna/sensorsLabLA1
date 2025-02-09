#ifndef THERMOELECTRIC_H
#define THERMOELECTRIC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TE_MIN_TEMP 0
#define TE_MAX_TEMP 60
#define TE_ACCURACY 2.5
#define TE_DRIFT 0.6  // 0.6% per year

typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoelectricSensor;

void init_thermoelectric(ThermoelectricSensor *sensor, int id);
float get_thermoelectric_temp(ThermoelectricSensor *sensor, int years);



void init_thermoelectric(ThermoelectricSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermoelectric");
    sensor->last_value = 0.0;
}

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

#endif
