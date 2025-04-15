#ifndef PHOTODIODE_SENSOR_H
#define PHOTODIODE_SENSOR_H

#include <stdlib.h>

#define N 0.8   // Quantum Efficiency
#define R 0.6   // Responsivity

typedef struct {
    int id;
    float last_current;
} PhotoDiodeSensor;

void init_PhotoDiode(PhotoDiodeSensor *sensor, int id);
float get_PhotoDiode_current(PhotoDiodeSensor *sensor);

void init_PhotoDiode(PhotoDiodeSensor *sensor, int id) {
    sensor->id = id;
    sensor->last_current = 0.0;
}

float get_PhotoDiode_current(PhotoDiodeSensor *sensor) {
    float Popt = ((float)(rand() % 100 + 1)) / 1000.0;  // Optical power [0.001, 0.1] W
    float current = N * Popt * R;
    sensor->last_current = current;
    return current;
}

#endif
