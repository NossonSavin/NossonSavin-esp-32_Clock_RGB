#include "settings.h"

Preferences preference;

void defaultSettings() {
    animationNum[0] = 1;
    animationNum[1] = 0;
    colors[0] = 2565;
    colors[1] = 65536;
    colors[2] = 3080225;
    colors[3] = 657928;
    colors[4] = 5575947;
    animationDelay[0] = 2000;
    animationDelay[1] = 2000;
    forwardAndBack[0] = false;
    forwardAndBack[1] = false;
    isReverse[0] = false;
    isReverse[1] = false;
    isVertical[0] = true;
    isVertical[1] = true;
    colorPicker[0][0] = 0;
    colorPicker[0][1] = 1;
    colorPicker[1][0] = 0;
    colorPicker[1][1] = 4;
    setAnimationFunc();
}

void saveSettings() {
    preference.begin("settings", false);

    for (size_t i = 0; i < 2; i++) {
        preference.putInt("animationNum" + i, animationNum[i]);
        preference.putInt("animationSpeed" + i, animationSpeed[i]);
        preference.putInt("animationDelay" + i, animationDelay[i]);
        preference.putInt("forwardAndBack" + i, forwardAndBack[i]);
        preference.putInt("isReverse" + i, isReverse[i]);
        preference.putInt("isVertical" + i, isVertical[i]);
        preference.putInt("colorPicker0" + i, colorPicker[0][i]);
        preference.putInt("colorPicker1" + i, colorPicker[1][i]);
    }

    for (int i = 0; i < 5; i++) {
        preference.putInt("color" + i, colors[i]);
    }

    preference.end();
}

void loadSettings() {
    preference.begin("settings", false);

    for (size_t i = 0; i < 2; i++) {
        animationNum[i] = preference.getInt("animationNum" + i);
        animationSpeed[i] = preference.getInt("animationSpeed" + i);
        animationDelay[i] = preference.getInt("animationDelay" + i);
        forwardAndBack[i] = preference.getInt("forwardAndBack" + i);
        isReverse[i] = preference.getInt("isReverse" + i);
        isVertical[i] = preference.getInt("isVertical" + i);

        colorPicker[0][i] = preference.getInt("colorPicker0" + i);
        colorPicker[1][i] = preference.getInt("colorPicker1" + i);
    }
    setAnimationFunc();

    for (int i = 0; i < 5; i++) {
        colors[i] = preference.getInt("color" + i);
    }

    wifiName = preference.getString("wifiName");
    wifiPW = preference.getString("wifiPW");

    preference.end();
}

void saveWifi(String name, String password) {
    preference.begin("settings", false);

    preference.putString("wifiName", name);
    preference.putString("wifiPW", password);

    preference.end();
    wifiName = name;
    wifiPW = password;

    WiFi.disconnect();
    delay(500);
    startWifi();
    // ESP.restart();
}