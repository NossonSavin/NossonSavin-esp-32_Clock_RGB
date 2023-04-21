#include "displayPicker.h"

void displayTimeTemp() {
    setDisplay1(time12Hour / 10, time12Hour % 10, isMiddleDotOn, timeMinute / 10, timeMinute % 10);
    setDisplay2(insideTemp / 10, insideTemp % 10);
    setDisplay3(OutsideTemperature / 10, OutsideTemperature % 10);
}

void displayLightLeval() {
    setDisplay1(0, (mapedLightLev / 100) % 10, 0, (mapedLightLev / 10) % 10, mapedLightLev % 10);
    setDisplay2(lightLevTrigerCount / 10, lightLevTrigerCount % 10);
}

void displayInsideTemp(int display) {
    if (display == 2) {
        setDisplay2(lightLevTrigerCount / 10, lightLevTrigerCount % 10);
    } else {
        setDisplay3(lightLevTrigerCount / 10, lightLevTrigerCount % 10);
    }
}
void (*displayArray[2])() = {displayTimeTemp, displayLightLeval};
void (*display)() = displayArray[0];