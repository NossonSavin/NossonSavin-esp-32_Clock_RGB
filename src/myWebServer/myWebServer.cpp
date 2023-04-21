#include "myWebServer/myWebServer.h"
#include "json.h"
#include "wifiDebug.h"

AsyncWebServer server(80);
AsyncWebSocket webSocketData("/data");

String argName;
String argValue1;
String argValue2;

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";
const char *PARAM_INPUT_3 = "state2";

//===Send States======================================================================================
void sendStates(AsyncWebServerRequest *request) {
    Json::start();

    Json::push("animationNum", animationNum, 2, false);
    Json::push("colors", colors, 5, false);
    Json::push("animationSpeed", animationSpeed, 2, false);
    Json::push("animationDelay", animationDelay, 2, false);
    Json::push("colorPicker0", colorPicker[0], 2, false);
    Json::push("colorPicker1", colorPicker[1], 2, false);

    Json::startArray("toggle");
    Json::push(forwardAndBack, 2, false);
    Json::push(isReverse, 2, false);
    Json::push(isVertical, 2, false);
    Json::endArray();

    request->send(200, "text/json", Json::end());
}

//===Update Data======================================================================================

void updateData(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "OK");
    statusLedOn();

    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
        argName = request->getParam(PARAM_INPUT_1)->value();
        argValue1 = request->getParam(PARAM_INPUT_2)->value();
        wifiPrint(argName + " " + argValue1);

        if (request->hasParam(PARAM_INPUT_3)) {
            argValue2 = request->getParam(PARAM_INPUT_3)->value();
            wifiPrint(argValue2);

            if (argName == "animation") {
                animationNum[argValue1.toInt()] = argValue2.toInt();
                setAnimationFunc();
            }

            else if (argName == "animationDelay") {
                animationDelay[argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "animationSpeed") {
                setAnimationSpeed[argValue1.toInt()] = argValue2.toInt();
                animationSpeed[argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "Back and Forth") {
                forwardAndBack[argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "Revers") {
                isReverse[argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "Vertical") {
                isVertical[argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "wifi") {
                saveWifi(argValue1, argValue2);
            }

            else if (argName == "setColor") {
                colors[argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "time") {
                long arg1 = argValue1.toInt();
                long arg2 = argValue2.toInt();
                int hour = arg1 / 10000;
                int min = (arg1 / 100) % 100;
                int sec = (arg1 % 100) + 2; // pluse 2 for latency
                int month = arg2 / 1000000;
                int day = (arg2 / 10000) % 100;
                int year = arg2 % 10000;
                rtc.setTime(sec, min, hour, day, month, year);
                wifiPrint(rtc.getTimeDate(true));
            }

            else if (argName == "colorPicker0") {
                colorPicker[0][argValue1.toInt()] = argValue2.toInt();
            }

            else if (argName == "colorPicker1") {
                colorPicker[1][argValue1.toInt()] = argValue2.toInt();
            }

        } else {

            if (argName == "display") {
                display = displayArray[argValue1.toInt()];
            }

            else if (argName == "btn") {
                if (argValue1 == "save") {
                    saveSettings();
                }

                else if (argValue1 == "load") {
                    loadSettings();
                }

                else if (argValue1 == "default") {
                    defaultSettings();
                }

                else if (argValue1 == "reset") {
                    ESP.restart();
                }

                else if (argValue1 == "accessPoint") {
                    toggleAccessPoint();
                }

                else if (argValue1 == "getIP") {
                    wifiPrint(WiFi.localIP().toString());
                }

                else if (argValue1 == "wifi") {
                    wifiPrint("SSID:" + wifiName + " => Password:" + wifiPW);
                }

                else if (argValue1 == "getTemp") {
                    wifiPrint(OutsideTemperature);
                }
            }
        }
    }

    delay(200); // for led
    statusLedOff();
}

void sendWifiNetworks(AsyncWebServerRequest *request) {
    int n = WiFi.scanComplete();

    if (n == -2) {
        WiFi.scanNetworks(true);
    } else if (n) {
        Json::start();
        Json::startArray("networks");
        for (int i = 0; i < n; ++i) {
            Json::push(WiFi.SSID(i));
        }
        Json::endArray();

        WiFi.scanDelete();
        if (WiFi.scanComplete() == -2) {
            WiFi.scanNetworks(true);
        }
        request->send(200, "application/json", Json::end());
    }
    request->send(204, "plain/text", "failed");
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        webSocketData.textAll(debugMsg);
        clearWifiPrint();
    }
}

void startServer() {
    LittleFS.begin();

    webSocketData.onEvent(onWsEvent);
    server.addHandler(&webSocketData);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*"); // enable CORS

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(LittleFS, "/index.html", "text/html"); });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(LittleFS, "/script.js", "text/javascript"); });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(LittleFS, "/style.css", "text/css"); });
    server.on("/icon.png", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(LittleFS, "/icon.png", "image/png"); });

    server.on("/updateData", HTTP_GET, updateData);
    server.on("/getState", HTTP_GET, sendStates);
    server.on("/debugMsg", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(200, "text/plain", debugMsg); });
    server.on("/wifiNetworks", HTTP_GET, sendWifiNetworks);

    server.begin();
}
