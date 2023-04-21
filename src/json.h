#pragma once
#include <Arduino.h>

namespace Json {
String data;

template <typename T>
void addKey(T key) {
    data += "\"";
    data += key;
    data += "\":";
}

template <typename T>
void addPair(T pair, bool isString) {
    data += isString ? "\"" : "";
    data += pair;
    data += isString ? "\"," : ",";
}

void start() {
    data = "{";
}

String end() {
    data.remove(data.length() - 1, 1);
    data += "}";

    return data;
}

template <typename T, typename U>
void push(T key, U pair, bool isString = true) {
    addKey(key);
    addPair(pair, isString);
}

template <typename T, typename U>
void push(T key, U array[], int arraySize, bool isString = true) {
    addKey(key);
    data += "[";

    for (int i = 0; i < arraySize; i++) {
        addPair(array[i], isString);
    }
    data.remove(data.length() - 1, 1);
    data += "],";
}

template <typename U>
void push(U array[], int arraySize, bool isString = true) {
    data += "[";

    for (int i = 0; i < arraySize; i++) {
        addPair(array[i], isString);
    }
    data.remove(data.length() - 1, 1);
    data += "],";
}

template <typename T>
void startArray(T key) {
    addKey(key);
    data += "[";
}

void endArray() {
    data.remove(data.length() - 1, 1);
    data += "],";
}

template <typename T>
void startObj(T key) {
    addKey(key);
    data += "{";
}

void startObj() {
    data += "{";
}

void endObj() {
    data.remove(data.length() - 1, 1);
    data += "},";
}

template <typename T>
void push(T pair, bool isString = true) {
    addPair(pair, isString);
}
}; // namespace Json