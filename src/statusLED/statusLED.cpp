#include "statusLED.h"

const int ledPin = 27;

void setupStatusLED() {
    pinMode(ledPin, OUTPUT);
}

void statusLedOn() {
    digitalWrite(ledPin, HIGH);
}

void statusLedOff() {
    digitalWrite(ledPin, LOW);
}

void statusLedToggle() {
    digitalWrite(ledPin, !digitalRead(ledPin));
}