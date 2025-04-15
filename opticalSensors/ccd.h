#ifndef CCD_SENSOR_H
#define CCD_SENSOR_H

#include <stdlib.h>
#include <math.h>

#define Q 1.6e-19    // Charge of an electron (Coulombs)
#define C 10e-12     // Capacitance (Farads)

typedef struct {
    int id;
    float last_voltage;
} CCDSensor;

void init_CCD(CCDSensor *sensor, int id);
float get_CCD_voltage(CCDSensor *sensor);

void init_CCD(CCDSensor *sensor, int id) {
    sensor->id = id;
    sensor->last_voltage = 0.0;
}

float get_CCD_voltage(CCDSensor *sensor) {
    int N = rand() % 5000 + 1000; // Random photons [1000, 5000]
    float voltage = (Q * N) / C;
    sensor->last_voltage = voltage;
    return voltage;
}

#endif
