#include "accessPoint.h"

bool isAccessPointOn = false;

void toggleAccessPoint() {
    if (isAccessPointOn) {
        statusLedOff();
        WiFi.mode(WIFI_MODE_STA);
    } else {
        statusLedOn();
        WiFi.softAP("Clock");
    }

    isAccessPointOn = !isAccessPointOn;
}