#pragma once
#include "clock/clock.h"
#include "insideTemp/insideTemp.h"
#include "myTime/myTime.h"
#include "outsideTemp/outsideTemp.h"
#include "roomLightLevel/roomLightLevel.h"

extern void (*display)();
extern void (*displayArray[2])();