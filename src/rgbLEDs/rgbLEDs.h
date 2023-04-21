// add  setLED(); in setup and #include "led.h"
#pragma once
#include "animation/animation.h"
#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel pixels;

extern bool activeLedState[];
const int numOfPixel = 76;