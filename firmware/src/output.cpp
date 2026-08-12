#include <Arduino.h>
#include "config.h"
#include "output.h"

static bool proximityOutput = false;

void outputInit()
{
    pinMode(LED_PIN, OUTPUT);

    // LED initially OFF
    digitalWrite(LED_PIN, LOW);

    proximityOutput = false;
}

void setProximityOutput(bool near)
{
    proximityOutput = near;

    if (near)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
}

bool getProximityOutput()
{
    return proximityOutput;
}
