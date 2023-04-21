#pragma once
#include "clock/clock.h"
#include <NTC_Thermistor.h>
#include <SmoothThermistor.h>
#include <Thermistor.h>

extern Thermistor *thermistor;

extern int insideTemp;

void startInsideTemp();
void getInsideTemp();