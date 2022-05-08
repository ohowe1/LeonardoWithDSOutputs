#include <Arduino.h>
#include "Joystick.h"

Joystick_ joystick;

uint8_t data[4];
int previousStates[6];

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    for (int i = 2; i < 8; ++i) {
        pinMode(i, INPUT_PULLUP);
        previousStates[i - 2] = 0;
    }

    joystick.begin();
    DynamicHID().prepareOutput(data, sizeof(data));
}

void loop() {
    int availableData = DynamicHID().available();
    if (availableData > 0) {
        for (int i = 0; i < availableData; i++) {
            Serial.println(DynamicHID().read());
        }
    }

    for (int i = 2; i < 8; ++i) {
        int readValue = digitalRead(i);
        if (readValue != previousStates[i - 2]) {
            previousStates[i - 2] = readValue;
            joystick.setButton(i - 2, readValue);
        }
    }
}