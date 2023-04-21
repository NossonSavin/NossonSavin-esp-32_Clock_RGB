#pragma once
#include "./animation/animation.h"
#include "./myWifi/myWifi.h"
#include <Preferences.h>

void defaultSettings();
void saveSettings();
void loadSettings();
void saveWifi(String name, String password);