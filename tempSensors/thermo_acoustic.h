#ifndef THERMO_ACOUSTIC_H
#define THERMO_ACOUSTIC_H
#include <stdio.h>  // Fix snprintf error
#include <stdlib.h> // Fix rand error
#include <math.h>
#define TA_MIN_TEMP 0
#define TA_MAX_TEMP 60
#define TA_ACCURACY 2.0
#define TA_DRIFT 0.6  

typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoAcousticSensor;

void init_thermo_acoustic(ThermoAcousticSensor *sensor, int id);
float get_thermo_acoustic_temp(ThermoAcousticSensor *sensor, int years);



void init_thermo_acoustic(ThermoAcousticSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermo-Acoustic");
    sensor->last_value = 0.0;
}

float get_thermo_acoustic_temp(ThermoAcousticSensor *sensor, int years) {
    float base_temp = (rand() % (TA_MAX_TEMP - TA_MIN_TEMP + 1)) + TA_MIN_TEMP;
    float noise = ((rand() % 100) / 100.0) * TA_ACCURACY * ((rand() % 2) ? 1 : -1);
    float drift = (base_temp * TA_DRIFT * years) / 100;
    float temp = base_temp + noise + drift;
    //Vout = (S0 * P) + (k * P^2)
    
    if (temp < TA_MIN_TEMP) temp = TA_MIN_TEMP;
    if (temp > TA_MAX_TEMP) temp = TA_MAX_TEMP;

    sensor->last_value = temp;
    return temp;
}
#endif
