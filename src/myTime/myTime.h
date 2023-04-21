#pragma once
#include "clock/clock.h"
#include <ESP32Time.h>

extern ESP32Time rtc;

extern bool isMiddleDotOn;
extern int time24Hour;
extern int time12Hour;
extern int timeMinute;
extern int time24HourInMin;
extern int timeSecond;

extern bool isOfflineMode;

void startTime();
void updateTime();