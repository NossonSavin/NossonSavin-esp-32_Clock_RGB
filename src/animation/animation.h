#pragma once
#include "rgbLEDs/rgbLEDs.h"

extern bool isNight;
extern bool isVertical[2];
extern bool isReverse[2];
extern bool forwardAndBack[2];
extern unsigned long MillisAnimtionSpeed;
extern int animationSpeed[2];
extern int setAnimationSpeed[2];
extern int animationDelay[2];
extern int colorPicker[2][2];
extern int colors[5];
extern int animationNum[2];

extern void (*curentAnimationFunc)();
extern void (*animationFuncArry[])();

void setAnimationFunc();