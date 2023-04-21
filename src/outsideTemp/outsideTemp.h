#pragma once
#include "clock/clock.h"
#include <asyncHTTPrequest.h>

extern int OutsideTemperature;
extern unsigned long currentMillis;

void pullOutsideTemperature();
void SetOutTemperature(void *optParm, asyncHTTPrequest *request, int readyState);
void startOutsideTemp();
void outsideTempLooping();