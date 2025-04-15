#ifndef AFIR_SENSOR_H
#define AFIR_SENSOR_H

#include <stdlib.h>
#include <math.h>

#define PIN 1.0   // Input infrared power in Watts
#define ALPHA 0.05 // Infrared attenuation coefficient

typedef struct {
    int id;
    float last_power;
} AFIRSensor;

void init_AFIR(AFIRSensor *sensor, int id);
float get_AFIR_power(AFIRSensor *sensor);

void init_AFIR(AFIRSensor *sensor, int id) {
    sensor->id = id;
    sensor->last_power = 0.0;
}

float get_AFIR_power(AFIRSensor *sensor) {
    float d = ((float)(rand() % 100 + 1)) / 10.0;  // Random distance [0.1, 10.0] meters
    float power = PIN * exp(-ALPHA * d);
    sensor->last_power = power;
    return power;
}

#endif
