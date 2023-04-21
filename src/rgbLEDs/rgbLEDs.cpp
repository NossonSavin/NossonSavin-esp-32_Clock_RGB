#include "rgbLEDs.h"

bool activeLedState[numOfPixel];

Adafruit_NeoPixel pixels(numOfPixel /* Number of led */, 13 /* PIN Number */, NEO_GRB + NEO_KHZ800 /* Type of led */);