#include "roomLightLevel.h"
#include <Arduino.h>

const int lightSensor = 34;
int mapedLightLev;
int userLightLev = 2;
const int lightLevTrigerAt = 30;
int lightLevTrigerCount = lightLevTrigerAt; // set to max so on startup it switch to night mode if room is dark

void updateLightLevel() {
    mapedLightLev = analogRead(lightSensor);
    mapedLightLev = mapedLightLev > 3095 ? mapedLightLev - 3095 : 0;
    mapedLightLev = map(mapedLightLev, 0, 1000, 999, 0);

    if (isNight) {
        if (mapedLightLev > userLightLev) {
            if (lightLevTrigerCount >= lightLevTrigerAt) {
                isNight = false;
                setAnimationFunc();
            } else {
                lightLevTrigerCount++;
            }
        } else {
            lightLevTrigerCount = 0;
        }
    } else {
        if (mapedLightLev < userLightLev) {
            if (lightLevTrigerCount >= lightLevTrigerAt) {
                isNight = true;
                setAnimationFunc();
            } else {
                lightLevTrigerCount++;
            }
        } else {
            lightLevTrigerCount = 0;
        }
    }
}