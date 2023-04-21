#pragma once
#include "wifiDebug.h"
#include <Arduino.h>

String debugMsg;

template <typename t>
void wifiPrint(t msg) {
    if (webSocketData.count() > 0) {
        webSocketData.textAll(String(msg));
    } else {
        debugMsg += msg;
        debugMsg += "\n";
    }
}

void clearWifiPrint() {
    debugMsg = "";
}