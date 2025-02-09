#ifndef THERMORESISTIVE_H
#define THERMORESISTIVE_H

#include <stdio.h>  // Fix snprintf error
#include <stdlib.h> // Fix rand error
#include <math.h>
#define TR_MIN_TEMP 0
#define TR_MAX_TEMP 60
#define TR_ACCURACY 1.0
#define TR_DRIFT 0.6  

#define R0 100.0       // Resistance at 0°C (ohms)
#define ALPHA 0.00385  // Temperature coefficient of resistance (1/°C)
#define A 3.9083e-3    // Callendar-Van Dusen constant A
#define B -5.775e-7    // Callendar-Van Dusen constant B
#define C -4.183e-12   // Callendar-Van Dusen constant C (used for T < 0°C)

typedef struct {
    int id;
    char type[20];
    float last_value;
} ThermoresistiveSensor;


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
void init_thermoresistive(ThermoresistiveSensor *sensor, int id);
float get_thermoresistive_temp(ThermoresistiveSensor *sensor, int years);


void init_thermoresistive(ThermoresistiveSensor *sensor, int id) {
    sensor->id = id;
    snprintf(sensor->type, 20, "Thermoresistive");
    sensor->last_value = 0.0;
}

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
