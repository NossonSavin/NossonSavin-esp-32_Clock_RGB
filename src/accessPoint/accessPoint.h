#pragma once
#include "ESPAsyncWebServer.h"
#include "statusLED/statusLED.h"
#include <AsyncTCP.h>
#include <WiFi.h>

extern bool isAccessPointOn;

void toggleAccessPoint();