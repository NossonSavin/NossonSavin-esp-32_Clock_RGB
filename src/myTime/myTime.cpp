#include "myTime/myTime.h"

ESP32Time rtc;

bool isMiddleDotOn;
int time24Hour;
int time12Hour;
int timeMinute;
int time24HourInMin;
int timeSecond;

bool isOfflineMode = false;

void startTime() {
    if (isOfflineMode) {
        rtc.setTime(0, 0, 0, 1, 1, 2023); // sec min hour day month year
    } else {
        configTime(-18000, 3600, "time4.google.com"); // set time
    }
}

void updateTime() {
    isMiddleDotOn = !isMiddleDotOn;
    time24Hour = rtc.getHour(true);
    time12Hour = rtc.getHour(false);
    timeMinute = rtc.getMinute();
    time24HourInMin = time24Hour * 60;
    timeSecond = rtc.getSecond();

    if (time12Hour == 0) {
        time12Hour = 12;
    }
}