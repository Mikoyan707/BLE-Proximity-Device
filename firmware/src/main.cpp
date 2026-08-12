#include <Arduino.h>

#include "config.h"
#include "ble_proximity.h"
#include "proximity.h"
#include "output.h"

void setup()
{
    Serial.begin(115200);

    delay(500);

    Serial.println();
    Serial.println("========================================");
    Serial.println(" ESP32-C3 BLE PROXIMITY DEVICE");
    Serial.println("========================================");

    // Hardware output initialization
    outputInit();

    // Proximity algorithm initialization
    proximityInit();

    // BLE advertising + scanning
    bleProximityInit();

    Serial.println("[SYSTEM] Initialization complete.");
    Serial.println("[SYSTEM] Waiting for another proximity device...");
}

void loop()
{
    unsigned long now = millis();

    // Evaluate the latest RSSI measurement.
    updateProximity(now);

    // Periodic diagnostic information.
    static unsigned long lastStatus = 0;

    if (now - lastStatus >= 1000)
    {
        lastStatus = now;

        if (isPeerPresent())
        {
            Serial.printf(
                "[STATUS] Peer detected | RSSI: %d dBm | State: %s\n",
                getFilteredRSSI(),
                getProximityState() == ProximityState::NEAR
                    ? "NEAR"
                    : "FAR"
            );
        }
        else
        {
            Serial.println(
                "[STATUS] No proximity device detected | State: FAR"
            );
        }
    }

    delay(10);
}
