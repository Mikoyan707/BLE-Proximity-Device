#include <Arduino.h>
#include "config.h"

void setup()
{
    // Start serial communication for debugging
    Serial.begin(115200);

    // Give the serial interface a moment to initialize
    delay(500);

    Serial.println();
    Serial.println("=================================");
    Serial.println("ESP32-C3 BLE Proximity Device");
    Serial.println("Hardware Test Firmware");
    Serial.println("=================================");

    // GPIO2 controls the LED transistor
    pinMode(LED_PIN, OUTPUT);

    // GPIO9 has an external 10 kΩ pull-up.
    // SW2 pulls it LOW when pressed.
    pinMode(BUTTON_PIN, INPUT);

    // Start with LED OFF
    digitalWrite(LED_PIN, LOW);

    Serial.println("Hardware initialized.");
    Serial.println("Press SW2 to turn the LED ON.");
}

void loop()
{
    // Read SW2
    bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

    if (buttonPressed)
    {
        digitalWrite(LED_PIN, HIGH);

        Serial.println("SW2 PRESSED -> LED ON");

        // Small delay to avoid flooding Serial
        delay(100);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);

        Serial.println("SW2 RELEASED -> LED OFF");

        delay(100);
    }
}
