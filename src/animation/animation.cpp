#include "animation/animation.h"

void (*curentAnimationFunc)();
unsigned long MillisAnimtionSpeed;
int setAnimationSpeed[2] = {500, 30};
int animationSpeed[2] = {30, 30};
int animationDelay[2] = {2000, 0};
int animationDelayCount = 0;
bool isDelaying;
int colorPicker[2][2] = {{0, 1}, {0, 3}};
int animationNum[2] = {1, 0};
bool isNight = false;
bool animationColorNum;
bool forwardAndBack[2] = {true, false};
bool isReverse[2] = {false, false};
bool isVertical[2] = {true, true};
int animationPosition;
int colors[5] = {2565, 65536, 3080225, 657928, 5575947};

const int pixelMapXCount = 12;
const int pixelMapYCount = 18;
int pixelMap[pixelMapXCount][pixelMapYCount] =
    {
        //  999 is empty
        /* 0 */ {999, 999, 49, 999, 999, 56, 999, 999, 999, 999, 999, 999, 63, 999, 999, 70, 999, 999},
        /* 1 */ {999, 48, 999, 50, 55, 999, 57, 999, 999, 999, 999, 62, 999, 64, 69, 999, 71, 999},
        /* 2 */ {999, 999, 54, 999, 999, 61, 999, 999, 999, 999, 999, 999, 68, 999, 999, 75, 999, 999},
        /* 3 */ {999, 53, 999, 51, 60, 999, 58, 999, 999, 999, 999, 67, 999, 65, 74, 999, 72, 999},
        /* 4 */ {999, 999, 52, 999, 999, 59, 999, 999, 999, 999, 999, 999, 66, 999, 999, 73, 999, 999},
        /* 5 */ {999, 999, 999, 6, 7, 999, 999, 999, 999, 22, 23, 999, 999, 999, 999, 36, 37, 999},
        /* 6 */ {0, 5, 999, 999, 999, 8, 999, 18, 21, 999, 999, 999, 24, 35, 999, 999, 999, 38},
        /* 7 */ {1, 4, 999, 999, 999, 9, 999, 999, 20, 999, 999, 999, 25, 34, 999, 999, 999, 39},
        /* 8 */ {999, 999, 999, 16, 17, 999, 999, 999, 999, 32, 33, 999, 999, 999, 999, 46, 47, 999},
        /* 9 */ {2, 15, 999, 999, 999, 10, 999, 999, 31, 999, 999, 999, 26, 45, 999, 999, 999, 40},
        /* 10*/ {3, 14, 999, 999, 999, 11, 999, 19, 30, 999, 999, 999, 27, 44, 999, 999, 999, 41},
        /* 11*/ {999, 999, 999, 13, 12, 999, 999, 999, 999, 29, 28, 999, 999, 999, 999, 43, 42, 999},
};

void setAnimationFunc() {
    if (animationColorNum) {
        curentAnimationFunc = animationFuncArry[animationNum[isNight]];
        animationSpeed[isNight] = setAnimationSpeed[animationNum[isNight]];
    } else {
        curentAnimationFunc = animationFuncArry[animationNum[isNight]];
        animationSpeed[isNight] = setAnimationSpeed[animationNum[isNight]];
    }
}

int outerLoopCount() {
    return isVertical[isNight] ? pixelMapXCount : pixelMapYCount;
}

int getPixel(int x, int y) {
    if (isVertical[isNight]) {
        return pixelMap[isReverse[isNight] ? (outerLoopCount() - 1) - y : y][x];
    } else {
        return pixelMap[x][isReverse[isNight] ? (outerLoopCount() - 1) - y : y];
    }
}

int innerLoopCount() {
    return isVertical[isNight] ? pixelMapYCount : pixelMapXCount;
}

void delayCheck() {
    if (!isDelaying) {
        return;
    }

    animationDelayCount += animationSpeed[isNight];

    if (animationDelayCount > animationDelay[isNight]) {
        animationDelayCount = 0;
        isDelaying = false;

        animationPosition = 0;
        animationColorNum = !animationColorNum;
        if (forwardAndBack[isNight]) {
            isReverse[isNight] = !isReverse[isNight];
        }
    }
}

void animationUpdater(int pixalCount) {
    delayCheck();
    if (isDelaying) {
        return;
    }

    animationPosition++;

    if (animationPosition > pixalCount) {
        isDelaying = true;
    }
}

void fill() {
    for (int i = 0; i < numOfPixel; i++) {
        if (activeLedState[i]) {
            pixels.setPixelColor(i, colors[colorPicker[isNight][0]]);
        } else {
            pixels.setPixelColor(i, 0);
        }
    }
    pixels.show();
}

void wipe() {
    animationUpdater(outerLoopCount());

    for (int y = 0; y < outerLoopCount(); y++) {
        for (int x = 0; x < innerLoopCount(); x++) {
            int pixelNum = getPixel(x, y);

            if (pixelNum != 999) {
                if (activeLedState[pixelNum]) {
                    if (animationPosition < y) {
                        pixels.setPixelColor(pixelNum, colors[animationColorNum ? colorPicker[isNight][0] : colorPicker[isNight][1]]);
                    } else {
                        pixels.setPixelColor(pixelNum, colors[animationColorNum ? colorPicker[isNight][1] : colorPicker[isNight][0]]);
                    }
                } else {
                    pixels.setPixelColor(pixelNum, 0);
                }
            }
        }
    }
    pixels.show();
}

void (*animationFuncArry[2])() = {fill, wipe};