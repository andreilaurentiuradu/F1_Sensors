#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

typedef void (*function_ptr)(void *);

void read_tire_sensor(tire_sensor *s, FILE *in)
{
	fread(&s->pressure, sizeof(float), 1, in);
	fread(&s->temperature, sizeof(float), 1, in);
	fread(&s->wear_level, sizeof(int), 1, in);
	fread(&s->performace_score, sizeof(int), 1, in);
}


void print_tire_sensor(tire_sensor *s)
{
	printf("Tire Sensor\n");
	printf("Pressure: %.2f\n", s->pressure);
	printf("Temperature: %.2f\n", s->temperature);
	printf("Wear Level: %d%%\n", s->wear_level);
	if (s->performace_score != 0) {
		printf("Performance Score: %d\n", s->performace_score);
	} else {
		printf("Performance Score: Not Calculated\n");
	}
}

void read_PMU(power_management_unit *s, FILE *in)
{
	fread(&s->voltage, sizeof(float), 1, in);
	fread(&s->current, sizeof(float), 1, in);
	fread(&s->power_consumption, sizeof(float), 1, in);
	fread(&s->energy_regen, sizeof(int), 1, in);
	fread(&s->energy_storage, sizeof(int), 1, in);
}

void print_PMU(power_management_unit *s)
{
	printf("Power Management Unit\n");
	printf("Voltage: %.2f\n", s->voltage);
	printf("Current: %.2f\n", s->current);
	printf("Power Consumption: %.2f\n", s->power_consumption);
	printf("Energy Regen: %d%%\n", s->energy_regen);
	printf("Energy Storage: %d%%\n", s->energy_storage);
}

int cmpfunc(const void *a, const void *b)
{
	int x, y;
	if ((((sensor *)a)->sensor_type) == TIRE)
		x = 1;
	else
		x = 0;

	if ((((sensor *)b)->sensor_type) == TIRE)
		y = 1;
	else
		y = 0;

	//  daca e pozitiv se face interschimbarea
	return x - y;
}

void swap_sensors(sensor *a, sensor *b)
{
	sensor aux = *a;
	*a = *b;
	*b = aux;
}

void analyze(sensor *s, function_ptr *op)
{
	for (int i = 0; i < s->nr_operations; ++i) {
		op[s->operations_idxs[i]](s->sensor_data);
	}
}


int check_PMU(power_management_unit *s)
{
	if (s->voltage < 10 || s->voltage > 20)
		return 0;
	if (s->current < -100 || s->current > 100)
		return 0;
	if (s->power_consumption < 0 || s->power_consumption > 1000)
		return 0;
	if (s->energy_regen < 0 || s->energy_regen > 100)
		return 0;
	if (s->energy_storage < 0 || s->energy_storage > 100)
		return 0;
	return 1;
}

int check_TIRE(tire_sensor *s)
{
	if (s->pressure < 19 || s->pressure > 28)
		return 0;
	if (s->temperature < 0 || s->temperature > 120)
		return 0;
	if (s->wear_level < 0 || s->wear_level > 100)
		return 0;
	return 1;
}

void delete_sensor(sensor *s, int index, int *nr_senzori)
{
	// eliberam memoria ocupata de senzor
	free(s[index].operations_idxs);
	free(s[index].sensor_data);
	// mutam senzorii de dupa index cu o pozitie la stanga
	for (int i = index + 1; i < (*nr_senzori); ++i) {
		s[i - 1] = s[i];
	}
	(*nr_senzori)--;
}

void clear_sensors(sensor s[], int *nr_senzori)
{
	for (int i = 0; i < (*nr_senzori); ++i) {
		if (s[i].sensor_type == TIRE &&
			!check_TIRE((tire_sensor *)(s[i].sensor_data))) {
			delete_sensor(s, i, nr_senzori);
			--i;
		}
		if (s[i].sensor_type == PMU &&
			!check_PMU((power_management_unit *)(s[i].sensor_data))) {
			delete_sensor(s, i, nr_senzori);
			--i;
		}
	}
}
