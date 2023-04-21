#include "myWifi.h"

String wifiName = "<ssid>";
String wifiPW = "<pw>";

void WiFiConnect() {
    WiFi.begin(wifiName.c_str(), wifiPW.c_str());
}

void WiFiReconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    WiFiConnect();
}

void startWifi() {
    WiFi.mode(WIFI_STA);
    WiFiConnect();
    MDNS.begin("esp"); // for esp.local in browser
    WiFi.onEvent(WiFiReconnect, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
}