#include "insideTemp.h"

#define SENSOR_PIN 35
#define REFERENCE_RESISTANCE 12500
#define NOMINAL_RESISTANCE 10000
#define NOMINAL_TEMPERATURE 25
#define B_VALUE 3950
#define STM32_ANALOG_RESOLUTION 4095
#define SMOOTHING_FACTOR 5

Thermistor *thermistor = NULL;

int insideTemp;

void startInsideTemp() {
    thermistor = new SmoothThermistor(new NTC_Thermistor(SENSOR_PIN, REFERENCE_RESISTANCE, NOMINAL_RESISTANCE, NOMINAL_TEMPERATURE, B_VALUE, STM32_ANALOG_RESOLUTION), SMOOTHING_FACTOR);
}

void getInsideTemp() {
    insideTemp = ((thermistor->readFahrenheit()) * 100 + 50) / 100;
}