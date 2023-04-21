// add  startWifi(); in setup and #include "myWifi.h"
#pragma once
#include <ESPmDNS.h>
#include <WiFi.h>

extern String wifiName;
extern String wifiPW;

void WiFiConnect();
void WiFiReconnect(WiFiEvent_t event, WiFiEventInfo_t info);
void startWifi();