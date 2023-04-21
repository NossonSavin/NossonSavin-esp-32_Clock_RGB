#include "outsideTemp.h"

asyncHTTPrequest request;

int OutsideTemperature;
unsigned long MillisOutsideTemper;
unsigned long currentMillis;

void pullOutsideTemperature() {
    if (request.readyState() == 0 || request.readyState() == 4) {
        request.open("GET", "http://api.openweathermap.org/data/2.5/weather?lat=<lat_here>&lon=<lon_here>&units=imperial&appid=<key>");
        request.send();
    }
}

void SetOutTemperature(void *optParm, asyncHTTPrequest *request, int readyState) {
    if (readyState == 4) {
        String response = request->responseText();
        int p1 = response.indexOf("\"temp\":") + 7;
        int p2 = response.indexOf(",\"feels_like");
        OutsideTemperature = response.substring(p1, p2).toInt();
        // wifiPrint(OutsideTemperature);
    }
}

void startOutsideTemp() {
    delay(1000);
    pullOutsideTemperature();
    request.onReadyStateChange(SetOutTemperature);
}

void outsideTempLooping() {
    if (currentMillis - MillisOutsideTemper >= 15 * 60 * 1000) // 15min
    {
        MillisOutsideTemper = currentMillis;
        pullOutsideTemperature();
    }
}