#include "clock.h"

int digitOffset[10] = {0, 4, 18, 20, 34, 48, 55, 62, 69, 76};
const int SegmentPatternCount = 38;
bool numberMap[SegmentPatternCount][7] = {
    /*spot 0 print 0      */ {1, 1, 1, 1, 1, 1, 0},
    /*spot 1 print 1      */ {0, 0, 1, 1, 0, 0, 0},
    /*spot 2 print 2      */ {0, 1, 1, 0, 1, 1, 1},
    /*spot 3 print 3      */ {0, 1, 1, 1, 1, 0, 1},
    /*spot 4 print 4      */ {1, 0, 1, 1, 0, 0, 1},
    /*spot 5 print 5      */ {1, 1, 0, 1, 1, 0, 1},
    /*spot 6 print 6      */ {1, 1, 0, 1, 1, 1, 1},
    /*spot 7 print 7      */ {0, 1, 1, 1, 0, 0, 0},
    /*spot 8 print 8      */ {1, 1, 1, 1, 1, 1, 1},
    /*spot 9 print 9      */ {1, 1, 1, 1, 1, 0, 1},
    /*spot 10 print blank */ {0, 0, 0, 0, 0, 0, 0},
    /*spot 11 print ---   */ {0, 1, 0, 0, 1, 0, 1},
    /*spot 12 print A     */ {1, 1, 1, 1, 0, 1, 1},
    /*spot 13 print b     */ {1, 0, 0, 1, 1, 1, 1},
    /*spot 14 print c     */ {0, 0, 0, 0, 1, 1, 1},
    /*spot 15 print d     */ {0, 0, 1, 1, 1, 1, 1},
    /*spot 16 print E     */ {1, 1, 0, 0, 1, 1, 1},
    /*spot 17 print F     */ {1, 1, 0, 0, 0, 1, 1},
    /*spot 18 print g     */ {1, 1, 1, 1, 1, 0, 1},
    /*spot 19 print H     */ {1, 0, 1, 1, 0, 1, 1},
    /*spot 20 print i     */ {1, 0, 0, 0, 0, 1, 0},
    /*spot 21 print j     */ {0, 0, 1, 1, 1, 0, 0},
    /*spot 22 print k     */ {1, 0, 0, 0, 0, 1, 1},
    /*spot 23 print L     */ {1, 0, 0, 0, 1, 1, 0},
    /*spot 24 print m     */ {0, 1, 0, 1, 0, 1, 1},
    /*spot 25 print n     */ {0, 0, 0, 1, 0, 1, 1},
    /*spot 26 print o     */ {0, 0, 0, 1, 1, 1, 1},
    /*spot 27 print P     */ {1, 1, 1, 0, 0, 1, 1},
    /*spot 28 print q     */ {1, 1, 1, 1, 0, 0, 1},
    /*spot 29 print r     */ {0, 0, 0, 0, 0, 1, 1},
    /*spot 30 print s     */ {1, 1, 0, 1, 1, 0, 1},
    /*spot 31 print t     */ {1, 0, 0, 0, 1, 1, 1},
    /*spot 32 print U     */ {1, 0, 1, 1, 1, 1, 0},
    /*spot 33 print v     */ {1, 0, 1, 0, 0, 0, 1},
    /*spot 34 print w     */ {0, 1, 0, 1, 1, 1, 0},
    /*spot 35 print x     */ {1, 0, 1, 1, 0, 1, 1},
    /*spot 36 print y     */ {1, 0, 1, 1, 1, 0, 1},
    /*spot 37 print z     */ {0, 1, 1, 0, 1, 1, 1},
};

void setDigit(int digitNum, int displayNum) {
    switch (digitNum) {
    case 0:
    case 2:
        for (int i = digitOffset[digitNum]; i < digitOffset[digitNum + 1]; i++) {
            activeLedState[i] = displayNum == 1 ? true : false;
        };
        break;
    case 1:
    case 3:
    case 4:
        for (int i = digitOffset[digitNum], j = 0; i < digitOffset[digitNum + 1]; i += 2, j++) {
            activeLedState[i] = numberMap[displayNum][j];
            activeLedState[i + 1] = numberMap[displayNum][j];
        };
        break;
    default:
        for (int i = digitOffset[digitNum], j = 0; i < digitOffset[digitNum + 1]; i++, j++) {
            activeLedState[i] = numberMap[displayNum][j];
        };
        break;
    }
}

void setDisplay1(int num1, int num2, int num3, int num4, int num5) {
    setDigit(0, num1);
    setDigit(1, num2);
    setDigit(2, num3);
    setDigit(3, num4);
    setDigit(4, num5);
}
void setDisplay2(int num1, int num2) {
    setDigit(5, num1);
    setDigit(6, num2);
}
void setDisplay3(int num1, int num2) {
    setDigit(7, num1);
    setDigit(8, num2);
}
