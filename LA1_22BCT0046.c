#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./tempSensors/thermoelectric.h"
#include "./tempSensors/thermoresistive.h"
#include "./tempSensors/thermo_optical.h"
#include "./tempSensors/thermo_acoustic.h"
#include "LA1_22BCT0046.h"

void log_to_csv(FILE *file, int time, float te_temp, float tr_temp, float to_temp, float ta_temp, float avg_temp, const char *action) {
    fprintf(file, "%d,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n", time, te_temp, tr_temp, to_temp, ta_temp, avg_temp, action);
}

int main() {
    int N_READINGS;
    srand(time(NULL));
    
    ThermoelectricSensor te_sensor;
    ThermoresistiveSensor tr_sensor;
    ThermoOpticalSensor to_sensor;
    ThermoAcousticSensor ta_sensor;

    init_thermoelectric(&te_sensor, 1);
    init_thermoresistive(&tr_sensor, 2);
    init_thermo_optical(&to_sensor, 3);
    init_thermo_acoustic(&ta_sensor, 4);

    FILE *file = fopen("./data/themperature_data.csv", "w");
    if (!file) {
        printf("Error opening CSV file!\n");
        return 1;
    }
    
    fprintf(file, "Time,Thermoelectric,Thermoresistive,Thermo-Optical,Thermo-Acoustic,Avg Temp,Action\n");
    printf("Input Number of sensor readings\n");
    scanf("%d", &N_READINGS);
    for (int t = 0; t < N_READINGS; t++) {
        float te_temp = get_thermoelectric_temp(&te_sensor, 1);
        float tr_temp = get_thermoresistive_temp(&tr_sensor, 1);
        float to_temp = get_thermo_optical_temp(&to_sensor, 1);
        float ta_temp = get_thermo_acoustic_temp(&ta_sensor, 1);

        float avg_temp = (te_temp + tr_temp + to_temp + ta_temp) / 4;
        char action[20] = "None";

        if (avg_temp > 35) {
            snprintf(action, 20, "Fan ON");
        } else if (avg_temp < 10) {
            snprintf(action, 20, "Heater ON");
        }

        log_to_csv(file, t, te_temp, tr_temp, to_temp, ta_temp, avg_temp, action);
    }

    fclose(file);
    printf("%d Sensor data logged successfully!\n", N_READINGS);

    return 0;
}
