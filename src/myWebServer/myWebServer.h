// add  startServer(); in setup and #include "myWebServer.h"
#pragma once
#include "./settings/settings.h"
#include "LittleFS.h"
#include "accessPoint/accessPoint.h"
#include "animation/animation.h"
#include "displayPicker/displayPicker.h"
#include "myTime/myTime.h"
#include "outsideTemp/outsideTemp.h"
#include <ESPAsyncWebServer.h>

#include "statusLED/statusLED.h"

extern AsyncWebServer server;
extern AsyncWebSocket webSocketData;

void sendStates(AsyncWebServerRequest *request);
void updateData(AsyncWebServerRequest *request);
void startServer();