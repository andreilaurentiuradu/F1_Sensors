#include <stdio.h>

#include "structs.h"

typedef void (*function_ptr)(void *);

void read_tire_sensor(tire_sensor *s, FILE *in) {
    fread(&s->pressure, sizeof(float), 1, in);
    fread(&s->temperature, sizeof(float), 1, in);
    fread(&s->wear_level, sizeof(int), 1, in);
    fread(&s->performace_score, sizeof(int), 1, in);
}

void print_tire_sensor(tire_sensor *s) {
    // fprintf(out, "Tire Sensor\n");
    // fprintf(out, "Pressure: %.2f\n", s->pressure);
    // fprintf(out, "Temperature: %.2f\n", s->temperature);
    // fprintf(out, "Wear Level: %d%%\n", s->wear_level);
    // if(s->performace_score != 0)
    //     fprintf(out, "Performance Score: %d\n", s->performace_score);
    // else
    //     fprintf(out, "Performance Score: Not Calculated\n");
    printf("Tire Sensor\n");
    printf("Pressure: %.2f\n", s->pressure);
    printf("Temperature: %.2f\n", s->temperature);
    printf("Wear Level: %d%%\n", s->wear_level);
    if (s->performace_score != 0)
        printf("Performance Score: %d\n", s->performace_score);
    else
        printf("Performance Score: Not Calculated\n");
}

void read_PMU(power_management_unit *s, FILE *in) {
    fread(&s->voltage, sizeof(float), 1, in);
    fread(&s->current, sizeof(float), 1, in);
    fread(&s->power_consumption, sizeof(float), 1, in);
    fread(&s->energy_regen, sizeof(int), 1, in);
    fread(&s->energy_storage, sizeof(int), 1, in);
}

void print_PMU(power_management_unit *s) {
    // fprintf(out, "Power Management Unit\n");
    // fprintf(out, "Voltage: %.2f\n", s->voltage);
    // fprintf(out, "Current: %.2f\n", s->current);
    // fprintf(out, "Power Consumption: %.2f\n", s->power_consumption);
    // fprintf(out, "Energy Regen: %d%%\n", s->energy_regen);
    // fprintf(out, "Energy Storage: %d%%\n", s->energy_storage);

    printf("Power Management Unit\n");
    printf("Voltage: %.2f\n", s->voltage);
    printf("Current: %.2f\n", s->current);
    printf("Power Consumption: %.2f\n", s->power_consumption);
    printf("Energy Regen: %d%%\n", s->energy_regen);
    printf("Energy Storage: %d%%\n", s->energy_storage);
}

int cmpfunc(const void *a, const void *b) {
    int x, y;
    if ((((sensor *)a)->sensor_type) == TIRE)
        x = 1;
    else
        x = 0;

    if ((((sensor *)b)->sensor_type) == TIRE)
        y = 1;
    else
        y = 0;

    return x - y;  //  daca e pozitiv se face interschimbarea
}

void swap_sensors(sensor *a, sensor *b) {
    sensor aux = *a;
    *a = *b;
    *b = aux;
}

void analyze(sensor *s, function_ptr *op) {
    for (int i = 0; i < s->nr_operations; ++i) {
        op[s->operations_idxs[i]](s->sensor_data);
    }
}