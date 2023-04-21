#include "animation/animation.h"
#include "displayPicker/displayPicker.h"
#include "insideTemp/insideTemp.h"
#include "myWebServer/myWebServer.h"
#include "myWifi/myWifi.h"
#include "outsideTemp/outsideTemp.h"
#include "rgbLEDs/rgbLEDs.h"
#include "roomLightLevel/roomLightLevel.h"
#include "statusLED/statusLED.h"
#include <Arduino.h>
#include <AsyncElegantOTA.h>

unsigned long MillisTime;

void setup() {
    setupStatusLED();
    statusLedOn();
    loadSettings();
    startWifi();
    startServer();
    AsyncElegantOTA.begin(&server);
    startTime();
    startOutsideTemp();
    startInsideTemp();
    setAnimationFunc();
    statusLedOff();
}

void loop() {
    currentMillis = millis();
    outsideTempLooping();

    if (currentMillis - MillisTime >= 500) {
        MillisTime = currentMillis;
        getInsideTemp();
        updateTime();
        updateLightLevel();

        display();
    }

    if (currentMillis - MillisAnimtionSpeed >= animationSpeed[isNight]) {
        MillisAnimtionSpeed = currentMillis;
        curentAnimationFunc();
    }
}