#include <Arduino.h>
#include <math.h>

#include "config.h"
#include "proximity.h"
#include "output.h"

static ProximityState currentState = ProximityState::FAR;

static float filteredRSSI = -100.0f;
static bool filterInitialized = false;

static int latestRSSI = -100;
static unsigned long lastPeerSeen = 0;

void proximityInit()
{
    currentState = ProximityState::FAR;

    filteredRSSI = -100.0f;
    latestRSSI = -100;

    filterInitialized = false;
    lastPeerSeen = 0;

    setProximityOutput(false);
}

void updateRSSI(int rssi)
{
    latestRSSI = rssi;
    lastPeerSeen = millis();

    if (!filterInitialized)
    {
        filteredRSSI = static_cast<float>(rssi);
        filterInitialized = true;
        return;
    }

    // Exponential Moving Average
    filteredRSSI =
        (RSSI_FILTER_ALPHA * static_cast<float>(rssi)) +
        ((1.0f - RSSI_FILTER_ALPHA) * filteredRSSI);
}

void updateProximity(unsigned long now)
{
    // No valid RSSI received yet
    if (!filterInitialized)
    {
        if (currentState != ProximityState::FAR)
        {
            currentState = ProximityState::FAR;
            setProximityOutput(false);
        }

        return;
    }

    // If the partner has disappeared for too long,
    // force the system into FAR state.
    if ((now - lastPeerSeen) > PEER_TIMEOUT_MS)
    {
        if (currentState != ProximityState::FAR)
        {
            currentState = ProximityState::FAR;
            setProximityOutput(false);

            Serial.println("[PROXIMITY] Peer timeout -> FAR");
        }

        return;
    }

    // Hysteresis
    if (currentState == ProximityState::FAR)
    {
        if (filteredRSSI >= RSSI_NEAR_THRESHOLD)
        {
            currentState = ProximityState::NEAR;
            setProximityOutput(true);

            Serial.printf(
                "[PROXIMITY] NEAR | Filtered RSSI: %.1f dBm\n",
                filteredRSSI
            );
        }
    }
    else
    {
        if (filteredRSSI <= RSSI_FAR_THRESHOLD)
        {
            currentState = ProximityState::FAR;
            setProximityOutput(false);

            Serial.printf(
                "[PROXIMITY] FAR | Filtered RSSI: %.1f dBm\n",
                filteredRSSI
            );
        }
    }
}

ProximityState getProximityState()
{
    return currentState;
}

int getFilteredRSSI()
{
    return static_cast<int>(round(filteredRSSI));
}

bool isPeerPresent()
{
    if (!filterInitialized)
    {
        return false;
    }

    return (millis() - lastPeerSeen) <= PEER_TIMEOUT_MS;
}
