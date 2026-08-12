#ifndef PROXIMITY_H
#define PROXIMITY_H

enum class ProximityState
{
    FAR,
    NEAR
};

void proximityInit();

void updateRSSI(int rssi);

void updateProximity(unsigned long now);

ProximityState getProximityState();

int getFilteredRSSI();

bool isPeerPresent();

#endif
